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

/// \file      console.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      21-10-2018

// Local includes.
#include "console.h"

#include "config.h"

#include <cstdio>
#include <memory>
#include <algorithm>
#include <numeric>

uint32_t GBConfig::clockFrequency;
const Coordinate GBConfig::lcdResolution(160, 144);
uint16_t GBConfig::vRAMSize;
uint16_t GBConfig::wRAMSize;

Console::Console(const GBType type, const std::filesystem::path& cartPath) :
    m_cpu(m_mmu), m_ppu(m_mmu), m_gameCart(cartPath), m_poweredOn(false)
{
    // Create the console's configuration.
    namespace freq = units::frequency;
    switch (type)
    {
    case GBType::eGBTYPE_dmg:
    case GBType::eGBTYPE_sgb:
    case GBType::eGBTYPE_mgb:
        GBConfig::clockFrequency = cbutil::toHzValue(freq::megahertz_t(4.194304));
        GBConfig::vRAMSize = MemoryAreasSizes::eMEMSIZE_vram;
        GBConfig::wRAMSize = MemoryAreasSizes::eMEMSIZE_wram;
        break;

    case GBType::eGBTYPE_cgb:
        GBConfig::clockFrequency = cbutil::toHzValue(freq::megahertz_t(8.4));
        GBConfig::vRAMSize = MemoryAreasSizes::eMEMSIZE_vram * 2;
        GBConfig::wRAMSize = MemoryAreasSizes::eMEMSIZE_wram * 8;
        break;
    }

    m_VRAMBanks.resize(GBConfig::vRAMSize);
    m_WRAMBanks.resize(GBConfig::wRAMSize);
}

// =================================================================================================

void Console::powerOn()
{
    // Map the fixed part of the memory into the Game Boy's internal memory.
    m_mmu.mapDataBufferToMemory(m_fixedMemory, MemoryAreas::eMEMADDR_echoramstart);
    // Map VRAM Bank 0 into the Game Boy's internal memory.
    m_mmu.mapDataBufferToMemory(m_VRAMBanks, MemoryAreas::eMEMADDR_vrambank0start);
    // Map WRAM Bank 0 into the Game Boy's internal memory.
    m_mmu.mapDataBufferToMemory(m_WRAMBanks, MemoryAreas::eMEMADDR_wrambank0start);

    // Writing 0 to 0xFF50 maps the CPU's internal ROM to the address 0x0000.
    m_mmu.writeByte(0x0, HardwareIORegisters::eIOREG_romswitch);

    auto cartROMBank0 = m_gameCart.getROMBank(0);
    m_mmu.mapDataBufferToMemory(cartROMBank0.first + MemoryAreas::eMEMADDR_cartridgeheaderstart,
                                cartROMBank0.second,
                                MemoryAreas::eMEMADDR_cartridgeheaderstart);

    m_poweredOn = true;

    while ((m_poweredOn == true) && (m_cpu.cycle() == true))
    {
        m_ppu.cycle(m_cpu.getCurrentCPUCycle());
    }
}

// =================================================================================================

void readCartridgeROM(const std::filesystem::path& cartPath)
{
    namespace fs = std::filesystem;

    if ((fs::exists(cartPath) == true) && (fs::is_regular_file(cartPath) == true))
    {
        const std::uintmax_t romSize = fs::file_size(cartPath);
        std::unique_ptr<uint8_t[]> smtROM = std::make_unique<uint8_t[]>(romSize);

        {
            std::unique_ptr<FILE, decltype(&fclose)> smtROMFile(
                std::fopen(static_cast<const std::string>(cartPath).c_str(), "rb"), &fclose);
            fread(smtROM.get(), romSize, 1, smtROMFile.get());
        }

        // Read the Nintendo Logo:
        printf("Nintendo Logo:\n");
        for (uint16_t idx = 0x0104, count = 1; idx <= 0x0133; ++idx, ++count)
        {
            printf("%02X ", smtROM[idx]);
            if ((count % 16) == 0)
            {
                printf("\n");
                count = 0;
            }
        }

        printf("\n");

        // Read the cartridge's title:
        printf("Title:\n");
        for (uint16_t idx = 0x0134, count = 1; idx <= 0x0143; ++idx, ++count)
        {
            if (smtROM[idx] == 0x0)
            {
                break;
            }
            printf("%c", smtROM[idx]);
        }
        printf("\n\n");

        // Read the manufacturer code:
        printf("Manufacturer Code:\n");
        for (uint16_t idx = 0x013F, count = 1; idx <= 0x0142; ++idx, ++count)
        {
            printf("%c", smtROM[idx]);
        }
        printf("\n\n");

        // Read the CGB Flag:
        printf("CGB Flag:\n");
        const uint8_t cgbFlag = smtROM[0x0143];
        printf("%02X\n", cgbFlag);
        if (cgbFlag == 0x80)
        {
            printf("\tWorks on GB and CGB\n");
        }
        else if (cgbFlag == 0xC0)
        {
            printf("\tWorks on CGB only\n");
        }
        printf("\n");

        // Read the new licensee code:
        printf("New Licensee Code:\n");
        const char chr1 = smtROM[0x0144];
        const char chr2 = smtROM[0x0145];
        std::string newLicCode(2, '\0');
        newLicCode = chr1;
        newLicCode += chr2;
        printf("%s\n", newLicCode.c_str());
        if (newLicCode == "00")
        {
            printf("\tNone\n");
        }
        else if (newLicCode == "01")
        {
            printf("\tNintendo R&D1\n");
        }
        else if (newLicCode == "08")
        {
            printf("\tCapcom\n");
        }
        else if (newLicCode == "13")
        {
            printf("\tElectronic Arts\n");
        }
        else if (newLicCode == "18")
        {
            printf("\tHudson Soft\n");
        }
        else if (newLicCode == "19")
        {
            printf("\tb-ai\n");
        }
        else if (newLicCode == "20")
        {
            printf("\tkss\n");
        }
        else if (newLicCode == "22")
        {
            printf("\tpow\n");
        }
        else if (newLicCode == "24")
        {
            printf("\tPCM Complete\n");
        }
        else if (newLicCode == "25")
        {
            printf("\tsan-x\n");
        }
        else if (newLicCode == "28")
        {
            printf("\tKemco Japan\n");
        }
        else if (newLicCode == "29")
        {
            printf("\tseta\n");
        }
        else if (newLicCode == "30")
        {
            printf("\tViacom\n");
        }
        else if (newLicCode == "31")
        {
            printf("\tNintendo\n");
        }
        else if (newLicCode == "32")
        {
            printf("\tBandai\n");
        }
        else if (newLicCode == "33")
        {
            printf("\tOcean/Acclaim\n");
        }
        else if (newLicCode == "34")
        {
            printf("\tKonami\n");
        }
        else if (newLicCode == "35")
        {
            printf("\tHector\n");
        }
        else if (newLicCode == "37")
        {
            printf("\tTaito\n");
        }
        else if (newLicCode == "38")
        {
            printf("\tHudson\n");
        }
        else if (newLicCode == "39")
        {
            printf("\tBanpresto\n");
        }
        else if (newLicCode == "41")
        {
            printf("\tUbi Soft\n");
        }
        else if (newLicCode == "42")
        {
            printf("\tAtlus\n");
        }
        else if (newLicCode == "44")
        {
            printf("\tMalibu\n");
        }
        else if (newLicCode == "46")
        {
            printf("\tangel\n");
        }
        else if (newLicCode == "47")
        {
            printf("\tBullet-Proof\n");
        }
        else if (newLicCode == "49")
        {
            printf("\tirem\n");
        }
        else if (newLicCode == "50")
        {
            printf("\tAbsolute\n");
        }
        else if (newLicCode == "51")
        {
            printf("\tAcclaim\n");
        }
        else if (newLicCode == "52")
        {
            printf("\tActivision\n");
        }
        else if (newLicCode == "53")
        {
            printf("\tAmerican sammy\n");
        }
        else if (newLicCode == "54")
        {
            printf("\tKonami\n");
        }
        else if (newLicCode == "55")
        {
            printf("\tHi tech entertainment\n");
        }
        else if (newLicCode == "56")
        {
            printf("\tLJN\n");
        }
        else if (newLicCode == "57")
        {
            printf("\tMatchbox\n");
        }
        else if (newLicCode == "58")
        {
            printf("\tMattel\n");
        }
        else if (newLicCode == "59")
        {
            printf("\tMilton Bradley\n");
        }
        else if (newLicCode == "60")
        {
            printf("\tTitus\n");
        }
        else if (newLicCode == "61")
        {
            printf("\tVirgin\n");
        }
        else if (newLicCode == "64")
        {
            printf("\tLucasArts\n");
        }
        else if (newLicCode == "67")
        {
            printf("\tOcean\n");
        }
        else if (newLicCode == "69")
        {
            printf("\tElectronic Arts\n");
        }
        else if (newLicCode == "70")
        {
            printf("\tInfogrames\n");
        }
        else if (newLicCode == "71")
        {
            printf("\tInterplay\n");
        }
        else if (newLicCode == "72")
        {
            printf("\tBroderbund\n");
        }
        else if (newLicCode == "73")
        {
            printf("\tsculptured\n");
        }
        else if (newLicCode == "75")
        {
            printf("\tsci\n");
        }
        else if (newLicCode == "78")
        {
            printf("\tTHQ\n");
        }
        else if (newLicCode == "79")
        {
            printf("\tAccolade\n");
        }
        else if (newLicCode == "80")
        {
            printf("\tmisawa\n");
        }
        else if (newLicCode == "83")
        {
            printf("\tlozc\n");
        }
        else if (newLicCode == "86")
        {
            printf("\ttokuma shoten i*\n");
        }
        else if (newLicCode == "87")
        {
            printf("\ttsukuda ori*\n");
        }
        else if (newLicCode == "91")
        {
            printf("\tChunsoft\n");
        }
        else if (newLicCode == "92")
        {
            printf("\tVideo system\n");
        }
        else if (newLicCode == "93")
        {
            printf("\tOcean/Acclaim\n");
        }
        else if (newLicCode == "95")
        {
            printf("\tVarie\n");
        }
        else if (newLicCode == "96")
        {
            printf("\tYonezawa/s'pal\n");
        }
        else if (newLicCode == "97")
        {
            printf("\tKaneko\n");
        }
        else if (newLicCode == "99")
        {
            printf("\tPack in soft\n");
        }
        else if (newLicCode == "A4")
        {
            printf("\tKonami (Yu-Gi-Oh!)\n");
        }
        printf("\t\n");

        // Read the SGB flag:
        printf("SGB Flag:\n");
        const uint8_t sgbFlag = smtROM[0x0146];
        printf("%02X\n", sgbFlag);
        if (sgbFlag == 0x00)
        {
            printf("\tWorks on GB and CGB only\n");
        }
        else if (sgbFlag == 0x03)
        {
            printf("\tWorks on GB, CGB and SGB\n");
        }
        printf("\n");

        // Read the cartridge type:
        printf("Cartridge Type:\n");
        const uint8_t cartType = smtROM[0x0147];
        switch (cartType)
        {
        case 0x00: printf("ROM ONLY\n"); break;
        case 0x01: printf("MBC1\n"); break;
        case 0x02: printf("MBC1+RAM\n"); break;
        case 0x03: printf("MBC1+RAM+BATTERY\n"); break;
        case 0x05: printf("MBC2\n"); break;
        case 0x06: printf("MBC2+BATTERY\n"); break;
        case 0x08: printf("ROM+RAM\n"); break;
        case 0x09: printf("ROM+RAM+BATTERY\n"); break;
        case 0x0B: printf("MMM01\n"); break;
        case 0x0C: printf("MMM01+RAM\n"); break;
        case 0x0D: printf("MMM01+RAM+BATTERY\n"); break;
        case 0x0F: printf("MBC3+TIMER+BATTERY\n"); break;
        case 0x10: printf("MBC3+TIMER+RAM+BATTERY\n"); break;
        case 0x11: printf("MBC3\n"); break;
        case 0x12: printf("MBC3+RAM\n"); break;
        case 0x13: printf("MBC3+RAM+BATTERY\n"); break;
        case 0x15: printf("MBC4\n"); break;
        case 0x16: printf("MBC4+RAM\n"); break;
        case 0x17: printf("MBC4+RAM+BATTERY\n"); break;
        case 0x19: printf("MBC5\n"); break;
        case 0x1A: printf("MBC5+RAM\n"); break;
        case 0x1B: printf("MBC5+RAM+BATTERY\n"); break;
        case 0x1C: printf("MBC5+RUMBLE\n"); break;
        case 0x1D: printf("MBC5+RUMBLE+RAM\n"); break;
        case 0x1E: printf("MBC5+RUMBLE+RAM+BATTERY\n"); break;
        case 0xFC: printf("POCKET CAMERA\n"); break;
        case 0xFD: printf("BANDAI TAMA5\n"); break;
        case 0xFE: printf("HuC3\n"); break;
        case 0xFF: printf("HuC1+RAM+BATTERY\n"); break;
        }
        printf("\n");

        // Read the ROM size:
        printf("ROM Size:\n");
        const uint8_t _romSize = smtROM[0x0148];
        switch (_romSize)
        {
        case 0x00: printf("32KByte (no ROM banking)\n"); break;
        case 0x01: printf("64KByte (4 banks)\n"); break;
        case 0x02: printf("128KByte (8 banks)\n"); break;
        case 0x03: printf("256KByte (16 banks)\n"); break;
        case 0x04: printf("512KByte (32 banks)\n"); break;
        case 0x05: printf("1MByte (64 banks)  - only 63 banks used by MBC1\n"); break;
        case 0x06: printf("2MByte (128 banks) - only 125 banks used by MBC1\n"); break;
        case 0x07: printf("4MByte (256 banks)\n"); break;
        case 0x52: printf("1.1MByte (72 banks)\n"); break;
        case 0x53: printf("1.2MByte (80 banks)\n"); break;
        case 0x54: printf("1.5MByte (96 banks)\n"); break;
        }
        printf("\n");

        // Read the RAM size:
        printf("RAM Size:\n");
        const uint8_t ramSize = smtROM[0x0149];
        switch (ramSize)
        {
        case 0x00: printf("None\n"); break;
        case 0x01: printf("2 KBytes\n"); break;
        case 0x02: printf("8 KBytes\n"); break;
        case 0x03: printf("32 KBytes (4 banks of 8KBytes each)\n"); break;
        }
        printf("\n");

        // Read the destination code:
        printf("Destination Code:\n");
        const uint8_t destCode = smtROM[0x014A];
        printf("%02X\n", destCode);
        if (destCode == 0x00)
        {
            printf("\tJapanese\n");
        }
        else if (destCode == 0x01)
        {
            printf("\tNon-Japanese\n");
        }
        printf("\n");

        // Read the old licensee code:
        printf("Old License Code:\n");
        const uint8_t oldLicCode = smtROM[0x014B];
        switch (oldLicCode)
        {
        case 0x00: printf("\tnone\n"); break;
        case 0x01: printf("\tnintendo\n"); break;
        case 0x08: printf("\tcapcom\n"); break;
        case 0x09: printf("\thot-b\n"); break;
        case 0x0A: printf("\tjaleco\n"); break;
        case 0x0B: printf("\tcoconuts\n"); break;
        case 0x0C: printf("\telite systems\n"); break;
        case 0x13: printf("\telectronic arts\n"); break;
        case 0x18: printf("\thudsonsoft\n"); break;
        case 0x19: printf("\titc entertainment\n"); break;
        case 0x1A: printf("\tyanoman\n"); break;
        case 0x1D: printf("\tclary\n"); break;
        case 0x1F: printf("\tvirgin\n"); break;
        case 0x24: printf("\tpcm complete\n"); break;
        case 0x25: printf("\tsan-x\n"); break;
        case 0x28: printf("\tkotobuki systems\n"); break;
        case 0x29: printf("\tseta\n"); break;
        case 0x30: printf("\tinfogrames\n"); break;
        case 0x31: printf("\tnintendo\n"); break;
        case 0x32: printf("\tbandai\n"); break;
        case 0x33: printf("\tUses New License Code\n"); break;
        case 0x34: printf("\tkonami\n"); break;
        case 0x35: printf("\thector\n"); break;
        case 0x38: printf("\tcapcom\n"); break;
        case 0x39: printf("\tbanpresto\n"); break;
        case 0x3C: printf("\t*entertainment i\n"); break;
        case 0x3E: printf("\tgremlin\n"); break;
        case 0x41: printf("\tubi soft\n"); break;
        case 0x42: printf("\tatlus\n"); break;
        case 0x44: printf("\tmalibu\n"); break;
        case 0x46: printf("\tangel\n"); break;
        case 0x47: printf("\tspectrum holoby\n"); break;
        case 0x49: printf("\tirem\n"); break;
        case 0x4A: printf("\tvirgin\n"); break;
        case 0x4D: printf("\tmalibu\n"); break;
        case 0x4F: printf("\tu.s. gold\n"); break;
        case 0x50: printf("\tabsolute\n"); break;
        case 0x51: printf("\tacclaim\n"); break;
        case 0x52: printf("\tactivision\n"); break;
        case 0x53: printf("\tamerican sammy\n"); break;
        case 0x54: printf("\tgametek\n"); break;
        case 0x55: printf("\tpark place\n"); break;
        case 0x56: printf("\tljn\n"); break;
        case 0x57: printf("\tmatchbox\n"); break;
        case 0x59: printf("\tmilton bradley\n"); break;
        case 0x5A: printf("\tmindscape\n"); break;
        case 0x5B: printf("\tromstar\n"); break;
        case 0x5C: printf("\tnaxat soft\n"); break;
        case 0x5D: printf("\ttradewest\n"); break;
        case 0x60: printf("\ttitus\n"); break;
        case 0x61: printf("\tvirgin\n"); break;
        case 0x67: printf("\tocean\n"); break;
        case 0x69: printf("\telectronic arts\n"); break;
        case 0x6E: printf("\telite systems\n"); break;
        case 0x6F: printf("\telectro brain\n"); break;
        case 0x70: printf("\tinfogrames\n"); break;
        case 0x71: printf("\tinterplay\n"); break;
        case 0x72: printf("\tbroderbund\n"); break;
        case 0x73: printf("\tsculptered soft\n"); break;
        case 0x75: printf("\tthe sales curve\n"); break;
        case 0x78: printf("\tt*hq\n"); break;
        case 0x79: printf("\taccolade\n"); break;
        case 0x7A: printf("\ttriffix entertainment\n"); break;
        case 0x7C: printf("\tmicroprose\n"); break;
        case 0x7F: printf("\tkemco\n"); break;
        case 0x80: printf("\tmisawa entertainment\n"); break;
        case 0x83: printf("\tlozc\n"); break;
        case 0x86: printf("\ttokuma shoten intermedia\n"); break;
        case 0x8B: printf("\tbullet-proof software\n"); break;
        case 0x8C: printf("\tvic tokai\n"); break;
        case 0x8E: printf("\tape\n"); break;
        case 0x8F: printf("\ti'max\n"); break;
        case 0x91: printf("\tchun soft\n"); break;
        case 0x92: printf("\tvideo system\n"); break;
        case 0x93: printf("\ttsuburava\n"); break;
        case 0x95: printf("\tvarie\n"); break;
        case 0x96: printf("\tyonezawa/s'pal\n"); break;
        case 0x97: printf("\tkaneko\n"); break;
        case 0x99: printf("\tarc\n"); break;
        case 0x9A: printf("\tnihon bussan\n"); break;
        case 0x9B: printf("\ttecmo\n"); break;
        case 0x9C: printf("\timagineer\n"); break;
        case 0x9D: printf("\tbanpresto\n"); break;
        case 0x9F: printf("\tnova\n"); break;
        case 0xA1: printf("\thori electric\n"); break;
        case 0xA2: printf("\tbandai\n"); break;
        case 0xA4: printf("\tkonami\n"); break;
        case 0xA6: printf("\tkawada\n"); break;
        case 0xA7: printf("\ttakara\n"); break;
        case 0xA9: printf("\ttechnos japan\n"); break;
        case 0xAA: printf("\tbroderbund\n"); break;
        case 0xAC: printf("\ttoei animation\n"); break;
        case 0xAD: printf("\ttoho\n"); break;
        case 0xAF: printf("\tnamco\n"); break;
        case 0xB0: printf("\tacclaim\n"); break;
        case 0xB1: printf("\tascii or nexoft\n"); break;
        case 0xB2: printf("\tbandai\n"); break;
        case 0xB4: printf("\tenix\n"); break;
        case 0xB6: printf("\thal\n"); break;
        case 0xB7: printf("\tsnk\n"); break;
        case 0xB9: printf("\tpony canyon\n"); break;
        case 0xBA: printf("\t*culture brain o\n"); break;
        case 0xBB: printf("\tsunsoft\n"); break;
        case 0xBD: printf("\tsony imagesoft\n"); break;
        case 0xBF: printf("\tsammy\n"); break;
        case 0xC0: printf("\ttaito\n"); break;
        case 0xC2: printf("\tkemco\n"); break;
        case 0xC3: printf("\tsquaresoft\n"); break;
        case 0xC4: printf("\ttokuma shoten intermedia\n"); break;
        case 0xC5: printf("\tdata east\n"); break;
        case 0xC6: printf("\ttonkin house\n"); break;
        case 0xC8: printf("\tkoei\n"); break;
        case 0xC9: printf("\tufl\n"); break;
        case 0xCA: printf("\tultra\n"); break;
        case 0xCB: printf("\tvap\n"); break;
        case 0xCC: printf("\tuse\n"); break;
        case 0xCD: printf("\tmeldac\n"); break;
        case 0xCE: printf("\t*pony canyon or\n"); break;
        case 0xCF: printf("\tangel\n"); break;
        case 0xD0: printf("\ttaito\n"); break;
        case 0xD1: printf("\tsofel\n"); break;
        case 0xD2: printf("\tquest\n"); break;
        case 0xD3: printf("\tsigma enterprises\n"); break;
        case 0xD4: printf("\task kodansha\n"); break;
        case 0xD6: printf("\tnaxat soft\n"); break;
        case 0xD7: printf("\tcopya systems\n"); break;
        case 0xD9: printf("\tbanpresto\n"); break;
        case 0xDA: printf("\ttomy\n"); break;
        case 0xDB: printf("\tljn\n"); break;
        case 0xDD: printf("\tncs\n"); break;
        case 0xDE: printf("\thuman\n"); break;
        case 0xDF: printf("\taltron\n"); break;
        case 0xE0: printf("\tjaleco\n"); break;
        case 0xE1: printf("\ttowachiki\n"); break;
        case 0xE2: printf("\tuutaka\n"); break;
        case 0xE3: printf("\tvarie\n"); break;
        case 0xE5: printf("\tepoch\n"); break;
        case 0xE7: printf("\tathena\n"); break;
        case 0xE8: printf("\tasmik\n"); break;
        case 0xE9: printf("\tnatsume\n"); break;
        case 0xEA: printf("\tking records\n"); break;
        case 0xEB: printf("\tatlus\n"); break;
        case 0xEC: printf("\tepic/sony records\n"); break;
        case 0xEE: printf("\tigs\n"); break;
        case 0xF0: printf("\ta wave\n"); break;
        case 0xF3: printf("\textreme entertainment\n"); break;
        case 0xFF: printf("\tljn\n"); break;
        }
        printf("\n");

        // Read the ROM version number:
        printf("ROM Version number:\n");
        const uint8_t romVersion = smtROM[0x014C];
        printf("%02X\n\n", romVersion);

        // Compute the header checksum:
        printf("Header Checksum:\n");
        const uint32_t headerChecksum = std::accumulate(smtROM.get() + 0x0134,
                                                        smtROM.get() + 0x014C + 1,
                                                        0,
                                                        [](const uint32_t a, const uint32_t b) {
                                                            return a - b - 1;
                                                        });
        printf("Computed       : %X\n", headerChecksum);
        printf("Value @ 0x014D : %02X\n", smtROM[0x014D]);
        if (smtROM[0x014D] == (headerChecksum & 0xFF))
        {
            printf("Checksum OK\n");
        }
        else
        {
            printf("Checksum NOT OK\n");
        }
        printf("\n\n");

        // Read the global checksum:
        printf("Global Checksum:\n");
        const uint16_t globalChecksum = cbutil::combineTwoBytes(smtROM[0x014E], smtROM[0x014F]);
        printf("%04X\n", globalChecksum);
    }
}
