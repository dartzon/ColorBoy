/// Copyright (c) 2018 - present    Othmane AIT EL CADI <dartzon@gmail.com>
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

/// \file      ppu.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      19-11-2018

// Local includes.
#include "ppu.h"

#include <thread>

void Ppu::cycle(const uint32_t currentCPUCycle)
{
    printf(">>> Line %u\tCPU Cycle %u\t",
           m_currentScanLine,
           (currentCPUCycle - m_lastCPUCycle) / 4);

    switch (m_screenMode)
    {
    case ScreenMode::eSCREENMODE_oamsearch:
        printf("Scanline OAM\n");
        scanOAM(currentCPUCycle);
        break;
    case ScreenMode::eSCREENMODE_lcdtransfer:
        printf("Scanline LCD transfer\n");
        transferPixels(currentCPUCycle);
        break;
    case ScreenMode::eSCREENMODE_hblank:
        printf("H-Blank\n");
        enterHBlankPeriod(currentCPUCycle);
        break;
    case ScreenMode::eSCREENMODE_vblank:
        printf("V-Blank\n");
        enterVBlankPeriod(currentCPUCycle);
        break;
    }
}

// =================================================================================================

void Ppu::switchState()
{
    switch (m_screenMode)
    {
    case ScreenMode::eSCREENMODE_oamsearch:

        m_screenMode = ScreenMode::eSCREENMODE_lcdtransfer;
        break;
    case ScreenMode::eSCREENMODE_lcdtransfer: m_screenMode = ScreenMode::eSCREENMODE_hblank; break;
    case ScreenMode::eSCREENMODE_hblank:
        if (m_currentScanLine != 144)
        {
            m_screenMode = ScreenMode::eSCREENMODE_oamsearch;
        }
        else
        {
            m_screenMode = ScreenMode::eSCREENMODE_vblank;
        }
        break;
    case ScreenMode::eSCREENMODE_vblank: m_screenMode = ScreenMode::eSCREENMODE_oamsearch; break;
    }
}

// =================================================================================================

void Ppu::scanOAM(const uint32_t currentCPUCycle)
{
    m_mmu.writeByte(m_currentScanLine, HardwareIORegisters::eIOREG_ly);

    if (((currentCPUCycle - m_lastCPUCycle) / 4) == LCDTiming::eLCDTIME_scanlineoam)
    {
        m_lastCPUCycle = currentCPUCycle;
        switchState();
    }
}

// =================================================================================================

void Ppu::transferPixels(const uint32_t currentCPUCycle)
{
    if (((currentCPUCycle - m_lastCPUCycle) / 4) == LCDTiming::eLCDTIME_pixeltransfer)
    {
        m_lastCPUCycle = currentCPUCycle;
        switchState();
    }
}

// =================================================================================================

void Ppu::enterHBlankPeriod(const uint32_t currentCPUCycle)
{
    if (((currentCPUCycle - m_lastCPUCycle) / 4) == LCDTiming::eLCDTIME_hblank)
    {
        m_lastCPUCycle = currentCPUCycle;

        ++m_currentScanLine;

        switchState();
    }
}

// =================================================================================================

void Ppu::enterVBlankPeriod(const uint32_t currentCPUCycle)
{
    // if (((currentCPUCycle - m_lastCPUCycle) / 4) == LCDTiming::eLCDTIME_vblank)
    if ((((currentCPUCycle - m_lastCPUCycle) / 4) % LCDTiming::eLCDTIME_onelinerender) == 0)
    {
        m_lastCPUCycle = currentCPUCycle;
        ++m_currentScanLine;
    }

    if (m_currentScanLine > 153)
    {
        m_lastCPUCycle = currentCPUCycle;
        m_currentScanLine = 0;

        switchState();
    }
}
