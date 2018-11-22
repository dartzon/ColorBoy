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

/// \file      mmu.h
///
/// \brief     Representation of a memory management unit.
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      20-05-2018

#ifndef MMU_H_
#define MMU_H_

#include <array>
#include <algorithm>

#include "config.h"

/// \brief Representation of a Memory management unit.
class Mmu
{
public:
    /// \brief Read byte from memory address.
    ///
    /// \param address Memory address to read from.
    ///
    /// \return Byte located at the given address.
    uint8_t readByte(const uint16_t address) const
    {
        CBASSERT((address >= 0) && (address <= m_memoryMap.size() - 1),
                 "Out of bounds memory read");

        return *m_memoryMap[address];
    }

    /// \brief Read word from memory address.
    ///
    /// \param address Memory address to read from.
    ///
    /// \return Word located at the given address.
    uint16_t readWord(const uint16_t address) const
    {
        CBASSERT((address >= 0) && (address <= m_memoryMap.size() - 1),
                 "Out of bounds memory read");

        return cbutil::combineTwoBytes(*m_memoryMap[address], *m_memoryMap[address + 1]);
    }

    /// \brief Write byte to memory address.
    ///
    /// \param byte Value to write.
    /// \param address Memory address to write into.
    void writeByte(const uint8_t byte, const uint16_t address)
    {
        CBASSERT((address >= 0) && (address <= m_memoryMap.size() - 1),
                 "Out of bounds memory write");

        *m_memoryMap[address] = byte;
    }

    /// \brief Write word to memory address.
    ///
    /// \param word Value to write.
    /// \param address Memory address to write into
    void writeWord(const uint16_t word, const uint16_t address)
    {
        CBASSERT((address >= 0) && (address <= m_memoryMap.size() - 1),
                 "Out of bounds memory write");

        *m_memoryMap[address] = word & 0xFF;
        *m_memoryMap[address + 1] = word >> 8;
    }

    /// \brief Map data from a buffer to the internal RAM.
    ///
    /// \param buffer buffer to map.
    /// \param startAddr start address where the data should be copied to.
    template<typename Container>
    void mapDataBufferToMemory(Container& buffer, const uint16_t startAddr)
    {
        for (size_t idx = 0; idx < buffer.size(); ++idx)
        {
            m_memoryMap[startAddr + idx] = &buffer[idx];
        }
    }

    template<class InputIt>
    void mapDataBufferToMemory(InputIt first, InputIt last, const uint16_t startAddr)
    {
        const size_t memSize = std::distance(first, last);
        for (size_t idx = 0; idx < memSize; ++idx)
        {
            m_memoryMap[startAddr + idx] = &(*(first + idx));
        }
    }

private:
    std::array<uint8_t*, GBConfig::memorySize> m_memoryMap;
};

#endif /* MMU_H_ */
