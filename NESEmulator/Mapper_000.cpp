#include "Precompile.h"
#include "Mapper_000.h"

Mapper_000::Mapper_000(uint8_t ProgramBanks, uint8_t PatternBanks)
	:Mapper(ProgramBanks, PatternBanks)
{
}

bool Mapper_000::CpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress)
{
	// if PRGROM is 16KB
	//     CPU Address Bus          PRG ROM
	//     0x8000 -> 0xBFFF: Map    0x0000 -> 0x3FFF
	//     0xC000 -> 0xFFFF: Mirror 0x0000 -> 0x3FFF
	// if PRGROM is 32KB
	//     CPU Address Bus          PRG ROM
	//     0x8000 -> 0xFFFF: Map    0x0000 -> 0x7FFF	
	if (Address >= 0x8000 && Address <= 0xFFFF)
	{
		MappedAddress = Address & (ProgramBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}

	return false;
}

bool Mapper_000::CpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress)
{
	if (Address >= 0x8000 && Address <= 0xFFFF)
	{
		MappedAddress = Address & (ProgramBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}

	return false;
}

bool Mapper_000::PpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress)
{
	// There is no mapping required for PPU
	// PPU Address Bus          CHR ROM
	// 0x0000 -> 0x1FFF: Map    0x0000 -> 0x1FFF
	if (Address >= 0x0000 && Address <= 0x1FFF)
	{
		MappedAddress = Address;
		return true;
	}

	return false;
}

bool Mapper_000::PpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress)
{
	if (Address >= 0x0000 && Address <= 0x1FFF)
	{
		if (PatternBanks == 0)
		{
			// Treat as RAM
			MappedAddress = Address;
			return true;
		}
	}

	return false;
}

void Mapper_000::Reset()
{
}
