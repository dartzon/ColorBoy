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
    ++B;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((B & 0x0F) == 0x0F));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (B == 0));
}

// =================================================================================================

void Cpu::op_DEC_B()
{
    const bool setHalfCarryFlag = (B < 1);
    --B;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, setHalfCarryFlag);
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
    HL += BC;

    // Set if carry from bit 15.
    setFlagRegisterBit(FlagRegisterBits::eCarryFlag, ((HL & 0x8000) == 0x8000));
    // Set if carry from bit 11.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((HL & 0x0800) == 0x0800));
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
    ++C;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((C & 0x0F) == 0x0F));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (C == 0));
}

// =================================================================================================

void Cpu::op_DEC_C()
{
    const bool setHalfCarryFlag = (C < 1);
    --C;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, setHalfCarryFlag);
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

    // Old bit 7 to Carry flag.
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
    ++D;

    // Set if carry from bit 3.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, ((D & 0x0F) == 0x0F));
    setFlagRegisterBit(FlagRegisterBits::eSubtractFlag, false);
    setFlagRegisterBit(FlagRegisterBits::eZeroFlag, (D == 0));
}

// =================================================================================================

void Cpu::op_DEC_D()
{
    const bool setHalfCarryFlag = (D < 1);
    --D;

    // Set if borrow from bit 4.
    setFlagRegisterBit(FlagRegisterBits::eHalfCarryFlag, setHalfCarryFlag);
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
    const bool bit7 = ((A & 0x80) == 0x80);
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
    PC += MBR[0];
}

// =================================================================================================

void Cpu::op_ADD_HL_DE()
{
}  // 0x19
void Cpu::op_LD_A__DE__()
{
}  // 0x1A
void Cpu::op_DEC_DE()
{
}  // 0x1B
void Cpu::op_INC_E()
{
}  // 0x1C
void Cpu::op_DEC_E()
{
}  // 0x1D
void Cpu::op_LD_E_d8()
{
}  // 0x1E
void Cpu::op_RRA()
{
}  // 0x1F
void Cpu::op_JR_NZ_r8()
{
}  // 0x20
void Cpu::op_LD_HL_d16()
{
}  // 0x21
void Cpu::op_LD__HLplus__A()
{
}  // 0x22
void Cpu::op_INC_HL()
{
}  // 0x23
void Cpu::op_INC_H()
{
}  // 0x24
void Cpu::op_DEC_H()
{
}  // 0x25
void Cpu::op_LD_H_d8()
{
}  // 0x26
void Cpu::op_DAA()
{
}  // 0x27
void Cpu::op_JR_Z_r8()
{
}  // 0x28
void Cpu::op_ADD_HL_HL()
{
}  // 0x29
void Cpu::op_LD_A__HLplus__()
{
}  // 0x2A
void Cpu::op_DEC_HL()
{
}  // 0x2B
void Cpu::op_INC_L()
{
}  // 0x2C
void Cpu::op_DEC_L()
{
}  // 0x2D
void Cpu::op_LD_L_d8()
{
}  // 0x2E
void Cpu::op_CPL()
{
}  // 0x2F
void Cpu::op_JR_NC_r8()
{
}  // 0x30
void Cpu::op_LD_SP_d16()
{
}  // 0x31
void Cpu::op_LD__HLminus__A()
{
}  // 0x32
void Cpu::op_INC_SP()
{
}  // 0x33
void Cpu::op_INC__HL__()
{
}  // 0x34
void Cpu::op_DEC__HL__()
{
}  // 0x35
void Cpu::op_LD__HL__d8()
{
}  // 0x36
void Cpu::op_SCF()
{
}  // 0x37
void Cpu::op_JR_C_r8()
{
}  // 0x38
void Cpu::op_ADD_HL_SP()
{
}  // 0x39
void Cpu::op_LD_A__HLminus__()
{
}  // 0x3A
void Cpu::op_DEC_SP()
{
}  // 0x3B
void Cpu::op_INC_A()
{
}  // 0x3C
void Cpu::op_DEC_A()
{
}  // 0x3D
void Cpu::op_LD_A_d8()
{
}  // 0x3E
void Cpu::op_CCF()
{
}  // 0x3F
void Cpu::op_LD_B_B()
{
}  // 0x40
void Cpu::op_LD_B_C()
{
}  // 0x41
void Cpu::op_LD_B_D()
{
}  // 0x42
void Cpu::op_LD_B_E()
{
}  // 0x43
void Cpu::op_LD_B_H()
{
}  // 0x44
void Cpu::op_LD_B_L()
{
}  // 0x45
void Cpu::op_LD_B__HL__()
{
}  // 0x46
void Cpu::op_LD_B_A()
{
}  // 0x47
void Cpu::op_LD_C_B()
{
}  // 0x48
void Cpu::op_LD_C_C()
{
}  // 0x49
void Cpu::op_LD_C_D()
{
}  // 0x4A
void Cpu::op_LD_C_E()
{
}  // 0x4B
void Cpu::op_LD_C_H()
{
}  // 0x4C
void Cpu::op_LD_C_L()
{
}  // 0x4D
void Cpu::op_LD_C__HL__()
{
}  // 0x4E
void Cpu::op_LD_C_A()
{
}  // 0x4F
void Cpu::op_LD_D_B()
{
}  // 0x50
void Cpu::op_LD_D_C()
{
}  // 0x51
void Cpu::op_LD_D_D()
{
}  // 0x52
void Cpu::op_LD_D_E()
{
}  // 0x53
void Cpu::op_LD_D_H()
{
}  // 0x54
void Cpu::op_LD_D_L()
{
}  // 0x55
void Cpu::op_LD_D__HL__()
{
}  // 0x56
void Cpu::op_LD_D_A()
{
}  // 0x57
void Cpu::op_LD_E_B()
{
}  // 0x58
void Cpu::op_LD_E_C()
{
}  // 0x59
void Cpu::op_LD_E_D()
{
}  // 0x5A
void Cpu::op_LD_E_E()
{
}  // 0x5B
void Cpu::op_LD_E_H()
{
}  // 0x5C
void Cpu::op_LD_E_L()
{
}  // 0x5D
void Cpu::op_LD_E__HL__()
{
}  // 0x5E
void Cpu::op_LD_E_A()
{
}  // 0x5F
void Cpu::op_LD_H_B()
{
}  // 0x60
void Cpu::op_LD_H_C()
{
}  // 0x61
void Cpu::op_LD_H_D()
{
}  // 0x62
void Cpu::op_LD_H_E()
{
}  // 0x63
void Cpu::op_LD_H_H()
{
}  // 0x64
void Cpu::op_LD_H_L()
{
}  // 0x65
void Cpu::op_LD_H__HL__()
{
}  // 0x66
void Cpu::op_LD_H_A()
{
}  // 0x67
void Cpu::op_LD_L_B()
{
}  // 0x68
void Cpu::op_LD_L_C()
{
}  // 0x69
void Cpu::op_LD_L_D()
{
}  // 0x6A
void Cpu::op_LD_L_E()
{
}  // 0x6B
void Cpu::op_LD_L_H()
{
}  // 0x6C
void Cpu::op_LD_L_L()
{
}  // 0x6D
void Cpu::op_LD_L__HL__()
{
}  // 0x6E
void Cpu::op_LD_L_A()
{
}  // 0x6F
void Cpu::op_LD__HL__B()
{
}  // 0x70
void Cpu::op_LD__HL__C()
{
}  // 0x71
void Cpu::op_LD__HL__D()
{
}  // 0x72
void Cpu::op_LD__HL__E()
{
}  // 0x73
void Cpu::op_LD__HL__H()
{
}  // 0x74
void Cpu::op_LD__HL__L()
{
}  // 0x75
void Cpu::op_HALT()
{
}  // 0x76
void Cpu::op_LD__HL__A()
{
}  // 0x77
void Cpu::op_LD_A_B()
{
}  // 0x78
void Cpu::op_LD_A_C()
{
}  // 0x79
void Cpu::op_LD_A_D()
{
}  // 0x7A
void Cpu::op_LD_A_E()
{
}  // 0x7B
void Cpu::op_LD_A_H()
{
}  // 0x7C
void Cpu::op_LD_A_L()
{
}  // 0x7D
void Cpu::op_LD_A__HL__()
{
}  // 0x7E
void Cpu::op_LD_A_A()
{
}  // 0x7F
void Cpu::op_ADD_A_B()
{
}  // 0x80
void Cpu::op_ADD_A_C()
{
}  // 0x81
void Cpu::op_ADD_A_D()
{
}  // 0x82
void Cpu::op_ADD_A_E()
{
}  // 0x83
void Cpu::op_ADD_A_H()
{
}  // 0x84
void Cpu::op_ADD_A_L()
{
}  // 0x85
void Cpu::op_ADD_A__HL__()
{
}  // 0x86
void Cpu::op_ADD_A_A()
{
}  // 0x87
void Cpu::op_ADC_A_B()
{
}  // 0x88
void Cpu::op_ADC_A_C()
{
}  // 0x89
void Cpu::op_ADC_A_D()
{
}  // 0x8A
void Cpu::op_ADC_A_E()
{
}  // 0x8B
void Cpu::op_ADC_A_H()
{
}  // 0x8C
void Cpu::op_ADC_A_L()
{
}  // 0x8D
void Cpu::op_ADC_A__HL__()
{
}  // 0x8E
void Cpu::op_ADC_A_A()
{
}  // 0x8F
void Cpu::op_SUB_B()
{
}  // 0x90
void Cpu::op_SUB_C()
{
}  // 0x91
void Cpu::op_SUB_D()
{
}  // 0x92
void Cpu::op_SUB_E()
{
}  // 0x93
void Cpu::op_SUB_H()
{
}  // 0x94
void Cpu::op_SUB_L()
{
}  // 0x95
void Cpu::op_SUB__HL__()
{
}  // 0x96
void Cpu::op_SUB_A()
{
}  // 0x97
void Cpu::op_SBC_A_B()
{
}  // 0x98
void Cpu::op_SBC_A_C()
{
}  // 0x99
void Cpu::op_SBC_A_D()
{
}  // 0x9A
void Cpu::op_SBC_A_E()
{
}  // 0x9B
void Cpu::op_SBC_A_H()
{
}  // 0x9C
void Cpu::op_SBC_A_L()
{
}  // 0x9D
void Cpu::op_SBC_A__HL__()
{
}  // 0x9E
void Cpu::op_SBC_A_A()
{
}  // 0x9F
void Cpu::op_AND_B()
{
}  // 0xA0
void Cpu::op_AND_C()
{
}  // 0xA1
void Cpu::op_AND_D()
{
}  // 0xA2
void Cpu::op_AND_E()
{
}  // 0xA3
void Cpu::op_AND_H()
{
}  // 0xA4
void Cpu::op_AND_L()
{
}  // 0xA5
void Cpu::op_AND__HL__()
{
}  // 0xA6
void Cpu::op_AND_A()
{
}  // 0xA7
void Cpu::op_XOR_B()
{
}  // 0xA8
void Cpu::op_XOR_C()
{
}  // 0xA9
void Cpu::op_XOR_D()
{
}  // 0xAA
void Cpu::op_XOR_E()
{
}  // 0xAB
void Cpu::op_XOR_H()
{
}  // 0xAC
void Cpu::op_XOR_L()
{
}  // 0xAD
void Cpu::op_XOR__HL__()
{
}  // 0xAE
void Cpu::op_XOR_A()
{
}  // 0xAF
void Cpu::op_OR_B()
{
}  // 0xB0
void Cpu::op_OR_C()
{
}  // 0xB1
void Cpu::op_OR_D()
{
}  // 0xB2
void Cpu::op_OR_E()
{
}  // 0xB3
void Cpu::op_OR_H()
{
}  // 0xB4
void Cpu::op_OR_L()
{
}  // 0xB5
void Cpu::op_OR__HL__()
{
}  // 0xB6
void Cpu::op_OR_A()
{
}  // 0xB7
void Cpu::op_CP_B()
{
}  // 0xB8
void Cpu::op_CP_C()
{
}  // 0xB9
void Cpu::op_CP_D()
{
}  // 0xBA
void Cpu::op_CP_E()
{
}  // 0xBB
void Cpu::op_CP_H()
{
}  // 0xBC
void Cpu::op_CP_L()
{
}  // 0xBD
void Cpu::op_CP__HL__()
{
}  // 0xBE
void Cpu::op_CP_A()
{
}  // 0xBF
void Cpu::op_RET_NZ()
{
}  // 0xC0
void Cpu::op_POP_BC()
{
}  // 0xC1
void Cpu::op_JP_NZ_a16()
{
}  // 0xC2
void Cpu::op_JP_a16()
{
}  // 0xC3
void Cpu::op_CALL_NZ_a16()
{
}  // 0xC4
void Cpu::op_PUSH_BC()
{
}  // 0xC5
void Cpu::op_ADD_A_d8()
{
}  // 0xC6
void Cpu::op_RST_00H()
{
}  // 0xC7
void Cpu::op_RET_Z()
{
}  // 0xC8
void Cpu::op_RET()
{
}  // 0xC9
void Cpu::op_JP_Z_a16()
{
}  // 0xCA
void Cpu::op_PREFIX_CB()
{
}  // 0xCB
void Cpu::op_CALL_Z_a16()
{
}  // 0xCC
void Cpu::op_CALL_a16()
{
}  // 0xCD
void Cpu::op_ADC_A_d8()
{
}  // 0xCE
void Cpu::op_RST_08H()
{
}  // 0xCF
void Cpu::op_RET_NC()
{
}  // 0xD0
void Cpu::op_POP_DE()
{
}  // 0xD1
void Cpu::op_JP_NC_a16()
{
}  // 0xD2
void Cpu::op_CALL_NC_a16()
{
}  // 0xD4
void Cpu::op_PUSH_DE()
{
}  // 0xD5
void Cpu::op_SUB_d8()
{
}  // 0xD6
void Cpu::op_RST_10H()
{
}  // 0xD7
void Cpu::op_RET_C()
{
}  // 0xD8
void Cpu::op_RETI()
{
}  // 0xD9
void Cpu::op_JP_C_a16()
{
}  // 0xDA
void Cpu::op_CALL_C_a16()
{
}  // 0xDC
void Cpu::op_SBC_A_d8()
{
}  // 0xDE
void Cpu::op_RST_18H()
{
}  // 0xDF
void Cpu::op_LDH__a8__A()
{
}  // 0xE0
void Cpu::op_POP_HL()
{
}  // 0xE1
void Cpu::op_LD__C__A()
{
}  // 0xE2
void Cpu::op_PUSH_HL()
{
}  // 0xE5
void Cpu::op_AND_d8()
{
}  // 0xE6
void Cpu::op_RST_20H()
{
}  // 0xE7
void Cpu::op_ADD_SP_r8()
{
}  // 0xE8
void Cpu::op_JP__HL__()
{
}  // 0xE9
void Cpu::op_LD__a16__A()
{
}  // 0xEA
void Cpu::op_XOR_d8()
{
}  // 0xEE
void Cpu::op_RST_28H()
{
}  // 0xEF
void Cpu::op_LDH_A__a8__()
{
}  // 0xF0
void Cpu::op_POP_AF()
{
}  // 0xF1
void Cpu::op_LD_A__C__()
{
}  // 0xF2
void Cpu::op_DI()
{
}  // 0xF3
void Cpu::op_PUSH_AF()
{
}  // 0xF5
void Cpu::op_OR_d8()
{
}  // 0xF6
void Cpu::op_RST_30H()
{
}  // 0xF7
void Cpu::op_LD_HL_SP_plus_r8()
{
}  // 0xF8
void Cpu::op_LD_SP_HL()
{
}  // 0xF9
void Cpu::op_LD_A__a16__()
{
}  // 0xFA
void Cpu::op_EI()
{
}  // 0xFB
void Cpu::op_CP_d8()
{
}  // 0xFE
void Cpu::op_RST_38H()
{
}  // 0xFF
