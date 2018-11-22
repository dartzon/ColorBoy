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

/// \file      cpu.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      17-05-2018

// Local includes.
#include "cpu.h"

// std includes.
#include <type_traits>
#include <chrono>
#include <ctime>
#include <thread>

// Local includes.
#include "utils.h"

Cpu::Cpu(Mmu& mmu) :
    A(m_registers[1]), B(m_registers[3]), C(m_registers[2]), D(m_registers[5]), E(m_registers[4]),
    F(m_registers[0]), H(m_registers[7]), L(m_registers[6]), AF(reinterpret_cast<uint16_t&>(F)),
    BC(reinterpret_cast<uint16_t&>(C)), DE(reinterpret_cast<uint16_t&>(E)),
    HL(reinterpret_cast<uint16_t&>(L)), SP(reinterpret_cast<uint16_t&>(m_registers[8])),
    PC(reinterpret_cast<uint16_t&>(m_registers[10])), IME(true), m_mmu(mmu),
    m_cpuCycleState(InstructionCycleState::eCYCLE_fetch), m_lastOpFinished(true),
    m_inPrefixCBOp(false)
{
    // Initialize the PC register to the start of the Game Boy's memory.
    PC = MemoryAreas::eMEMADDR_rombank0start;

    // Map the CPU's ROM to the internal memory at address 0x0.
    m_mmu.mapDataBufferToMemory(m_CPUROM, MemoryAreas::eMEMADDR_rombank0start);
}

// =================================================================================================

bool Cpu::checkForInterrupts()
{
    const std::bitset<8> interruptFlagsReg(m_mmu.readByte(HardwareIORegisters::eIOREG_if) & 0x1F);
    const std::bitset<8> interruptEnableReg(m_mmu.readByte(MemoryAreas::eMEMADDR_eireg) & 0x1F);

    const uint16_t oldPC = PC;

    if (IME == true)
    {
        if ((interruptFlagsReg == true) && (interruptEnableReg == true))
        {
            if ((interruptFlagsReg.to_ulong() == 0x01) && (interruptEnableReg.to_ulong() == 0x01))
            {
                // LCD V-Blank interrupt.

                execPUSH(PC);

                PC = InterruptAddresses::eINTADDR_vblank;
            }

            if ((interruptFlagsReg.to_ulong() == 0x02) && (interruptEnableReg.to_ulong() == 0x02))
            {
                // LCD stat interrupt.

                execPUSH(PC);

                PC = InterruptAddresses::eINTADDR_lcdstat;
            }

            if ((interruptFlagsReg.to_ulong() == 0x04) && (interruptEnableReg.to_ulong() == 0x04))
            {
                // Timer interrupt.

                execPUSH(PC);

                PC = InterruptAddresses::eINTADDR_timer;
            }

            if ((interruptFlagsReg.to_ulong() == 0x08) && (interruptEnableReg.to_ulong() == 0x08))
            {
                // Serial interrupt.

                execPUSH(PC);

                PC = InterruptAddresses::eINTADDR_serial;
            }

            if ((interruptFlagsReg.to_ulong() == 0x10) && (interruptEnableReg.to_ulong() == 0x10))
            {
                // Joypad interrupt.

                execPUSH(PC);

                PC = InterruptAddresses::eINTADDR_joypad;
            }
        }
    }

    switchState();

    return oldPC != PC;
}

// =================================================================================================

void Cpu::waitForInterrupt()
{
    while (checkForInterrupts() == false)
    {
    }
}

// =================================================================================================

void Cpu::fetch()
{
    // Fetch the next instruction from memory into IR.
    IR = fetchNextByte();

    // Get the length of the fetched instruction.
    uint8_t opLength = 0;
    if (m_inPrefixCBOp == false)
    {
        opLength = m_opsLengths[IR];
    }
    else
    {
        // Prefix CB instructions are all 1 byte long.
        opLength = 1;
    }

    // Save the current address pointer by PC.
    m_currentInstructionAddr = PC;

    // Advance PC to point to the next instruction in memory.
    PC += opLength;

    switchState();
}

// =================================================================================================

void Cpu::decode()
{
    // Get the length of the current instruction.
    const uint8_t opLength = m_opsLengths[IR];

    if (m_opLength > 1)
    {
    }
    else
    {
        m_lastOpFinished = true;
    }

    // Fetch the instruction's data (if any) from memory to MBR.
    for (uint8_t pos = 0; pos < opLength - 1; ++pos)
    {
        MBR[pos] = fetchByteFromAddress(m_currentInstructionAddr + pos + 1);
    }

    // Check if indirect memory operation on right hand operand.
    // 0A
    // 1A
    // 2A
    // 34 35 3A
    // 46 4E
    // 56 5E
    // 66 6E
    // 7E
    // 86 8E
    // 96 9E
    // A6 AE
    // B6 BE
    // E9
    // F0 F2 FA

    switch (IR)
    {
    case 0x0A:
    case 0x1A:
    case 0x2A:
    case 0x34:
    case 0x35:
    case 0x3A:
    case 0x46:
    case 0x4E:
    case 0x56:
    case 0x5E:
    case 0x66:
    case 0x6E:
    case 0x7E:
    case 0x86:
    case 0x8E:
    case 0x96:
    case 0x9E:
    case 0xA6:
    case 0xAE:
    case 0xB6:
    case 0xBE:
    case 0xE9:
    case 0xF0:
    case 0xF2:
    case 0xFA:
        // Fetch data from the memory address stored in MBR.
        MBR[0] = fetchByteFromAddress(cbutil::combineTwoBytes(MBR[0], MBR[1]));
        break;
    }

    switchState();
}

// =================================================================================================

void Cpu::execute()
{
    // Call the current CPU instruction's method.

    if (m_inPrefixCBOp == false)
    {
        m_opsFunctions[IR]();
    }
    else
    {
        m_inPrefixCBOp = false;
        m_opsPrefixCBFunctions[IR]();
    }

    switchState();
}

// =================================================================================================

void Cpu::switchState()
{
    switch (m_cpuCycleState)
    {
    case InstructionCycleState::eCYCLE_checkint:
        m_cpuCycleState = InstructionCycleState::eCYCLE_fetch;
        break;
    case InstructionCycleState::eCYCLE_fetch:
        m_cpuCycleState = InstructionCycleState::eCYCLE_decode;
        break;
    case InstructionCycleState::eCYCLE_decode:
        m_cpuCycleState = InstructionCycleState::eCYCLE_execute;
        break;
    case InstructionCycleState::eCYCLE_execute:
    case InstructionCycleState::eCYCLE_stop:
        m_cpuCycleState = InstructionCycleState::eCYCLE_checkint;
        break;
    }
}

// =================================================================================================

void Cpu::switchState(const InstructionCycleState state)
{
    m_cpuCycleState = state;
}

// =================================================================================================

bool Cpu::cycle()
{
    // std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    // start = std::chrono::high_resolution_clock::now();

    switch (m_cpuCycleState)
    {
    case InstructionCycleState::eCYCLE_checkint: checkForInterrupts(); break;
    case InstructionCycleState::eCYCLE_fetch: fetch(); break;
    case InstructionCycleState::eCYCLE_decode: decode(); break;
    case InstructionCycleState::eCYCLE_execute: execute(); break;
    case InstructionCycleState::eCYCLE_stop: waitForInterrupt(); break;
    }

    // end = std::chrono::high_resolution_clock::now();

    // std::chrono::duration<double, std::nano> timeSpentInTick = end - start;

    // using namespace std::chrono_literals;
    // const std::chrono::duration<double> oneCPUTick(954ns);

    // if (m_cpuCycles == 4)
    // {
    //     const std::chrono::duration<double, std::nano> total = oneCPUTick - timeSpentInTick;

    //     printf(">>>>>>>> Elapsed time: %f\tCompensation: %f\t",
    //            timeSpentInTick.count(),
    //            total.count());

    //     start = std::chrono::high_resolution_clock::now();
    //     std::this_thread::sleep_for(1s);

    //     // ==============================

    //     end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double, std::nano> timeSpentInTick2 = end - start;

    //     printf("One frame takes : %f\n", timeSpentInTick2.count());

    //     // ==============================

    //     m_cpuCycles = 0;
    // }

    // m_cpuCycles += 4;

    return true;
}

// =================================================================================================

uint8_t Cpu::fetchNextByte()
{
    return fetchByteFromAddress(PC);
}

// =================================================================================================

uint8_t Cpu::fetchByteFromAddress(const uint16_t addr)
{
    const uint8_t byte = m_mmu.readByte(addr);
    m_cpuCycles += 4;

    return byte;
}

// =================================================================================================

void Cpu::loadByteToAddress(const uint8_t data, const uint16_t addr)
{
    m_mmu.writeByte(data, addr);
    m_cpuCycles += 4;
}

// =================================================================================================

void Cpu::loadWordToAddress(const uint16_t data, const uint16_t addr)
{
    m_mmu.writeWord(data, addr);
    m_cpuCycles += 8;
}
