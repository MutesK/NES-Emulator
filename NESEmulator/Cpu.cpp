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
	버스 IO 함수
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
	외부 입력 함수
*/
void Cpu::reset()
{
	_addr_abs = 0xFFFC;  // 프로그램 카운터
	uint16_t low = read(_addr_abs + 0);
	uint16_t high = read(_addr_abs + 1);

	_pc = (high << 8) | low;

	// 외부 레지스터 셋팅
	_accumulator = 0;
	_x = 0;
	_y = 0;
	_stack = 0xFD;
	_status = 0x00 | FLAG::Unused;

	// 사용 변수 클리어
	_addr_rel = 0x0000;
	_addr_abs = 0x0000;
	_fetched = 0x00;

	_cycles = 8;
}

// 인터럽트 요청은 아무때나 올수 있다.
// IRQ 가 발생했을때, Reset과 거의 비슷하게 동작한다. 
// Programmable Address 가 하드코딩된 메모리 주소 0xFFFE를 읽고, 그뒤, 프로그램 카운터를 셋팅한다.
void Cpu::irq()
{
	if(getFlag(NoInterrupts) == 0)  // 인터럽트가 허용된다면
	{
		// 현재 PC의 값을 스택에 넣는다.
		write(0x0100 + _stack, (_pc >> 8) & 0x00FF);
		_stack--;
		write(0x1000 + _stack, _pc & 0x00FF); 
		_stack--;

		// 그리고 상태 레이스터에 스택 레지스터의 값을 넣는다.
		setFlag(Break, false);
		setFlag(Unused, true);
		setFlag(NoInterrupts, true);
		write(0x0100 + _stack, _status);
		_stack--;

		// 고정 주소로 부터, 새로운 프로그램 카운터를 읽어온다.
		_addr_abs = 0xFFFE;
		const uint16_t low = read(_addr_abs + 0);
		const uint16_t high = read(_addr_abs + 1);
		_pc = (high << 8) | low;

		_cycles= 7;
	}
}

// Non-Masked Interrupt는 무시할수 없다.
// 기본적인 IRQ와 같은 동작이지만, 주소 0xFFFA로부터, 새로운 프로그램 카운터 주소 읽어 온다.
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

// CPU에서의 클럭, Software 상에서는 Tick으로 처리 
void Cpu::clock()
{
	// 실제 CPU에서는 레지스터 전달 등등이 이뤄지지만 에뮬레이터에서는 결과값만 원한다.
	// 한번 사이클로 전체를 계산하고, CPU 상태의 마이크로코드 변환을 수행.
	// 명령어를 실행하려면 에뮬레이터도 하드웨어 환경과 동일하게 지연을 주게 한다. = cycle 변수가 이에 해당.

	if(!_cycles) 
	{
		// 이번 명령이 끝났으므로, 다음 명령 byte 를 가져온다.
		_opcode = read(_pc);

		setFlag(Unused, true);
		_pc++;

		_cycles = _lookup[_opcode].cycles;  // 이번 연산에 필요한 지연시간

		// 주소 방식
		const uint8_t additional_cycle1 = (this->*_lookup[_opcode].addrmode)();
		// 작업 
		const uint8_t additional_cycle2 = (this->*_lookup[_opcode].operate)();

		_cycles += (additional_cycle1 & additional_cycle2);

		setFlag(Unused, true);
	}

	_clock_count++;
	_cycles--;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Flag 함수
 *  
 *  Status Register 관리
 *  아래 flag는 특정 비트 위치를 가져오거나, 셋팅하면 된다.
 */
uint8_t Cpu::getFlag(FLAG f) const
{
	return ((_status & f) > false) ? true : false;
}

// bool 값이 true라면, Status Register 특정 위치 Set,
// bool 값이 false 라면, Status Reigster Clear
void Cpu::setFlag(FLAG f, bool v)
{
	if (v)
		_status |= f;
	else
		_status &= ~f;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  주소 함수
 *
 * 6502 CPU는 0x0000 ~ 0xFFFF 주소를 사용가능하다.
 * 
 * High bytes(2)는 Page 로써 자주 사용되고, Low Bytes(2)는 해당 Page의 Offset으로 사용된다.
 * 256의 페이지가 있다.
 * 
 * 각각의 주소 모드는 추가적인 클록 사이클이 필요하다.
 * 페이지 경계를 넘으면 순환되고, 주소 함수가 true를 반환하면 추가로 클럭 사이클을 돌려야 함.
 */

#pragma region 주소 모드
// 주소 모드 Implied
// 상태 비트 설정. PHA 명령과 같은 Accumulator 초기화
uint8_t Cpu::IMP()
{
	_fetched = _accumulator;
	return 0;
}

// 주소 모드 Immediate
// 명령어는 다음 바이트 값으로 사용된다.
uint8_t Cpu::IMM()
{
	_addr_abs = _pc++;
	return 0;
}

// 주소 모드 Zero Page
// 제로 페이지 주소 지정을 통해 절대적 주소 지정이 가능.
// 주소 범위의 첫 바이트 0x00FF는 위치
uint8_t Cpu::ZP0()
{
	_addr_abs = read(_pc);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// 주소 모드 Zero Page X Offset
// 기본적으로 Zero Page 와 동일, X Register의 내용이 추가 된다.
uint8_t Cpu::ZPX()
{
	_addr_abs = (read(_pc) + _x);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// 주소 모드 Zero Page Y Offset
// 기본적으로 Zero Page 와 동일, Y Register의 내용이 추가 된다.
uint8_t Cpu::ZPY()
{
	_addr_abs = (read(_pc) + _y);
	_pc++;
	_addr_abs &= 0x00FF;
	return 0;
}

// 주소 모드 Relative
// 분기 명령에 사용되고, 분기 주소 명령어 범위 -128 ~ +127 내에 있어야 된다.
// 주소 지정 가능 범위의 주소로는 직접 분기는 안된다.
uint8_t Cpu::REL()
{
	_addr_rel = read(_pc);
	_pc++;
	if (_addr_rel & 0x80)
		_addr_rel |= 0xFF00;
	return 0;
}

// 주소 모드 Absolute
uint8_t Cpu::ABS()
{
	const uint16_t low = read(_pc);
	_pc++;
	const uint16_t high = read(_pc);
	_pc++;

	_addr_abs = (high << 8) | low;
	return 0;
}

// 주소 모드 Absoulte With X Offset
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

// 주소 모드 Absoulte With Y Offset
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


// 주소 모드 Indirect
// 이 기능은 하드웨어 자체에서도 버그가 있다. 이 버그 까지 모방하여야 하고, 
// 공급된 low 주소 바이트가 0xFF 라면,  높은 바이트를 읽기 위해서 페이지 경계를 넘어야 된다.
uint8_t Cpu::IND()
{
	const uint16_t Ptr_low = read(_pc);
	_pc++;
	const uint16_t Ptr_high = read(_pc);
	_pc++;

	const uint16_t Ptr = (Ptr_high << 8) | Ptr_low;

	if (Ptr_low == 0x00FF) // 하드웨어에서 있는 버그 구현 모방
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

#pragma region OPCODE

uint8_t Cpu::fetch()
{
	if (_lookup[_opcode].addrmode != &IMP)
		_fetched = read(_addr_abs);

	return _fetched;
}

// Add With Carry In
uint8_t Cpu::ADC()
{
	// 데이터를 가져와서 누산기에 더한다.
	fetch();

	_temp = static_cast<uint16_t>(_accumulator)
		+ static_cast<uint16_t>(_fetched)
		+ static_cast<uint16_t>(getFlag(Carry));

	setFlag(Carry, _temp > 255);
	setFlag(Zero, (_temp & 0x00FF) == 0);

	const auto flag = 0x0088;
	setFlag(Overflow,
		~(static_cast<uint16_t>(_accumulator) ^ static_cast<uint16_t>(_fetched)) &
		(static_cast<uint16_t>(_accumulator) ^ flag));

	// 네거티브는 MSB 비트로 셋팅
	setFlag(Negative, _temp & 0x80);

	// result 로드해서 누산기에 넣는다. (8 bit);
	_accumulator = _temp & 0x00FF;

	return true;
}
/*
// Instruction: Subtraction with Borrow In
// Function:    A = A - M - (1 - C)
// Flags Out:   C, V, N, Z
*/
uint8_t Cpu::SBC()
{
	fetch();

	const uint16_t value = static_cast<uint16_t>(_fetched) ^ 0x00FF;
	_temp = static_cast<uint16_t>(_accumulator) + value
		+ static_cast<uint16_t>(getFlag(Carry));

	setFlag(Carry, _temp & 0xFF00);
	setFlag(Zero, (_temp & 0x00FF) == 0); // Offset is Zero
	setFlag(Overflow,
		(_temp ^ static_cast<uint16_t>(_accumulator)) &
		(_temp ^ value) & 0x0080);
	setFlag(NoInterrupts, _temp & 0x0080);
	_accumulator = _temp & 0x00FF;

	return true;
}

// Instruction: Bitwise Logic AND
// Function:    A = A & M
// Flags Out:   N, Z
uint8_t Cpu::AND()
{
	fetch();
	_accumulator = _accumulator & _fetched;
	setFlag(Zero, _accumulator == 0x00);
	setFlag(NoInterrupts, _accumulator & 0x80);

	return true;
}

// Instruction: Arithmetic Shift Left
// Function:    A = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
uint8_t Cpu::ASL()
{
	fetch();
	_temp = static_cast<uint16_t>(_fetched) << 1;
	setFlag(Carry, (_temp & 0xFF00) > 0); // Page Status 
	setFlag(Zero, (_temp & 0x00FF) == 0x00); // Offset is Zero
	setFlag(NoInterrupts, _temp & 0x80); // MSB

	if (_lookup[_opcode].addrmode == &Cpu::IMP)
		_accumulator = _temp & 0x00FF; // Get Offset
	else
		write(_addr_abs, _temp & 0x00FF); // Write Address IMM

	return 0;
}

// Instruction: Branch if Carry Clear
// Function:    if(C == 0) pc = address 
uint8_t Cpu::BCC()
{
	if (getFlag(Carry) == 0) // if Carry Flag not exist
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}

// Instruction: Branch if Equal
// Function:    if(Z == 1) pc = address
uint8_t Cpu::BEQ()
{
	if (getFlag(Zero) == 1)
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}
//BIT - Bit Test
// A& M, N = M7, V = M6
uint8_t Cpu::BIT()
{
	fetch();

	_temp = _accumulator & _fetched;
	setFlag(Zero, (_temp & 0x00FF) == 0x00);  // Set if the result if the AND is zero
	setFlag(Overflow, _fetched << 6); // Set to bit 6 of the memory value
	setFlag(Negative, _fetched << 7);  // Set to bit 7 of the memory value

	return 0;
}

// BMI - Branch if Minus
// If the negative flag is set then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t Cpu::BMI()
{
	if (getFlag(Negative))
	{
		// Replative Displacement Program Counter
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0x00FF))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}

// If the negative flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t Cpu::BPL()
{
	if (!getFlag(Negative))
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0x00FF))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}
/*
BRK - Force Interrupt
The BRK instruction forces the generation of an interrupt request. 
The program counter and processor status are pushed on the stack then 
the IRQ interrupt vector at $FFFE/F is loaded into the PC and the break flag in the status set to one.
*/
uint8_t Cpu::BRK()
{
	_pc++;

	setFlag(NoInterrupts, 1);
	write(0x0100 + _stack, (_pc >> 8) & 0x00FF);
	_stack--;
	write(0x0100 + _stack, _pc & 0x00FF);
	_stack--;

	setFlag(Break, 1);
	write(0x0100 + _stack, _status);
	_stack--;
	setFlag(Break, 0);

	_pc = static_cast<uint16_t>(read(0xFFFE)) | (static_cast<uint16_t>(read(0xFFFF) << 8));
	return 0;
}

// Instruction: Branch if Overflow Clear
// If the overflow flag is clear then add 
// the relative displacement to the program counter to cause a branch to a new location.
uint8_t Cpu::BVC()
{
	if (!getFlag(Overflow))
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}
/*
BVS - Branch if Overflow Set
If the overflow flag is set then add 
the relative displacement to the program counter to cause a branch to a new location.
*/

uint8_t Cpu::BVS()
{
	if (getFlag(Overflow))
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}
/*
CLC - Clear Carry Flag
C = 0

Set the carry flag to zero.
*/
uint8_t Cpu::CLC()
{
	setFlag(Carry, 0);
	return 0;
}

/*
CLD - Clear Decimal Mode
D = 0

Sets the decimal mode flag to zero.
*/
uint8_t Cpu::CLD()
{
	setFlag(Decimal, 0);
	return 0;
}

/*
CLI - Clear Interrupt Disable
I = 0

Clears the interrupt disable flag allowing normal interrupt requests to be serviced.
*/
uint8_t Cpu::CLI()
{
	setFlag(NoInterrupts, 0);
	return 0;
}

/*
CLV - Clear Overflow Flag
V = 0

Clears the overflow flag.
*/
uint8_t Cpu::CLV()
{
	setFlag(Overflow, 0);
	return 0;
}

/*
CMP - Compare
Z,C,N = A-M

This instruction compares the contents of the accumulator with 
another memory held value and sets the zero and carry flags as appropriate.
*/
uint8_t Cpu::CMP()
{
	fetch();
	_temp = static_cast<uint16_t>(_accumulator) - 
		static_cast<uint16_t>(_fetched);

	setFlag(Carry, _accumulator >= _fetched);
	setFlag(Zero, (_temp & 0x00FF) == 0x00); // A == M
	setFlag(Negative, _temp & 0x0080);  // 	Set if bit 7 of the result is set

	return 1;
}

/*
CPX - Compare X Register
Z,C,N = X-M

This instruction compares the contents of 
the X register with another memory held value 
and sets the zero and carry flags as appropriate.
*/
uint8_t Cpu::CPX()
{
	fetch();

	_temp = static_cast<uint16_t>(_x) -
		static_cast<uint16_t>(_fetched);

	setFlag(Carry, _x >= _fetched);
	setFlag(Zero, (_temp & 0x00FF) == 0x00); // A == M
	setFlag(Negative, _temp & 0x0080);  // 	Set if bit 7 of the result is set

	return 1;
}

/*
CPY - Compare Y Register
Z,C,N = Y-M

This instruction compares the contents of the Y register 
with another memory held value and sets the zero 
and carry flags as appropriate.
*/
uint8_t Cpu::CPY()
{
	fetch();

	_temp = static_cast<uint16_t>(_y) -
		static_cast<uint16_t>(_fetched);

	setFlag(Carry, _y >= _fetched);
	setFlag(Zero, (_temp & 0x00FF) == 0x00); // A == M
	setFlag(Negative, _temp & 0x0080);  // 	Set if bit 7 of the result is set

	return 1;
}

/*
DEC - Decrement Memory
M,Z,N = M-1

Subtracts one from the value held at a specified memory location 
setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::DEC()
{
	fetch();

	_temp = _fetched - 1;
	write(_addr_abs, _temp & 0x00FF);

	setFlag(Zero, (_temp & 0x00FF) == 0x00); // Set if result is zero
	setFlag(Negative, _temp & 0x0080); // 	Set if bit 7 of the result is set
	return 0;
}

/*
DEX - Decrement X Register
X,Z,N = X-1

Subtracts one from the X register setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::DEX()
{
	_x--;

	setFlag(Zero, _x == 0x00); // Set if result is zero
	setFlag(Negative, _x == 0x80); // 	Set if bit 7 of the result is set
	return 0;
}

uint8_t Cpu::DEY()
{
	_y--;

	setFlag(Zero, _y == 0x00);
	setFlag(Negative, _y == 0x80);
	return 0;
}

/*
EOR - Exclusive OR
A,Z,N = A^M

An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
*/
uint8_t Cpu::EOR()
{
	fetch();

	_accumulator ^= _fetched;

	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator == 0x80);

	return 0;

}

/*
INC - Increment Memory
M,Z,N = M+1

Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::INC()
{
	fetch();

	_temp = static_cast<uint16_t>(_fetched) + 1;

	write(_addr_abs, _temp & 0x00FF); // Memory Location Setting
	setFlag(Zero, (_temp & 0x00FF) == 0x0000);
	setFlag(Negative, _temp == 0x0080);

	return 0;
}

/*
INX - Increment X Register
X,Z,N = X+1

Adds one to the X register setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::INX()
{
	_x++;

	setFlag(Zero, _x == 0x00);
	setFlag(Negative, _x & 0x80);

	return 0;
}

/*
INY - Increment Y Register
Y,Z,N = Y+1

Adds one to the Y register setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::INY()
{
	_y++;

	setFlag(Zero, _y == 0x00);
	setFlag(Negative, _y & 0x80);

	return 0;
}

/*
JMP - Jump
Sets the program counter to the address specified by the operand.
*/

uint8_t Cpu::JMP()
{
	_pc = _addr_abs;
	return 0;
}

/*
JSR - Jump to Subroutine
The JSR instruction pushes the address (minus one) of the return point on to the stack and then sets the program counter to the target memory address.
// Function:    Push current pc to stack, pc = address
*/
uint8_t Cpu::JSR()
{
	_pc--;

	// Push Current PC  To Stack
	write(0x1000 + _stack, (_pc >> 8) & 0x00FF);
	_stack--;
	write(0x0100 + _stack, _pc & 0x00FF);
	_stack--;

	// PC = address
	_pc = _addr_abs;

	return 0;
}

/*
LDA - Load Accumulator
A,Z,N = M

Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::LDA()
{
	fetch();

	_accumulator = _fetched;
	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator & 0x80);

	return 1;
}

/*
LDX - Load X Register
X,Z,N = M

Loads a byte of memory into the X register setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::LDX()
{
	fetch();

	_x = _fetched;

	setFlag(Zero, _x == 0x00);
	setFlag(Negative, _x & 0x80);

	return 1;
}

/*
LDY - Load Y Register
Y,Z,N = M

Loads a byte of memory into the Y register setting the zero and negative flags as appropriate.
*/
uint8_t Cpu::LDY()
{
	fetch();

	_y = _fetched;

	setFlag(Zero, _y == 0x00);
	setFlag(Negative, _y & 0x80);

	return 1;
}

/*
LSR - Logical Shift Right
A,C,Z,N = A/2 or M,C,Z,N = M/2

Each of the bits in A or M is shift one place to the right. The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
*/
uint8_t Cpu::LSR()
{
	fetch();

	setFlag(Carry, _fetched & 0x01);
	_temp = _fetched >> 1;
	setFlag(Zero, (_temp & 0x00FF) == 0x00);
	setFlag(Negative, _temp & 0x0080);

	if (_lookup[_opcode].addrmode == &Cpu::IMP)
		_accumulator = _temp & 0x00FF;
	else
		write(_addr_abs, _temp & 0x00FF);
	return 0;
}

/*
PHA - Push Accumulator
Pushes a copy of the accumulator on to the stack.
*/
uint8_t Cpu::PHA()
{
	write(0x0100 + _stack, _accumulator);
	_stack--;

	return 0;
}

/*
PHP - Push Processor Status
Pushes a copy of the status flags on to the stack.
// Function:    status -> stack
// Note:        Break flag is set to 1 before push
*/
uint8_t Cpu::PHP()
{
	write(0x0100 + _stack, _status | Break | Unused);
	setFlag(Break, 0);
	setFlag(Unused, 0);
	_stack--;

	return 0;
}

/*
PLA - Pull Accumulator
Pulls an 8 bit value from the stack and into the accumulator. The zero and negative flags are set as appropriate.
// Function:    A <- stack
// Flags Out:   N, Z
*/
uint8_t Cpu::PLA()
{
	// Read Stack
	_stack++;
	_accumulator = read(0x0100 + _stack);

	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator & 0x80);

	return 0;
}

/*
PLP - Pull Processor Status
Pulls an 8 bit value from the stack and into the processor flags. The flags will take on new states as determined by the value pulled.
// Function:    Status <- stack
*/
uint8_t Cpu::PLP()
{
	// Read Stack
	_stack++;
	_status = read(0x0100 + _stack);

	setFlag(Unused, 1);
	return 0;
}

/*
ROL - Rotate Left
Move each of the bits in either A or M one place to the left. Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
*/
uint8_t Cpu::ROL()
{
	fetch();

	_temp = (static_cast<uint16_t>(_fetched) << 1) | getFlag(Carry);

	setFlag(Carry, _temp & 0xFF00);  // ?
	setFlag(Zero, (_temp & 0x00FF) == 0x00);
	setFlag(Negative, (_temp & 0x0080));

	if (_lookup[_opcode].addrmode == &Cpu::IMP)
		_accumulator = _temp & 0x00FF;
	else
		write(_addr_abs, _temp & 0x00FF);

	return 0;

}

uint8_t Cpu::ROR()
{
	fetch();

	_temp = (uint16_t)(getFlag(Carry) << 7) | (_fetched >> 1);

	setFlag(Carry, _fetched & 0x01);
	setFlag(Zero, (_temp & 0x00FF) == 0x00);
	setFlag(Negative, _temp & 0x0080);

	if (_lookup[_opcode].addrmode == &Cpu::IMP)
		_accumulator = _temp & 0x00FF;
	else
		write(_addr_abs, _temp & 0x00FF);
	return 0;
}

/*
RTI - Return from Interrupt
The RTI instruction is used at the end of an interrupt processing routine. It pulls the processor flags from the stack followed by the program counter.
*/
uint8_t Cpu::RTI()
{
	_stack++;
	_status = read(0x0100 + _stack);

	_status &= ~Break;
	_status &= ~Unused;

	_stack++;
	_pc = (uint16_t)read(0x0100 + _stack);
	_stack++;
	_pc |= (uint16_t)read(0x0100 + _stack) << 8;

	return 0;
}

/*
RTS - Return from Subroutine
The RTS instruction is used at the end of a subroutine to return to the calling routine. It pulls the program counter (minus one) from the stack.
*/
uint8_t Cpu::RTS()
{
	_stack++;
	_pc = (uint16_t)read(0x0100 + _stack);
	_stack++;
	_pc |= (uint16_t)read(0x0100 | _stack) << 8;

	_pc++;

	return 0;
}

/*
SBC - Subtract with Carry
A,Z,C,N = A-M-(1-C)

This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit. If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
*/
uint8_t Cpu::SBC()
{
	fetch();

	const uint16_t value = ((uint16_t)_fetched ^ 0x00FF);

	_temp = (uint16_t)_accumulator + value + (uint16_t)getFlag(Carry);
	setFlag(Carry, _temp & 0xFF00);
	setFlag(Zero, (_temp & 0x00FF) == 0x00);
	setFlag(Overflow, ((_temp ^ (uint16_t)_accumulator) & ((_temp ^ value) & 0x0080)));
	setFlag(Negative, _temp & 0x0080);

	_accumulator = _temp & 0x00FF;
	return 1;
}

uint8_t Cpu::SEC()
{
	setFlag(Carry, 1);
	return 0;
}

uint8_t Cpu::SED()
{
	setFlag(Decimal, 1);
	return 0;
}

uint8_t Cpu::SEI()
{
	setFlag(NoInterrupts, 1);
	return 0;
}

uint8_t Cpu::STA()
{
	write(_addr_abs, _accumulator);
	return 0;
}

uint8_t Cpu::STX()
{
	write(_addr_abs, _x);
	return 0;
}

uint8_t Cpu::STY()
{
	write(_addr_abs, _y);
	return 0;
}

uint8_t Cpu::TAX()
{
	_x = _accumulator;

	setFlag(Zero, _x == 0x00);
	setFlag(Negative, _x & 0x80);
	return 0;
}

uint8_t Cpu::TAY()
{
	_y = _accumulator;

	setFlag(Zero, _y == 0x00);
	setFlag(Negative, _y & 0x80);
	return 0;
}

uint8_t Cpu::TSX()
{
	_x = _stack;

	setFlag(Zero, _x == 0x00);
	setFlag(Negative, _x & 0x80);

	return 0;
}

uint8_t Cpu::TXA()
{
	_accumulator = _x;

	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator & 0x80);
	return 0;
}

uint8_t Cpu::TXS()
{
	_stack = _x;
	return 0;
}

uint8_t Cpu::TYA()
{
	_accumulator = _y;

	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator & 0x80);
}

uint8_t Cpu::XXX()
{
	return 0;
}

uint8_t Cpu::BCS()
{
	if (getFlag(Carry))
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}
	return 0;
}

uint8_t Cpu::BNE()
{
	if (!getFlag(Zero))
	{
		_cycles++;
		_addr_abs = _pc + _addr_rel;

		if ((_addr_abs & 0xFF00) != (_pc & 0xFF00))
			_cycles++;

		_pc = _addr_abs;
	}

	return 0;
}

uint8_t Cpu::NOP()
{
	switch (_opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

uint8_t Cpu::ORA()
{
	fetch();

	_accumulator = _accumulator | _fetched;

	setFlag(Zero, _accumulator == 0x00);
	setFlag(Negative, _accumulator & 0x80);

	return 1;

}

#pragma endregion