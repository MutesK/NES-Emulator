#pragma once


class Mapper;
class Cartridge
{
	std::vector<uint8_t> ProgramMemory;
	std::vector<uint8_t> PatternMemory;

	uint8_t MapperID;
	uint8_t ProgramBanks = 0;  // ���α׷� ��ũ(��ɾ�)�� ���Ӹ��� �ٴٸ�
	uint8_t PatternBanks = 0;  // ���� ��ũ(��������Ʈ)�� ���Ӹ��� �ٴٸ�

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

	// Cpu ���� ���� Ŀ�´� ���̼�
	bool CpuWrite(uint16_t AddressPosition, uint8_t Data);
	bool CpuRead(uint16_t AddressPosition, uint8_t& Data);

	// PPU Bus ���� Ŀ�´����̼�
	bool PpuWrite(uint16_t AddressPosition, uint8_t Data);
	bool PpuRead(uint16_t AddressPosition, uint8_t& Data);

	bool isImageValid();
	void Reset();
};

