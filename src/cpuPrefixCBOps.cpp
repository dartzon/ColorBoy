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

void Cpu::execRLC(uint8_t& data)
{
    // Save bit 7.
    const bool bit7 = ((data & 0x80) == 0x80);
    data <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execRRC(uint8_t& data)
{
    const bool bit0 = ((data & 0x01) == 0x01);
    data >>= 1;

    // Old bit 0 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execRL(uint8_t& data)
{
    const bool bit7 = hasCarry(data);
    data <<= 1;
    data |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execRR(uint8_t& data)
{
    const bool bit0 = ((data & 0x01) == 0x01);
    data >>= 1;
    data |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execSLA(uint8_t& data)
{
    const bool bit7 = (data & 0x80) == 0x80;
    data <<= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execSRA(uint8_t& data)
{
    const bool bit0 = (data & 0x01) == 0x01;
    const bool bit7 = (data & 0x80) == 0x80;

    data >>= 1;

    if (bit7 == true)
    {
        data |= 0x80;
    }

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execSWAP(uint8_t& data)
{
    data = ((data & 0x0F) << 4) | (data >> 4);

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execSRL(uint8_t& data)
{
    const bool bit0 = (data & 0x01) == 0x01;

    data >>= 1;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (data == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::execBIT(const uint8_t data, const uint8_t bitPos)
{
    const uint8_t mask = 0x01 << bitPos;
    const bool isBitSet = (data & mask) == mask;

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, !isBitSet);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
}

// =================================================================================================

void Cpu::execRES(uint8_t& data, const uint8_t bitPos)
{
    data &= ~(0x01 << bitPos);
}

// =================================================================================================

void Cpu::execSET(uint8_t& data, const uint8_t bitPos)
{
    data |= (0x01 << bitPos);
}

// =================================================================================================

void Cpu::op_RLC_B()
{
    execRLC(B);

    PRINTOP("RLC B", {});
}

// =================================================================================================

void Cpu::op_RLC_C()
{
    execRLC(C);

    PRINTOP("RLC C", {});
}

// =================================================================================================

void Cpu::op_RLC_D()
{
    execRLC(D);

    PRINTOP("RLC D", {});
}

// =================================================================================================

void Cpu::op_RLC_E()
{
    execRLC(E);

    PRINTOP("RLC E", {});
}

// =================================================================================================

void Cpu::op_RLC_H()
{
    execRLC(H);

    PRINTOP("RLC H", {});
}

// =================================================================================================

void Cpu::op_RLC_L()
{
    execRLC(L);

    PRINTOP("RLC L", {});
}

// =================================================================================================

void Cpu::op_RLC__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRLC(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("RLC (HL)", {});
}

// =================================================================================================

void Cpu::op_RLC_A()
{
    execRLC(A);

    PRINTOP("RLC A", {});
}

// =================================================================================================

void Cpu::op_RRC_B()
{
    execRRC(B);

    PRINTOP("RRC B", {});
}

// =================================================================================================

void Cpu::op_RRC_C()
{
    execRRC(C);

    PRINTOP("RRC C", {});
}

// =================================================================================================

void Cpu::op_RRC_D()
{
    execRRC(D);

    PRINTOP("RRC D", {});
}

// =================================================================================================

void Cpu::op_RRC_E()
{
    execRRC(E);

    PRINTOP("RRC E", {});
}

// =================================================================================================

void Cpu::op_RRC_H()
{
    execRRC(H);

    PRINTOP("RRC H", {});
}

// =================================================================================================

void Cpu::op_RRC_L()
{
    execRRC(L);

    PRINTOP("RRC L", {});
}

// =================================================================================================

void Cpu::op_RRC__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRRC(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("RRC (HL)", {});
}

// =================================================================================================

void Cpu::op_RRC_A()
{
    execRRC(A);

    PRINTOP("RRC A", {});
}

// =================================================================================================

void Cpu::op_RL_B()
{
    execRL(B);

    PRINTOP("RL B", {});
}

// =================================================================================================

void Cpu::op_RL_C()
{
    execRL(C);

    PRINTOP("RL C", {});
}

// =================================================================================================

void Cpu::op_RL_D()
{
    execRL(D);

    PRINTOP("RL D", {});
}

// =================================================================================================

void Cpu::op_RL_E()
{
    execRL(E);

    PRINTOP("RL E", {});
}

// =================================================================================================

void Cpu::op_RL_H()
{
    execRL(H);

    PRINTOP("RL H", {});
}

// =================================================================================================

void Cpu::op_RL_L()
{
    execRL(L);

    PRINTOP("RL L", {});
}

// =================================================================================================

void Cpu::op_RL__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRL(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("RL (HL)", {});
}

// =================================================================================================

void Cpu::op_RL_A()
{
    execRL(A);

    PRINTOP("RL A", {});
}

// =================================================================================================

void Cpu::op_RR_B()
{
    execRR(B);

    PRINTOP("RR B", {});
}

// =================================================================================================

void Cpu::op_RR_C()
{
    execRR(C);

    PRINTOP("RR C", {});
}

// =================================================================================================

void Cpu::op_RR_D()
{
    execRR(D);

    PRINTOP("RR D", {});
}

// =================================================================================================

void Cpu::op_RR_E()
{
    execRR(E);

    PRINTOP("RR E", {});
}

// =================================================================================================

void Cpu::op_RR_H()
{
    execRR(H);

    PRINTOP("RR H", {});
}

// =================================================================================================

void Cpu::op_RR_L()
{
    execRR(L);

    PRINTOP("RR L", {});
}

// =================================================================================================

void Cpu::op_RR__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRR(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("RR (HL)", {});
}

// =================================================================================================

void Cpu::op_RR_A()
{
    execRR(A);

    PRINTOP("RR A", {});
}

// =================================================================================================

void Cpu::op_SLA_B()
{
    execSLA(B);

    PRINTOP("SLA B", {});
}

// =================================================================================================

void Cpu::op_SLA_C()
{
    execSLA(C);

    PRINTOP("SLA C", {});
}

// =================================================================================================

void Cpu::op_SLA_D()
{
    execSLA(D);

    PRINTOP("SLA D", {});
}

// =================================================================================================

void Cpu::op_SLA_E()
{
    execSLA(E);

    PRINTOP("SLA E", {});
}

// =================================================================================================

void Cpu::op_SLA_H()
{
    execSLA(H);

    PRINTOP("SLA H", {});
}

// =================================================================================================

void Cpu::op_SLA_L()
{
    execSLA(L);

    PRINTOP("SLA L", {});
}

// =================================================================================================

void Cpu::op_SLA__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSLA(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("SLA (HL)", {});
}

// =================================================================================================

void Cpu::op_SLA_A()
{
    execSLA(A);

    PRINTOP("SLA A", {});
}

// =================================================================================================

void Cpu::op_SRA_B()
{
    execSRA(B);

    PRINTOP("SRA B", {});
}

// =================================================================================================

void Cpu::op_SRA_C()
{
    execSRA(C);

    PRINTOP("SRA C", {});
}

// =================================================================================================

void Cpu::op_SRA_D()
{
    execSRA(D);

    PRINTOP("SRA D", {});
}

// =================================================================================================

void Cpu::op_SRA_E()
{
    execSRA(E);

    PRINTOP("SRA E", {});
}

// =================================================================================================

void Cpu::op_SRA_H()
{
    execSRA(H);

    PRINTOP("SRA H", {});
}

// =================================================================================================

void Cpu::op_SRA_L()
{
    execSRA(L);

    PRINTOP("SRA L", {});
}

// =================================================================================================

void Cpu::op_SRA__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSRA(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("SRA (HL)", {});
}

// =================================================================================================

void Cpu::op_SRA_A()
{
    execSRA(A);

    PRINTOP("SRA A", {});
}

// =================================================================================================

void Cpu::op_SWAP_B()
{
    execSWAP(B);

    PRINTOP("SWAP B", {});
}

// =================================================================================================

void Cpu::op_SWAP_C()
{
    execSWAP(C);

    PRINTOP("SWAP C", {});
}

// =================================================================================================

void Cpu::op_SWAP_D()
{
    execSWAP(D);

    PRINTOP("SWAP D", {});
}

// =================================================================================================

void Cpu::op_SWAP_E()
{
    execSWAP(E);

    PRINTOP("SWAP E", {});
}

// =================================================================================================

void Cpu::op_SWAP_H()
{
    execSWAP(H);

    PRINTOP("SWAP H", {});
}

// =================================================================================================

void Cpu::op_SWAP_L()
{
    execSWAP(L);

    PRINTOP("SWAP L", {});
}

// =================================================================================================

void Cpu::op_SWAP__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSWAP(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("SWAP (HL)", {});
}

// =================================================================================================

void Cpu::op_SWAP_A()
{
    execSWAP(A);

    PRINTOP("SWAP A", {});
}

// =================================================================================================

void Cpu::op_SRL_B()
{
    execSRL(B);

    PRINTOP("SRL B", {});
}

// =================================================================================================

void Cpu::op_SRL_C()
{
    execSRL(C);

    PRINTOP("SRL C", {});
}

// =================================================================================================

void Cpu::op_SRL_D()
{
    execSRL(D);

    PRINTOP("SRL D", {});
}

// =================================================================================================

void Cpu::op_SRL_E()
{
    execSRL(E);

    PRINTOP("SRL E", {});
}

// =================================================================================================

void Cpu::op_SRL_H()
{
    execSRL(H);

    PRINTOP("SRL H", {});
}

// =================================================================================================

void Cpu::op_SRL_L()
{
    execSRL(L);

    PRINTOP("SRL L", {});
}

// =================================================================================================

void Cpu::op_SRL__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSRL(byte);

    loadByteToAddress(HL, byte);

    PRINTOP("SRL (HL)", {});
}

// =================================================================================================

void Cpu::op_SRL_A()
{
    execSRL(A);

    PRINTOP("SRL A", {});
}

// =================================================================================================

void Cpu::op_BIT_0_B()
{
    execBIT(B, 0);

    PRINTOP("BIT 0, B", {});
}

// =================================================================================================

void Cpu::op_BIT_0_C()
{
    execBIT(C, 0);

    PRINTOP("BIT 0, C", {});
}

// =================================================================================================

void Cpu::op_BIT_0_D()
{
    execBIT(D, 0);

    PRINTOP("BIT 0, D", {});
}

// =================================================================================================

void Cpu::op_BIT_0_E()
{
    execBIT(E, 0);

    PRINTOP("BIT 0, E", {});
}

// =================================================================================================

void Cpu::op_BIT_0_H()
{
    execBIT(H, 0);

    PRINTOP("BIT 0, H", {});
}

// =================================================================================================

void Cpu::op_BIT_0_L()
{
    execBIT(B, 0);

    PRINTOP("BIT 0, L", {});
}

// =================================================================================================

void Cpu::op_BIT_0__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 0);

    PRINTOP("BIT 0, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_0_A()
{
    execBIT(A, 0);

    PRINTOP("BIT 0, A", {});
}

// =================================================================================================

void Cpu::op_BIT_1_B()
{
    execBIT(B, 1);

    PRINTOP("BIT 1, B", {});
}

// =================================================================================================

void Cpu::op_BIT_1_C()
{
    execBIT(C, 1);

    PRINTOP("BIT 1, C", {});
}

// =================================================================================================

void Cpu::op_BIT_1_D()
{
    execBIT(D, 1);

    PRINTOP("BIT 1, D", {});
}

// =================================================================================================

void Cpu::op_BIT_1_E()
{
    execBIT(E, 1);

    PRINTOP("BIT 1, E", {});
}

// =================================================================================================

void Cpu::op_BIT_1_H()
{
    execBIT(H, 1);

    PRINTOP("BIT 1, H", {});
}

// =================================================================================================

void Cpu::op_BIT_1_L()
{
    execBIT(L, 1);

    PRINTOP("BIT 1, L", {});
}

// =================================================================================================

void Cpu::op_BIT_1__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 1);

    PRINTOP("BIT 1, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_1_A()
{
    execBIT(A, 1);

    PRINTOP("BIT 1, A", {});
}

// =================================================================================================

void Cpu::op_BIT_2_B()
{
    execBIT(B, 2);

    PRINTOP("BIT 2, B", {});
}

// =================================================================================================

void Cpu::op_BIT_2_C()
{
    execBIT(C, 2);

    PRINTOP("BIT Z, C", {});
}

// =================================================================================================

void Cpu::op_BIT_2_D()
{
    execBIT(D, 2);

    PRINTOP("BIT 2, D", {});
}

// =================================================================================================

void Cpu::op_BIT_2_E()
{
    execBIT(E, 2);

    PRINTOP("BIT 2, E", {});
}

// =================================================================================================

void Cpu::op_BIT_2_H()
{
    execBIT(H, 2);

    PRINTOP("BIT 2, H", {});
}

// =================================================================================================

void Cpu::op_BIT_2_L()
{
    execBIT(L, 2);

    PRINTOP("BIT 2, L", {});
}

// =================================================================================================

void Cpu::op_BIT_2__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 2);

    PRINTOP("BIT 2, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_2_A()
{
    execBIT(A, 2);

    PRINTOP("BIT 2, A", {});
}

// =================================================================================================

void Cpu::op_BIT_3_B()
{
    execBIT(B, 3);

    PRINTOP("BIT 3, B", {});
}

// =================================================================================================

void Cpu::op_BIT_3_C()
{
    execBIT(C, 3);

    PRINTOP("BIT 3, C", {});
}

// =================================================================================================

void Cpu::op_BIT_3_D()
{
    execBIT(D, 3);

    PRINTOP("BIT 3, D", {});
}

// =================================================================================================

void Cpu::op_BIT_3_E()
{
    execBIT(E, 3);

    PRINTOP("BIT 3, E", {});
}

// =================================================================================================

void Cpu::op_BIT_3_H()
{
    execBIT(H, 3);

    PRINTOP("BIT 3, H", {});
}

// =================================================================================================

void Cpu::op_BIT_3_L()
{
    execBIT(L, 3);

    PRINTOP("BIT 3, L", {});
}

// =================================================================================================

void Cpu::op_BIT_3__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 3);

    PRINTOP("BIT 3, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_3_A()
{
    execBIT(A, 3);

    PRINTOP("BIT 3, A", {});
}

// =================================================================================================

void Cpu::op_BIT_4_B()
{
    execBIT(B, 4);

    PRINTOP("BIT 4, B", {});
}

// =================================================================================================

void Cpu::op_BIT_4_C()
{
    execBIT(C, 4);

    PRINTOP("BIT 4, C", {});
}

// =================================================================================================

void Cpu::op_BIT_4_D()
{
    execBIT(D, 4);

    PRINTOP("BIT 4, D", {});
}

// =================================================================================================

void Cpu::op_BIT_4_E()
{
    execBIT(E, 4);

    PRINTOP("BIT 4, E", {});
}

// =================================================================================================

void Cpu::op_BIT_4_H()
{
    execBIT(H, 4);

    PRINTOP("BIT 4, H", {});
}

// =================================================================================================

void Cpu::op_BIT_4_L()
{
    execBIT(L, 4);

    PRINTOP("BIT 4, L", {});
}

// =================================================================================================

void Cpu::op_BIT_4__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 4);

    PRINTOP("BIT 4, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_4_A()
{
    execBIT(A, 4);

    PRINTOP("BIT 4, A", {});
}

// =================================================================================================

void Cpu::op_BIT_5_B()
{
    execBIT(B, 5);

    PRINTOP("BIT 5, B", {});
}

// =================================================================================================

void Cpu::op_BIT_5_C()
{
    execBIT(C, 5);

    PRINTOP("BIT 5, C", {});
}

// =================================================================================================

void Cpu::op_BIT_5_D()
{
    execBIT(D, 5);

    PRINTOP("BIT 5, D", {});
}

// =================================================================================================

void Cpu::op_BIT_5_E()
{
    execBIT(E, 5);

    PRINTOP("BIT 5, E", {});
}

// =================================================================================================

void Cpu::op_BIT_5_H()
{
    execBIT(H, 5);

    PRINTOP("BIT 5, H", {});
}

// =================================================================================================

void Cpu::op_BIT_5_L()
{
    execBIT(L, 5);

    PRINTOP("BIT 5, L", {});
}

// =================================================================================================

void Cpu::op_BIT_5__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 5);

    PRINTOP("BIT 5, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_5_A()
{
    execBIT(A, 5);

    PRINTOP("BIT 5, A", {});
}

// =================================================================================================

void Cpu::op_BIT_6_B()
{
    execBIT(B, 6);

    PRINTOP("BIT 6, B", {});
}

// =================================================================================================

void Cpu::op_BIT_6_C()
{
    execBIT(C, 6);

    PRINTOP("BIT 6, C", {});
}

// =================================================================================================

void Cpu::op_BIT_6_D()
{
    execBIT(D, 6);

    PRINTOP("BIT 6, D", {});
}

// =================================================================================================

void Cpu::op_BIT_6_E()
{
    execBIT(E, 6);

    PRINTOP("BIT 6, E", {});
}

// =================================================================================================

void Cpu::op_BIT_6_H()
{
    execBIT(H, 6);

    PRINTOP("BIT 6, H", {});
}

// =================================================================================================

void Cpu::op_BIT_6_L()
{
    execBIT(L, 6);

    PRINTOP("BIT 6, L", {});
}

// =================================================================================================

void Cpu::op_BIT_6__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 6);

    PRINTOP("BIT 6, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_6_A()
{
    execBIT(A, 6);

    PRINTOP("BIT 6, A", {});
}

// =================================================================================================

void Cpu::op_BIT_7_B()
{
    execBIT(B, 7);

    PRINTOP("BIT 7, B", {});
}

// =================================================================================================

void Cpu::op_BIT_7_C()
{
    execBIT(C, 7);

    PRINTOP("BIT 7, C", {});
}

// =================================================================================================

void Cpu::op_BIT_7_D()
{
    execBIT(D, 7);

    PRINTOP("BIT 7, D", {});
}

// =================================================================================================

void Cpu::op_BIT_7_E()
{
    execBIT(E, 7);

    PRINTOP("BIT 7, E", {});
}

// =================================================================================================

void Cpu::op_BIT_7_H()
{
    execBIT(H, 7);

    PRINTOP("BIT 7, H", {});
}

// =================================================================================================

void Cpu::op_BIT_7_L()
{
    execBIT(L, 7);

    PRINTOP("BIT 7, L", {});
}

// =================================================================================================

void Cpu::op_BIT_7__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    execBIT(byte, 7);

    PRINTOP("BIT 7, (HL)", {});
}

// =================================================================================================

void Cpu::op_BIT_7_A()
{
    execBIT(A, 7);

    PRINTOP("BIT 7, A", {});
}

// =================================================================================================

void Cpu::op_RES_0_B()
{
    execRES(B, 0);

    PRINTOP("RES 0, B", {});
}

// =================================================================================================

void Cpu::op_RES_0_C()
{
    execRES(C, 0);

    PRINTOP("RES 0, C", {});
}

// =================================================================================================

void Cpu::op_RES_0_D()
{
    execRES(D, 0);

    PRINTOP("RES 0, D", {});
}

// =================================================================================================

void Cpu::op_RES_0_E()
{
    execRES(E, 0);

    PRINTOP("RES 0, E", {});
}

// =================================================================================================

void Cpu::op_RES_0_H()
{
    execRES(H, 0);

    PRINTOP("RES 0, H", {});
}

// =================================================================================================

void Cpu::op_RES_0_L()
{
    execRES(L, 0);

    PRINTOP("RES 0, L", {});
}

// =================================================================================================

void Cpu::op_RES_0__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);
    execRES(byte, 0);
    loadByteToAddress(HL, byte);

    PRINTOP("RES 0, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_0_A()
{
    execRES(A, 0);

    PRINTOP("RES 0, A", {});
}

// =================================================================================================

void Cpu::op_RES_1_B()
{
    execRES(B, 1);

    PRINTOP("RES 1, B", {});
}

// =================================================================================================

void Cpu::op_RES_1_C()
{
    execRES(C, 1);

    PRINTOP("RES 1, C", {});
}

// =================================================================================================

void Cpu::op_RES_1_D()
{
    execRES(D, 1);

    PRINTOP("RES 1, D", {});
}

// =================================================================================================

void Cpu::op_RES_1_E()
{
    execRES(E, 1);

    PRINTOP("RES 1, E", {});
}

// =================================================================================================

void Cpu::op_RES_1_H()
{
    execRES(H, 1);

    PRINTOP("RES 1, H", {});
}

// =================================================================================================

void Cpu::op_RES_1_L()
{
    execRES(L, 1);

    PRINTOP("RES 1, L", {});
}

// =================================================================================================

void Cpu::op_RES_1__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);
    execRES(byte, 1);
    loadByteToAddress(HL, byte);

    PRINTOP("RES 1, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_1_A()
{
    execRES(A, 1);

    PRINTOP("RES 1, A", {});
}

// =================================================================================================

void Cpu::op_RES_2_B()
{
    execRES(B, 2);

    PRINTOP("RES 2, B", {});
}

// =================================================================================================

void Cpu::op_RES_2_C()
{
    execRES(C, 2);

    PRINTOP("RES 2, C", {});
}

// =================================================================================================

void Cpu::op_RES_2_D()
{
    execRES(D, 2);

    PRINTOP("RES 2, D", {});
}

// =================================================================================================

void Cpu::op_RES_2_E()
{
    execRES(E, 2);

    PRINTOP("RES 2, E", {});
}

// =================================================================================================

void Cpu::op_RES_2_H()
{
    execRES(H, 2);

    PRINTOP("RES 2, H", {});
}

// =================================================================================================

void Cpu::op_RES_2_L()
{
    execRES(L, 2);

    PRINTOP("RES 2, L", {});
}

// =================================================================================================

void Cpu::op_RES_2__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte);

    PRINTOP("RES 2, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_2_A()
{
    execRES(A, 2);

    PRINTOP("RES 2, A", {});
}

// =================================================================================================

void Cpu::op_RES_3_B()
{
    execRES(B, 3);

    PRINTOP("RES 3, B", {});
}

// =================================================================================================

void Cpu::op_RES_3_C()
{
    execRES(C, 3);

    PRINTOP("RES 3, C", {});
}

// =================================================================================================

void Cpu::op_RES_3_D()
{
    execRES(D, 3);

    PRINTOP("RES 3, D", {});
}

// =================================================================================================

void Cpu::op_RES_3_E()
{
    execRES(E, 3);

    PRINTOP("RES 3, E", {});
}

// =================================================================================================

void Cpu::op_RES_3_H()
{
    execRES(H, 3);

    PRINTOP("RES 3, H", {});
}

// =================================================================================================

void Cpu::op_RES_3_L()
{
    execRES(L, 3);

    PRINTOP("RES 3, L", {});
}

// =================================================================================================

void Cpu::op_RES_3__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    loadByteToAddress(HL, byte);

    PRINTOP("RES 3, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_3_A()
{
    execRES(A, 3);

    PRINTOP("RES 3, A", {});
}

// =================================================================================================

void Cpu::op_RES_4_B()
{
    execRES(B, 4);

    PRINTOP("RES 4, B", {});
}

// =================================================================================================

void Cpu::op_RES_4_C()
{
    execRES(C, 4);

    PRINTOP("RES 4, C", {});
}

// =================================================================================================

void Cpu::op_RES_4_D()
{
    execRES(D, 4);

    PRINTOP("RES 4, D", {});
}

// =================================================================================================

void Cpu::op_RES_4_E()
{
    execRES(E, 4);

    PRINTOP("RES 4, E", {});
}

// =================================================================================================

void Cpu::op_RES_4_H()
{
    execRES(H, 4);

    PRINTOP("RES 4, H", {});
}

// =================================================================================================

void Cpu::op_RES_4_L()
{
    execRES(L, 4);

    PRINTOP("RES 4, L", {});
}

// =================================================================================================

void Cpu::op_RES_4__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRES(byte, 4);

    loadByteToAddress(HL, byte);

    PRINTOP("RES 4, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_4_A()
{
    execRES(A, 4);

    PRINTOP("RES 4, A", {});
}

// =================================================================================================

void Cpu::op_RES_5_B()
{
    execRES(B, 5);

    PRINTOP("RES 5, B", {});
}

// =================================================================================================

void Cpu::op_RES_5_C()
{
    execRES(C, 5);

    PRINTOP("RES 5, C", {});
}

// =================================================================================================

void Cpu::op_RES_5_D()
{
    execRES(D, 5);

    PRINTOP("RES 5, D", {});
}

// =================================================================================================

void Cpu::op_RES_5_E()
{
    execRES(E, 5);

    PRINTOP("RES 5, E", {});
}

// =================================================================================================

void Cpu::op_RES_5_H()
{
    execRES(H, 5);

    PRINTOP("RES 5, H", {});
}

// =================================================================================================

void Cpu::op_RES_5_L()
{
    execRES(L, 5);

    PRINTOP("RES 5, L", {});
}

// =================================================================================================

void Cpu::op_RES_5__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRES(byte, 5);

    loadByteToAddress(HL, byte);

    PRINTOP("RES 5, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_5_A()
{
    execRES(A, 5);

    PRINTOP("RES 5, A", {});
}

// =================================================================================================

void Cpu::op_RES_6_B()
{
    execRES(B, 6);

    PRINTOP("RES 6, B", {});
}

// =================================================================================================

void Cpu::op_RES_6_C()
{
    execRES(C, 6);

    PRINTOP("RES 6, C", {});
}

// =================================================================================================

void Cpu::op_RES_6_D()
{
    execRES(D, 6);

    PRINTOP("RES 6, D", {});
}

// =================================================================================================

void Cpu::op_RES_6_E()
{
    execRES(E, 6);

    PRINTOP("RES 6, E", {});
}

// =================================================================================================

void Cpu::op_RES_6_H()
{
    execRES(H, 6);

    PRINTOP("RES 6, H", {});
}

// =================================================================================================

void Cpu::op_RES_6_L()
{
    execRES(L, 6);

    PRINTOP("RES 6, L", {});
}

// =================================================================================================

void Cpu::op_RES_6__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRES(byte, 6);

    loadByteToAddress(HL, byte);

    PRINTOP("RES 6, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_6_A()
{
    execRES(A, 6);

    PRINTOP("RES 6, A", {});
}

// =================================================================================================

void Cpu::op_RES_7_B()
{
    execRES(B, 7);

    PRINTOP("RES 7, B", {});
}

// =================================================================================================

void Cpu::op_RES_7_C()
{
    execRES(C, 7);

    PRINTOP("RES 7, C", {});
}

// =================================================================================================

void Cpu::op_RES_7_D()
{
    execRES(D, 7);

    PRINTOP("RES 7, D", {});
}

// =================================================================================================

void Cpu::op_RES_7_E()
{
    execRES(E, 7);

    PRINTOP("RES 7, E", {});
}

// =================================================================================================

void Cpu::op_RES_7_H()
{
    execRES(H, 7);

    PRINTOP("RES 7, H", {});
}

// =================================================================================================

void Cpu::op_RES_7_L()
{
    execRES(L, 7);

    PRINTOP("RES 7, L", {});
}

// =================================================================================================

void Cpu::op_RES_7__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execRES(byte, 7);

    loadByteToAddress(HL, byte & 0x7F);

    PRINTOP("RES 7, (HL)", {});
}

// =================================================================================================

void Cpu::op_RES_7_A()
{
    execRES(A, 7);

    PRINTOP("RES 7, A", {});
}

// =================================================================================================

void Cpu::op_SET_0_B()
{
    execSET(B, 0);

    PRINTOP("SET 0, B", {});
}

// =================================================================================================

void Cpu::op_SET_0_C()
{
    execSET(C, 0);

    PRINTOP("SET 0, C", {});
}

// =================================================================================================

void Cpu::op_SET_0_D()
{
    execSET(D, 0);

    PRINTOP("SET 0, D", {});
}

// =================================================================================================

void Cpu::op_SET_0_E()
{
    execSET(E, 0);

    PRINTOP("SET 0, E", {});
}

// =================================================================================================

void Cpu::op_SET_0_H()
{
    execSET(H, 0);

    PRINTOP("SET 0, H", {});
}

// =================================================================================================

void Cpu::op_SET_0_L()
{
    execSET(L, 0);

    PRINTOP("SET 0, L", {});
}

// =================================================================================================

void Cpu::op_SET_0__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 0);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 0, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_0_A()
{
    execSET(A, 0);

    PRINTOP("SET 0, A", {});
}

// =================================================================================================

void Cpu::op_SET_1_B()
{
    execSET(B, 1);

    PRINTOP("SET 1, B", {});
}

// =================================================================================================

void Cpu::op_SET_1_C()
{
    execSET(C, 1);

    PRINTOP("SET 1, C", {});
}

// =================================================================================================

void Cpu::op_SET_1_D()
{
    execSET(D, 1);

    PRINTOP("SET 1, D", {});
}

// =================================================================================================

void Cpu::op_SET_1_E()
{
    execSET(E, 1);

    PRINTOP("SET 1, E", {});
}

// =================================================================================================

void Cpu::op_SET_1_H()
{
    execSET(H, 1);

    PRINTOP("SET 1, H", {});
}

// =================================================================================================

void Cpu::op_SET_1_L()
{
    execSET(L, 1);

    PRINTOP("SET 1, L", {});
}

// =================================================================================================

void Cpu::op_SET_1__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 1);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 1, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_1_A()
{
    execSET(A, 1);

    PRINTOP("SET 1, A", {});
}

// =================================================================================================

void Cpu::op_SET_2_B()
{
    execSET(B, 2);

    PRINTOP("SET 2, B", {});
}

// =================================================================================================

void Cpu::op_SET_2_C()
{
    execSET(C, 2);

    PRINTOP("SET 2, C", {});
}

// =================================================================================================

void Cpu::op_SET_2_D()
{
    execSET(D, 2);

    PRINTOP("SET 2, D", {});
}

// =================================================================================================

void Cpu::op_SET_2_E()
{
    execSET(E, 2);

    PRINTOP("SET 2, E", {});
}

// =================================================================================================

void Cpu::op_SET_2_H()
{
    execSET(H, 2);

    PRINTOP("SET 2, H", {});
}

// =================================================================================================

void Cpu::op_SET_2_L()
{
    execSET(L, 2);

    PRINTOP("SET 2, L", {});
}

// =================================================================================================

void Cpu::op_SET_2__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 2);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 2, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_2_A()
{
    execSET(A, 2);

    PRINTOP("SET 2, A", {});
}

// =================================================================================================

void Cpu::op_SET_3_B()
{
    execSET(B, 3);

    PRINTOP("SET 3, B", {});
}

// =================================================================================================

void Cpu::op_SET_3_C()
{
    execSET(C, 3);

    PRINTOP("SET 3, C", {});
}

// =================================================================================================

void Cpu::op_SET_3_D()
{
    execSET(D, 3);

    PRINTOP("SET 3, D", {});
}

// =================================================================================================

void Cpu::op_SET_3_E()
{
    execSET(E, 3);

    PRINTOP("SET 3, E", {});
}

// =================================================================================================

void Cpu::op_SET_3_H()
{
    execSET(H, 3);

    PRINTOP("SET 3, H", {});
}

// =================================================================================================

void Cpu::op_SET_3_L()
{
    execSET(L, 3);

    PRINTOP("SET 3, L", {});
}

// =================================================================================================

void Cpu::op_SET_3__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 3);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 3, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_3_A()
{
    execSET(A, 3);

    PRINTOP("SET 3, A", {});
}

// =================================================================================================

void Cpu::op_SET_4_B()
{
    execSET(B, 4);

    PRINTOP("SET 4, B", {});
}

// =================================================================================================

void Cpu::op_SET_4_C()
{
    execSET(C, 4);

    PRINTOP("SET 4, C", {});
}

// =================================================================================================

void Cpu::op_SET_4_D()
{
    execSET(D, 4);

    PRINTOP("SET 4, D", {});
}

// =================================================================================================

void Cpu::op_SET_4_E()
{
    execSET(E, 4);

    PRINTOP("SET 4, E", {});
}

// =================================================================================================

void Cpu::op_SET_4_H()
{
    execSET(H, 4);

    PRINTOP("SET 4, H", {});
}

// =================================================================================================

void Cpu::op_SET_4_L()
{
    execSET(L, 4);

    PRINTOP("SET 4, L", {});
}

// =================================================================================================

void Cpu::op_SET_4__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 4);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 4, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_4_A()
{
    execSET(A, 4);

    PRINTOP("SET 4, A", {});
}

// =================================================================================================

void Cpu::op_SET_5_B()
{
    execSET(B, 5);

    PRINTOP("SET 5, B", {});
}

// =================================================================================================

void Cpu::op_SET_5_C()
{
    execSET(C, 5);

    PRINTOP("SET 5, C", {});
}

// =================================================================================================

void Cpu::op_SET_5_D()
{
    execSET(D, 5);

    PRINTOP("SET 5, D", {});
}

// =================================================================================================

void Cpu::op_SET_5_E()
{
    execSET(E, 5);

    PRINTOP("SET 5, E", {});
}

// =================================================================================================

void Cpu::op_SET_5_H()
{
    execSET(H, 5);

    PRINTOP("SET 5, H", {});
}

// =================================================================================================

void Cpu::op_SET_5_L()
{
    execSET(L, 5);

    PRINTOP("SET 5, L", {});
}

// =================================================================================================

void Cpu::op_SET_5__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 5);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 5, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_5_A()
{
    execSET(A, 5);

    PRINTOP("SET 5, A", {});
}

// =================================================================================================

void Cpu::op_SET_6_B()
{
    execSET(B, 6);

    PRINTOP("SET 6, B", {});
}

// =================================================================================================

void Cpu::op_SET_6_C()
{
    execSET(C, 6);

    PRINTOP("SET 6, C", {});
}

// =================================================================================================

void Cpu::op_SET_6_D()
{
    execSET(D, 6);

    PRINTOP("SET 6, D", {});
}

// =================================================================================================

void Cpu::op_SET_6_E()
{
    execSET(E, 6);

    PRINTOP("SET 6, E", {});
}

// =================================================================================================

void Cpu::op_SET_6_H()
{
    execSET(H, 6);

    PRINTOP("SET 6, H", {});
}

// =================================================================================================

void Cpu::op_SET_6_L()
{
    execSET(L, 6);

    PRINTOP("SET 6, L", {});
}

// =================================================================================================

void Cpu::op_SET_6__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 6);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 6, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_6_A()
{
    execSET(A, 6);

    PRINTOP("SET 6, A", {});
}

// =================================================================================================

void Cpu::op_SET_7_B()
{
    execSET(B, 7);

    PRINTOP("SET 7, B", {});
}

// =================================================================================================

void Cpu::op_SET_7_C()
{
    execSET(C, 7);

    PRINTOP("SET 7, C", {});
}

// =================================================================================================

void Cpu::op_SET_7_D()
{
    execSET(D, 7);

    PRINTOP("SET 7, D", {});
}

// =================================================================================================

void Cpu::op_SET_7_E()
{
    execSET(E, 7);

    PRINTOP("SET 7, E", {});
}

// =================================================================================================

void Cpu::op_SET_7_H()
{
    execSET(H, 7);

    PRINTOP("SET 7, H", {});
}

// =================================================================================================

void Cpu::op_SET_7_L()
{
    execSET(L, 7);

    PRINTOP("SET 7, L", {});
}

// =================================================================================================

void Cpu::op_SET_7__HL__()
{
    uint8_t byte = fetchByteFromAddress(HL);

    execSET(byte, 7);

    loadByteToAddress(HL, byte);

    PRINTOP("SET 7, (HL)", {});
}

// =================================================================================================

void Cpu::op_SET_7_A()
{
    execSET(A, 7);

    PRINTOP("SET 7, A", {});
}
