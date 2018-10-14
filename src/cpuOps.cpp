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

/// \file      cpuOps.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      03-06-2018

// Local includes.
#include "cpu.h"

#include "utils.h"

void Cpu::op_NOP()
{
}

// =================================================================================================

void Cpu::op_LD_BC_d16()
{
    B = MBR[0];
    C = MBR[1];
}

// =================================================================================================

void Cpu::op_LD__BC__A()
{
    loadByteToAddress(BC, A);
}

// =================================================================================================

void Cpu::op_INC_BC()
{
    ++BC;
}

// =================================================================================================

void Cpu::op_INC_B()
{
    const bool halfCarry = hasHalfCarry(B);
    ++B;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
}

// =================================================================================================

void Cpu::op_DEC_B()
{
    const bool noHalfBorrow = !(hasHalfBorrow(B));
    --B;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
}

// =================================================================================================

void Cpu::op_LD_B_d8()
{
    B = MBR[0];
}

// =================================================================================================

void Cpu::op_RLCA()
{
    // Save bit 7.
    const bool bit7 = ((A & 0x80) == 0x80);
    A <<= 1;

    // Old bit 7 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_LD__a16__SP()
{
    loadWordToAddress(BC, SP);
}

// =================================================================================================

void Cpu::op_ADD_HL_BC()
{
    const bool halfCarry = hasHalfCarry(HL, BC);
    const bool carry = hasCarry(HL, BC);

    HL += BC;

    // Set if carry from bit 15.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 11.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
}

// =================================================================================================

void Cpu::op_LD_A__BC__()
{
    A = fetchByteFromAddress(BC);
}

// =================================================================================================

void Cpu::op_DEC_BC()
{
    --BC;
}

// =================================================================================================

void Cpu::op_INC_C()
{
    const bool halfCarry = hasHalfCarry(C);
    ++C;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
}

// =================================================================================================

void Cpu::op_DEC_C()
{
    const bool noHalfBorrow = !(hasHalfBorrow(C));
    --C;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
}

// =================================================================================================

void Cpu::op_LD_C_d8()
{
    C = MBR[0];
}

// =================================================================================================

void Cpu::op_RRCA()
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

void Cpu::op_STOP()
{
    switchState(InstructionCycleState::eStop);
}

// =================================================================================================

void Cpu::op_LD_DE_d16()
{
    D = MBR[0];
    E = MBR[1];
}

// =================================================================================================

void Cpu::op_LD__DE__A()
{
    loadByteToAddress(DE, A);
}

// =================================================================================================

void Cpu::op_INC_DE()
{
    ++DE;
}

// =================================================================================================

void Cpu::op_INC_D()
{
    const bool halfCarry = hasHalfCarry(D);
    ++D;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
}

// =================================================================================================

void Cpu::op_DEC_D()
{
    const bool noHalfBorrow = !(hasHalfBorrow(D));
    --D;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
}

// =================================================================================================

void Cpu::op_LD_D_d8()
{
    D = MBR[0];
}

// =================================================================================================

void Cpu::op_RLA()
{
    const bool bit7 = hasCarry(A);
    A <<= 1;
    A |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    // Old bit 7 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit7);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_JR_r8()
{
    PC += static_cast<const int8_t>(MBR[0]);
}

// =================================================================================================

void Cpu::op_ADD_HL_DE()
{
    const bool halfCarry = hasHalfCarry(HL, DE);
    const bool carry = hasCarry(HL, DE);

    HL += DE;

    // Set if carry from bit 15.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 11.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
}

// =================================================================================================

void Cpu::op_LD_A__DE__()
{
    A = fetchByteFromAddress(DE);
}

// =================================================================================================

void Cpu::op_DEC_DE()
{
    --DE;
}

// =================================================================================================

void Cpu::op_INC_E()
{
    ++E;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((E & 0x0F) == 0x0F));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
}

// =================================================================================================

void Cpu::op_DEC_E()
{
    const bool noHalfBorrow = !(hasHalfBorrow(E));
    --E;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));
}

// =================================================================================================

void Cpu::op_LD_E_d8()
{
    E = MBR[0];
}

// =================================================================================================

void Cpu::op_RRA()
{
    const bool bit0 = ((A & 0x01) == 0x01);
    A >>= 1;
    A |= static_cast<uint8_t>(checkFlagRegisterBit(FlagRegisterBits::eCarryFlag)) << 7;

    // Old bit 7 to Carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, bit0);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
}

// =================================================================================================

void Cpu::op_JR_NZ_r8()
{
    const uint8_t jumpFactor = static_cast<const uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eZeroFlag));
    PC += static_cast<const int8_t>(MBR[0]) * !jumpFactor;
}

// =================================================================================================

void Cpu::op_LD_HL_d16()
{
    H = MBR[0];
    L = MBR[1];
}

// =================================================================================================

void Cpu::op_LD__HLplus__A()
{
    loadByteToAddress(HL, A);
    ++HL;
}

// =================================================================================================

void Cpu::op_INC_HL()
{
    ++HL;
}

// =================================================================================================

void Cpu::op_INC_H()
{
    const bool halfCarry = hasHalfCarry(H);
    ++H;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
}

// =================================================================================================

void Cpu::op_DEC_H()
{
    const bool noHalfBorrow = !(hasHalfBorrow(H));
    --H;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (H == 0));
}

// =================================================================================================

void Cpu::op_LD_H_d8()
{
    H = MBR[0];
}

// =================================================================================================

void Cpu::op_DAA()
{
    NOTYETIMPLEMENTED();
}

// =================================================================================================

void Cpu::op_JR_Z_r8()
{
    const uint8_t jumpFactor = static_cast<const uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eZeroFlag));
    PC += static_cast<const int8_t>(MBR[0]) * jumpFactor;
}

// =================================================================================================

void Cpu::op_ADD_HL_HL()
{
    const bool halfCarry = hasHalfCarry(HL, HL);
    const bool carry = hasCarry(HL, HL);

    HL += HL;

    // Set if carry from bit 15.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 11.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
}

// =================================================================================================

void Cpu::op_LD_A__HLplus__()
{
    A = fetchByteFromAddress(HL);
    ++HL;
}

// =================================================================================================

void Cpu::op_DEC_HL()
{
    --HL;
}

// =================================================================================================

void Cpu::op_INC_L()
{
    const bool halfCarry = hasHalfCarry(L);
    ++L;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
}

// =================================================================================================

void Cpu::op_DEC_L()
{
    const bool noHalfBorrow = !(hasHalfBorrow(L));
    --L;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (L == 0));
}

// =================================================================================================

void Cpu::op_LD_L_d8()
{
    L = MBR[0];
}

// =================================================================================================

void Cpu::op_CPL()
{
    A = ~A;

    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
}

// =================================================================================================

void Cpu::op_JR_NC_r8()
{
    const uint8_t jumpFactor = static_cast<const uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));
    PC += static_cast<const int8_t>(MBR[0]) * !jumpFactor;
}

// =================================================================================================

void Cpu::op_LD_SP_d16()
{
    SP = cbutil::combineTowBytes(MBR[0], MBR[1]);
}

// =================================================================================================

void Cpu::op_LD__HLminus__A()
{
    loadByteToAddress(HL, A);
    --HL;
}

// =================================================================================================

void Cpu::op_INC_SP()
{
    ++SP;
}

// =================================================================================================

void Cpu::op_INC__HL__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    uint8_t byte = fetchByteFromAddress(HL);

    const bool halfCarry = hasHalfCarry(byte);
    ++byte;
    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
}

// =================================================================================================

void Cpu::op_DEC__HL__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    uint8_t byte = fetchByteFromAddress(HL);

    const bool noHalfBorrow = !(hasHalfBorrow(byte));
    --byte;
    loadByteToAddress(HL, byte);

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
}

// =================================================================================================

void Cpu::op_LD__HL__d8()
{
    loadByteToAddress(HL, MBR[0]);
}

// =================================================================================================

void Cpu::op_SCF()
{
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, true);
}

// =================================================================================================

void Cpu::op_JR_C_r8()
{
    const uint8_t jumpFactor = static_cast<const uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));
    PC += static_cast<const int8_t>(MBR[0]) * jumpFactor;
}

// =================================================================================================

void Cpu::op_ADD_HL_SP()
{
    const bool halfCarry = hasHalfCarry(HL, SP);
    const bool carry = hasCarry(HL, SP);

    HL += SP;

    // Set if carry from bit 15.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 11.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
}

// =================================================================================================

void Cpu::op_LD_A__HLminus__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    const uint8_t byte = fetchByteFromAddress(HL);
    A = byte;

    --HL;
}

// =================================================================================================

void Cpu::op_DEC_SP()
{
    --SP;
}

// =================================================================================================

void Cpu::op_INC_A()
{
    const bool halfCarry = hasHalfCarry(A);
    ++A;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_DEC_A()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A));
    --A;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_LD_A_d8()
{
    A = MBR[0];
}

// =================================================================================================

void Cpu::op_CCF()
{
    const bool carryFlag = checkFlagRegisterBit(FlagRegisterBits::eCarryFlag);

    // Complement carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, !carryFlag);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
}

// =================================================================================================

void Cpu::op_LD_B_B()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_B_C()
{
    B = C;
}

// =================================================================================================

void Cpu::op_LD_B_D()
{
    B = D;
}

// =================================================================================================

void Cpu::op_LD_B_E()
{
    B = E;
}

// =================================================================================================

void Cpu::op_LD_B_H()
{
    B = H;
}

// =================================================================================================

void Cpu::op_LD_B_L()
{
    B = L;
}

// =================================================================================================

void Cpu::op_LD_B__HL__()
{
    B = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_B_A()
{
    B = A;
}

// =================================================================================================

void Cpu::op_LD_C_B()
{
    C = B;
}

// =================================================================================================

void Cpu::op_LD_C_C()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_C_D()
{
    C = D;
}

// =================================================================================================

void Cpu::op_LD_C_E()
{
    C = E;
}

// =================================================================================================

void Cpu::op_LD_C_H()
{
    C = H;
}

// =================================================================================================

void Cpu::op_LD_C_L()
{
    C = L;
}

// =================================================================================================

void Cpu::op_LD_C__HL__()
{
    C = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_C_A()
{
    C = A;
}

// =================================================================================================

void Cpu::op_LD_D_B()
{
    D = B;
}

// =================================================================================================

void Cpu::op_LD_D_C()
{
    D = C;
}

// =================================================================================================

void Cpu::op_LD_D_D()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_D_E()
{
    D = E;
}

// =================================================================================================

void Cpu::op_LD_D_H()
{
    D = H;
}

// =================================================================================================

void Cpu::op_LD_D_L()
{
    D = L;
}

// =================================================================================================

void Cpu::op_LD_D__HL__()
{
    D = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_D_A()
{
    D = A;
}

// =================================================================================================

void Cpu::op_LD_E_B()
{
    E = B;
}

// =================================================================================================

void Cpu::op_LD_E_C()
{
    E = C;
}

// =================================================================================================

void Cpu::op_LD_E_D()
{
    E = D;
}

// =================================================================================================

void Cpu::op_LD_E_E()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_E_H()
{
    E = H;
}

// =================================================================================================

void Cpu::op_LD_E_L()
{
    E = L;
}

// =================================================================================================

void Cpu::op_LD_E__HL__()
{
    E = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_E_A()
{
    E = A;
}

// =================================================================================================

void Cpu::op_LD_H_B()
{
    H = B;
}

// =================================================================================================

void Cpu::op_LD_H_C()
{
    H = C;
}

// =================================================================================================

void Cpu::op_LD_H_D()
{
    H = D;
}

// =================================================================================================

void Cpu::op_LD_H_E()
{
    H = E;
}

// =================================================================================================

void Cpu::op_LD_H_H()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_H_L()
{
    H = L;
}

// =================================================================================================

void Cpu::op_LD_H__HL__()
{
    H = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_H_A()
{
    H = A;
}

// =================================================================================================

void Cpu::op_LD_L_B()
{
    L = B;
}

// =================================================================================================

void Cpu::op_LD_L_C()
{
    L = C;
}

// =================================================================================================

void Cpu::op_LD_L_D()
{
    L = D;
}

// =================================================================================================

void Cpu::op_LD_L_E()
{
    L = E;
}

// =================================================================================================

void Cpu::op_LD_L_H()
{
    L = H;
}

// =================================================================================================

void Cpu::op_LD_L_L()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_LD_L__HL__()
{
    L = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_L_A()
{
    L = A;
}

// =================================================================================================

void Cpu::op_LD__HL__B()
{
    loadByteToAddress(HL, B);
}

// =================================================================================================

void Cpu::op_LD__HL__C()
{
    loadByteToAddress(HL, C);
}

// =================================================================================================

void Cpu::op_LD__HL__D()
{
    loadByteToAddress(HL, D);
}

// =================================================================================================

void Cpu::op_LD__HL__E()
{
    loadByteToAddress(HL, E);
}

// =================================================================================================

void Cpu::op_LD__HL__H()
{
    loadByteToAddress(HL, E);
}

// =================================================================================================

void Cpu::op_LD__HL__L()
{
    loadByteToAddress(HL, L);
}

// =================================================================================================

void Cpu::op_HALT()
{
    waitForInterrupt();
}

// =================================================================================================

void Cpu::op_LD__HL__A()
{
    loadByteToAddress(HL, A);
}

// =================================================================================================

void Cpu::op_LD_A_B()
{
    A = B;
}

// =================================================================================================

void Cpu::op_LD_A_C()
{
    A = C;
}

// =================================================================================================

void Cpu::op_LD_A_D()
{
    A = D;
}

// =================================================================================================

void Cpu::op_LD_A_E()
{
    A = E;
}

// =================================================================================================

void Cpu::op_LD_A_H()
{
    A = H;
}

// =================================================================================================

void Cpu::op_LD_A_L()
{
    A = L;
}

// =================================================================================================

void Cpu::op_LD_A__HL__()
{
    A = fetchByteFromAddress(HL);
}

// =================================================================================================

void Cpu::op_LD_A_A()
{
    // Avoid self assignment.
}

// =================================================================================================

void Cpu::op_ADD_A_B()
{
    const bool halfCarry = hasHalfCarry(A, B);
    const bool carry = hasCarry(A, B);

    A += B;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_C()
{
    const bool halfCarry = hasHalfCarry(A, C);
    const bool carry = hasCarry(A, C);

    A += C;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_D()
{
    const bool halfCarry = hasHalfCarry(A, D);
    const bool carry = hasCarry(A, D);

    A += D;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_E()
{
    const bool halfCarry = hasHalfCarry(A, E);
    const bool carry = hasCarry(A, E);

    A += E;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_H()
{
    const bool halfCarry = hasHalfCarry(A, H);
    const bool carry = hasCarry(A, H);

    A += H;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_L()
{
    const bool halfCarry = hasHalfCarry(A, L);
    const bool carry = hasCarry(A, L);

    A += L;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);

    const bool halfCarry = hasHalfCarry(A, byte);
    const bool carry = hasCarry(A, byte);

    A += byte;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADD_A_A()
{
    const bool halfCarry = hasHalfCarry(A, A);
    const bool carry = hasCarry(A, A);

    A += A;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_B()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(B + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(B + carryFlag));

    A += B + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_C()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(C + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(C + carryFlag));

    A += C + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_D()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(D + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(D + carryFlag));

    A += D + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_E()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(E + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(E + carryFlag));

    A += E + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_H()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(H + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(H + carryFlag));

    A += H + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_L()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(L + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(L + carryFlag));

    A += L + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(byte + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(byte + carryFlag));

    A += byte + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_ADC_A_A()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(A + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(A + carryFlag));

    A += A + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_B()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, B));
    const bool noBorrow = !(hasBorrow(A, B));

    A -= B;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_C()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, C));
    const bool noBorrow = !(hasBorrow(A, C));

    A -= C;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_D()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, D));
    const bool noBorrow = !(hasBorrow(A, D));

    A -= D;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_E()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, E));
    const bool noBorrow = !(hasBorrow(A, E));

    A -= E;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_H()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, H));
    const bool noBorrow = !(hasBorrow(A, H));

    A -= H;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_L()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, L));
    const bool noBorrow = !(hasBorrow(A, L));

    A -= L;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);

    const bool noHalfBorrow = !(hasHalfBorrow(A, byte));
    const bool noBorrow = !(hasBorrow(A, byte));

    A -= byte;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SUB_A()
{
    // A - A == 0 and no borrow or half borrow.
    A = 0;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, true);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, true);
}

// =================================================================================================

void Cpu::op_SBC_A_B()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(B + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(B + carryFlag)));

    A -= B + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_C()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(C + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(C + carryFlag)));

    A -= C + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_D()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(D + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(D + carryFlag)));

    A -= D + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_E()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(E + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(E + carryFlag)));

    A -= E + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_H()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(H + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(H + carryFlag)));

    A -= H + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_L()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(L + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(L + carryFlag)));

    A -= L + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A__HL__()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));
    const uint8_t byte = fetchByteFromAddress(HL);

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(byte + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(byte + carryFlag)));

    A -= byte + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_SBC_A_A()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(A + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(A + carryFlag)));

    A -= A + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_B()
{
    A &= B;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_C()
{
    A &= C;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_D()
{
    A &= D;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_E()
{
    A &= E;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_H()
{
    A &= H;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_L()
{
    A &= L;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);

    A &= byte;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_AND_A()
{
    // Nothing to do for A & A.

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_B()
{
    A ^= B;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_C()
{
    A ^= C;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_D()
{
    A ^= D;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_E()
{
    A ^= E;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_H()
{
    A ^= H;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_L()
{
    A ^= L;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    A ^= byte;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_XOR_A()
{
    // A ^ A is 0.
    A = 0;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, true);
}

// =================================================================================================

void Cpu::op_OR_B()
{
    A |= B;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_C()
{
    A |= C;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_D()
{
    A |= D;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_E()
{
    A |= E;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_H()
{
    A |= H;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_L()
{
    A |= L;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);
    A |= byte;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_OR_A()
{
    // Nothing to do for A | A.

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_CP_B()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, B));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < B);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == B));
}

// =================================================================================================

void Cpu::op_CP_C()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, C));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < C);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == C));
}

// =================================================================================================

void Cpu::op_CP_D()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, D));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < D);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == D));
}

// =================================================================================================

void Cpu::op_CP_E()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, E));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < E);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == E));
}

// =================================================================================================

void Cpu::op_CP_H()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, H));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < H);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == H));
}

// =================================================================================================

void Cpu::op_CP_L()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, L));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < L);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == L));
}

// =================================================================================================

void Cpu::op_CP__HL__()
{
    const uint8_t byte = fetchByteFromAddress(HL);

    const bool noHalfBorrow = !(hasHalfBorrow(A, byte));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < byte);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == byte));
}

// =================================================================================================

void Cpu::op_CP_A()
{
    // Nothing to do for A == A.

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, true);
}

// =================================================================================================

void Cpu::op_RET_NZ()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        const uint8_t lByte = fetchByteFromAddress(SP);
        const uint8_t hByte = fetchByteFromAddress(SP + 1);
        SP += 2;

        const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

        PC = addr;
    }
}

// =================================================================================================

void Cpu::op_POP_BC()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);

    BC = cbutil::combineTowBytes(lByte, hByte);

    SP += 2;
}

// =================================================================================================

void Cpu::op_JP_NZ_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_JP_a16()
{
    PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
}

// =================================================================================================

void Cpu::op_CALL_NZ_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        loadWordToAddress(PC, SP - 2);
        SP -= 2;

        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_PUSH_BC()
{
    loadWordToAddress(BC, SP - 2);

    SP -= 2;
}

// =================================================================================================

void Cpu::op_ADD_A_d8()
{
    const uint8_t byte = MBR[0];

    const bool halfCarry = hasHalfCarry(A, byte);
    const bool carry = hasCarry(A, byte);

    A += byte;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_00H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x0;
}

// =================================================================================================

void Cpu::op_RET_Z()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        const uint8_t lByte = fetchByteFromAddress(SP);
        const uint8_t hByte = fetchByteFromAddress(SP + 1);
        SP += 2;

        const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

        PC = addr;
    }
}

// =================================================================================================

void Cpu::op_RET()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);
    SP += 2;

    const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

    PC = addr;
}

// =================================================================================================

void Cpu::op_JP_Z_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_PREFIX_CB()
{
}

// =================================================================================================

void Cpu::op_CALL_Z_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        loadWordToAddress(PC, SP - 2);
        SP -= 2;

        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_CALL_a16()
{
    loadWordToAddress(PC, SP - 2);
    SP -= 2;

    PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
}

// =================================================================================================

void Cpu::op_ADC_A_d8()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const uint8_t byte = MBR[0];

    const bool halfCarry = hasHalfCarry(static_cast<const uint16_t>(A),
                                        static_cast<const uint16_t>(byte + carryFlag));
    const bool carry = hasCarry(static_cast<const uint16_t>(A),
                                static_cast<const uint16_t>(byte + carryFlag));

    A += byte + carryFlag;

    // Set if carry from bit 7.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_08H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x8;
}

// =================================================================================================

void Cpu::op_RET_NC()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        const uint8_t lByte = fetchByteFromAddress(SP);
        const uint8_t hByte = fetchByteFromAddress(SP + 1);
        SP += 2;

        const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

        PC = addr;
    }
}

// =================================================================================================

void Cpu::op_POP_DE()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);

    DE = cbutil::combineTowBytes(lByte, hByte);

    SP += 2;
}

// =================================================================================================

void Cpu::op_JP_NC_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_CALL_NC_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        loadWordToAddress(PC, SP - 2);
        SP -= 2;

        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_PUSH_DE()
{
    loadWordToAddress(DE, SP - 2);

    SP -= 2;
}

// =================================================================================================

void Cpu::op_SUB_d8()
{
    const uint8_t byte = MBR[0];

    const bool noHalfBorrow = !(hasHalfBorrow(A, byte));
    const bool noBorrow = !(hasBorrow(A, byte));

    A -= byte;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_10H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x10;
}

// =================================================================================================

void Cpu::op_RET_C()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        const uint8_t lByte = fetchByteFromAddress(SP);
        const uint8_t hByte = fetchByteFromAddress(SP + 1);
        SP += 2;

        const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

        PC = addr;
    }
}

// =================================================================================================

void Cpu::op_RETI()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);
    SP += 2;

    const uint16_t addr = cbutil::combineTowBytes(lByte, hByte);

    PC = addr;

    enableInterrupts();
}

// =================================================================================================

void Cpu::op_JP_C_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_CALL_C_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        loadWordToAddress(PC, SP - 2);
        SP -= 2;

        PC = cbutil::combineTowBytes(MBR[0], MBR[1]);
    }
}

// =================================================================================================

void Cpu::op_SBC_A_d8()
{
    const uint8_t carryFlag = static_cast<uint8_t>(
        checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));

    const uint8_t byte = MBR[0];

    const bool noHalfBorrow = !(hasHalfBorrow(A, static_cast<const uint16_t>(byte + carryFlag)));
    const bool noBorrow = !(hasBorrow(A, static_cast<const uint16_t>(byte + carryFlag)));

    A -= byte + carryFlag;

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, noBorrow);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_18H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x18;
}

// =================================================================================================

void Cpu::op_LDH__a8__A()
{
    const uint16_t addr = MBR[0] + 0xFF00;
    loadByteToAddress(addr, A);
}

// =================================================================================================

void Cpu::op_POP_HL()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);

    HL = cbutil::combineTowBytes(lByte, hByte);

    SP += 2;
}

// =================================================================================================

void Cpu::op_LD__C__A()
{
    const uint16_t addr = C + 0xFF00;
    loadByteToAddress(addr, A);
}

// =================================================================================================

void Cpu::op_PUSH_HL()
{
    loadWordToAddress(HL, SP - 2);

    SP -= 2;
}

// =================================================================================================

void Cpu::op_AND_d8()
{
    A &= MBR[0];

    // Set if no borrow.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    // Set if no borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_20H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x20;
}

// =================================================================================================

void Cpu::op_ADD_SP_r8()
{
    const uint8_t byte = MBR[0];

    const bool halfCarry = hasHalfCarry(A, byte);
    const bool carry = hasCarry(A, byte);

    SP += byte;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, false);
}

// =================================================================================================

void Cpu::op_JP__HL__()
{
    PC = HL;
}

// =================================================================================================

void Cpu::op_LD__a16__A()
{
    const uint16_t addr = cbutil::combineTowBytes(MBR[0], MBR[1]);

    loadByteToAddress(addr, A);
}

// =================================================================================================

void Cpu::op_XOR_d8()
{
    A ^= MBR[0];

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_28H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x28;
}

// =================================================================================================

void Cpu::op_LDH_A__a8__()
{
    const uint16_t addr = MBR[0] + 0xFF00;
    A = fetchByteFromAddress(addr);
}

// =================================================================================================

void Cpu::op_POP_AF()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);

    AF = cbutil::combineTowBytes(lByte, hByte);

    SP += 2;
}

// =================================================================================================

void Cpu::op_LD_A__C__()
{
    const uint16_t addr = C + 0xFF00;

    A = fetchByteFromAddress(addr);
}

// =================================================================================================

void Cpu::op_DI()
{
    disableInterrupts();
}

// =================================================================================================

void Cpu::op_PUSH_AF()
{
    loadWordToAddress(AF, SP - 2);

    SP -= 2;
}

// =================================================================================================

void Cpu::op_OR_d8()
{
    A |= MBR[0];

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_RST_30H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x30;
}

// =================================================================================================

void Cpu::op_LD_HL_SP_plus_r8()
{
    // Offset can be a signed value.
    const int8_t byte = static_cast<const int8_t>(MBR[0]);

    const bool halfCarry = hasHalfCarry(SP, byte);
    const bool carry = hasCarry(SP, byte);

    HL = SP + byte;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, carry);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));
}

// =================================================================================================

void Cpu::op_LD_SP_HL()
{
    SP = HL;
}

// =================================================================================================

void Cpu::op_LD_A__a16__()
{
    const uint16_t addr = cbutil::combineTowBytes(MBR[0], MBR[1]);
    A = fetchByteFromAddress(addr);
}

// =================================================================================================

void Cpu::op_EI()
{
    enableInterrupts();
}

// =================================================================================================

void Cpu::op_CP_d8()
{
    const uint8_t byte = MBR[0];
    const bool noHalfBorrow = !(hasHalfBorrow(A, byte));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < byte);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == byte));
}

// =================================================================================================

void Cpu::op_RST_38H()
{
    loadWordToAddress(m_currentInstructionAddr, SP - 2);
    SP -= 2;

    PC = 0x38;
}
