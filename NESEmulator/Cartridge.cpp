#include "Precompile.h"
#include "Cartridge.h"
#include "Mapper_000.h"

Cartridge::Cartridge(const std::string& FileName)
{
	// iNES Format Header
	struct Header
	{
		char name[4];
		uint8_t ProgramRomChunks;
		uint8_t PatternRomChunks;
		uint8_t Mapper1;
		uint8_t Mapper2;
		uint8_t ProgramRamSize;
		uint8_t TvSystem1;
		uint8_t TvSystem2;
		char unused[5];
	};

	ImageValid = false;

	Header header;

	std::ifstream ifstream;
	ifstream.open(FileName, std::ifstream::binary);
	if (ifstream.is_open())
	{
		ifstream.read(reinterpret_cast<char*>(&header),
			sizeof(struct Header));

		if (header.Mapper1 & 0x04)
			ifstream.seekg(512, std::ios_base::cur);

		// Mapper ID 정의
		MapperID = ((header.Mapper2 >> 4) << 4) | (header.Mapper1 >> 4);
		mirror = (header.Mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		// 파일 포맷타입
		uint8_t FileType = 1;

		switch (FileType)
		{
		case 0:
			break;
		case 1:
			ProgramBanks = header.ProgramRomChunks;
			ProgramMemory.resize(static_cast<std::size_t>(ProgramBanks * 16384));
			ifstream.read(reinterpret_cast<char*>(ProgramMemory.data()), ProgramMemory.size());

			PatternBanks = header.PatternRomChunks;
			PatternMemory.resize(static_cast<std::size_t>(PatternBanks * 8192));
			ifstream.read(reinterpret_cast<char*>(PatternMemory.data()), PatternMemory.size());
			break;
		case 2:
			break;
		}

		switch (MapperID)
		{
		case 0:
			Mapper = std::make_shared<Mapper_000>(ProgramBanks, PatternBanks);
			break;
		}

		ImageValid = true;
		ifstream.close();
	}

}

bool Cartridge::CpuWrite(uint16_t AddressPosition, uint8_t Data)
{
	uint32_t MappedAddr = 0;

	if (Mapper->CpuMapWrite(AddressPosition, MappedAddr))
	{
		ProgramMemory[MappedAddr] = Data;

		return true;
	}

	return false;
}

bool Cartridge::CpuRead(uint16_t AddressPosition, uint8_t& Data)
{
	uint32_t MappedAddr = 0;

	if (Mapper->CpuMapRead(AddressPosition, MappedAddr))
	{
		Data = ProgramMemory[MappedAddr];

		return true;
	}

	return false;
}

bool Cartridge::PpuWrite(uint16_t AddressPosition, uint8_t Data)
{
	uint32_t MappedAddr = 0;

	if (Mapper->PpuMapWrite(AddressPosition, MappedAddr))
	{
		PatternMemory[MappedAddr] = Data;

		return true;
	}

	return false;
}

bool Cartridge::PpuRead(uint16_t AddressPosition, uint8_t& Data)
{
	uint32_t MappedAddr = 0;

	if (Mapper->PpuMapRead(AddressPosition, MappedAddr))
	{
		Data = PatternMemory[MappedAddr];

		return true;
	}

	return false;
}

bool Cartridge::isImageValid()
{
	return ImageValid;
}

void Cartridge::Reset()
{

	if (Mapper != nullptr)
		Mapper->Reset();
}
