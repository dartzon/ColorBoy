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
    m_cpuCycleState(InstructionCycleState::eCYCLE_fetch), m_unfinishedLastOp(false),
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
    if (m_inPrefixCBOp == false)
    {
        m_opLength = m_opsLengths[IR];
    }
    else
    {
        // Prefix CB instructions are all 1 byte long.
        m_opLength = 1;
    }

    // Save the current address pointer by PC.
    m_currentInstructionAddr = PC;

    // Advance PC to point to the next instruction in memory.
    PC += m_opLength;

    switchState();
}

// =================================================================================================

void Cpu::decode()
{
    if (m_unfinishedLastOp == false)
    {
        if (m_opLength > 1)
        {
            MBR[0] = fetchByteFromAddress(m_currentInstructionAddr + 1);
            m_unfinishedLastOp = true;

            return;
        }
        else
        {
            // Fetch the instruction's data (if any) from memory to MBR.
            for (uint8_t pos = 0; pos < m_opLength - 1; ++pos)
            {
                MBR[0] = fetchByteFromAddress(m_currentInstructionAddr + pos + 1);
            }
        }
    }
    else
    {
        MBR[1] = fetchByteFromAddress(m_currentInstructionAddr + 2);
        m_unfinishedLastOp = false;
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
    const InstructionCycleState lastCpuCycleState = m_cpuCycleState;
    switch (m_cpuCycleState)
    {
    case InstructionCycleState::eCYCLE_checkint: checkForInterrupts(); break;
    case InstructionCycleState::eCYCLE_fetch: fetch(); break;
    case InstructionCycleState::eCYCLE_decode: decode(); break;
    case InstructionCycleState::eCYCLE_execute: execute(); break;
    case InstructionCycleState::eCYCLE_stop: waitForInterrupt(); break;
    }

    // There must be an operation which took more that one CPU cycle.
    if (m_unfinishedLastOp == true)
    {
        m_cpuCycleState = lastCpuCycleState;
    }

    if (m_cpuCycles == GBConfig::clockFrequency)
    {
        m_cpuCycles = 0;
        exit(404);
    }
    m_cpuCycles += 4;

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

    return byte;
}

// =================================================================================================

void Cpu::loadByteToAddress(const uint8_t data, const uint16_t addr)
{
    m_mmu.writeByte(data, addr);
}
