#pragma once

/*
	카트리지에 해당하는 메모리로 변환
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

