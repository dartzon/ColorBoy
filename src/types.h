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

/// \file      types.h
///
/// \brief     <brief description>
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      02-11-2018

#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include <utility>

#include "utils.h"

/// \brief Starting addresses of the Game Boy's internal memory's sections.
enum MemoryAreas : uint16_t
{
    eMEMADDR_rombank0start = 0x0000,
    eMEMADDR_cartridgeheaderstart = 0x0100,
    eMEMADDR_rombank1start = 0x4000,
    eMEMADDR_vrambank0start = 0x8000,
    eMEMADDR_wrambank0start = 0xC000,
    eMEMADDR_echoramstart = 0xE000,
    eMEMADDR_oamstart = 0xFE00,
    eMEMADDDR_unusedramstart = 0xFEA0,
    eMEMADDR_ioregsstart = 0xFF00,
    eMEMADDR_zeropagestart = 0xFF80,
    eMEMADDR_eireg = 0xFFFF
};

/// \brief Sizes of the different fixed areas in the Game Boy's internal memory.
enum MemoryAreasSizes : uint16_t
{
    eMEMSIZE_rombank0 = cbutil::toByteValue(units::data::kibibyte_t(16)),
    eMEMSIZE_rombank1 = cbutil::toByteValue(units::data::kibibyte_t(16)),
    eMEMSIZE_vram = cbutil::toByteValue(units::data::kibibyte_t(8)),
    eMEMSIZE_wram = cbutil::toByteValue(units::data::kibibyte_t(4)),
    eMEMSIZE_echo = 7680,     ///< Echo RAM : 7.68 KB.
    eMEMSIZE_oam = 160,       ///< Sprite attribute table.
    eMEMSIZE_unused = 96,     ///< Not Usable.
    eMEMSIZE_ioregs = 128,    ///< I/O registers.
    eMEMSIZE_zeropage = 127,  ///< Zero Page (HRAM : High RAM).
    eMEMSIZE_iereg = 1        ///< Interrupts Enable Register.
};

/// \brief List of hardware IO registers' addresses.
enum HardwareIORegisters : uint16_t
{
    eIOREG_scrolly = 0xFF42,
    eIOREG_scrollx,
    eIOREG_if = 0xFF0F,    ///< Interrupt Flags (R/W).
    eIOREG_lcdc = 0xFF40,  ///< LCD Control (R/W).
    eIOREG_stat = 0xFF41,  ///< LCD Status (R/W).
    eIOREG_scy = 0xFF42,   ///< BG Scroll Y (R/W).
    eIOREG_scx = 0xFF43,   ///< BG Scroll X (R/W).
    eIOREG_ly = 0xFF44,    ///< LCD Current Scanline (R).
    eIOREG_lyc = 0xFF45,   ///< LY Compare (R/W).
    eIOREG_wy = 0xFF4A,    ///< Window Y Position (R/W).
    eIOREG_wx = 0xFF4B,    ///< Window X Position (R/W).
    eIOREG_romswitch = 0xFF50
};

/// \brief Adresses of the Game Boy's interrupts.
enum InterruptAddresses : uint16_t
{
    eINTADDR_vblank = 0x0040,   ///< V-Blank interrupt.
    eINTADDR_lcdstat = 0x0048,  ///< LCD STAT interrupt.
    eINTADDR_timer = 0x0050,    ///< Timer interrupt.
    eINTADDR_serial = 0x0058,   ///< Serial interrupt.
    eINTADDR_joypad = 0x0060    ///< Joypad interrupt.
};

/// \brief LCD's periods timing in number of clock cycles.
enum LCDTiming : uint16_t
{
    eLCDTIME_scanlineoam = 80,
    eLCDTIME_pixeltransfer = 172,
    eLCDTIME_hblank = 204,
    eLCDTIME_onelinerender = eLCDTIME_scanlineoam + eLCDTIME_pixeltransfer + eLCDTIME_hblank,
    eLCDTIME_vblank = eLCDTIME_onelinerender * 10
};

/// \brief Used to represent pixels coordinates on the screen.
struct Coordinate
{
    Coordinate(const uint8_t _x = 0, const uint8_t _y = 0) : x(_x), y(_y) {}

    uint8_t x;
    uint8_t y;
};

#endif /* TYPES_H_ */
