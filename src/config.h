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

/// \file      config.h
///
/// \brief     Global variables and emulator's configuration values.
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      18-05-2018

#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstdint>

// From Nintendo's website:
// +---------------------------+---------------------------+------------------------+
// | Game Boy                  | Game Boy Pocket           | Game Boy Color         |
// +---------------------------+---------------------------+------------------------+
// | Arch: 8 Bit               | Arch: 8 Bit               | Arch: 8 Bit            |
// | Clock frequency: 4.19 MHz | Clock frequency: 4.19 MHz | Clock frequency: 8 MHz |
// | RAM: 8 Kbytes             | RAM: 8 Kbytes             | RAM: 32 Kbytes         |
// +---------------------------+---------------------------+------------------------+

/// \brief Game Boy type.
enum class GBType : uint8_t
{
    GBT_gb = 0,  ///< Original Game Boy (GameBoy Classic).
    GBT_gbp,     ///< Game Boy Pocket/GameBoy Light.
    GBT_gbc      ///< Game Boy Color.
};

/// \brief Emulator's configuration.
struct GBConfig
{
    /// \brief Constructor.
    ///
    /// \param type The represented Game Boy type.
    ///
    GBConfig(const GBType type)
    {
        switch (type)
        {
        case GBType::GBT_gb:
        case GBType::GBT_gbp:
            clockFrequency = 4;
            wRAMSize = 8;
            vRAMSize = 8;
            break;

        case GBType::GBT_gbc:
            clockFrequency = 8;
            wRAMSize = 32;
            vRAMSize = 16;
            break;
        }
    }

    static constexpr uint32_t sysMemSize = 65536;  ///< Gameboy CPU has 16-bit address bus (2^16).
    mutable uint8_t clockFrequency;                ///< CPU clock frequency.
    mutable uint8_t wRAMSize;                      ///< Working ram size.
    mutable uint8_t vRAMSize;                      ///< Video ram size.
};

#endif /* CONFIG_H_ */
