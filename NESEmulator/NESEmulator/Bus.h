#pragma once

#include <cstdint>
#include <array>
#include "Cpu.h"

static const size_t RAMSIZE = 64 * 1024;

class Bus final
{
private:
	Cpu _cpu;
	std::array<uint8_t, RAMSIZE> _ram;
public:
	Bus();
	~Bus() = default;
public:
	void write(const uint16_t destaddr,const uint8_t data);
	uint8_t read(const uint16_t destaddr, const bool readOnly);
};

