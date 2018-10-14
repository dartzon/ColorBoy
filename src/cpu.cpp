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

// Local includes.
#include "utils.h"

Cpu::Cpu(Mmu& mmu) :
    A(m_registers[1]), B(m_registers[3]), C(m_registers[2]), D(m_registers[5]), E(m_registers[4]),
    F(m_registers[0]), H(m_registers[7]), L(m_registers[6]), AF(reinterpret_cast<uint16_t&>(F)),
    BC(reinterpret_cast<uint16_t&>(C)), DE(reinterpret_cast<uint16_t&>(E)),
    HL(reinterpret_cast<uint16_t&>(L)), SP(*reinterpret_cast<uint16_t*>(&H + 8)),
    PC(*reinterpret_cast<uint16_t*>(&H + 24)), m_mmu(mmu), m_interruptsEnabled(true),
    m_inPrefixCBOp(false)
{
    PC = 0x0;
}

// =================================================================================================

void Cpu::waitForInterrupt()
{
}

// =================================================================================================

void Cpu::fetch()
{
    // Fetch the next instruction from memory into IR.
    IR = fetchNextByte();
    // Get the length of the fetched instruction.
    const uint8_t opLength = m_opsLengths[IR];

    // Save the current address pointer by PC.
    m_currentInstructionAddr = PC;

    // Advance PC to point to the next instruction in memory.
    PC += opLength;

    switchState(InstructionCycleState::eDecode);
}

// =================================================================================================

void Cpu::decode()
{
    // Get the length of the current instruction.
    const uint8_t opLength = m_opsLengths[IR];

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
        MBR[0] = fetchByteFromAddress(cbutil::combineTowBytes(MBR[1], MBR[0]));
        break;
    }

    switchState();
}

// =================================================================================================

void Cpu::execute()
{
    // Call the current CPU instruction's method.
    m_opsFunctions[IR]();

    switchState();
}

// =================================================================================================

void Cpu::switchState()
{
    switch (m_cpuCycleState)
    {
    case InstructionCycleState::eFetch: m_cpuCycleState = InstructionCycleState::eDecode; break;
    case InstructionCycleState::eDecode: m_cpuCycleState = InstructionCycleState::eExecute; break;
    case InstructionCycleState::eExecute:
    case InstructionCycleState::eStop: m_cpuCycleState = InstructionCycleState::eFetch; break;
    }
}

// =================================================================================================

void Cpu::switchState(const InstructionCycleState state)
{
    m_cpuCycleState = state;
}

// =================================================================================================

void Cpu::run()
{
    switch (m_cpuCycleState)
    {
    case InstructionCycleState::eStop: waitForInterrupt(); break;
    case InstructionCycleState::eFetch: fetch(); break;
    case InstructionCycleState::eDecode: decode(); break;
    case InstructionCycleState::eExecute: execute(); break;
    }
}

// =================================================================================================

uint8_t Cpu::fetchNextByte()
{
    const uint8_t byte = m_mmu.readByte(PC);
    m_cpuCycles += 4;

    return byte;
}

// =================================================================================================

uint8_t Cpu::fetchByteFromAddress(const uint16_t addr)
{
    const uint8_t byte = m_mmu.readByte(addr);
    m_cpuCycles += 4;

    return byte;
}

// =================================================================================================

void Cpu::loadByteToAddress(const uint16_t addr, const uint8_t data)
{
    m_mmu.writeByte(addr, data);
}

// =================================================================================================

void Cpu::loadWordToAddress(const uint16_t addr, const uint16_t data)
{
    m_mmu.writeWord(addr, data);
}
