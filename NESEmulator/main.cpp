//
//  main.cpp
//  NesEmulator
//
//  Created by JunMin Kim on 2020/02/27.
//  Copyright © 2020 JunMin Kim. All rights reserved.
//

#include "Precompile.h"
#include "Bus.hpp"
#include "Processor.hpp"
#include "Cartridge.h"
#include "PictureProcessor.h"

using namespace PixelEngine;

class DebugProcessor : public PixelGameEngine
{
    std::map<uint16_t, std::string> AssemblyLog;
    std::shared_ptr<Bus>       NesBus;
    std::shared_ptr<Cartridge> cart;

    bool bEmulationRun = false;
    float fResidualTime = 0.0f;

    uint8_t SelectedPalette = 0;
public:
    DebugProcessor()
    {
        sAppName = "Processor 6502 Demonstration Made By Mute";
        NesBus = std::make_shared<Bus>();
    }
    
    bool OnUserCreate()  // Call Engine Start Thread
    {
        cart = std::make_shared<Cartridge>("rom/Ice Climber (U).nes");
        
        NesBus->InsertCartridge(cart);
        

        // if you play with those, then IRQ, NMI Vector Need To Set
        AssemblyLog = NesBus->GetProcessor()->Disassemble(0x0000, 0xFFFF);
        
        NesBus->GetProcessor()->ResetInterrupt();
        return true;
            
    }
    
    bool OnUserUpdate(float fElapsedTime) // Update Call
    {
        auto Processor = NesBus->GetProcessor();

        Clear(BLACK);

        NesBus->GetController(0) = 0x00;
        NesBus->GetController(0) |= GetKey(Key::X).bHeld ? 0x80 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::Z).bHeld ? 0x40 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::A).bHeld ? 0x20 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::S).bHeld ? 0x10 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::UP).bHeld ? 0x08 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::DOWN).bHeld ? 0x04 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::LEFT).bHeld ? 0x02 : 0x00;
        NesBus->GetController(0) |= GetKey(Key::RIGHT).bHeld ? 0x01 : 0x00;

        if (GetKey(Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;
        if (GetKey(Key::R).bPressed) NesBus->Reset();
        if (GetKey(Key::P).bPressed)
        {
            (++SelectedPalette) &= 0x07;
        }

        if (bEmulationRun)
        {
            if (fResidualTime > 0.0f)
                fResidualTime -= fElapsedTime;
            else
            {
                fResidualTime += (1.0f / 60.0f) - fElapsedTime;
                do { NesBus->Clock(); } while (!NesBus->GetPictureProcessor()->FrameComplete);
                NesBus->GetPictureProcessor()->FrameComplete = false;
            }
        }
        else
        {
            if (GetKey(Key::C).bPressed)
            {
                do
                {
                    NesBus->Clock();
                } while (!Processor->Complete());

                do
                {
                    NesBus->Clock();
                } while (Processor->Complete());
            }

            // Emulate one whole frame
            if (GetKey(Key::F).bPressed)
            {
                // Clock enough times to draw a single frame
                do { NesBus->Clock(); } while (!NesBus->GetPictureProcessor()->FrameComplete);
                // Use residual clock cycles to complete current instruction
                do { NesBus->Clock(); } while (!Processor->Complete());
                // Reset frame completion flag
                NesBus->GetPictureProcessor()->FrameComplete = false;
            }
        }

        DrawProcessorStatus(516, 2);
        // DrawCode(516, 72, 26);

        // Draw OAM Contents (first 26 out of 64) ======================================
        for (int i = 0; i < 26; i++)
        {
            std::string s = hex(i, 2) + ": (" + std::to_string(NesBus->GetPictureProcessor()->GetOAMPointer()[i * 4 + 3])
                + ", " + std::to_string(NesBus->GetPictureProcessor()->GetOAMPointer()[i * 4 + 0]) + ") "
                + "ID: " + hex(NesBus->GetPictureProcessor()->GetOAMPointer()[i * 4 + 1], 2) +
                +" AT: " + hex(NesBus->GetPictureProcessor()->GetOAMPointer()[i * 4 + 2], 2);
            DrawString(516, 72 + i * 10, s);
        }


        const int WatchSize = 6;
        for (int p = 0; p < 8; ++p)
        {
            for (int s = 0; s < 4; ++s)
            {
                FillRect(516 + p * (WatchSize * 5) + s * WatchSize,
                    340, WatchSize, WatchSize, NesBus->GetPictureProcessor()->GetColorFromPalette(p, s));
            }
        }

        DrawRect(516 + SelectedPalette * (WatchSize * 5) - 1, 339, (WatchSize * 4), WatchSize, WHITE);
  

        DrawSprite(516, 348, &NesBus->GetPictureProcessor()->GetPatternTable(0, SelectedPalette));
        DrawSprite(648, 348, &NesBus->GetPictureProcessor()->GetPatternTable(1, SelectedPalette));

        DrawSprite(0, 0, &NesBus->GetPictureProcessor()->GetScreen(), 2);

        return true;
        
    }
    std::string hex(uint32_t n, uint8_t d)
    {
        std::string s(d, '0');
        for (int i = d - 1; i >= 0; i--, n >>= 4)
            s[i] = "0123456789ABCDEF"[n & 0xF];
        return s;
    }
    
    void DrawProcessorStatus(int x, int y)
    {
        auto Processor = NesBus->GetProcessor();
        std::string status = "STATUS : ";
        
        
        DrawString(x , y , "STATUS:", WHITE);
        DrawString(x  + 64, y, "N", Processor->StatusRegister & (int)Processor::Flag::Negative ? GREEN : RED);
        DrawString(x  + 80, y , "V", Processor->StatusRegister & (int)Processor::Flag::Overflow ? GREEN : RED);
        DrawString(x  + 96, y , "-", Processor->StatusRegister & (int)Processor::Flag::UnUsed ? GREEN : RED);
        DrawString(x  + 112, y , "B", Processor->StatusRegister & (int)Processor::Flag::Break ? GREEN : RED);
        DrawString(x  + 128, y , "D", Processor->StatusRegister & (int)Processor::Flag::Decimal ? GREEN : RED);
        DrawString(x  + 144, y , "I", Processor->StatusRegister & (int)Processor::Flag::DisableInterrupt ? GREEN : RED);
        DrawString(x  + 160, y , "Z", Processor->StatusRegister & (int)Processor::Flag::Zero ? GREEN : RED);
        DrawString(x  + 178, y , "C", Processor->StatusRegister & (int)Processor::Flag::CarryBit ? GREEN : RED);
        DrawString(x , y + 10, "Program Counter: $" + hex(Processor->ProgramCounter, 4));
        DrawString(x , y + 20, "A: $" +  hex(Processor->Accumulator, 2) + "  [" + std::to_string(Processor->Accumulator) + "]");
        DrawString(x , y + 30, "X: $" +  hex(Processor->XRegister, 2) + "  [" + std::to_string(Processor->XRegister) + "]");
        DrawString(x , y + 40, "Y: $" +  hex(Processor->YRegister, 2) + "  [" + std::to_string(Processor->YRegister) + "]");
        DrawString(x , y + 50, "Stack P: $" + hex(Processor->StackPtr, 4));
    }
    
    
    void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
    {
        int nRamX = x, nRamY = y;
        for (int row = 0; row < nRows; row++)
        {
            std::string sOffset = "$" + hex(nAddr, 4) + ":";
            for (int col = 0; col < nColumns; col++)
            {
                sOffset += " " + hex(NesBus->CpuRead(nAddr, true), 2);
                nAddr += 1;
            }
            DrawString(nRamX, nRamY, sOffset);
            nRamY += 10;
        }
    }
    
    void DrawCode(int x, int y, int nLines)
    {
        auto Processor = NesBus->GetProcessor();
        
        auto it_a = AssemblyLog.find(Processor->ProgramCounter);
        int nLineY = (nLines >> 1) * 10 + y;
        if (it_a != AssemblyLog.end())
        {
            DrawString(x, nLineY, (*it_a).second, CYAN);
            while (nLineY < (nLines * 10) + y)
            {
                nLineY += 10;
                if (++it_a != AssemblyLog.end())
                {
                    DrawString(x, nLineY, (*it_a).second);
                }
            }
        }

        it_a = AssemblyLog.find(Processor->ProgramCounter);
        nLineY = (nLines >> 1) * 10 + y;
        if (it_a != AssemblyLog.end())
        {
            while (nLineY > y)
            {
                nLineY -= 10;
                if (--it_a != AssemblyLog.end())
                {
                    DrawString(x, nLineY, (*it_a).second);
                }
            }
        }
    }
};


int main(int argc, const char * argv[]) {

    std::cout << "Loading Graphic User Interface .......";

    DebugProcessor debug;
    debug.Construct(780, 480, 2, 2);
    debug.Start();
  
    // if you want console debug, use this..!
  //  while (1) { std::this_thread::yield(); }
    return 0;
}
