#pragma once

#include "Mapper.h"

class Mapper_000 : public Mapper
{
public:
	Mapper_000(uint8_t ProgramBanks, uint8_t PatternBanks);

	// Mapper을(를) 통해 상속됨
	virtual bool CpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress) override;
	virtual bool CpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress) override;
	virtual bool PpuMapRead(uint16_t Address, uint32_t& OUT MappedAddress) override;
	virtual bool PpuMapWrite(uint16_t Address, uint32_t& OUT MappedAddress) override;

	virtual void Reset() override;
};

