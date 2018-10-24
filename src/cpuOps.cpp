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
/// THE SOFTWARE IS PROVIDED "AS IS", m_currentInstructionAddr,  WITHOUT WARRANTY OF ANY KIND,
/// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
/// A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
/// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE

/// \file      cpuOps.cpp
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      03-06-2018

// Local includes.
#include "cpu.h"

#include "utils.h"

void Cpu::execPUSH(const uint16_t word)
{
    SP -= 2;
    loadWordToAddress(word, SP);
}

// =================================================================================================

uint16_t Cpu::execPOP()
{
    const uint8_t lByte = fetchByteFromAddress(SP);
    const uint8_t hByte = fetchByteFromAddress(SP + 1);

    SP += 2;

    const uint16_t word = cbutil::combineTwoBytes(lByte, hByte);

    return word;
}

// =================================================================================================

void Cpu::op_NOP()
{
    printf("0x%04x\t NOP\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_BC_d16()
{
    B = MBR[0];
    C = MBR[1];

    printf("0x%04x\t LD BC, $%x\n", m_currentInstructionAddr, BC);
}

// =================================================================================================

void Cpu::op_LD__BC__A()
{
    loadByteToAddress(A, BC);

    printf("0x%04x\t LD BC, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC_BC()
{
    ++BC;

    printf("0x%04x\t INC BC\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_d8()
{
    B = MBR[0];

    printf("0x%04x\t LD B, $%x\n", m_currentInstructionAddr, B);
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

    printf("0x%04x\t RLCA\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__a16__SP()
{
    const uint16_t addr = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    loadWordToAddress(SP, addr);

    printf("0x%04x\t LD ($%x), SP\n", m_currentInstructionAddr, addr);
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

    printf("0x%04x\t ADD HL, BC\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__BC__()
{
    A = fetchByteFromAddress(BC);

    printf("0x%04x\t ADD A, (BC)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DEC_BC()
{
    --BC;

    printf("0x%04x\t DEC BC\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_d8()
{
    C = MBR[0];

    printf("0x%04x\t LD C, $%x\n", m_currentInstructionAddr, C);
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

    printf("0x%04x\t RRCA\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_STOP()
{
    switchState(InstructionCycleState::eStop);

    printf("0x%04x\t STOP\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_DE_d16()
{
    D = MBR[0];
    E = MBR[1];

    printf("0x%04x\t LD DE, $%x\n", m_currentInstructionAddr, DE);
}

// =================================================================================================

void Cpu::op_LD__DE__A()
{
    loadByteToAddress(A, DE);

    printf("0x%04x\t LD (DE), A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC_DE()
{
    ++DE;

    printf("0x%04x\t INC DE\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_d8()
{
    D = MBR[0];

    printf("0x%04x\t LD D, $%x\n", m_currentInstructionAddr, D);
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

    printf("0x%04x\t RLA\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JR_r8()
{
    PC += static_cast<const int8_t>(MBR[0]);

    printf("0x%04x\t JR $%x\n", m_currentInstructionAddr, MBR[0]);
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

    printf("0x%04x\t ADD HL, DE\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__DE__()
{
    A = fetchByteFromAddress(DE);

    printf("0x%04x\t LD A, (DE)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DEC_DE()
{
    --DE;

    printf("0x%04x\t DEC DE\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC_E()
{
    ++E;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((E & 0x0F) == 0x0F));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (E == 0));

    printf("0x%04x\t INC E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_d8()
{
    E = MBR[0];

    printf("0x%04x\t LD E, $%x\n", m_currentInstructionAddr, E);
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

    printf("0x%04x\t RRA\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JR_NZ_r8()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        const uint8_t jumpFactor = static_cast<const uint8_t>(
            checkFlagRegisterBit(FlagRegisterBits::eZeroFlag));
        PC += static_cast<const int8_t>(MBR[0]) * !jumpFactor;
    }

    printf("0x%04x\t JR NZ, $%02x\n",
           m_currentInstructionAddr,
           static_cast<const int8_t>(MBR[0]) & 0xFF);
}

// =================================================================================================

void Cpu::op_LD_HL_d16()
{
    HL = cbutil::combineTwoBytes(MBR[0], MBR[1]);

    printf("0x%04x\t LD HL, $%x\n", m_currentInstructionAddr, HL);
}

// =================================================================================================

void Cpu::op_LD__HLplus__A()
{
    loadByteToAddress(A, HL);
    ++HL;

    printf("0x%04x\t LD (HL+), A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC_HL()
{
    ++HL;

    printf("0x%04x\t INC HL\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_d8()
{
    H = MBR[0];

    printf("0x%04x\t LD H, $%x\n", m_currentInstructionAddr, H);
}

// =================================================================================================

void Cpu::op_DAA()
{
    const bool substractOccured = checkFlagRegisterBit(FlagRegisterBits::eSubtractFlag);
    const bool carryOccured = checkFlagRegisterBit(FlagRegisterBits::eCarryFlag);
    const bool halfCarryOccured = checkFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag);

    if (substractOccured == false)
    {
        if ((carryOccured == true) || (A > 0x99))
        {
            A += 0x60;
            setFlagRegisterBit(FlagRegisterBits::eCarryFlag, true);
        }

        if ((halfCarryOccured == true) || ((A & 0x0f) > 0x09))
        {
            A += 0x06;
        }
    }
    else
    {
        if (carryOccured == true)
        {
            A -= 0x60;
        }

        if (halfCarryOccured == true)
        {
            A -= 0x06;
        }
    }

    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t DAA\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JR_Z_r8()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        const uint8_t jumpFactor = static_cast<const uint8_t>(
            checkFlagRegisterBit(FlagRegisterBits::eZeroFlag));
        PC += static_cast<const int8_t>(MBR[0]) * jumpFactor;
    }

    printf("0x%04x\t JR Z, $%02x\n",
           m_currentInstructionAddr,
           static_cast<const int8_t>(MBR[0]) & 0xFF);
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

    printf("0x%04x\t ADD HL, HL\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__HLplus__()
{
    A = fetchByteFromAddress(HL);
    ++HL;

    printf("0x%04x\t ADD A, (HL+)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DEC_HL()
{
    --HL;

    printf("0x%04x\t DEC HL\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_d8()
{
    L = MBR[0];

    printf("0x%04x\t LD L, $%x\n", m_currentInstructionAddr, L);
}

// =================================================================================================

void Cpu::op_CPL()
{
    A = ~A;

    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);

    printf("0x%04x\t CPL\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JR_NC_r8()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        const uint8_t jumpFactor = static_cast<const uint8_t>(
            checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));
        PC += static_cast<const int8_t>(MBR[0]) * !jumpFactor;
    }

    printf("0x%04x\t JR NC, $%02x\n",
           m_currentInstructionAddr,
           static_cast<const int8_t>(MBR[0]) & 0xFF);
}

// =================================================================================================

void Cpu::op_LD_SP_d16()
{
    SP = cbutil::combineTwoBytes(MBR[0], MBR[1]);

    printf("0x%04x\t LD SP, $%x\n", m_currentInstructionAddr, SP);
}

// =================================================================================================

void Cpu::op_LD__HLminus__A()
{
    loadByteToAddress(A, HL);
    --HL;

    printf("0x%04x\t LD (HL-), A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC_SP()
{
    ++SP;

    printf("0x%04x\t INC SP\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_INC__HL__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    uint8_t byte = fetchByteFromAddress(HL);

    const bool halfCarry = hasHalfCarry(byte);
    ++byte;
    loadByteToAddress(byte, HL);

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, halfCarry);

    printf("0x%04x\t INC (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DEC__HL__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    uint8_t byte = fetchByteFromAddress(HL);

    const bool noHalfBorrow = !(hasHalfBorrow(byte));
    --byte;
    loadByteToAddress(byte, HL);

    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (byte == 0));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);

    printf("0x%04x\t DEC (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__d8()
{
    loadByteToAddress(MBR[0], HL);

    printf("0x%04x\t LD (HL), $%x\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_SCF()
{
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, true);

    printf("0x%04x\t SCF\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JR_C_r8()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        const uint8_t jumpFactor = static_cast<const uint8_t>(
            checkFlagRegisterBit(FlagRegisterBits::eCarryFlag));
        PC += static_cast<const int8_t>(MBR[0]) * jumpFactor;
    }

    printf("0x%04x\t JR C, $%02x\n",
           m_currentInstructionAddr,
           static_cast<const int8_t>(MBR[0]) & 0xFF);
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

    printf("0x%04x\t ADD HL, SP\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__HLminus__()
{
    // TODO: Check if the fetched byte should be stored in a specific register before the
    // incrementation.
    const uint8_t byte = fetchByteFromAddress(HL);
    A = byte;

    --HL;

    printf("0x%04x\t LD A, (HL-)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DEC_SP()
{
    --SP;

    printf("0x%04x\t DEC SP\n", m_currentInstructionAddr);
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

    printf("0x%04x\t INC A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t DEC A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_d8()
{
    A = MBR[0];

    printf("0x%04x\t LD A, $%x\n", m_currentInstructionAddr, A);
}

// =================================================================================================

void Cpu::op_CCF()
{
    const bool carryFlag = checkFlagRegisterBit(FlagRegisterBits::eCarryFlag);

    // Complement carry flag.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, !carryFlag);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);

    printf("0x%04x\t CCF\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_B()
{
    // Avoid self assignment.
    printf("0x%04x\t LD B, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_C()
{
    B = C;

    printf("0x%04x\t LD B, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_D()
{
    B = D;

    printf("0x%04x\t LD B, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_E()
{
    B = E;

    printf("0x%04x\t LD B, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_H()
{
    B = H;

    printf("0x%04x\t LD B, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_L()
{
    B = L;

    printf("0x%04x\t LD B, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B__HL__()
{
    B = fetchByteFromAddress(HL);

    printf("0x%04x\t LD B, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_B_A()
{
    B = A;

    printf("0x%04x\t LD B, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_B()
{
    C = B;

    printf("0x%04x\t LD C, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_C()
{
    // Avoid self assignment.
    printf("0x%04x\t LD C, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_D()
{
    C = D;

    printf("0x%04x\t LD C, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_E()
{
    C = E;

    printf("0x%04x\t LD C, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_H()
{
    C = H;

    printf("0x%04x\t LD C, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_L()
{
    C = L;

    printf("0x%04x\t LD C, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C__HL__()
{
    C = fetchByteFromAddress(HL);

    printf("0x%04x\t LD C, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_C_A()
{
    C = A;

    printf("0x%04x\t LD C, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_B()
{
    D = B;

    printf("0x%04x\t LD D, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_C()
{
    D = C;

    printf("0x%04x\t LD D, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_D()
{
    // Avoid self assignment.
    printf("0x%04x\t LD D, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_E()
{
    D = E;

    printf("0x%04x\t LD D, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_H()
{
    D = H;

    printf("0x%04x\t LD D, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_L()
{
    D = L;

    printf("0x%04x\t LD D, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D__HL__()
{
    D = fetchByteFromAddress(HL);

    printf("0x%04x\t LD D, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_D_A()
{
    D = A;

    printf("0x%04x\t LD D, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_B()
{
    E = B;

    printf("0x%04x\t LD E, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_C()
{
    E = C;

    printf("0x%04x\t LD E, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_D()
{
    E = D;

    printf("0x%04x\t LD E, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_E()
{
    // Avoid self assignment.
    printf("0x%04x\t LD E, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_H()
{
    E = H;

    printf("0x%04x\t LD E, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_L()
{
    E = L;

    printf("0x%04x\t LD E, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E__HL__()
{
    E = fetchByteFromAddress(HL);

    printf("0x%04x\t LD E, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_E_A()
{
    E = A;

    printf("0x%04x\t LD E, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_B()
{
    H = B;

    printf("0x%04x\t LD H, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_C()
{
    H = C;

    printf("0x%04x\t LD H, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_D()
{
    H = D;

    printf("0x%04x\t LD H, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_E()
{
    H = E;

    printf("0x%04x\t LD H, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_H()
{
    // Avoid self assignment.
    printf("0x%04x\t LD H, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_L()
{
    H = L;

    printf("0x%04x\t LD H, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H__HL__()
{
    H = fetchByteFromAddress(HL);

    printf("0x%04x\t LD H, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_H_A()
{
    H = A;

    printf("0x%04x\t LD H, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_B()
{
    L = B;

    printf("0x%04x\t LD L, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_C()
{
    L = C;

    printf("0x%04x\t LD L, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_D()
{
    L = D;

    printf("0x%04x\t LD L, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_E()
{
    L = E;

    printf("0x%04x\t LD L, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_H()
{
    L = H;

    printf("0x%04x\t LD L, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_L()
{
    // Avoid self assignment.
    printf("0x%04x\t LD L, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L__HL__()
{
    L = fetchByteFromAddress(HL);

    printf("0x%04x\t LD L, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_L_A()
{
    L = A;

    printf("0x%04x\t LD L, A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__B()
{
    loadByteToAddress(B, HL);

    printf("0x%04x\t LD (HL), B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__C()
{
    loadByteToAddress(C, HL);

    printf("0x%04x\t LD (HL), C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__D()
{
    loadByteToAddress(D, HL);

    printf("0x%04x\t LD (HL), D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__E()
{
    loadByteToAddress(E, HL);

    printf("0x%04x\t LD (HL), E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__H()
{
    loadByteToAddress(E, HL);

    printf("0x%04x\t LD (HL), H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__L()
{
    loadByteToAddress(L, HL);

    printf("0x%04x\t LD (HL), L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_HALT()
{
    waitForInterrupt();

    printf("0x%04x\t HALT\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__HL__A()
{
    loadByteToAddress(A, HL);

    printf("0x%04x\t LD (HL), A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_B()
{
    A = B;

    printf("0x%04x\t LD A, B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_C()
{
    A = C;

    printf("0x%04x\t LD A, C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_D()
{
    A = D;

    printf("0x%04x\t LD A, D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_E()
{
    A = E;

    printf("0x%04x\t LD A, E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_H()
{
    A = H;

    printf("0x%04x\t LD A, H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_L()
{
    A = L;

    printf("0x%04x\t LD A, L\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__HL__()
{
    A = fetchByteFromAddress(HL);

    printf("0x%04x\t LD A, (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A_A()
{
    // Avoid self assignment.
    printf("0x%04x\t LD A, A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADC A, A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SBC A, A\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND B\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND C\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND D\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND E\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_B()
{
    A ^= B;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_C()
{
    A ^= C;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_D()
{
    A ^= D;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_E()
{
    A ^= E;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_H()
{
    A ^= H;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_XOR_L()
{
    A ^= L;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t XOR (HL)\n", m_currentInstructionAddr);
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

    printf("0x%04x\t XOR A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_B()
{
    A |= B;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_C()
{
    A |= C;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_D()
{
    A |= D;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_E()
{
    A |= E;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_H()
{
    A |= H;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_L()
{
    A |= L;

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t OR (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_A()
{
    // Nothing to do for A | A.

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_B()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, B));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < B);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == B));

    printf("0x%04x\t CP B\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_C()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, C));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < C);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == C));

    printf("0x%04x\t CP C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_D()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, D));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < D);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == D));

    printf("0x%04x\t CP D\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_E()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, E));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < E);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == E));

    printf("0x%04x\t CP E\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_H()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, H));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < H);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == H));

    printf("0x%04x\t CP H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_L()
{
    const bool noHalfBorrow = !(hasHalfBorrow(A, L));

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, A < L);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, noHalfBorrow);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == L));

    printf("0x%04x\t CP L\n", m_currentInstructionAddr);
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

    printf("0x%04x\t CP (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_CP_A()
{
    // Nothing to do for A == A.

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, true);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, true);

    printf("0x%04x\t CP A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RET_NZ()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        PC = execPOP();
    }

    printf("0x%04x\t RET NZ\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_POP_BC()
{
    BC = execPOP();

    printf("0x%04x\t POP BC\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JP_NZ_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t JP NZ, $%x\n", m_currentInstructionAddr, PC);
}

// =================================================================================================

void Cpu::op_JP_a16()
{
    PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);

    printf("0x%04x\t JP $%x\n", m_currentInstructionAddr, PC);
}

// =================================================================================================

void Cpu::op_CALL_NZ_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == false)
    {
        execPUSH(PC);

        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t CALL NZ, $%x\n", m_currentInstructionAddr, PC);
}

// =================================================================================================

void Cpu::op_PUSH_BC()
{
    execPUSH(BC);

    printf("0x%04x\t PUSH BC\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD A, $%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_RST_00H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x0;

    printf("0x%04x\t RST 00H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RET_Z()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        PC = execPOP();
    }

    printf("0x%04x\t RET Z\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RET()
{
    PC = execPOP();

    printf("0x%04x\t RET\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JP_Z_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t JP Z, $%x\n", m_currentInstructionAddr, PC);
}

// =================================================================================================

void Cpu::op_PREFIX_CB()
{
    m_inPrefixCBOp = true;
}

// =================================================================================================

void Cpu::op_CALL_Z_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eZeroFlag) == true)
    {
        execPUSH(PC);

        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t CALL Z, $%x\n", m_currentInstructionAddr, PC);
}

// =================================================================================================

void Cpu::op_CALL_a16()
{
    execPUSH(PC);

    PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);

    printf("0x%04x\t CALL $%x\n", m_currentInstructionAddr, PC);
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

    printf("0x%04x\t ADC A, $%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_RST_08H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x8;

    printf("0x%04x\t RST 08H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RET_NC()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        PC = execPOP();
    }

    printf("0x%04x\t RET NC\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_POP_DE()
{
    DE = execPOP();

    printf("0x%04x\t POP DE\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JP_NC_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t JP NC, $%x\n",
           m_currentInstructionAddr,
           cbutil::combineTwoBytes(MBR[0], MBR[1]));
}

// =================================================================================================

void Cpu::op_CALL_NC_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == false)
    {
        execPUSH(PC);

        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t CALL NC, $%x\n",
           m_currentInstructionAddr,
           cbutil::combineTwoBytes(MBR[0], MBR[1]));
}

// =================================================================================================

void Cpu::op_PUSH_DE()
{
    execPUSH(DE);

    printf("0x%04x\t PUSH DE\n", m_currentInstructionAddr);
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

    printf("0x%04x\t SUB $%d\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_RST_10H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x10;

    printf("0x%04x\t RST 10H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RET_C()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        PC = execPOP();
    }

    printf("0x%04x\t RET C\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_RETI()
{
    PC = execPOP();

    enableInterrupts();

    printf("0x%04x\t RETI\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_JP_C_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t JP C, $%x\n",
           m_currentInstructionAddr,
           cbutil::combineTwoBytes(MBR[0], MBR[1]));
}

// =================================================================================================

void Cpu::op_CALL_C_a16()
{
    if (checkFlagRegisterBit(FlagRegisterBits::eCarryFlag) == true)
    {
        execPUSH(PC);

        PC = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    }

    printf("0x%04x\t CALL C, $%x\n",
           m_currentInstructionAddr,
           cbutil::combineTwoBytes(MBR[0], MBR[1]));
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

    printf("0x%04x\t SBC A, $%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_RST_18H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x18;

    printf("0x%04x\t RST 18H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LDH__a8__A()
{
    const uint16_t addr = MBR[0] + 0xFF00;
    loadByteToAddress(A, addr);

    printf("0x%04x\t LDH ($%x), A\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_POP_HL()
{
    HL = execPOP();

    printf("0x%04x\t POP HL\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__C__A()
{
    const uint16_t addr = C + 0xFF00;
    loadByteToAddress(A, addr);

    printf("0x%04x\t LD (C), A\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_PUSH_HL()
{
    execPUSH(HL);

    printf("0x%04x\t PUSH HL\n", m_currentInstructionAddr);
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

    printf("0x%04x\t AND $%x\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_RST_20H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x20;

    printf("0x%04x\t RST 20H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t ADD SP, $%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_JP__HL__()
{
    PC = HL;

    printf("0x%04x\t JP (HL)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD__a16__A()
{
    const uint16_t addr = cbutil::combineTwoBytes(MBR[0], MBR[1]);

    loadByteToAddress(A, addr);

    printf("0x%04x\t LD ($%x), A\n", m_currentInstructionAddr, addr);
}

// =================================================================================================

void Cpu::op_XOR_d8()
{
    A ^= MBR[0];

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t XOR $%x\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_RST_28H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x28;

    printf("0x%04x\t RST 28H\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LDH_A__a8__()
{
    const uint16_t addr = MBR[0] + 0xFF00;
    A = fetchByteFromAddress(addr);

    printf("0x%04x\t LDH A, ($%x)\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_POP_AF()
{
    AF = execPOP();

    printf("0x%04x\t POP AF\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__C__()
{
    const uint16_t addr = C + 0xFF00;

    A = fetchByteFromAddress(addr);

    printf("0x%04x\t LD A, (C)\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_DI()
{
    disableInterrupts();

    printf("0x%04x\t DI\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_PUSH_AF()
{
    execPUSH(AF);

    printf("0x%04x\t PUSH AF\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_OR_d8()
{
    A |= MBR[0];

    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (A == 0));

    printf("0x%04x\t OR $%x\n", m_currentInstructionAddr, MBR[0]);
}

// =================================================================================================

void Cpu::op_RST_30H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x30;

    printf("0x%04x\t RST 30H\n", m_currentInstructionAddr);
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

    printf("0x%04x\t LD HL, SP+$%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_LD_SP_HL()
{
    SP = HL;

    printf("0x%04x\t LD SP, HL\n", m_currentInstructionAddr);
}

// =================================================================================================

void Cpu::op_LD_A__a16__()
{
    const uint16_t addr = cbutil::combineTwoBytes(MBR[0], MBR[1]);
    A = fetchByteFromAddress(addr);

    printf("0x%04x\t LD A, ($%x)\n", m_currentInstructionAddr, addr);
}

// =================================================================================================

void Cpu::op_EI()
{
    enableInterrupts();

    printf("0x%04x\t EI\n", m_currentInstructionAddr);
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

    printf("0x%04x\t CP $%x\n", m_currentInstructionAddr, byte);
}

// =================================================================================================

void Cpu::op_RST_38H()
{
    execPUSH(m_currentInstructionAddr);

    PC = 0x38;

    printf("0x%04x\t RST 38H\n", m_currentInstructionAddr);
}
