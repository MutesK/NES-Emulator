#include "Bus.h"

Bus::Bus()
{
	_cpu.connectBus(this);

	for(auto& bit : _ram)
	{
		bit = 0x00;
	}
}

void Bus::write(const uint16_t destaddr, const uint8_t data)
{
	if (destaddr >= 0x0000 && destaddr <= 0xFFFF)
		_ram[destaddr] = data;
}

uint8_t Bus::read(const uint16_t destaddr, const bool readOnly)
{
	if (destaddr >= 0x0000 && destaddr <= 0xFFFF)
		return _ram[destaddr];

	return 0x0000;
}
