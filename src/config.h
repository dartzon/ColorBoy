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

/// \file      config.h
///
/// \brief     Global variables and emulator's configuration values.
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      18-05-2018

#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstdint>

#include "utils.h"
#include "types.h"

// From Nintendo's website:
// +---------------------------+---------------------------+--------------------------+
// | Game Boy                  | Game Boy Pocket           | Game Boy Color           |
// +---------------------------+---------------------------+--------------------------+
// | Arch: 8 Bit               | Arch: 8 Bit               | Arch: 8 Bit              |
// | Clock frequency: 4.19 MHz | Clock frequency: 4.19 MHz | Clock frequency: 8.4 MHz |
// | RAM: 8 Kbytes             | RAM: 8 Kbytes             | RAM: 32 Kbytes           |
// +---------------------------+---------------------------+--------------------------+

/// \brief The Game Boy's type.
enum class GBType : uint8_t
{
    eGBTYPE_dmg,
    eGBTYPE_sgb,
    eGBTYPE_mgb,
    eGBTYPE_cgb
};

/// \brief Emulator's configuration.
struct GBConfig
{
    static const uint32_t memorySize = cbutil::toByteValue(
        units::data::kibibyte_t(64));  ///< Gameboy CPU has 16-bit address bus (2^16).
    static uint32_t clockFrequency;    ///< CPU clock frequency in Hz.

    ///< Size of the fixed parts of the Game Boy's memory.
    static const uint16_t fixedMemSize = MemoryAreasSizes::eMEMSIZE_echo +
                                         MemoryAreasSizes::eMEMSIZE_oam +
                                         MemoryAreasSizes::eMEMSIZE_unused +
                                         MemoryAreasSizes::eMEMSIZE_ioregs +
                                         MemoryAreasSizes::eMEMSIZE_zeropage +
                                         MemoryAreasSizes::eMEMSIZE_iereg;

    static const Coordinate lcdResolution;  ///< The Game Boy LCD is 160x144 pixels.
    static uint16_t vRAMSize;               ///< Video ram size in Byte.
    static uint16_t wRAMSize;               ///< Working ram size in Byte.
};

#endif /* CONFIG_H_ */
