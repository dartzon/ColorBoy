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

#include <cstdint>
#include <array>

#include "config.h"

/// \brief Representation of a Memory management unit.
class Mmu
{
public:
    /// \brief Constructor.
    ///
    /// \param memory std::array representing the Game Boy's internal memory.
    explicit Mmu(std::array<uint8_t, GBConfig::sysMemSize>& memory) : m_memory(memory) {}

    /// \brief Read byte from memory address.
    ///
    /// \param address Memory address to read from.
    ///
    /// \return Byte located at the given address.
    uint8_t readByte(const uint16_t address) const;

    /// \brief Read word from memory address.
    ///
    /// \param address Memory address to read from.
    ///
    /// \return Word located at the given address.
    uint16_t readWord(const uint16_t address) const;

    /// \brief Write byte to memory address.
    ///
    /// \param address Memory address to write into.
    /// \param byte Value to write.
    void writeByte(const uint16_t address, const uint8_t byte);

    /// \brief Write word to memory address.
    ///
    /// \param address Memory address to write into
    /// \param word Value to write.
    void writeWord(const uint16_t address, const uint16_t word);

private:
    std::array<uint8_t, GBConfig::sysMemSize>&
        m_memory;  ///< Representation of the console's memory.
};

#endif /* MMU_H_ */
