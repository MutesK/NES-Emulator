#pragma once


class Mapper;
class Cartridge
{
	std::vector<uint8_t> ProgramMemory;
	std::vector<uint8_t> PatternMemory;

	uint8_t MapperID;
	uint8_t ProgramBanks = 0;  // 프로그램 뱅크(명령어)는 게임마다 다다름
	uint8_t PatternBanks = 0;  // 패턴 뱅크(스프라이트)는 게임마다 다다름

	std::shared_ptr<Mapper> Mapper;
	bool ImageValid = false;
public:
	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

	Cartridge(const std::string& FileName);

	// Cpu 버스 통한 커뮤니 케이션
	bool CpuWrite(uint16_t AddressPosition, uint8_t Data);
	bool CpuRead(uint16_t AddressPosition, uint8_t& Data);

	// PPU Bus 통해 커뮤니케이션
	bool PpuWrite(uint16_t AddressPosition, uint8_t Data);
	bool PpuRead(uint16_t AddressPosition, uint8_t& Data);

	bool isImageValid();
	void Reset();
};

