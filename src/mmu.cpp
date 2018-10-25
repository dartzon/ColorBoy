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

#include "utils.h"

uint8_t Mmu::readByte(const uint16_t address) const
{
    CBASSERT((address >= 0) && (address <= m_memory.size() - 1), "Out of bounds memory read");

    // Handle reading from the echo RAM.
    uint16_t offset = 0x0;
    if ((address >= MemoryAreas::eEchoRAMStart) && (address <= MemoryAreas::eEchoRAMEnd))
    {
        offset = 0x2000;
    }

    return m_memory[address - offset];
}

// =================================================================================================

uint16_t Mmu::readWord(const uint16_t address) const
{
    CBASSERT((address >= 0) && (address <= m_memory.size() - 1), "Out of bounds memory read");

    // Handle reading from the echo RAM.
    uint16_t offset = 0x0;
    if ((address >= MemoryAreas::eEchoRAMStart) && (address <= MemoryAreas::eEchoRAMEnd))
    {
        offset = 0x2000;
    }

    return cbutil::combineTwoBytes(m_memory[address - offset], m_memory[address + 1 - offset]);
}

// =================================================================================================

void Mmu::writeByte(const uint8_t byte, const uint16_t address)
{
    CBASSERT((address >= 0) && (address <= m_memory.size() - 1), "Out of bounds memory write");

    // Handle writing to the echo RAM.
    uint16_t offset = 0x0;
    if ((address >= MemoryAreas::eEchoRAMStart) && (address <= MemoryAreas::eEchoRAMEnd))
    {
        offset = 0x2000;
    }

    m_memory[address - offset] = byte;
}

// =================================================================================================

void Mmu::writeWord(const uint16_t word, const uint16_t address)
{
    CBASSERT((address >= 0) && (address <= m_memory.size() - 1), "Out of bounds memory write");

    // Handle writing to the echo RAM.
    uint16_t offset = 0x0;
    if ((address >= MemoryAreas::eEchoRAMStart) && (address <= MemoryAreas::eEchoRAMEnd))
    {
        offset = 0x2000;
    }

    m_memory[address - offset] = word & 0xFF;
    m_memory[address + 1 - offset] = word >> 8;
}
