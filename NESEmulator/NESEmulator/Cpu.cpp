#include "Cpu.h"
#include "Bus.h"

Cpu::Cpu()
{
	// Cpu Member Function Init To _lookup
	_lookup =
	{
		{ "BRK", &Cpu::BRK, &Cpu::IMM, 7 },{ "ORA", &Cpu::ORA, &Cpu::IZX, 6 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::ZP0, 3 },
		{ "ASL", &Cpu::ASL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "PHP", &Cpu::PHP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::IMM, 2 },
		{ "ASL", &Cpu::ASL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABS, 4 },
		{ "ASL", &Cpu::ASL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BPL", &Cpu::BPL, &Cpu::REL, 2 },{ "ORA", &Cpu::ORA, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ZPX, 4 },
		{ "ASL", &Cpu::ASL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "CLC", &Cpu::CLC, &Cpu::IMP, 2 },{ "ORA", &Cpu::ORA, &Cpu::ABY, 4 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABX, 4 },
		{ "ASL", &Cpu::ASL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "JSR", &Cpu::JSR, &Cpu::ABS, 6 },{ "AND", &Cpu::AND, &Cpu::IZX, 6 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "BIT", &Cpu::BIT, &Cpu::ZP0, 3 },{ "AND", &Cpu::AND, &Cpu::ZP0, 3 },
		{ "ROL", &Cpu::ROL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "PLP", &Cpu::PLP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::IMM, 2 },
		{ "ROL", &Cpu::ROL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "BIT", &Cpu::BIT, &Cpu::ABS, 4 },{ "AND", &Cpu::AND, &Cpu::ABS, 4 },
		{ "ROL", &Cpu::ROL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BMI", &Cpu::BMI, &Cpu::REL, 2 },{ "AND", &Cpu::AND, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ZPX, 4 },
		{ "ROL", &Cpu::ROL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "SEC", &Cpu::SEC, &Cpu::IMP, 2 },{ "AND", &Cpu::AND, &Cpu::ABY, 4 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ABX, 4 },
		{ "ROL", &Cpu::ROL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "RTI", &Cpu::RTI, &Cpu::IMP, 6 },{ "EOR", &Cpu::EOR, &Cpu::IZX, 6 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::ZP0, 3 },
		{ "LSR", &Cpu::LSR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "PHA", &Cpu::PHA, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::IMM, 2 },
		{ "LSR", &Cpu::LSR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "JMP", &Cpu::JMP, &Cpu::ABS, 3 },{ "EOR", &Cpu::EOR, &Cpu::ABS, 4 },
		{ "LSR", &Cpu::LSR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BVC", &Cpu::BVC, &Cpu::REL, 2 },{ "EOR", &Cpu::EOR, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ZPX, 4 },
		{ "LSR", &Cpu::LSR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "CLI", &Cpu::CLI, &Cpu::IMP, 2 },{ "EOR", &Cpu::EOR, &Cpu::ABY, 4 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ABX, 4 },
		{ "LSR", &Cpu::LSR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "RTS", &Cpu::RTS, &Cpu::IMP, 6 },{ "ADC", &Cpu::ADC, &Cpu::IZX, 6 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ADC", &Cpu::ADC, &Cpu::ZP0, 3 },
		{ "ROR", &Cpu::ROR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "PLA", &Cpu::PLA, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::IMM, 2 },
		{ "ROR", &Cpu::ROR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "JMP", &Cpu::JMP, &Cpu::IND, 5 },{ "ADC", &Cpu::ADC, &Cpu::ABS, 4 },
		{ "ROR", &Cpu::ROR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BVS", &Cpu::BVS, &Cpu::REL, 2 },{ "ADC", &Cpu::ADC, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ZPX, 4 },
		{ "ROR", &Cpu::ROR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "SEI", &Cpu::SEI, &Cpu::IMP, 2 },{ "ADC", &Cpu::ADC, &Cpu::ABY, 4 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ABX, 4 },
		{ "ROR", &Cpu::ROR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::IZX, 6 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "STY", &Cpu::STY, &Cpu::ZP0, 3 },{ "STA", &Cpu::STA, &Cpu::ZP0, 3 },
		{ "STX", &Cpu::STX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },
		{ "DEY", &Cpu::DEY, &Cpu::IMP, 2 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },
		{ "TXA", &Cpu::TXA, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "STY", &Cpu::STY, &Cpu::ABS, 4 },{ "STA", &Cpu::STA, &Cpu::ABS, 4 },
		{ "STX", &Cpu::STX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "BCC", &Cpu::BCC, &Cpu::REL, 2 },{ "STA", &Cpu::STA, &Cpu::IZY, 6 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "STY", &Cpu::STY, &Cpu::ZPX, 4 },{ "STA", &Cpu::STA, &Cpu::ZPX, 4 },
		{ "STX", &Cpu::STX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "TYA", &Cpu::TYA, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::ABY, 5 },
		{ "TXS", &Cpu::TXS, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 5 },{ "STA", &Cpu::STA, &Cpu::ABX, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "LDY", &Cpu::LDY, &Cpu::IMM, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZX, 6 },
		{ "LDX", &Cpu::LDX, &Cpu::IMM, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "LDY", &Cpu::LDY, &Cpu::ZP0, 3 },{ "LDA", &Cpu::LDA, &Cpu::ZP0, 3 },
		{ "LDX", &Cpu::LDX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },
		{ "TAY", &Cpu::TAY, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::IMM, 2 },
		{ "TAX", &Cpu::TAX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "LDY", &Cpu::LDY, &Cpu::ABS, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABS, 4 },
		{ "LDX", &Cpu::LDX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "BCS", &Cpu::BCS, &Cpu::REL, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "LDY", &Cpu::LDY, &Cpu::ZPX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ZPX, 4 },
		{ "LDX", &Cpu::LDX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "CLV", &Cpu::CLV, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::ABY, 4 },
		{ "TSX", &Cpu::TSX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "LDY", &Cpu::LDY, &Cpu::ABX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABX, 4 },
		{ "LDX", &Cpu::LDX, &Cpu::ABY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "CPY", &Cpu::CPY, &Cpu::IMM, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZX, 6 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "CPY", &Cpu::CPY, &Cpu::ZP0, 3 },{ "CMP", &Cpu::CMP, &Cpu::ZP0, 3 },
		{ "DEC", &Cpu::DEC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "INY", &Cpu::INY, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::IMM, 2 },
		{ "DEX", &Cpu::DEX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },
		{ "CPY", &Cpu::CPY, &Cpu::ABS, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABS, 4 },
		{ "DEC", &Cpu::DEC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BNE", &Cpu::BNE, &Cpu::REL, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ZPX, 4 },
		{ "DEC", &Cpu::DEC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "CLD", &Cpu::CLD, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::ABY, 4 },
		{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABX, 4 },
		{ "DEC", &Cpu::DEC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "CPX", &Cpu::CPX, &Cpu::IMM, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZX, 6 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "CPX", &Cpu::CPX, &Cpu::ZP0, 3 },{ "SBC", &Cpu::SBC, &Cpu::ZP0, 3 },
		{ "INC", &Cpu::INC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "INX", &Cpu::INX, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::IMM, 2 },
		{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::SBC, &Cpu::IMP, 2 },
		{ "CPX", &Cpu::CPX, &Cpu::ABS, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABS, 4 },
		{ "INC", &Cpu::INC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BEQ", &Cpu::BEQ, &Cpu::REL, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZY, 5 },
		{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ZPX, 4 },
		{ "INC", &Cpu::INC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "SED", &Cpu::SED, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::ABY, 4 },
		{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABX, 4 },
		{ "INC", &Cpu::INC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
	 };
}

//////////////////////////////////////////////////////////////////////////////////////////////
/*
	���� IO �Լ�
 */
uint8_t Cpu::read(uint16_t bytes)
{
	return _bus->read(bytes, false);
}

void Cpu::write(uint16_t addr, uint8_t bytes)
{
	_bus->write(addr, bytes);
}

//////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ܺ� �Է� �Լ�
*/
void Cpu::reset()
{
	_addr_abs = 0xFFFC;  // ���α׷� ī����
	uint16_t low = read(_addr_abs + 0);
	uint16_t high = read(_addr_abs + 1);

	_pc = (high << 8) | low;

	// �ܺ� �������� ����
	_accumulator = 0;
	_x = 0;
	_y = 0;
	_stack = 0xFD;
	_status = 0x00 | FLAG::Unused;

	// ��� ���� Ŭ����
	_addr_rel = 0x0000;
	_addr_abs = 0x0000;
	_fetched = 0x00;

	_cycles = 8;
}

// ���ͷ�Ʈ ��û�� �ƹ����� �ü� �ִ�.
// IRQ �� �߻�������, Reset�� ���� ����ϰ� �����Ѵ�. 
// Programmable Address �� �ϵ��ڵ��� �޸� �ּ� 0xFFFE�� �а�, �׵�, ���α׷� ī���͸� �����Ѵ�.
void Cpu::irq()
{
	if(getFlag(NoInterrupts) == 0)  // ���ͷ�Ʈ�� ���ȴٸ�
	{
		// ���� PC�� ���� ���ÿ� �ִ´�.
		write(0x0100 + _stack, (_pc >> 8) & 0x00FF);
		_stack--;
		write(0x1000 + _stack, _pc & 0x00FF); 
		_stack--;

		// �׸��� ���� ���̽��Ϳ� ���� ���������� ���� �ִ´�.
		setFlag(Break, false);
		setFlag(Unused, true);
		setFlag(NoInterrupts, true);
		write(0x0100 + _stack, _status);
		_stack--;

		// ���� �ּҷ� ����, ���ο� ���α׷� ī���͸� �о�´�.
		_addr_abs = 0xFFFE;
		const uint16_t low = read(_addr_abs + 0);
		const uint16_t high = read(_addr_abs + 1);
		_pc = (high << 8) | low;

		_cycles= 7;
	}
}

// Non-Masked Interrupt�� �����Ҽ� ����.
// �⺻���� IRQ�� ���� ����������, �ּ� 0xFFFA�κ���, ���ο� ���α׷� ī���� �ּ� �о� �´�.
void Cpu::nmi()
{
	write(0x1000 + _stack, (_pc >> 8) & 0x00FF);
	_stack--;
	write(0x0100 + _stack, _pc & 0x00FF);
	_stack--;

	setFlag(Break, false);
	setFlag(Unused, true);
	setFlag(NoInterrupts, true);
	write(0x0100 + _stack, _status);
	_stack--;

	_addr_abs = 0xFFFA;
	const uint16_t low = read(_addr_abs + 0);
	const uint16_t high = read(_addr_abs + 1);
	_pc = (high << 8) | low;

	_cycles = 8;

}

// CPU������ Ŭ��, Software �󿡼��� Tick���� ó�� 
void Cpu::clock()
{
	// ���� CPU������ �������� ���� ����� �̷������� ���ķ����Ϳ����� ������� ���Ѵ�.
	// �ѹ� ����Ŭ�� ��ü�� ����ϰ�, CPU ������ ����ũ���ڵ� ��ȯ�� ����.
	// ��ɾ �����Ϸ��� ���ķ����͵� �ϵ���� ȯ��� �����ϰ� ������ �ְ� �Ѵ�. = cycle ������ �̿� �ش�.

	if(!_cycles) 
	{
		// �̹� ����� �������Ƿ�, ���� ��� byte �� �����´�.
		_opcode = read(_pc);

		setFlag(Unused, true);
		_pc++;

		_cycles = _lookup[_opcode].cycles;  // �̹� ���꿡 �ʿ��� �����ð�

		// �ּ� ���
		const uint8_t additional_cycle1 = (this->*_lookup[_opcode].addrmode)();
		// �۾� 
		const uint8_t additional_cycle2 = (this->*_lookup[_opcode].operate)();

		_cycles += (additional_cycle1 & additional_cycle2);

		setFlag(Unused, true);
	}

	_clock_count++;
	_cycles--;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Flag �Լ�
 *  
 *  Status Register ����
 *  �Ʒ� flag�� Ư�� ��Ʈ ��ġ�� �������ų�, �����ϸ� �ȴ�.
 */
uint8_t Cpu::getFlag(FLAG f) const
{
	return ((_status & f) > false) ? true : false;
}

// bool ���� true���, Status Register Ư�� ��ġ Set,
// bool ���� false ���, Status Reigster Clear
void Cpu::setFlag(FLAG f, bool v)
{
	if (v)
		_status |= f;
	else
		_status &= ~f;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  �ּ� �Լ�
 *
 * 6502 CPU�� 0x0000 ~ 0xFFFF �ּҸ� ��밡���ϴ�.
 * 
 * High bytes(2)�� Page �ν� ���� ���ǰ�, Low Bytes(2)�� �ش� Page�� Offset���� ���ȴ�.
 * 256�� �������� �ִ�.
 * 
 * ������ �ּ� ���� �߰����� Ŭ�� ����Ŭ�� �ʿ��ϴ�.
 * ������ ��踦 ������ ��ȯ�ǰ�, �ּ� �Լ��� true�� ��ȯ�ϸ� �߰��� Ŭ�� ����Ŭ�� ������ ��.
 */

#pragma region �ּ� ���
// �ּ� ��� Implied
// ���� ��Ʈ ����. PHA ��ɰ� ���� Accumulator �ʱ�ȭ
uint8_t Cpu::IMP()
{
	_fetched = _accumulator;
	return 0;
}

// �ּ� ��� Immediate
// ��ɾ�� ���� ����Ʈ ������ ���ȴ�.
uint8_t Cpu::IMM()
{
	_addr_abs = _pc++;
	return 0;
}

// �ּ� ��� Zero Page
// ���� ������ �ּ� ������ ���� ������ �ּ� ������ ����.
// �ּ� ������ ù ����Ʈ 0x00FF�� ��ġ
uint8_t Cpu::ZP0()
{
	_addr_abs = read(_pc);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// �ּ� ��� Zero Page X Offset
// �⺻������ Zero Page �� ����, X Register�� ������ �߰� �ȴ�.
uint8_t Cpu::ZPX()
{
	_addr_abs = (read(_pc) + _x);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// �ּ� ��� Zero Page Y Offset
// �⺻������ Zero Page �� ����, Y Register�� ������ �߰� �ȴ�.
uint8_t Cpu::ZPY()
{
	_addr_abs = (read(_pc) + _y);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// �ּ� ��� Relative
// �б� ��ɿ� ���ǰ�, �б� �ּ� ��ɾ� ���� -128 ~ +127 ���� �־�� �ȴ�.
// �ּ� ���� ���� ������ �ּҷδ� ���� �б�� �ȵȴ�.
uint8_t Cpu::REL()
{
	_addr_rel = read(_pc);
	_pc++;
	if (_addr_rel & 0x80)
		_addr_rel |= 0xFF00;
	return 0;
}

// �ּ� ��� Absolute
uint8_t Cpu::ABS()
{
	const uint16_t low = read(_pc);
	_pc++;
	const uint16_t high = read(_pc);
	_pc++;

	_addr_abs = (high << 8) | low;
	return 0;
}

// �ּ� ��� Absoulte With X Offset
uint8_t Cpu::ABX()
{
	const uint16_t low = read(_pc);
	_pc++;
	const uint16_t high = read(_pc);
	_pc++;

	_addr_abs = (high << 8) | low;
	_addr_abs += _x;

	if ((_addr_abs & 0xFF00) != (high << 8))
		return 1;
	else
		return 0;
}

// �ּ� ��� Absoulte With Y Offset
uint8_t Cpu::ABY()
{
	const uint16_t low = read(_pc);
	_pc++;
	const uint16_t high = read(_pc);
	_pc++;

	_addr_abs = (high << 8) | low;
	_addr_abs += _y;

	if ((_addr_abs & 0xFF00) != (high << 8))
		return 1;
	else
		return 0;
}


// �ּ� ��� Indirect
// �� ����� �ϵ���� ��ü������ ���װ� �ִ�. �� ���� ���� ����Ͽ��� �ϰ�, 
// ���޵� low �ּ� ����Ʈ�� 0xFF ���,  ���� ����Ʈ�� �б� ���ؼ� ������ ��踦 �Ѿ�� �ȴ�.
uint8_t Cpu::IND()
{
	const uint16_t Ptr_low = read(_pc);
	_pc++;
	const uint16_t Ptr_high = read(_pc);
	_pc++;

	const uint16_t Ptr = (Ptr_high << 8) | Ptr_low;

	if (Ptr_low == 0x00FF) // �ϵ����� �ִ� ���� ���� ���
		_addr_abs = (read(Ptr & 0xFF00) << 8) | read(Ptr + 0);
	else
		_addr_abs = (read(Ptr + 1) << 8) | read(Ptr + 0);

	return 0;
}

uint8_t Cpu::IZX()
{
	const uint16_t t = read(_pc);
	_pc++;

	const uint16_t lo = read((uint16_t)(t + (uint16_t)_x) & 0x00FF);
	const uint16_t hi = read((uint16_t)(t + (uint16_t)_x + 1) & 0x00FF);

	_addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t Cpu::IZY()
{
	const uint16_t t = read(_pc);
	_pc++;

	const uint16_t lo = read(t & 0x00FF);
	const uint16_t hi = read((t + 1) & 0x00FF);

	_addr_abs = (hi << 8) | lo;
	_addr_abs += _y;

	if ((_addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

#pragma endregion 
