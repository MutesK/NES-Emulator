#pragma once

/*
	īƮ������ �ش��ϴ� �޸𸮷� ��ȯ
*/

class Mapper
{
protected:
	uint8_t ProgramBanks;
	uint8_t PatternBanks;
public:
	Mapper(uint8_t ProgramBanks, uint8_t PatternBanks);

	virtual bool CpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress) = 0;
	virtual bool CpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress) = 0;

	virtual bool PpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress) = 0;
	virtual bool PpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress) = 0;

	virtual void Reset() = 0;
};

