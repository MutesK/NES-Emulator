#pragma once

/*
 *  BUS 주소 공간 표현
 *  0x0000												    0xFFFF
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *  |														  |
 *  |														  |
 *  |														  |
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *
 *
 *  RAM
 *  0x0000												   0xFFFF
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *  |														  |
 *  |					  		64Kb						  |
 *  |														  |
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *
	State Register (8 Bit)

	8	7	6	5	4	3	2	1		Flag Postion
	N	O	U	B	D	I	Z	C


	Program Counter (16 Bit)

	8 Bit | 8 Bit
	 Page   Offset

 *
 */


#include <vector>
#include <map>
#include <string>

class Bus;
class Cpu final
{
	enum FLAG
	{
		Carry = (1 << 0),	// Carry Bit
		Zero = (1 << 1),	// Zero
		NoInterrupts = (1 << 2),	// Disable Interrupts
		Decimal = (1 << 3),	// Decimal Mode (unused in this implementation)
		Break = (1 << 4),	// Break
		Unused = (1 << 5),	// Unused
		Overflow = (1 << 6),	// Overflow
		Negative = (1 << 7),	// Negative
	};

	struct Instruction
	{
		std::string name;
		uint8_t(Cpu::*operate)(void) = nullptr;
		uint8_t(Cpu::*addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};
public:
	Cpu();
	~Cpu() = default;

public:
	// CPU Core Registers
	uint8_t _accumulator = 0x00;
	uint8_t _x			 = 0x00; // register
	uint8_t _y			 = 0x00; // register
	uint8_t _stack		 = 0x00; // stack pointer;
	uint16_t _pc		 = 0x0000; // Program Counter
	uint8_t _status		 = 0x00; // Status Register

	uint8_t _fetched = 0x00;
	uint8_t _temp = 0x0000;
	uint8_t _addr_abs = 0;  // 절대 주소
	uint16_t _addr_rel = 0;  // 간접 절대 주소
	uint8_t _opcode = 0x00;
	uint8_t _cycles = 0;
	uint8_t _clock_count = 0;

	Bus* _bus = nullptr;
	std::vector<Instruction> _lookup;

#pragma region Interrupt
	void reset();
	void irq();
	void nmi();
	void clock();
#pragma endregion

	void complete();

	void connectBus(Bus* bus);
	uint8_t read(uint16_t bytes);
	void write(uint16_t addr, uint8_t bytes);

	std::map<uint16_t, std::string> disassemble(uint16_t start, uint16_t stop);

private:
	uint8_t getFlag(FLAG f) const;
	void setFlag(FLAG f, bool v);

private:
	// 주소 모드
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

private:
	// Op Code

	uint8_t fetch();

	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();


	uint8_t XXX();
};

