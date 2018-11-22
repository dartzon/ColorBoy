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

/// \file      cartridge.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      27-10-2018

// Local includes.
#include "cartridge.h"

#include <algorithm>

Cartridge::Cartridge(const std::filesystem::path& cartPath)
{
    parseROMFile(cartPath);
}

// =================================================================================================

void Cartridge::parseROMFile(const std::filesystem::path& cartPath)
{
    namespace fs = std::filesystem;

    if ((fs::exists(cartPath) == true) && (fs::is_regular_file(cartPath) == true))
    {
        const std::uintmax_t romSize = fs::file_size(cartPath);
        m_ROMBanks.resize(romSize);

        {
            std::unique_ptr<FILE, decltype(&fclose)> smtROMFile(
                std::fopen(static_cast<const std::string>(cartPath).c_str(), "rb"), &fclose);
            fread(m_ROMBanks.data(), romSize, 1, smtROMFile.get());
        }
    }
}

// =================================================================================================

void Cartridge::extractROMInfo()
{
    CBLOG("Parsing the Cartridge data...");

    // *********************************************************************************************

    CBLOG("Read the Cartridge's title");
    m_cartInfo.m_title = std::string(reinterpret_cast<const char*>(&m_ROMBanks[0x0134]),
                                     0x0143 - 0x0134);

    // *********************************************************************************************

    CBLOG("Read the Cartridge's Game Boy compatibility");
    const uint8_t cgbFlag = m_ROMBanks[0x0143];
    if (cgbFlag == 0x80)
    {
        m_cartInfo.m_GBCOnly = false;
    }
    else if (cgbFlag == 0xC0)
    {
        m_cartInfo.m_GBCOnly = true;
    }

    // *********************************************************************************************

    CBLOG("Check if the Cartridge has a battery");
    const uint8_t cartType = m_ROMBanks[0x0147];
    switch (cartType)
    {
    case 0x03:
    case 0x06:
    case 0x09:
    case 0x0D:
    case 0x0F:
    case 0x10:
    case 0x13:
    case 0x17:
    case 0x1B:
    case 0x1E:
    case 0xFF: m_cartInfo.m_hasBattery = true; break;

    default: m_cartInfo.m_hasBattery = false;
    }

    // *********************************************************************************************

    CBLOG("Read the Cartridge's ROM size");
    const uint8_t romType = m_ROMBanks[0x0148];
    if (romType >= 0 && romType <= 8)
    {
        // 32KB << Val @ 0x0148.
        m_cartInfo.m_romSize = cbutil::toByteValue(32_KiB) << romType;
        m_cartInfo.m_romBanksCount = m_cartInfo.m_romSize / cbutil::toByteValue(32_KiB);
    }
    else
    {
        switch (romType)
        {
        case 0x52:  // 1.1MB.
            m_cartInfo.m_romSize = cbutil::toByteValue(1.1_MiB);
            m_cartInfo.m_romBanksCount = 72;
            break;
        case 0x53:  // 1.2MB.
            m_cartInfo.m_romSize = cbutil::toByteValue(1.2_MiB);
            m_cartInfo.m_romBanksCount = 80;
            break;
        case 0x54:  // 1.5MB.
            m_cartInfo.m_romSize = cbutil::toByteValue(1.5_MiB);
            m_cartInfo.m_romBanksCount = 96;
            break;
        }
    }

    // *********************************************************************************************

    CBLOG("Read the Cartridge's RAM size");
    switch (m_ROMBanks[0x0149])
    {
    case 0: m_cartInfo.m_ramSize = 0; break;                             // None.
    case 1: m_cartInfo.m_ramSize = cbutil::toByteValue(2_KiB); break;    // 2KB.
    case 2: m_cartInfo.m_ramSize = cbutil::toByteValue(8_KiB); break;    // 8KB.
    case 3: m_cartInfo.m_ramSize = cbutil::toByteValue(32_KiB); break;   // 32KB.
    case 4: m_cartInfo.m_ramSize = cbutil::toByteValue(128_KiB); break;  // 128KB.
    case 5: m_cartInfo.m_ramSize = cbutil::toByteValue(64_KiB); break;   // 64KB.
    }
    m_cartInfo.m_ramBanksCount = m_cartInfo.m_ramSize / cbutil::toByteValue(8_KiB);
    m_RAMBanks.reserve(m_cartInfo.m_ramBanksCount);

    CBLOG("Parsing finished!");
}
