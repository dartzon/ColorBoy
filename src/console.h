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

#include "config.h"
#include "mmu.h"
#include "cpu.h"

/// \brief MemoryType definition
typedef std::array<uint8_t, GBConfig::sysMemSize> MemoryType;

/// \brief Representation of a Game Boy console with its internal components.
class Console
{
public:
    /// \brief Constructor.
    ///
    /// \param type The Game Boy type to emulate.
    Console(const GBType type) : config(type), m_cpu(m_mmu), m_mmu(m_memory) {}
    
    /// \brief getMemory
    ///
    /// dirty and direct access to internal memory
    MemoryType& getMemory() {
        return m_memory;
    }
    
    ///\ brief Run previously loaded program in console
    void run() {
        //very basic implementation; may need interruptions handling
        while(true){
            m_cpu.run();
        }
    }
    
    /// \brief Run one instruction
    void runOnce(){
        m_cpu.run();
    }
    
private:
    GBConfig config;  ///< Console's configuration.
    Cpu m_cpu;        ///< Console's CPU.
    Mmu m_mmu;        ///< Console's Memory management unit.

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
    MemoryType m_memory;  ///< Console's RAM (64KB memory system).
};

#endif /* CONSOLE_H_ */
