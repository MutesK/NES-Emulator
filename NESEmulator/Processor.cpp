//
//  Processor.cpp
//  NesEmulator
//
//  Created by JunMin Kim on 2020/02/27.
//  Copyright © 2020 JunMin Kim. All rights reserved.
//

#include "Precompile.h"
#include "Processor.hpp"
#include "Bus.hpp"


Processor::Processor()
{
    using a = Processor;

	LookupInstructions =
    {
        { "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
        { "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
    };
}

void Processor::ResetInterrupt() {
    AddressAbsolute = 0xFFFC;
    uint16_t Low = Read(AddressAbsolute + 0);
    uint16_t High = Read(AddressAbsolute + 1);

    ProgramCounter = (High << 8) | Low;

    Accumulator = 0;
    XRegister = 0;
    YRegister = 0;
    StackPtr = 0xFD;
	StatusRegister = 0x00 | static_cast<int>(Flag::UnUsed);

}

void Processor::InterruptRequest() {
    if (0 == GetFlag(Flag::DisableInterrupt))
    {
        Write(0x0100 + StackPtr, (ProgramCounter >> 8) & 0x00FF);
        StackPtr--;
        Write(0x0100 + StackPtr, ProgramCounter & 0x00FF);
        StackPtr--;

        SetFlag(Flag::Break, 0);
        SetFlag(Flag::UnUsed, 1);
        SetFlag(Flag::DisableInterrupt, 1);
        Write(0x0100 + StackPtr, StatusRegister);
        StackPtr--;

        AddressAbsolute = 0xFFFE;
        uint16_t Low = Read(AddressAbsolute + 0);
        uint16_t High = Read(AddressAbsolute + 1);
        ProgramCounter = (High << 8) | Low;

        Cycles = 7;  // 이 연산의 사이클 지연시간
    }
}

void Processor::NonMaskableInterruptRequest() {
    Write(0x0100 + StackPtr, (ProgramCounter >> 8) & 0x00FF);
    StackPtr--;
    Write(0x0100 + StackPtr, ProgramCounter & 0x00FF);
    StackPtr--;

    SetFlag(Flag::Break, 0);
    SetFlag(Flag::UnUsed, 1);
    SetFlag(Flag::DisableInterrupt, 1);
    Write(0x0100 + StackPtr, StatusRegister);
    StackPtr--;

    AddressAbsolute = 0xFFFA;
    uint16_t Low = Read(AddressAbsolute + 0);
    uint16_t High = Read(AddressAbsolute + 1);
    ProgramCounter = (High << 8) | Low;

    Cycles = 7;
}

void Processor::Clock() {
    if (0 >= Cycles)
    {
		OpCode = Read(ProgramCounter);

        SetFlag(Flag::UnUsed, true);

        ProgramCounter++;
        Cycles = LookupInstructions[OpCode].Cycle;

        uint8_t AdditionalCycle1 = (this->*LookupInstructions[OpCode].AddressMode)();
        uint8_t AdditionalCycle2 = (this->*LookupInstructions[OpCode].InstructionOperator)();

        Cycles += (AdditionalCycle1 & AdditionalCycle2);
        SetFlag(Flag::UnUsed, true);
    }

    ClockCount++;
    Cycles--;
}

bool Processor::Complete() {
    return Cycles == 0;
}

void Processor::ConnectBus(Bus* bus) {
    this->bus = bus;
}

std::map<uint16_t, std::string> Processor::Disassemble(uint16_t start, uint16_t stop)
{
    uint32_t Address = start;
    uint8_t Value = 0, Low = 0, High = 0;
    std::map<uint16_t, std::string> MapLines;
    uint16_t LineAddress = 0;

    auto Hex = [](uint32_t n, uint32_t d)
    {
        std::string s(d, '0');

        for (int i = d - 1; i >= 0; i--, n >>= 4)
            s[i] = "0123456789ABCDEF"[n & 0xF];

        return s;
    };

    while (Address <= static_cast<uint32_t>(stop))
    {
        LineAddress = Address;

        std::string Instance = "$" + Hex(Address, 4) + ": ";

        uint8_t oProgramCounterode = bus->CpuRead(Address, true);
        Address++;

        Instance += LookupInstructions[oProgramCounterode].OpName + " ";

        if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::IMP)
        {
            Instance += " {IMP}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ZP0)
        {
            Low = bus->CpuRead(Address, true);
            Address++;
            High = 0x00;
            Instance += "$" + Hex(Low, 2) + " {ZP0}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ZPX)
        {
            Low = bus->CpuRead(Address, true);
            Address++;
            High = 0x00;
            Instance += "$" + Hex(Low, 2) + ", X {ZPX}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ZPY)
        {
            Low = bus->CpuRead(Address, true);
            Address++;
            High = 0x00;
            Instance += "$" + Hex(Low, 2) + ", Y {ZPY}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::IZX)
        {
            Low = bus->CpuRead(Address, true);
            Address++;
            High = 0x00;
            Instance += "($" + Hex(Low, 2) + ", X) {IZX}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::IZY)
        {
            Low = bus->CpuRead(Address, true);
            Address++;
            High = 0x00;
            Instance += "($" + Hex(Low, 2) + "), Y {IZY}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ABS)
        {
            Low = bus->CpuRead(Address, true); Address++;
            High = bus->CpuRead(Address, true); Address++;
            Instance += "$" + Hex((uint16_t)(High << 8) | Low, 4) + " {ABS}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ABX)
        {
            Low = bus->CpuRead(Address, true); Address++;
            High = bus->CpuRead(Address, true); Address++;
            Instance += "$" + Hex((uint16_t)(High << 8) | Low, 4) + ", X {ABX}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::ABY)
        {
            Low = bus->CpuRead(Address, true); Address++;
            High = bus->CpuRead(Address, true); Address++;
            Instance += "$" + Hex((uint16_t)(High << 8) | Low, 4) + ", Y {ABY}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::IND)
        {
            Low = bus->CpuRead(Address, true); Address++;
            High = bus->CpuRead(Address, true); Address++;
            Instance += "($" + Hex((uint16_t)(High << 8) | Low, 4) + ") {IND}";
        }
        else if (LookupInstructions[oProgramCounterode].AddressMode == &Processor::REL)
        {
            Value = bus->CpuRead(Address, true);
            Address++;
            Instance += "$" + Hex(Value, 2) + " [$" + Hex(Address + Value, 4)
                + "] {REL}";
        }

        MapLines[LineAddress] = Instance;
    }

    return MapLines;



}

uint8_t Processor::GetFlag(Processor::Flag flag) {
    return ((StatusRegister & static_cast<int>(flag)) > 0) ? true : false;
}

void Processor::SetFlag(Processor::Flag flag, bool SpecificBit) {
    if (SpecificBit)
    {
		StatusRegister |= static_cast<int>(flag);
    }
    else
    {
		StatusRegister &= ~static_cast<int>(flag);
    }
}

uint8_t Processor::Read(uint16_t a) {
    return bus->CpuRead(a, false);
}

void Processor::Write(uint16_t a, uint8_t b) {
    bus->CpuWrite(a, b);
}

uint8_t Processor::Fetch() {
    if (!(LookupInstructions[OpCode].AddressMode == &Processor::IMP))
        Fetched = Read(AddressAbsolute);

    return Fetched;
}

uint8_t Processor::IMP() {
    Fetched = Accumulator;
    return 0;
}

uint8_t Processor::IMM() {
    AddressAbsolute = ProgramCounter++;
    return 0;
}

uint8_t Processor::ZP0() {
    AddressAbsolute = Read(ProgramCounter);
    ProgramCounter++;
    AddressAbsolute &= 0x00FF;
    return 0;
}

uint8_t Processor::ZPX() {
    AddressAbsolute = (Read(ProgramCounter) + XRegister);
    ProgramCounter++;
    AddressAbsolute &= 0x00FF;
    return 0;
}

uint8_t Processor::ZPY() {
    AddressAbsolute = (Read(ProgramCounter) + YRegister);
    ProgramCounter++;
    AddressAbsolute &= 0x00FF;
    return 0;
}

uint8_t Processor::REL() {
    AddressRedirect = Read(ProgramCounter);
    ProgramCounter++;

    if (AddressRedirect & 0x80)
        AddressRedirect |= 0xFF00;

    return 0;
}

uint8_t Processor::ABS() {
    uint16_t Low = Read(ProgramCounter);
    ProgramCounter++;
    uint16_t High = Read(ProgramCounter);
    ProgramCounter++;

    AddressAbsolute = (High << 8) | Low;

    return 0;
}

uint8_t Processor::ABX() {
    uint16_t Low = Read(ProgramCounter);
    ProgramCounter++;
    uint16_t High = Read(ProgramCounter);
    ProgramCounter++;

    AddressAbsolute = (High << 8) | Low;
    AddressAbsolute += XRegister;

    if ((AddressAbsolute & 0xFF00) != (High << 8))
        return 1;

    return 0;
}

uint8_t Processor::ABY() {
    uint16_t Low = Read(ProgramCounter);
    ProgramCounter++;
    uint16_t High = Read(ProgramCounter);
    ProgramCounter++;

    AddressAbsolute = (High << 8) | Low;
    AddressAbsolute += YRegister;

    if ((AddressAbsolute & 0xFF00) != (High << 8))
        return 1;

    return 0;
}

uint8_t Processor::IND() {
    uint16_t Low = Read(ProgramCounter);
    ProgramCounter++;
    uint16_t High = Read(ProgramCounter);
    ProgramCounter++;

    uint16_t Ptr = (High << 8) | Low;

    if (Low == 0x00FF)
    {
        AddressAbsolute = (Read(Ptr & 0xFF00) << 8) | Read(Ptr + 0);
    }
    else
    {
        AddressAbsolute = (Read(Ptr + 1) << 8) | Read(Ptr + 0);
    }

    return 0;
}

uint8_t Processor::IZX() {
    uint16_t Temp = Read(ProgramCounter);
    ProgramCounter++;

    uint16_t Low = Read(Temp & 0x00FF);
    uint16_t High = Read((Temp + 1) & 0x00FF);

    AddressAbsolute = (High << 8) | Low;

    return 0;
}

uint8_t Processor::IZY() {
    uint16_t Temp = Read(ProgramCounter);
    ProgramCounter++;

    uint16_t Low = Read(Temp & 0x00FF);
    uint16_t High = Read((Temp + 1) & 0x00FF);

    AddressAbsolute = (High << 8) | Low;
    AddressAbsolute += YRegister;

    if ((AddressAbsolute & 0xFF00) != (High << 8))
        return 1;

    return 0;
}






uint8_t Processor::ADC()
{
	// Grab the data that we are adding to the accumulator
	Fetch();

	// Add is performed in 16-bit domain for emulation to capture any
	// carry bit, which will exist in bit 8 of the 16-bit word
	temp = (uint16_t)Accumulator + (uint16_t)Fetched + (uint16_t)GetFlag(Flag::CarryBit);

	// The carry flag out exists in the high byte bit 0
	SetFlag(Flag::CarryBit, temp > 255);

	// The Flag::Zero flag is set if the result is 0
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0);

	// The signed Overflow flag is set based on all that up there! :D
	SetFlag(Flag::Overflow, (~((uint16_t)Accumulator ^ (uint16_t)Fetched) & ((uint16_t)Accumulator ^ (uint16_t)temp)) & 0x0080);

	// The Flag::Negative flag is set to the most significant bit of the result
	SetFlag(Flag::Negative, temp & 0x80);

	// Load the result into the accumulator (it's 8-bit dont forget!)
	Accumulator = temp & 0x00FF;

	// This instruction has the potential to require an additional clock cycle
	return 1;
}


uint8_t Processor::SBC()
{
	Fetch();

	// Operating in 16-bit domain to capture carry out

	// We can invert the bottom 8 bits with bitwise xor
	uint16_t value = ((uint16_t)Fetched) ^ 0x00FF;

	// Notice this is exactly the same as addition from here!
	temp = (uint16_t)Accumulator + value + (uint16_t)GetFlag(Flag::CarryBit);
	SetFlag(Flag::CarryBit, temp & 0xFF00);
	SetFlag(Flag::Zero, ((temp & 0x00FF) == 0));
	SetFlag(Flag::Overflow, (temp ^ (uint16_t)Accumulator) & (temp ^ value) & 0x0080);
	SetFlag(Flag::Negative, temp & 0x0080);
	Accumulator = temp & 0x00FF;
	return 1;
}

// OK! Complicated operations are done! the following are much simpler
// and conventional. The typical order of events is:
// 1) Fetch the data you are working with
// 2) Perform calculation
// 3) Store the result in desired place
// 4) Set Flags of the StatusRegister register
// 5) Return if instruction has potential to require additional 
//    clock cycle


// Instruction: Bitwise Logic AND
// Function:    A = A & M
// Flags Out:   N, Z
uint8_t Processor::AND()
{
	Fetch();
	Accumulator = Accumulator & Fetched;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 1;
}


// Instruction: Arithmetic Shift Left
// Function:    A = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
uint8_t Processor::ASL()
{
	Fetch();
	temp = (uint16_t)Fetched << 1;
	SetFlag(Flag::CarryBit, (temp & 0xFF00) > 0);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x00);
	SetFlag(Flag::Negative, temp & 0x80);
	if (LookupInstructions[OpCode].AddressMode == &Processor::IMP)
		Accumulator = temp & 0x00FF;
	else
		Write(AddressAbsolute, temp & 0x00FF);
	return 0;
}


// Instruction: Branch if Carry Clear
// Function:    if(C == 0) ProgramCounter = address 
uint8_t Processor::BCC()
{
	if (GetFlag(Flag::CarryBit) == 0)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Branch if Carry Set
// Function:    if(C == 1) ProgramCounter = address
uint8_t Processor::BCS()
{
	if (GetFlag(Flag::CarryBit) == 1)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Branch if Equal
// Function:    if(Z == 1) ProgramCounter = address
uint8_t Processor::BEQ()
{
	if (GetFlag(Flag::Zero) == 1)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}

uint8_t Processor::BIT()
{
	Fetch();
	temp = Accumulator & Fetched;
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x00);
	SetFlag(Flag::Negative, Fetched & (1 << 7));
	SetFlag(Flag::Overflow, Fetched & (1 << 6));
	return 0;
}


// Instruction: Branch if Flag::Negative
// Function:    if(N == 1) ProgramCounter = address
uint8_t Processor::BMI()
{
	if (GetFlag(Flag::Negative) == 1)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Branch if Not Equal
// Function:    if(Z == 0) ProgramCounter = address
uint8_t Processor::BNE()
{
	if (GetFlag(Flag::Zero) == 0)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Branch if Positive
// Function:    if(N == 0) ProgramCounter = address
uint8_t Processor::BPL()
{
	if (GetFlag(Flag::Negative) == 0)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}

// Instruction: Break
// Function:    Program Sourced Interrupt
uint8_t Processor::BRK()
{
	ProgramCounter++;

	SetFlag(Flag::DisableInterrupt, 1);
	Write(0x0100 + StackPtr, (ProgramCounter >> 8) & 0x00FF);
	StackPtr--;
	Write(0x0100 + StackPtr, ProgramCounter & 0x00FF);
	StackPtr--;

	SetFlag(Flag::Break, 1);
	Write(0x0100 + StackPtr, StatusRegister);
	StackPtr--;
	SetFlag(Flag::Break, 0);

	ProgramCounter = (uint16_t)Read(0xFFFE) | ((uint16_t)Read(0xFFFF) << 8);
	return 0;
}


// Instruction: Branch if Overflow Clear
// Function:    if(V == 0) ProgramCounter = address
uint8_t Processor::BVC()
{
	if (GetFlag(Flag::Overflow) == 0)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Branch if Overflow Set
// Function:    if(V == 1) ProgramCounter = address
uint8_t Processor::BVS()
{
	if (GetFlag(Flag::Overflow) == 1)
	{
		Cycles++;
		AddressAbsolute = ProgramCounter + AddressRedirect;

		if ((AddressAbsolute & 0xFF00) != (ProgramCounter & 0xFF00))
			Cycles++;

		ProgramCounter = AddressAbsolute;
	}
	return 0;
}


// Instruction: Clear Carry Flag
// Function:    C = 0
uint8_t Processor::CLC()
{
	SetFlag(Flag::CarryBit, false);
	return 0;
}


// Instruction: Clear Decimal Flag
// Function:    D = 0
uint8_t Processor::CLD()
{
	SetFlag(Flag::Decimal, false);
	return 0;
}


// Instruction: Disable Interrupts / Clear Interrupt Flag
// Function:    I = 0
uint8_t Processor::CLI()
{
	SetFlag(Flag::DisableInterrupt, false);
	return 0;
}


// Instruction: Clear Overflow Flag
// Function:    V = 0
uint8_t Processor::CLV()
{
	SetFlag(Flag::Overflow, false);
	return 0;
}

// Instruction: Compare Accumulator
// Function:    C <- A >= M      Z <- (A - M) == 0
// Flags Out:   N, C, Z
uint8_t Processor::CMP()
{
	Fetch();
	temp = (uint16_t)Accumulator - (uint16_t)Fetched;
	SetFlag(Flag::CarryBit, Accumulator >= Fetched);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	return 1;
}


// Instruction: Compare X Register
// Function:    C <- X >= M      Z <- (X - M) == 0
// Flags Out:   N, C, Z
uint8_t Processor::CPX()
{
	Fetch();
	temp = (uint16_t)XRegister - (uint16_t)Fetched;
	SetFlag(Flag::CarryBit, XRegister >= Fetched);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	return 0;
}


// Instruction: Compare Y Register
// Function:    C <- Y >= M      Z <- (Y - M) == 0
// Flags Out:   N, C, Z
uint8_t Processor::CPY()
{
	Fetch();
	temp = (uint16_t)YRegister - (uint16_t)Fetched;
	SetFlag(Flag::CarryBit, YRegister >= Fetched);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	return 0;
}


// Instruction: Decrement Value at Memory Location
// Function:    M = M - 1
// Flags Out:   N, Z
uint8_t Processor::DEC()
{
	Fetch();
	temp = Fetched - 1;
	Write(AddressAbsolute, temp & 0x00FF);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	return 0;
}


// Instruction: Decrement X Register
// Function:    X = X - 1
// Flags Out:   N, Z
uint8_t Processor::DEX()
{
	XRegister--;
	SetFlag(Flag::Zero, XRegister == 0x00);
	SetFlag(Flag::Negative, XRegister & 0x80);
	return 0;
}


// Instruction: Decrement Y Register
// Function:    Y = Y - 1
// Flags Out:   N, Z
uint8_t Processor::DEY()
{
	YRegister--;
	SetFlag(Flag::Zero, YRegister == 0x00);
	SetFlag(Flag::Negative, YRegister & 0x80);
	return 0;
}


// Instruction: Bitwise Logic XOR
// Function:    A = A xor M
// Flags Out:   N, Z
uint8_t Processor::EOR()
{
	Fetch();
	Accumulator = Accumulator ^ Fetched;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 1;
}


// Instruction: Increment Value at Memory Location
// Function:    M = M + 1
// Flags Out:   N, Z
uint8_t Processor::INC()
{
	Fetch();
	temp = Fetched + 1;
	Write(AddressAbsolute, temp & 0x00FF);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	return 0;
}


// Instruction: Increment X Register
// Function:    X = X + 1
// Flags Out:   N, Z
uint8_t Processor::INX()
{
	XRegister++;
	SetFlag(Flag::Zero, XRegister == 0x00);
	SetFlag(Flag::Negative, XRegister & 0x80);
	return 0;
}


// Instruction: Increment Y Register
// Function:    Y = Y + 1
// Flags Out:   N, Z
uint8_t Processor::INY()
{
	YRegister++;
	SetFlag(Flag::Zero, YRegister == 0x00);
	SetFlag(Flag::Negative, YRegister & 0x80);
	return 0;
}


// Instruction: Jump To Location
// Function:    ProgramCounter = address
uint8_t Processor::JMP()
{
	ProgramCounter = AddressAbsolute;
	return 0;
}


// Instruction: Jump To Sub-Routine
// Function:    Push current ProgramCounter to stack, ProgramCounter = address
uint8_t Processor::JSR()
{
	ProgramCounter--;

	Write(0x0100 + StackPtr, (ProgramCounter >> 8) & 0x00FF);
	StackPtr--;
	Write(0x0100 + StackPtr, ProgramCounter & 0x00FF);
	StackPtr--;

	ProgramCounter = AddressAbsolute;
	return 0;
}


// Instruction: Load The Accumulator
// Function:    A = M
// Flags Out:   N, Z
uint8_t Processor::LDA()
{
	Fetch();
	Accumulator = Fetched;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 1;
}


// Instruction: Load The X Register
// Function:    X = M
// Flags Out:   N, Z
uint8_t Processor::LDX()
{
	Fetch();
	XRegister = Fetched;
	SetFlag(Flag::Zero, XRegister == 0x00);
	SetFlag(Flag::Negative, XRegister & 0x80);
	return 1;
}


// Instruction: Load The Y Register
// Function:    Y = M
// Flags Out:   N, Z
uint8_t Processor::LDY()
{
	Fetch();
	YRegister = Fetched;
	SetFlag(Flag::Zero, YRegister == 0x00);
	SetFlag(Flag::Negative, YRegister & 0x80);
	return 1;
}

uint8_t Processor::LSR()
{
	Fetch();
	SetFlag(Flag::CarryBit, Fetched & 0x0001);
	temp = Fetched >> 1;
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	if (LookupInstructions[OpCode].AddressMode == &Processor::IMP)
		Accumulator = temp & 0x00FF;
	else
		Write(AddressAbsolute, temp & 0x00FF);
	return 0;
}

uint8_t Processor::NOP()
{
	// Sadly not all NOPs are equal, Ive added a few here
	// based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_oProgramCounterodes
	// and will add more based on game compatibility, and ultimately
	// I'd like to cover all illegal oProgramCounterodes too
	switch (OpCode) {
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


// Instruction: Bitwise Logic OR
// Function:    A = A | M
// Flags Out:   N, Z
uint8_t Processor::ORA()
{
	Fetch();
	Accumulator = Accumulator | Fetched;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 1;
}


// Instruction: Push Accumulator to Stack
// Function:    A -> stack
uint8_t Processor::PHA()
{
	Write(0x0100 + StackPtr, Accumulator);
	StackPtr--;
	return 0;
}


// Instruction: Push StatusRegister Register to Stack
// Function:    StatusRegister -> stack
// Note:        Break flag is set to 1 before push
uint8_t Processor::PHP()
{
	Write(0x0100 + StackPtr, StatusRegister | (int)Flag::Break | (int)Flag::UnUsed);
	SetFlag(Flag::Break, 0);
	SetFlag(Flag::UnUsed, 0);
	StackPtr--;
	return 0;
}


// Instruction: Pop Accumulator off Stack
// Function:    A <- stack
// Flags Out:   N, Z
uint8_t Processor::PLA()
{
	StackPtr++;
	Accumulator = Read(0x0100 + StackPtr);
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 0;
}


// Instruction: Pop StatusRegister Register off Stack
// Function:    StatusRegister <- stack
uint8_t Processor::PLP()
{
	StackPtr++;
	StatusRegister = Read(0x0100 + StackPtr);
	SetFlag(Flag::UnUsed, 1);
	return 0;
}

uint8_t Processor::ROL()
{
	Fetch();
	temp = (uint16_t)(Fetched << 1) | GetFlag(Flag::CarryBit);
	SetFlag(Flag::CarryBit, temp & 0xFF00);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x0000);
	SetFlag(Flag::Negative, temp & 0x0080);
	if (LookupInstructions[OpCode].AddressMode == &Processor::IMP)
		Accumulator = temp & 0x00FF;
	else
		Write(AddressAbsolute, temp & 0x00FF);
	return 0;
}

uint8_t Processor::ROR()
{
	Fetch();
	temp = (uint16_t)(GetFlag(Flag::CarryBit) << 7) | (Fetched >> 1);
	SetFlag(Flag::CarryBit, Fetched & 0x01);
	SetFlag(Flag::Zero, (temp & 0x00FF) == 0x00);
	SetFlag(Flag::Negative, temp & 0x0080);
	if (LookupInstructions[OpCode].AddressMode == &Processor::IMP)
		Accumulator = temp & 0x00FF;
	else
		Write(AddressAbsolute, temp & 0x00FF);
	return 0;
}

uint8_t Processor::RTI()
{
	StackPtr++;
	StatusRegister = Read(0x0100 + StackPtr);
	StatusRegister &= ~(int)Flag::Break;
	StatusRegister &= ~(int)Flag::UnUsed;

	StackPtr++;
	ProgramCounter = (uint16_t)Read(0x0100 + StackPtr);
	StackPtr++;
	ProgramCounter |= (uint16_t)Read(0x0100 + StackPtr) << 8;
	return 0;
}

uint8_t Processor::RTS()
{
	StackPtr++;
	ProgramCounter = (uint16_t)Read(0x0100 + StackPtr);
	StackPtr++;
	ProgramCounter |= (uint16_t)Read(0x0100 + StackPtr) << 8;

	ProgramCounter++;
	return 0;
}




// Instruction: Set Carry Flag
// Function:    C = 1
uint8_t Processor::SEC()
{
	SetFlag(Flag::CarryBit, true);
	return 0;
}


// Instruction: Set Decimal Flag
// Function:    D = 1
uint8_t Processor::SED()
{
	SetFlag(Flag::Decimal, true);
	return 0;
}


// Instruction: Set Interrupt Flag / Enable Interrupts
// Function:    I = 1
uint8_t Processor::SEI()
{
	SetFlag(Flag::DisableInterrupt, true);
	return 0;
}


// Instruction: Store Accumulator at Address
// Function:    M = A
uint8_t Processor::STA()
{
	Write(AddressAbsolute, Accumulator);
	return 0;
}


// Instruction: Store X Register at Address
// Function:    M = X
uint8_t Processor::STX()
{
	Write(AddressAbsolute, XRegister);
	return 0;
}


// Instruction: Store Y Register at Address
// Function:    M = Y
uint8_t Processor::STY()
{
	Write(AddressAbsolute, YRegister);
	return 0;
}


// Instruction: Transfer Accumulator to X Register
// Function:    X = A
// Flags Out:   N, Z
uint8_t Processor::TAX()
{
	XRegister = Accumulator;
	SetFlag(Flag::Zero, XRegister == 0x00);
	SetFlag(Flag::Negative, XRegister & 0x80);
	return 0;
}


// Instruction: Transfer Accumulator to Y Register
// Function:    Y = A
// Flags Out:   N, Z
uint8_t Processor::TAY()
{
	YRegister = Accumulator;
	SetFlag(Flag::Zero, YRegister == 0x00);
	SetFlag(Flag::Negative, YRegister & 0x80);
	return 0;
}


// Instruction: Transfer Stack Pointer to X Register
// Function:    X = stack pointer
// Flags Out:   N, Z
uint8_t Processor::TSX()
{
	XRegister = StackPtr;
	SetFlag(Flag::Zero, XRegister == 0x00);
	SetFlag(Flag::Negative, XRegister & 0x80);
	return 0;
}


// Instruction: Transfer X Register to Accumulator
// Function:    A = X
// Flags Out:   N, Z
uint8_t Processor::TXA()
{
	Accumulator = XRegister;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 0;
}


// Instruction: Transfer X Register to Stack Pointer
// Function:    stack pointer = X
uint8_t Processor::TXS()
{
	StackPtr = XRegister;
	return 0;
}


// Instruction: Transfer Y Register to Accumulator
// Function:    A = Y
// Flags Out:   N, Z
uint8_t Processor::TYA()
{
	Accumulator = YRegister;
	SetFlag(Flag::Zero, Accumulator == 0x00);
	SetFlag(Flag::Negative, Accumulator & 0x80);
	return 0;
}


// This function captures illegal oProgramCounterodes
uint8_t Processor::XXX()
{
	return 0;
}

