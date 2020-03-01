//
//  Bus.hpp
//  NesEmulator
//
//  Created by JunMin Kim on 2020/02/27.
//  Copyright © 2020 JunMin Kim. All rights reserved.
//

#pragma once

using RamStorage = std::array<uint8_t, 2048>;

class Processor;
using ProcessorPtr = std::shared_ptr<Processor>;

class PictureProcessor;
using PictureProcessorPtr = std::shared_ptr<PictureProcessor>;

class Cartridge;


class Bus
{
    std::shared_ptr<Processor> Cpu;
    std::shared_ptr<PictureProcessor> Ppu;
    std::shared_ptr<Cartridge>      cartridge;

    RamStorage                 Ram;
    uint32_t                   SystemClockCounter;

    // Direct Memory Access
    uint8_t DMAPage = 0;
    uint8_t DMAAddress = 0;
    uint8_t DMAData = 0;
    bool    DMATransfer = false;
    bool    DMADummy = true;

    // Controll
    uint8_t Controller[2];
    uint8_t ControllerState[2];
public:
    Bus();
    
    RamStorage& GetRam();
    ProcessorPtr& GetProcessor();
    PictureProcessorPtr& GetPictureProcessor();
    uint8_t& GetController(int index);

   
    void CpuWrite(uint16_t AddressPosition, uint8_t Data);
    uint8_t CpuRead(uint16_t AddressPosition, bool ReadOnly = false);


public:
    void InsertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void Reset();
    void Clock();  // System Tick
};

