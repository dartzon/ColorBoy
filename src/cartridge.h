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

#include <array>
#include <vector>
#include <memory>
#include <filesystem>

using namespace units::literals;
namespace dataunit = units::data;

class Cartridge
{
public:
    /// \brief Constructor.
    ///
    /// \param cartPath path to the game ROM file.
    Cartridge(const std::filesystem::path& cartPath);

    enum : uint16_t
    {
        eROMBankSize = cbutil::toByteValue(16_KiB)  ///< Each individual Rom Bank is 16KB long.
    };

    auto getROMBank(const uint8_t bankNum)
    {
        CBASSERT((bankNum * eROMBankSize) < m_ROMBanks.size(),
                 "Invalid Cartridge's ROM bank selection");

        using RomBanksIter = decltype(m_ROMBanks.begin());
        return (std::make_pair<RomBanksIter, RomBanksIter>(m_ROMBanks.begin() +
                                                               (bankNum * (eROMBankSize + 1)),
                                                           m_ROMBanks.begin() +
                                                               (bankNum * eROMBankSize) +
                                                               eROMBankSize));
    }

    struct CartridgeInfo;

    const CartridgeInfo& getCartInfo() const { return m_cartInfo; }

    struct CartridgeInfo
    {
    private:
        CartridgeInfo() {}

    public:
        std::string m_title;
        bool m_GBCOnly;
        bool m_hasBattery;

        uint32_t m_romSize;
        uint32_t m_ramSize;

        uint8_t m_romBanksCount;
        uint8_t m_ramBanksCount;

        friend class Cartridge;
    };

private:
    /// \brief Read the game ROM file.
    ///
    /// \param cartPath path to the game ROM file.
    void parseROMFile(const std::filesystem::path& cartPath);

    /// \brief Extract the ROM's info from its header.
    void extractROMInfo();

    std::vector<uint8_t> m_ROMBanks;
    std::vector<uint8_t> m_RAMBanks;

    CartridgeInfo m_cartInfo;
};

#endif /* CARTRIDGE_H_ */
