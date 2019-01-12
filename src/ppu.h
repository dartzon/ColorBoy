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

/// \file      ppu.h
///
/// \brief     <brief description>
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      12-11-2018

#ifndef PPU_H_
#define PPU_H_

#include "mmu.h"

#include "lcd.h"

// PPU timing:
// ---------------
// OAM search: 80 cycles.
// Pixel transfer: 172 cycles.
// H-Blank: 204 cycles.

class Ppu
{
public:
    explicit Ppu(Mmu& mmu) :
        m_mmu(mmu), m_lastCPUCycle(0), m_currentScanLine(0),
        m_screenMode(ScreenMode::eSCREENMODE_oamsearch)
    {
        printf("OAM mode\n");
    }

    /// \brief Run the PPU for one cycle.
    ///
    /// \param currentCPUCycle the current CPU cycle.
    void cycle(const uint32_t currentCPUCycle);

private:
    /// \brief Switch the PPU to its next state.
    void switchState();

    void scanOAM(const uint32_t currentCPUCycle);
    void transferPixels(const uint32_t currentCPUCycle);
    void enterHBlankPeriod(const uint32_t currentCPUCycle);
    void enterVBlankPeriod(const uint32_t currentCPUCycle);

    enum class ScreenMode : uint8_t
    {
        eSCREENMODE_hblank = 0,
        eSCREENMODE_vblank = 1,
        eSCREENMODE_oamsearch = 2,
        eSCREENMODE_lcdtransfer = 3
    };

    Mmu& m_mmu;                 ///< Memory management unit.
    uint32_t m_lastCPUCycle;    ///< Last CPU cycle where the PPU processed data.
    uint8_t m_currentScanLine;  ///< Current horizontal line from 0 to 153.
    ScreenMode m_screenMode;    ///< Current operating mode of the screen.
};

#endif /* PPU_H_ */
