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

/// \file      cartridge.h
///
/// \brief     <brief description>
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      25-10-2018

#ifndef CARTRIDGE_H_
#define CARTRIDGE_H_

#include "config.h"

#include <vector>

class Cartridge
{
public:
    Cartridge(const std::vector<uint8_t>& ROM) : m_ROM(std::move(ROM)) {}

    const std::vector<uint8_t>& getROM() const { return m_ROM; }

private:
    const std::vector<uint8_t> m_ROM;
    std::vector<uint8_t> m_extRAM;
};

#endif /* CARTRIDGE_H_ */
