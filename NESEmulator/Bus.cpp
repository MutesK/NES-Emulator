
#include "Precompile.h"
#include "Bus.hpp"
#include "Processor.hpp"
#include "PictureProcessor.h"
#include "Cartridge.h"


/*
	CPU Memory 맵

	$0000-$07FF	$0800	2KB internal RAM
	$0800-$0FFF	$0800	Mirrors of $0000-$07FF
	$1000-$17FF	$0800
	$1800-$1FFF	$0800
	$2000-$2007	$0008	NES PPU registers
	$2008-$3FFF	$1FF8	Mirrors of $2000-2007 (repeats every 8 bytes)
	$4000-$4017	$0018	NES APU and I/O registers
	$4018-$401F	$0008	APU and I/O functionality that is normally disabled. See CPU Test Mode.
	$4020-$FFFF	$BFE0	Cartridge space: PRG ROM, PRG RAM, and mapper registers (See Note)
*/
Bus::Bus()
{
	Cpu = std::make_shared<Processor>();
	Ppu = std::make_shared<PictureProcessor>();

	Cpu->ConnectBus(this);
	for (auto& i : Ram) i = 0x00;
}


RamStorage& Bus::GetRam()
{
	return Ram;
}

ProcessorPtr& Bus::GetProcessor()
{
	return Cpu;
}

PictureProcessorPtr& Bus::GetPictureProcessor()
{
	return Ppu;
}

uint8_t& Bus::GetController(int index)
{
	return Controller[index];
}


void Bus::CpuWrite(uint16_t AddressPosition, uint8_t Data)
{
	if (cartridge->CpuWrite(AddressPosition, Data))
	{

	}
	else if (AddressPosition >= 0x0000 && AddressPosition <= 0x1FFF) // 램 또는 미러링(0000-07FF)
	{
		Ram[AddressPosition & 0x07FF] = Data;
	}
	else if (AddressPosition >= 0x2000 && AddressPosition <= 0x3FFF)  // PPU 주소 대역 또는 미러링($2000-2007)
	{
		Ppu->CpuWrite(AddressPosition & 0x0007, Data);
	}
	else if (AddressPosition == 0x4014)
	{
		DMAPage = Data;
		DMAAddress = 0;
		DMATransfer = true;
	}
	else if (AddressPosition >= 0x4016 && AddressPosition <= 0x4017)
	{
		ControllerState[AddressPosition & 0x0001] = Controller[AddressPosition & 0x0001];
	}
}

uint8_t Bus::CpuRead(uint16_t AddressPosition, bool ReadOnly)
{
	uint8_t data = 0x00;

	if (cartridge->CpuRead(AddressPosition, data))
	{

	}
	else if (AddressPosition >= 0x0000 && AddressPosition <= 0x1FFF)
	{
		return Ram[AddressPosition & 0x07FF];
	}
	else if (AddressPosition >= 0x2000 && AddressPosition <= 0x3FFF)
	{
		data = Ppu->CpuRead(AddressPosition & 0x0007, ReadOnly);
	}
	else if (AddressPosition >= 0x4016 && AddressPosition <= 0x4017)
	{
		data = (ControllerState[AddressPosition & 0x0001] & 0x80) > 0;
		ControllerState[AddressPosition & 0x0001] <<= 1;
	}

	return data;
}

void Bus::InsertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cartridge = cartridge;

	Ppu->ConnectCartridge(cartridge);
}

void Bus::Reset()
{
	cartridge->Reset();
	Cpu->ResetInterrupt();
	Ppu->Reset();
	SystemClockCounter = 0;
}

void Bus::Clock()
{
	Ppu->Clock();

	if (SystemClockCounter % 3 == 0)
	{
		if (DMATransfer)  // DMA 는 Cpu와 동기화를 위해 Clock를 하지않게 한다.
		{
			if (DMADummy)
			{
				if (SystemClockCounter % 2 == 1)
				{
					DMADummy = false;
				}
			}
			else
			{
				if (SystemClockCounter % 2 == 0)
				{
					DMAData = CpuRead(DMAPage << 8 | DMAAddress);
				}
				else
				{
					Ppu->GetOAMPointer()[DMAAddress] = DMAData;
					DMAAddress++;

					if (DMAAddress == 0x00)
					{
						DMATransfer = false;
						DMADummy = true;
					}
				}
			}
		}
		else
		{
			Cpu->Clock();
		}
	}

	if (Ppu->NMI)
	{
		Ppu->NMI = false;
		Cpu->NonMaskableInterruptRequest();
	}

	SystemClockCounter++;
}
