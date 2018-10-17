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

/// \file      cpuPrefixCBOps.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      14-10-2018

// Local includes.
#include "cpu.h"

#include "utils.h"

void Cpu::op_RLC_B()
{
    // Save bit 7.
    const bool bit7 = ((B & 0x80) == 0x80);
    B <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_C()
{
    // Save bit 7.
    const bool bit7 = ((C & 0x80) == 0x80);
    C <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_D()
{
    // Save bit 7.
    const bool bit7 = ((D & 0x80) == 0x80);
    D <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_E()
{
    // Save bit 7.
    const bool bit7 = ((E & 0x80) == 0x80);
    E <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_H()
{
    // Save bit 7.
    const bool bit7 = ((H & 0x80) == 0x80);
    H <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_L()
{
    // Save bit 7.
    const bool bit7 = ((L & 0x80) == 0x80);
    L <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    // Save bit 7.
    const bool bit7 = ((byte & 0x80) == 0x80);
    byte <<= 1;
    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RLC_A()
{
    // Save bit 7.
    const bool bit7 = ((A & 0x80) == 0x80);
    A <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_B()
{
    const bool bit0 = ((B & 0x01) == 0x01);
    B >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_C()
{
    const bool bit0 = ((C & 0x01) == 0x01);
    C >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_D()
{
    const bool bit0 = ((D & 0x01) == 0x01);
    D >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_E()
{
    const bool bit0 = ((E & 0x01) == 0x01);
    E >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_H()
{
    const bool bit0 = ((H & 0x01) == 0x01);
    H >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_L()
{
    const bool bit0 = ((L & 0x01) == 0x01);
    L >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit0 = ((byte & 0x01) == 0x01);
    byte >>= 1;

    loadByteToAddress(HL, byte);

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RRC_A()
{
    const bool bit0 = ((A & 0x01) == 0x01);
    A >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_B()
{
    const bool bit7 = hasCarry(B);
    B <<= 1;
    B |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_C()
{
    const bool bit7 = hasCarry(C);
    C <<= 1;
    C |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_D()
{
    const bool bit7 = hasCarry(D);
    D <<= 1;
    D |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_E()
{
    const bool bit7 = hasCarry(E);
    E <<= 1;
    E |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_H()
{
    const bool bit7 = hasCarry(H);
    H <<= 1;
    H |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_L()
{
    const bool bit7 = hasCarry(L);
    L <<= 1;
    L |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit7 = hasCarry(byte);
    byte <<= 1;
    byte |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RL_A()
{
    const bool bit7 = hasCarry(A);
    A <<= 1;
    A |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_B()
{
    const bool bit0 = ((B & 0x01) == 0x01);
    B >>= 1;
    B |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_C()
{
    const bool bit0 = ((C & 0x01) == 0x01);
    C >>= 1;
    C |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_D()
{
    const bool bit0 = ((D & 0x01) == 0x01);
    D >>= 1;
    D |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_E()
{
    const bool bit0 = ((E & 0x01) == 0x01);
    E >>= 1;
    E |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_H()
{
    const bool bit0 = ((H & 0x01) == 0x01);
    H >>= 1;
    H |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_L()
{
    const bool bit0 = ((L & 0x01) == 0x01);
    L >>= 1;
    L |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit0 = ((byte & 0x01) == 0x01);
    byte >>= 1;
    byte |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_RR_A()
{
    const bool bit0 = ((A & 0x01) == 0x01);
    A >>= 1;
    A |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_B()
{
    const bool bit7 = (B & 0x80) == 0x80;
    B <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_C()
{
    const bool bit7 = (C & 0x80) == 0x80;
    C <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_D()
{
    const bool bit7 = (D & 0x80) == 0x80;
    D <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_E()
{
    const bool bit7 = (E & 0x80) == 0x80;
    E <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_H()
{
    const bool bit7 = (H & 0x80) == 0x80;
    H <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_L()
{
    const bool bit7 = (L & 0x80) == 0x80;
    L <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit7 = (byte & 0x80) == 0x80;
    byte <<= 1;

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SLA_A()
{
    const bool bit7 = (A & 0x80) == 0x80;
    A <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_B()
{
    const bool bit0 = (B & 0x01) == 0x01;
    const bool bit7 = (B & 0x80) == 0x80;

    B >>= 1;

    if (bit7 == true)
    {
        B |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_C()
{
    const bool bit0 = (C & 0x01) == 0x01;
    const bool bit7 = (C & 0x80) == 0x80;

    C >>= 1;

    if (bit7 == true)
    {
        C |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_D()
{
    const bool bit0 = (D & 0x01) == 0x01;
    const bool bit7 = (D & 0x80) == 0x80;

    D >>= 1;

    if (bit7 == true)
    {
        D |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_E()
{
    const bool bit0 = (E & 0x01) == 0x01;
    const bool bit7 = (E & 0x80) == 0x80;

    E >>= 1;

    if (bit7 == true)
    {
        E |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_H()
{
    const bool bit0 = (H & 0x01) == 0x01;
    const bool bit7 = (H & 0x80) == 0x80;

    H >>= 1;

    if (bit7 == true)
    {
        H |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_L()
{
    const bool bit0 = (L & 0x01) == 0x01;
    const bool bit7 = (L & 0x80) == 0x80;

    L >>= 1;

    if (bit7 == true)
    {
        L |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit0 = (byte & 0x01) == 0x01;
    const bool bit7 = (byte & 0x80) == 0x80;

    byte >>= 1;

    if (bit7 == true)
    {
        byte |= 0x80;
    }

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRA_A()
{
    const bool bit0 = (A & 0x01) == 0x01;
    const bool bit7 = (A & 0x80) == 0x80;

    A >>= 1;

    if (bit7 == true)
    {
        A |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_B()
{
    B = ((B & 0x0F) << 4) | (B >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_C()
{
    C = ((C & 0x0F) << 4) | (C >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_D()
{
    D = ((D & 0x0F) << 4) | (D >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_E()
{
    E = ((E & 0x0F) << 4) | (E >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_H()
{
    H = ((H & 0x0F) << 4) | (H >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_L()
{
    L = ((L & 0x0F) << 4) | (L >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    byte = ((byte & 0x0F) << 4) | (byte >> 4);

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SWAP_A()
{
    A = ((A & 0x0F) << 4) | (A >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_B()
{
    const bool bit0 = (B & 0x01) == 0x01;

    B >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_C()
{
    const bool bit0 = (C & 0x01) == 0x01;

    C >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_D()
{
    const bool bit0 = (D & 0x01) == 0x01;

    D >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_E()
{
    const bool bit0 = (E & 0x01) == 0x01;

    E >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_H()
{
    const bool bit0 = (H & 0x01) == 0x01;

    H >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_L()
{
    const bool bit0 = (L & 0x01) == 0x01;

    L >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    const bool bit0 = (byte & 0x01) == 0x01;

    byte >>= 1;

    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_SRL_A()
{
    const bool bit0 = (A & 0x01) == 0x01;

    A >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_BIT_0_B()
{
    const bool isBitSet = (B & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_C()
{
    const bool isBitSet = (C & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_D()
{
    const bool isBitSet = (D & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_E()
{
    const bool isBitSet = (E & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_H()
{
    const bool isBitSet = (H & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_L()
{
    const bool isBitSet = (L & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_0_A()
{
    const bool isBitSet = (A & 0x01) == 0x01;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_B()
{
    const bool isBitSet = (B & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_C()
{
    const bool isBitSet = (C & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_D()
{
    const bool isBitSet = (D & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_E()
{
    const bool isBitSet = (E & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_H()
{
    const bool isBitSet = (H & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_L()
{
    const bool isBitSet = (L & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_1_A()
{
    const bool isBitSet = (A & 0x02) == 0x02;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_B()
{
    const bool isBitSet = (B & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_C()
{
    const bool isBitSet = (C & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_D()
{
    const bool isBitSet = (D & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_E()
{
    const bool isBitSet = (E & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_H()
{
    const bool isBitSet = (H & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_L()
{
    const bool isBitSet = (L & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_2_A()
{
    const bool isBitSet = (A & 0x04) == 0x04;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_B()
{
    const bool isBitSet = (B & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_C()
{
    const bool isBitSet = (C & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_D()
{
    const bool isBitSet = (D & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_E()
{
    const bool isBitSet = (E & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_H()
{
    const bool isBitSet = (H & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_L()
{
    const bool isBitSet = (L & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_3_A()
{
    const bool isBitSet = (A & 0x08) == 0x08;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_B()
{
    const bool isBitSet = (B & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_C()
{
    const bool isBitSet = (C & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_D()
{
    const bool isBitSet = (D & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_E()
{
    const bool isBitSet = (E & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_H()
{
    const bool isBitSet = (H & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_L()
{
    const bool isBitSet = (L & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_4_A()
{
    const bool isBitSet = (A & 0x10) == 0x10;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_B()
{
    const bool isBitSet = (B & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_C()
{
    const bool isBitSet = (C & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_D()
{
    const bool isBitSet = (D & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_E()
{
    const bool isBitSet = (E & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_H()
{
    const bool isBitSet = (H & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_L()
{
    const bool isBitSet = (L & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_5_A()
{
    const bool isBitSet = (A & 0x20) == 0x20;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_B()
{
    const bool isBitSet = (B & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_C()
{
    const bool isBitSet = (C & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_D()
{
    const bool isBitSet = (D & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_E()
{
    const bool isBitSet = (E & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_H()
{
    const bool isBitSet = (H & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_L()
{
    const bool isBitSet = (L & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_6_A()
{
    const bool isBitSet = (A & 0x40) == 0x40;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_B()
{
    const bool isBitSet = (B & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_C()
{
    const bool isBitSet = (C & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_D()
{
    const bool isBitSet = (D & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_E()
{
    const bool isBitSet = (E & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_H()
{
    const bool isBitSet = (H & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_L()
{
    const bool isBitSet = (L & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const bool isBitSet = (byte & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_BIT_7_A()
{
    const bool isBitSet = (A & 0x80) == 0x80;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::op_RES_0_B()
{
    B &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0_C()
{
    C &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0_D()
{
    D &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0_E()
{
    E &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0_H()
{
    H &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0_L()
{
    L &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_0__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xFE);
}

// =================================================================================================

void Cpu::op_RES_0_A()
{
    A &= 0xFE;
}

// =================================================================================================

void Cpu::op_RES_1_B()
{
    B &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1_C()
{
    C &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1_D()
{
    D &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1_E()
{
    E &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1_H()
{
    H &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1_L()
{
    L &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_1__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xFD);
}

// =================================================================================================

void Cpu::op_RES_1_A()
{
    A &= 0xFD;
}

// =================================================================================================

void Cpu::op_RES_2_B()
{
    B &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2_C()
{
    C &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2_D()
{
    D &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2_E()
{
    E &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2_H()
{
    H &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2_L()
{
    L &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_2__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xFB);
}

// =================================================================================================

void Cpu::op_RES_2_A()
{
    A &= 0xFB;
}

// =================================================================================================

void Cpu::op_RES_3_B()
{
    B &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3_C()
{
    C &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3_D()
{
    D &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3_E()
{
    E &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3_H()
{
    H &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3_L()
{
    L &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_3__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xF7);
}

// =================================================================================================

void Cpu::op_RES_3_A()
{
    A &= 0xF7;
}

// =================================================================================================

void Cpu::op_RES_4_B()
{
    B &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4_C()
{
    C &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4_D()
{
    D &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4_E()
{
    E &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4_H()
{
    H &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4_L()
{
    L &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_4__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xEF);
}

// =================================================================================================

void Cpu::op_RES_4_A()
{
    A &= 0xEF;
}

// =================================================================================================

void Cpu::op_RES_5_B()
{
    B &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5_C()
{
    C &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5_D()
{
    D &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5_E()
{
    E &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5_H()
{
    H &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5_L()
{
    L &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_5__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xDF);
}

// =================================================================================================

void Cpu::op_RES_5_A()
{
    A &= 0xDF;
}

// =================================================================================================

void Cpu::op_RES_6_B()
{
    B &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6_C()
{
    C &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6_D()
{
    D &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6_E()
{
    E &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6_H()
{
    H &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6_L()
{
    L &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_6__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0xBF);
}

// =================================================================================================

void Cpu::op_RES_6_A()
{
    A &= 0xBF;
}

// =================================================================================================

void Cpu::op_RES_7_B()
{
    B &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7_C()
{
    C &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7_D()
{
    D &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7_E()
{
    E &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7_H()
{
    H &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7_L()
{
    L &= 0x7F;
}

// =================================================================================================

void Cpu::op_RES_7__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte & 0x7F);
}

// =================================================================================================

void Cpu::op_RES_7_A()
{
    A &= 0x7F;
}

// =================================================================================================

void Cpu::op_SET_0_B()
{
    B |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0_C()
{
    C |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0_D()
{
    D |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0_E()
{
    E |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0_H()
{
    H |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0_L()
{
    L |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_0__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x01);
}

// =================================================================================================

void Cpu::op_SET_0_A()
{
    A |= 0x01;
}

// =================================================================================================

void Cpu::op_SET_1_B()
{
    B |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1_C()
{
    C |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1_D()
{
    D |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1_E()
{
    E |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1_H()
{
    H |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1_L()
{
    L |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_1__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x02);
}

// =================================================================================================

void Cpu::op_SET_1_A()
{
    A |= 0x02;
}

// =================================================================================================

void Cpu::op_SET_2_B()
{
    B |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2_C()
{
    C |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2_D()
{
    D |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2_E()
{
    E |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2_H()
{
    H |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2_L()
{
    L |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_2__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x04);
}

// =================================================================================================

void Cpu::op_SET_2_A()
{
    A |= 0x04;
}

// =================================================================================================

void Cpu::op_SET_3_B()
{
    B |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3_C()
{
    C |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3_D()
{
    D |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3_E()
{
    E |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3_H()
{
    H |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3_L()
{
    L |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_3__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x08);
}

// =================================================================================================

void Cpu::op_SET_3_A()
{
    A |= 0x08;
}

// =================================================================================================

void Cpu::op_SET_4_B()
{
    B |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4_C()
{
    C |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4_D()
{
    D |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4_E()
{
    E |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4_H()
{
    H |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4_L()
{
    L |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_4__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x10);
}

// =================================================================================================

void Cpu::op_SET_4_A()
{
    A |= 0x10;
}

// =================================================================================================

void Cpu::op_SET_5_B()
{
    B |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5_C()
{
    C |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5_D()
{
    D |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5_E()
{
    E |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5_H()
{
    H |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5_L()
{
    L |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_5__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x20);
}

// =================================================================================================

void Cpu::op_SET_5_A()
{
    A |= 0x20;
}

// =================================================================================================

void Cpu::op_SET_6_B()
{
    B |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6_C()
{
    C |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6_D()
{
    D |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6_E()
{
    E |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6_H()
{
    H |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6_L()
{
    L |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_6__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x40);
}

// =================================================================================================

void Cpu::op_SET_6_A()
{
    A |= 0x40;
}

// =================================================================================================

void Cpu::op_SET_7_B()
{
    B |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7_C()
{
    C |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7_D()
{
    D |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7_E()
{
    E |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7_H()
{
    H |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7_L()
{
    L |= 0x80;
}

// =================================================================================================

void Cpu::op_SET_7__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte | 0x80);
}

// =================================================================================================

void Cpu::op_SET_7_A()
{
    A |= 0x80;
}
