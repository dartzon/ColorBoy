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

/// \file      console.h
///
/// \brief     Representation of the whole console (Config + CPU + Memory, etc...).
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      19-05-2018

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "types.h"
#include "mmu.h"
#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"

#include <filesystem>

/// \brief Representation of a Game Boy console with its internal components.
class Console
{
public:
    /// \brief Constructor.
    ///
    /// \param type Game Boy's type to emulate.
    /// \param cartPath path to the game ROM file.
    Console(const GBType type, const std::filesystem::path& cartPath);

    /// \brief Power on the console.
    void powerOn();

private:
    Mmu m_mmu;             ///< Console's Memory management unit.
    Cpu m_cpu;             ///< Console's CPU.
    Ppu m_ppu;             ///< Console's PPU.
    Cartridge m_gameCart;  ///< Game cartridge.
    bool m_poweredOn;      ///< Is the console powered on?

    // =============================================================================================
    //   General Memory Map:
    //
    // 0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
    // 4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
    // 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
    // A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
    // C000-CFFF   4KB Work RAM Bank 0 (WRAM)
    // D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
    // E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
    // FE00-FE9F   Sprite Attribute Table (OAM)
    // FEA0-FEFF   Not Usable
    // FF00-FF7F   I/O Ports
    // FF80-FFFE   High RAM (HRAM)
    // FFFF        Interrupt Enable Register
    // =============================================================================================
    std::array<uint8_t, GBConfig::fixedMemSize> m_fixedMemory;  ///< Fixed part of the GB's memory.
    std::vector<uint8_t> m_VRAMBanks;                           ///< VRAM banks.
    std::vector<uint8_t> m_WRAMBanks;                           ///< WRAM banks.
};

#endif /* CONSOLE_H_ */
