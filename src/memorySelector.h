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

/// \file      memorySelector.h
///
/// \brief     <brief description>
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      25-10-2018

#ifndef MEMORYSELECTOR_H_
#define MEMORYSELECTOR_H_

#include "periodic.h"

#include <array>

#include "config.h"

#include "mmu.h"
#include "cartridge.h"

class MemorySelector : public Periodic
{
public:
    MemorySelector(std::array<uint8_t, GBConfig::sysMemSize>& memory,
                   Mmu& mmu,
                   const Cartridge& cartridge) :
        m_memory(memory),
        m_mmu(mmu), m_cartridge(cartridge)
    {
    }

    void run() override;

private:
    std::array<uint8_t,
               GBConfig::sysMemSize>& m_memory;  ///< Representation of the console's memory.
    Mmu& m_mmu;                                  ///< Memory management unit.
    const Cartridge& m_cartridge;  ///< Representation of the console's game cartridge.
};

#endif /* MEMORYSELECTOR_H_ */
