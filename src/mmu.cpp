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

/// \file      mmu.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      20-05-2018

// Local includes.
#include "mmu.h"

uint8_t Mmu::readByte(const uint16_t address) const
{
    if ((address >= 0) && (address <= m_memory.size() - 1))
    {
        return m_memory[address];
    }

    return 0;
}

// =================================================================================================

uint16_t Mmu::readWord(const uint16_t address) const
{
    if ((address >= 0) && (address <= m_memory.size() - 1))
    {
        return m_memory[address] | (m_memory[address + 1] << 8);
    }

    return 0;
}

// =================================================================================================

void Mmu::writeByte(const uint16_t address, const uint8_t byte)
{
    if ((address >= 0) && (address <= m_memory.size() - 1))
    {
        m_memory[address] = byte;
    }
}

// =================================================================================================

void Mmu::writeWord(const uint16_t address, const uint16_t word)
{
    if ((address >= 0) && (address <= m_memory.size() - 1))
    {
        m_memory[address] = word & 0xFF;
        m_memory[address + 1] = word >> 8;
    }
}
