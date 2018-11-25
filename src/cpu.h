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

/// \file      cpu.h
///
/// \brief     Representation of the LR35902 CPU.
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      17-05-2018

#ifndef CPU_H_
#define CPU_H_

#include "mmu.h"

#include <cstdint>
#include <array>
#include <stack>
#include <bitset>
#include <functional>

/// \brief Representation of the Sharp LR35902's Game Boy CPU.
class Cpu
{
public:
    /// \brief Constructor
    ///
    /// \param mmu Memory management unit.
    explicit Cpu(Mmu& mmu);

    /// \brief Execute one instruction at a time.
    ///
    /// \return true if the CPU is still executing instructions, false otherwise.
    bool cycle();

private:
    // =============================================================================================
    // Gameboy CPU (Sharp LR35902) instruction set.
    // =============================================================================================

    /// \brief Push a word to the stack.
    ///
    /// \param word the word to push.
    void execPUSH(const uint16_t word);

    /// \brief Pop a word from the stack.
    ///
    /// \return return the next word from the stack.
    uint16_t execPOP();

    void op_NOP();               ///< opcode: 0x00
    void op_LD_BC_d16();         ///< opcode: 0x01
    void op_LD__BC__A();         ///< opcode: 0x02
    void op_INC_BC();            ///< opcode: 0x03
    void op_INC_B();             ///< opcode: 0x04
    void op_DEC_B();             ///< opcode: 0x05
    void op_LD_B_d8();           ///< opcode: 0x06
    void op_RLCA();              ///< opcode: 0x07
    void op_LD__a16__SP();       ///< opcode: 0x08
    void op_ADD_HL_BC();         ///< opcode: 0x09
    void op_LD_A__BC__();        ///< opcode: 0x0A
    void op_DEC_BC();            ///< opcode: 0x0B
    void op_INC_C();             ///< opcode: 0x0C
    void op_DEC_C();             ///< opcode: 0x0D
    void op_LD_C_d8();           ///< opcode: 0x0E
    void op_RRCA();              ///< opcode: 0x0F
    void op_STOP();              ///< opcode: 0x10
    void op_LD_DE_d16();         ///< opcode: 0x11
    void op_LD__DE__A();         ///< opcode: 0x12
    void op_INC_DE();            ///< opcode: 0x13
    void op_INC_D();             ///< opcode: 0x14
    void op_DEC_D();             ///< opcode: 0x15
    void op_LD_D_d8();           ///< opcode: 0x16
    void op_RLA();               ///< opcode: 0x17
    void op_JR_r8();             ///< opcode: 0x18
    void op_ADD_HL_DE();         ///< opcode: 0x19
    void op_LD_A__DE__();        ///< opcode: 0x1A
    void op_DEC_DE();            ///< opcode: 0x1B
    void op_INC_E();             ///< opcode: 0x1C
    void op_DEC_E();             ///< opcode: 0x1D
    void op_LD_E_d8();           ///< opcode: 0x1E
    void op_RRA();               ///< opcode: 0x1F
    void op_JR_NZ_r8();          ///< opcode: 0x20
    void op_LD_HL_d16();         ///< opcode: 0x21
    void op_LD__HLplus__A();     ///< opcode: 0x22
    void op_INC_HL();            ///< opcode: 0x23
    void op_INC_H();             ///< opcode: 0x24
    void op_DEC_H();             ///< opcode: 0x25
    void op_LD_H_d8();           ///< opcode: 0x26
    void op_DAA();               ///< opcode: 0x27
    void op_JR_Z_r8();           ///< opcode: 0x28
    void op_ADD_HL_HL();         ///< opcode: 0x29
    void op_LD_A__HLplus__();    ///< opcode: 0x2A
    void op_DEC_HL();            ///< opcode: 0x2B
    void op_INC_L();             ///< opcode: 0x2C
    void op_DEC_L();             ///< opcode: 0x2D
    void op_LD_L_d8();           ///< opcode: 0x2E
    void op_CPL();               ///< opcode: 0x2F
    void op_JR_NC_r8();          ///< opcode: 0x30
    void op_LD_SP_d16();         ///< opcode: 0x31
    void op_LD__HLminus__A();    ///< opcode: 0x32
    void op_INC_SP();            ///< opcode: 0x33
    void op_INC__HL__();         ///< opcode: 0x34
    void op_DEC__HL__();         ///< opcode: 0x35
    void op_LD__HL__d8();        ///< opcode: 0x36
    void op_SCF();               ///< opcode: 0x37
    void op_JR_C_r8();           ///< opcode: 0x38
    void op_ADD_HL_SP();         ///< opcode: 0x39
    void op_LD_A__HLminus__();   ///< opcode: 0x3A
    void op_DEC_SP();            ///< opcode: 0x3B
    void op_INC_A();             ///< opcode: 0x3C
    void op_DEC_A();             ///< opcode: 0x3D
    void op_LD_A_d8();           ///< opcode: 0x3E
    void op_CCF();               ///< opcode: 0x3F
    void op_LD_B_B();            ///< opcode: 0x40
    void op_LD_B_C();            ///< opcode: 0x41
    void op_LD_B_D();            ///< opcode: 0x42
    void op_LD_B_E();            ///< opcode: 0x43
    void op_LD_B_H();            ///< opcode: 0x44
    void op_LD_B_L();            ///< opcode: 0x45
    void op_LD_B__HL__();        ///< opcode: 0x46
    void op_LD_B_A();            ///< opcode: 0x47
    void op_LD_C_B();            ///< opcode: 0x48
    void op_LD_C_C();            ///< opcode: 0x49
    void op_LD_C_D();            ///< opcode: 0x4A
    void op_LD_C_E();            ///< opcode: 0x4B
    void op_LD_C_H();            ///< opcode: 0x4C
    void op_LD_C_L();            ///< opcode: 0x4D
    void op_LD_C__HL__();        ///< opcode: 0x4E
    void op_LD_C_A();            ///< opcode: 0x4F
    void op_LD_D_B();            ///< opcode: 0x50
    void op_LD_D_C();            ///< opcode: 0x51
    void op_LD_D_D();            ///< opcode: 0x52
    void op_LD_D_E();            ///< opcode: 0x53
    void op_LD_D_H();            ///< opcode: 0x54
    void op_LD_D_L();            ///< opcode: 0x55
    void op_LD_D__HL__();        ///< opcode: 0x56
    void op_LD_D_A();            ///< opcode: 0x57
    void op_LD_E_B();            ///< opcode: 0x58
    void op_LD_E_C();            ///< opcode: 0x59
    void op_LD_E_D();            ///< opcode: 0x5A
    void op_LD_E_E();            ///< opcode: 0x5B
    void op_LD_E_H();            ///< opcode: 0x5C
    void op_LD_E_L();            ///< opcode: 0x5D
    void op_LD_E__HL__();        ///< opcode: 0x5E
    void op_LD_E_A();            ///< opcode: 0x5F
    void op_LD_H_B();            ///< opcode: 0x60
    void op_LD_H_C();            ///< opcode: 0x61
    void op_LD_H_D();            ///< opcode: 0x62
    void op_LD_H_E();            ///< opcode: 0x63
    void op_LD_H_H();            ///< opcode: 0x64
    void op_LD_H_L();            ///< opcode: 0x65
    void op_LD_H__HL__();        ///< opcode: 0x66
    void op_LD_H_A();            ///< opcode: 0x67
    void op_LD_L_B();            ///< opcode: 0x68
    void op_LD_L_C();            ///< opcode: 0x69
    void op_LD_L_D();            ///< opcode: 0x6A
    void op_LD_L_E();            ///< opcode: 0x6B
    void op_LD_L_H();            ///< opcode: 0x6C
    void op_LD_L_L();            ///< opcode: 0x6D
    void op_LD_L__HL__();        ///< opcode: 0x6E
    void op_LD_L_A();            ///< opcode: 0x6F
    void op_LD__HL__B();         ///< opcode: 0x70
    void op_LD__HL__C();         ///< opcode: 0x71
    void op_LD__HL__D();         ///< opcode: 0x72
    void op_LD__HL__E();         ///< opcode: 0x73
    void op_LD__HL__H();         ///< opcode: 0x74
    void op_LD__HL__L();         ///< opcode: 0x75
    void op_HALT();              ///< opcode: 0x76
    void op_LD__HL__A();         ///< opcode: 0x77
    void op_LD_A_B();            ///< opcode: 0x78
    void op_LD_A_C();            ///< opcode: 0x79
    void op_LD_A_D();            ///< opcode: 0x7A
    void op_LD_A_E();            ///< opcode: 0x7B
    void op_LD_A_H();            ///< opcode: 0x7C
    void op_LD_A_L();            ///< opcode: 0x7D
    void op_LD_A__HL__();        ///< opcode: 0x7E
    void op_LD_A_A();            ///< opcode: 0x7F
    void op_ADD_A_B();           ///< opcode: 0x80
    void op_ADD_A_C();           ///< opcode: 0x81
    void op_ADD_A_D();           ///< opcode: 0x82
    void op_ADD_A_E();           ///< opcode: 0x83
    void op_ADD_A_H();           ///< opcode: 0x84
    void op_ADD_A_L();           ///< opcode: 0x85
    void op_ADD_A__HL__();       ///< opcode: 0x86
    void op_ADD_A_A();           ///< opcode: 0x87
    void op_ADC_A_B();           ///< opcode: 0x88
    void op_ADC_A_C();           ///< opcode: 0x89
    void op_ADC_A_D();           ///< opcode: 0x8A
    void op_ADC_A_E();           ///< opcode: 0x8B
    void op_ADC_A_H();           ///< opcode: 0x8C
    void op_ADC_A_L();           ///< opcode: 0x8D
    void op_ADC_A__HL__();       ///< opcode: 0x8E
    void op_ADC_A_A();           ///< opcode: 0x8F
    void op_SUB_B();             ///< opcode: 0x90
    void op_SUB_C();             ///< opcode: 0x91
    void op_SUB_D();             ///< opcode: 0x92
    void op_SUB_E();             ///< opcode: 0x93
    void op_SUB_H();             ///< opcode: 0x94
    void op_SUB_L();             ///< opcode: 0x95
    void op_SUB__HL__();         ///< opcode: 0x96
    void op_SUB_A();             ///< opcode: 0x97
    void op_SBC_A_B();           ///< opcode: 0x98
    void op_SBC_A_C();           ///< opcode: 0x99
    void op_SBC_A_D();           ///< opcode: 0x9A
    void op_SBC_A_E();           ///< opcode: 0x9B
    void op_SBC_A_H();           ///< opcode: 0x9C
    void op_SBC_A_L();           ///< opcode: 0x9D
    void op_SBC_A__HL__();       ///< opcode: 0x9E
    void op_SBC_A_A();           ///< opcode: 0x9F
    void op_AND_B();             ///< opcode: 0xA0
    void op_AND_C();             ///< opcode: 0xA1
    void op_AND_D();             ///< opcode: 0xA2
    void op_AND_E();             ///< opcode: 0xA3
    void op_AND_H();             ///< opcode: 0xA4
    void op_AND_L();             ///< opcode: 0xA5
    void op_AND__HL__();         ///< opcode: 0xA6
    void op_AND_A();             ///< opcode: 0xA7
    void op_XOR_B();             ///< opcode: 0xA8
    void op_XOR_C();             ///< opcode: 0xA9
    void op_XOR_D();             ///< opcode: 0xAA
    void op_XOR_E();             ///< opcode: 0xAB
    void op_XOR_H();             ///< opcode: 0xAC
    void op_XOR_L();             ///< opcode: 0xAD
    void op_XOR__HL__();         ///< opcode: 0xAE
    void op_XOR_A();             ///< opcode: 0xAF
    void op_OR_B();              ///< opcode: 0xB0
    void op_OR_C();              ///< opcode: 0xB1
    void op_OR_D();              ///< opcode: 0xB2
    void op_OR_E();              ///< opcode: 0xB3
    void op_OR_H();              ///< opcode: 0xB4
    void op_OR_L();              ///< opcode: 0xB5
    void op_OR__HL__();          ///< opcode: 0xB6
    void op_OR_A();              ///< opcode: 0xB7
    void op_CP_B();              ///< opcode: 0xB8
    void op_CP_C();              ///< opcode: 0xB9
    void op_CP_D();              ///< opcode: 0xBA
    void op_CP_E();              ///< opcode: 0xBB
    void op_CP_H();              ///< opcode: 0xBC
    void op_CP_L();              ///< opcode: 0xBD
    void op_CP__HL__();          ///< opcode: 0xBE
    void op_CP_A();              ///< opcode: 0xBF
    void op_RET_NZ();            ///< opcode: 0xC0
    void op_POP_BC();            ///< opcode: 0xC1
    void op_JP_NZ_a16();         ///< opcode: 0xC2
    void op_JP_a16();            ///< opcode: 0xC3
    void op_CALL_NZ_a16();       ///< opcode: 0xC4
    void op_PUSH_BC();           ///< opcode: 0xC5
    void op_ADD_A_d8();          ///< opcode: 0xC6
    void op_RST_00H();           ///< opcode: 0xC7
    void op_RET_Z();             ///< opcode: 0xC8
    void op_RET();               ///< opcode: 0xC9
    void op_JP_Z_a16();          ///< opcode: 0xCA
    void op_PREFIX_CB();         ///< opcode: 0xCB
    void op_CALL_Z_a16();        ///< opcode: 0xCC
    void op_CALL_a16();          ///< opcode: 0xCD
    void op_ADC_A_d8();          ///< opcode: 0xCE
    void op_RST_08H();           ///< opcode: 0xCF
    void op_RET_NC();            ///< opcode: 0xD0
    void op_POP_DE();            ///< opcode: 0xD1
    void op_JP_NC_a16();         ///< opcode: 0xD2
    void op_CALL_NC_a16();       ///< opcode: 0xD4
    void op_PUSH_DE();           ///< opcode: 0xD5
    void op_SUB_d8();            ///< opcode: 0xD6
    void op_RST_10H();           ///< opcode: 0xD7
    void op_RET_C();             ///< opcode: 0xD8
    void op_RETI();              ///< opcode: 0xD9
    void op_JP_C_a16();          ///< opcode: 0xDA
    void op_CALL_C_a16();        ///< opcode: 0xDC
    void op_SBC_A_d8();          ///< opcode: 0xDE
    void op_RST_18H();           ///< opcode: 0xDF
    void op_LDH__a8__A();        ///< opcode: 0xE0
    void op_POP_HL();            ///< opcode: 0xE1
    void op_LD__C__A();          ///< opcode: 0xE2
    void op_PUSH_HL();           ///< opcode: 0xE5
    void op_AND_d8();            ///< opcode: 0xE6
    void op_RST_20H();           ///< opcode: 0xE7
    void op_ADD_SP_r8();         ///< opcode: 0xE8
    void op_JP__HL__();          ///< opcode: 0xE9
    void op_LD__a16__A();        ///< opcode: 0xEA
    void op_XOR_d8();            ///< opcode: 0xEE
    void op_RST_28H();           ///< opcode: 0xEF
    void op_LDH_A__a8__();       ///< opcode: 0xF0
    void op_POP_AF();            ///< opcode: 0xF1
    void op_LD_A__C__();         ///< opcode: 0xF2
    void op_DI();                ///< opcode: 0xF3
    void op_PUSH_AF();           ///< opcode: 0xF5
    void op_OR_d8();             ///< opcode: 0xF6
    void op_RST_30H();           ///< opcode: 0xF7
    void op_LD_HL_SP_plus_r8();  ///< opcode: 0xF8
    void op_LD_SP_HL();          ///< opcode: 0xF9
    void op_LD_A__a16__();       ///< opcode: 0xFA
    void op_EI();                ///< opcode: 0xFB
    void op_CP_d8();             ///< opcode: 0xFE
    void op_RST_38H();           ///< opcode: 0xFF

    // =============================================================================================
    //  Prefix CB instruction set.
    // =============================================================================================

    void execRLC(uint8_t& data);   ///< opcode from 0xCB00 to 0xCB07.
    void execRRC(uint8_t& data);   ///< opcode from 0xCB08 to 0xCB0F.
    void execRL(uint8_t& data);    ///< opcode from 0xCB10 to 0xCB17.
    void execRR(uint8_t& data);    ///< opcode from 0xCB18 to 0xCB1F.
    void execSLA(uint8_t& data);   ///< opcode from 0xCB20 to 0xCB27.
    void execSRA(uint8_t& data);   ///< opcode from 0xCB28 to 0xCB2F.
    void execSWAP(uint8_t& data);  ///< opcode from 0xCB30 to 0xCB37.
    void execSRL(uint8_t& data);   ///< opcode from 0xCB38 to 0xCB3F.
    void execBIT(const uint8_t data,
                 const uint8_t bitPos);  ///< opcode from 0xCB40 to 0xCB7F.
    void execRES(uint8_t& data,
                 const uint8_t bitPos);  ///< opcode from 0xCB80 to 0xCBBF.
    void execSET(uint8_t& data,
                 const uint8_t bitPos);  ///< opcode from 0xCBC0 to 0xCBFF.

    void op_RLC_B();        ///< opcode: 0xCB00
    void op_RLC_C();        ///< opcode: 0xCB01
    void op_RLC_D();        ///< opcode: 0xCB02
    void op_RLC_E();        ///< opcode: 0xCB03
    void op_RLC_H();        ///< opcode: 0xCB04
    void op_RLC_L();        ///< opcode: 0xCB05
    void op_RLC__HL__();    ///< opcode: 0xCB06
    void op_RLC_A();        ///< opcode: 0xCB07
    void op_RRC_B();        ///< opcode: 0xCB08
    void op_RRC_C();        ///< opcode: 0xCB09
    void op_RRC_D();        ///< opcode: 0xCB0A
    void op_RRC_E();        ///< opcode: 0xCB0B
    void op_RRC_H();        ///< opcode: 0xCB0C
    void op_RRC_L();        ///< opcode: 0xCB0D
    void op_RRC__HL__();    ///< opcode: 0xCB0E
    void op_RRC_A();        ///< opcode: 0xCB0F
    void op_RL_B();         ///< opcode: 0xCB10
    void op_RL_C();         ///< opcode: 0xCB11
    void op_RL_D();         ///< opcode: 0xCB12
    void op_RL_E();         ///< opcode: 0xCB13
    void op_RL_H();         ///< opcode: 0xCB14
    void op_RL_L();         ///< opcode: 0xCB15
    void op_RL__HL__();     ///< opcode: 0xCB16
    void op_RL_A();         ///< opcode: 0xCB17
    void op_RR_B();         ///< opcode: 0xCB18
    void op_RR_C();         ///< opcode: 0xCB19
    void op_RR_D();         ///< opcode: 0xCB1A
    void op_RR_E();         ///< opcode: 0xCB1B
    void op_RR_H();         ///< opcode: 0xCB1C
    void op_RR_L();         ///< opcode: 0xCB1D
    void op_RR__HL__();     ///< opcode: 0xCB1E
    void op_RR_A();         ///< opcode: 0xCB1F
    void op_SLA_B();        ///< opcode: 0xCB20
    void op_SLA_C();        ///< opcode: 0xCB21
    void op_SLA_D();        ///< opcode: 0xCB22
    void op_SLA_E();        ///< opcode: 0xCB23
    void op_SLA_H();        ///< opcode: 0xCB24
    void op_SLA_L();        ///< opcode: 0xCB25
    void op_SLA__HL__();    ///< opcode: 0xCB26
    void op_SLA_A();        ///< opcode: 0xCB27
    void op_SRA_B();        ///< opcode: 0xCB28
    void op_SRA_C();        ///< opcode: 0xCB29
    void op_SRA_D();        ///< opcode: 0xCB2A
    void op_SRA_E();        ///< opcode: 0xCB2B
    void op_SRA_H();        ///< opcode: 0xCB2C
    void op_SRA_L();        ///< opcode: 0xCB2D
    void op_SRA__HL__();    ///< opcode: 0xCB2E
    void op_SRA_A();        ///< opcode: 0xCB2F
    void op_SWAP_B();       ///< opcode: 0xCB30
    void op_SWAP_C();       ///< opcode: 0xCB31
    void op_SWAP_D();       ///< opcode: 0xCB32
    void op_SWAP_E();       ///< opcode: 0xCB33
    void op_SWAP_H();       ///< opcode: 0xCB34
    void op_SWAP_L();       ///< opcode: 0xCB35
    void op_SWAP__HL__();   ///< opcode: 0xCB36
    void op_SWAP_A();       ///< opcode: 0xCB37
    void op_SRL_B();        ///< opcode: 0xCB38
    void op_SRL_C();        ///< opcode: 0xCB39
    void op_SRL_D();        ///< opcode: 0xCB3A
    void op_SRL_E();        ///< opcode: 0xCB3B
    void op_SRL_H();        ///< opcode: 0xCB3C
    void op_SRL_L();        ///< opcode: 0xCB3D
    void op_SRL__HL__();    ///< opcode: 0xCB3E
    void op_SRL_A();        ///< opcode: 0xCB3F
    void op_BIT_0_B();      ///< opcode: 0xCB40
    void op_BIT_0_C();      ///< opcode: 0xCB41
    void op_BIT_0_D();      ///< opcode: 0xCB42
    void op_BIT_0_E();      ///< opcode: 0xCB43
    void op_BIT_0_H();      ///< opcode: 0xCB44
    void op_BIT_0_L();      ///< opcode: 0xCB45
    void op_BIT_0__HL__();  ///< opcode: 0xCB46
    void op_BIT_0_A();      ///< opcode: 0xCB47
    void op_BIT_1_B();      ///< opcode: 0xCB48
    void op_BIT_1_C();      ///< opcode: 0xCB49
    void op_BIT_1_D();      ///< opcode: 0xCB4A
    void op_BIT_1_E();      ///< opcode: 0xCB4B
    void op_BIT_1_H();      ///< opcode: 0xCB4C
    void op_BIT_1_L();      ///< opcode: 0xCB4D
    void op_BIT_1__HL__();  ///< opcode: 0xCB4E
    void op_BIT_1_A();      ///< opcode: 0xCB4F
    void op_BIT_2_B();      ///< opcode: 0xCB50
    void op_BIT_2_C();      ///< opcode: 0xCB51
    void op_BIT_2_D();      ///< opcode: 0xCB52
    void op_BIT_2_E();      ///< opcode: 0xCB53
    void op_BIT_2_H();      ///< opcode: 0xCB54
    void op_BIT_2_L();      ///< opcode: 0xCB55
    void op_BIT_2__HL__();  ///< opcode: 0xCB56
    void op_BIT_2_A();      ///< opcode: 0xCB57
    void op_BIT_3_B();      ///< opcode: 0xCB58
    void op_BIT_3_C();      ///< opcode: 0xCB59
    void op_BIT_3_D();      ///< opcode: 0xCB5A
    void op_BIT_3_E();      ///< opcode: 0xCB5B
    void op_BIT_3_H();      ///< opcode: 0xCB5C
    void op_BIT_3_L();      ///< opcode: 0xCB5D
    void op_BIT_3__HL__();  ///< opcode: 0xCB5E
    void op_BIT_3_A();      ///< opcode: 0xCB5F
    void op_BIT_4_B();      ///< opcode: 0xCB60
    void op_BIT_4_C();      ///< opcode: 0xCB61
    void op_BIT_4_D();      ///< opcode: 0xCB62
    void op_BIT_4_E();      ///< opcode: 0xCB63
    void op_BIT_4_H();      ///< opcode: 0xCB64
    void op_BIT_4_L();      ///< opcode: 0xCB65
    void op_BIT_4__HL__();  ///< opcode: 0xCB66
    void op_BIT_4_A();      ///< opcode: 0xCB67
    void op_BIT_5_B();      ///< opcode: 0xCB68
    void op_BIT_5_C();      ///< opcode: 0xCB69
    void op_BIT_5_D();      ///< opcode: 0xCB6A
    void op_BIT_5_E();      ///< opcode: 0xCB6B
    void op_BIT_5_H();      ///< opcode: 0xCB6C
    void op_BIT_5_L();      ///< opcode: 0xCB6D
    void op_BIT_5__HL__();  ///< opcode: 0xCB6E
    void op_BIT_5_A();      ///< opcode: 0xCB6F
    void op_BIT_6_B();      ///< opcode: 0xCB70
    void op_BIT_6_C();      ///< opcode: 0xCB71
    void op_BIT_6_D();      ///< opcode: 0xCB72
    void op_BIT_6_E();      ///< opcode: 0xCB73
    void op_BIT_6_H();      ///< opcode: 0xCB74
    void op_BIT_6_L();      ///< opcode: 0xCB75
    void op_BIT_6__HL__();  ///< opcode: 0xCB76
    void op_BIT_6_A();      ///< opcode: 0xCB77
    void op_BIT_7_B();      ///< opcode: 0xCB78
    void op_BIT_7_C();      ///< opcode: 0xCB79
    void op_BIT_7_D();      ///< opcode: 0xCB7A
    void op_BIT_7_E();      ///< opcode: 0xCB7B
    void op_BIT_7_H();      ///< opcode: 0xCB7C
    void op_BIT_7_L();      ///< opcode: 0xCB7D
    void op_BIT_7__HL__();  ///< opcode: 0xCB7E
    void op_BIT_7_A();      ///< opcode: 0xCB7F
    void op_RES_0_B();      ///< opcode: 0xCB80
    void op_RES_0_C();      ///< opcode: 0xCB81
    void op_RES_0_D();      ///< opcode: 0xCB82
    void op_RES_0_E();      ///< opcode: 0xCB83
    void op_RES_0_H();      ///< opcode: 0xCB84
    void op_RES_0_L();      ///< opcode: 0xCB85
    void op_RES_0__HL__();  ///< opcode: 0xCB86
    void op_RES_0_A();      ///< opcode: 0xCB87
    void op_RES_1_B();      ///< opcode: 0xCB88
    void op_RES_1_C();      ///< opcode: 0xCB89
    void op_RES_1_D();      ///< opcode: 0xCB8A
    void op_RES_1_E();      ///< opcode: 0xCB8B
    void op_RES_1_H();      ///< opcode: 0xCB8C
    void op_RES_1_L();      ///< opcode: 0xCB8D
    void op_RES_1__HL__();  ///< opcode: 0xCB8E
    void op_RES_1_A();      ///< opcode: 0xCB8F
    void op_RES_2_B();      ///< opcode: 0xCB90
    void op_RES_2_C();      ///< opcode: 0xCB91
    void op_RES_2_D();      ///< opcode: 0xCB92
    void op_RES_2_E();      ///< opcode: 0xCB93
    void op_RES_2_H();      ///< opcode: 0xCB94
    void op_RES_2_L();      ///< opcode: 0xCB95
    void op_RES_2__HL__();  ///< opcode: 0xCB96
    void op_RES_2_A();      ///< opcode: 0xCB97
    void op_RES_3_B();      ///< opcode: 0xCB98
    void op_RES_3_C();      ///< opcode: 0xCB99
    void op_RES_3_D();      ///< opcode: 0xCB9A
    void op_RES_3_E();      ///< opcode: 0xCB9B
    void op_RES_3_H();      ///< opcode: 0xCB9C
    void op_RES_3_L();      ///< opcode: 0xCB9D
    void op_RES_3__HL__();  ///< opcode: 0xCB9E
    void op_RES_3_A();      ///< opcode: 0xCB9F
    void op_RES_4_B();      ///< opcode: 0xCBA0
    void op_RES_4_C();      ///< opcode: 0xCBA1
    void op_RES_4_D();      ///< opcode: 0xCBA2
    void op_RES_4_E();      ///< opcode: 0xCBA3
    void op_RES_4_H();      ///< opcode: 0xCBA4
    void op_RES_4_L();      ///< opcode: 0xCBA5
    void op_RES_4__HL__();  ///< opcode: 0xCBA6
    void op_RES_4_A();      ///< opcode: 0xCBA7
    void op_RES_5_B();      ///< opcode: 0xCBA8
    void op_RES_5_C();      ///< opcode: 0xCBA9
    void op_RES_5_D();      ///< opcode: 0xCBAA
    void op_RES_5_E();      ///< opcode: 0xCBAB
    void op_RES_5_H();      ///< opcode: 0xCBAC
    void op_RES_5_L();      ///< opcode: 0xCBAD
    void op_RES_5__HL__();  ///< opcode: 0xCBAE
    void op_RES_5_A();      ///< opcode: 0xCBAF
    void op_RES_6_B();      ///< opcode: 0xCBB0
    void op_RES_6_C();      ///< opcode: 0xCBB1
    void op_RES_6_D();      ///< opcode: 0xCBB2
    void op_RES_6_E();      ///< opcode: 0xCBB3
    void op_RES_6_H();      ///< opcode: 0xCBB4
    void op_RES_6_L();      ///< opcode: 0xCBB5
    void op_RES_6__HL__();  ///< opcode: 0xCBB6
    void op_RES_6_A();      ///< opcode: 0xCBB7
    void op_RES_7_B();      ///< opcode: 0xCBB8
    void op_RES_7_C();      ///< opcode: 0xCBB9
    void op_RES_7_D();      ///< opcode: 0xCBBA
    void op_RES_7_E();      ///< opcode: 0xCBBB
    void op_RES_7_H();      ///< opcode: 0xCBBC
    void op_RES_7_L();      ///< opcode: 0xCBBD
    void op_RES_7__HL__();  ///< opcode: 0xCBBE
    void op_RES_7_A();      ///< opcode: 0xCBBF
    void op_SET_0_B();      ///< opcode: 0xCBC0
    void op_SET_0_C();      ///< opcode: 0xCBC1
    void op_SET_0_D();      ///< opcode: 0xCBC2
    void op_SET_0_E();      ///< opcode: 0xCBC3
    void op_SET_0_H();      ///< opcode: 0xCBC4
    void op_SET_0_L();      ///< opcode: 0xCBC5
    void op_SET_0__HL__();  ///< opcode: 0xCBC6
    void op_SET_0_A();      ///< opcode: 0xCBC7
    void op_SET_1_B();      ///< opcode: 0xCBC8
    void op_SET_1_C();      ///< opcode: 0xCBC9
    void op_SET_1_D();      ///< opcode: 0xCBCA
    void op_SET_1_E();      ///< opcode: 0xCBCB
    void op_SET_1_H();      ///< opcode: 0xCBCC
    void op_SET_1_L();      ///< opcode: 0xCBCD
    void op_SET_1__HL__();  ///< opcode: 0xCBCE
    void op_SET_1_A();      ///< opcode: 0xCBCF
    void op_SET_2_B();      ///< opcode: 0xCBD0
    void op_SET_2_C();      ///< opcode: 0xCBD1
    void op_SET_2_D();      ///< opcode: 0xCBD2
    void op_SET_2_E();      ///< opcode: 0xCBD3
    void op_SET_2_H();      ///< opcode: 0xCBD4
    void op_SET_2_L();      ///< opcode: 0xCBD5
    void op_SET_2__HL__();  ///< opcode: 0xCBD6
    void op_SET_2_A();      ///< opcode: 0xCBD7
    void op_SET_3_B();      ///< opcode: 0xCBD8
    void op_SET_3_C();      ///< opcode: 0xCBD9
    void op_SET_3_D();      ///< opcode: 0xCBDA
    void op_SET_3_E();      ///< opcode: 0xCBDB
    void op_SET_3_H();      ///< opcode: 0xCBDC
    void op_SET_3_L();      ///< opcode: 0xCBDD
    void op_SET_3__HL__();  ///< opcode: 0xCBDE
    void op_SET_3_A();      ///< opcode: 0xCBDF
    void op_SET_4_B();      ///< opcode: 0xCBE0
    void op_SET_4_C();      ///< opcode: 0xCBE1
    void op_SET_4_D();      ///< opcode: 0xCBE2
    void op_SET_4_E();      ///< opcode: 0xCBE3
    void op_SET_4_H();      ///< opcode: 0xCBE4
    void op_SET_4_L();      ///< opcode: 0xCBE5
    void op_SET_4__HL__();  ///< opcode: 0xCBE6
    void op_SET_4_A();      ///< opcode: 0xCBE7
    void op_SET_5_B();      ///< opcode: 0xCBE8
    void op_SET_5_C();      ///< opcode: 0xCBE9
    void op_SET_5_D();      ///< opcode: 0xCBEA
    void op_SET_5_E();      ///< opcode: 0xCBEB
    void op_SET_5_H();      ///< opcode: 0xCBEC
    void op_SET_5_L();      ///< opcode: 0xCBED
    void op_SET_5__HL__();  ///< opcode: 0xCBEE
    void op_SET_5_A();      ///< opcode: 0xCBEF
    void op_SET_6_B();      ///< opcode: 0xCBF0
    void op_SET_6_C();      ///< opcode: 0xCBF1
    void op_SET_6_D();      ///< opcode: 0xCBF2
    void op_SET_6_E();      ///< opcode: 0xCBF3
    void op_SET_6_H();      ///< opcode: 0xCBF4
    void op_SET_6_L();      ///< opcode: 0xCBF5
    void op_SET_6__HL__();  ///< opcode: 0xCBF6
    void op_SET_6_A();      ///< opcode: 0xCBF7
    void op_SET_7_B();      ///< opcode: 0xCBF8
    void op_SET_7_C();      ///< opcode: 0xCBF9
    void op_SET_7_D();      ///< opcode: 0xCBFA
    void op_SET_7_E();      ///< opcode: 0xCBFB
    void op_SET_7_H();      ///< opcode: 0xCBFC
    void op_SET_7_L();      ///< opcode: 0xCBFD
    void op_SET_7__HL__();  ///< opcode: 0xCBFE
    void op_SET_7_A();      ///< opcode: 0xCBFF

    /// \brief Representation of the four usable bits of the flag register.
    enum class FlagRegisterBits : uint8_t
    {
        eCarryFlag = 4,
        eHalfCarryFlag,
        eSubtractFlag,
        eZeroFlag,
    };

    /// \brief Check the status of a specific bit in the flag register.
    ///
    /// \param eBit Specific bit to check.
    ///
    /// \return Bit status (set or not).
    bool checkFlagRegisterBit(const FlagRegisterBits eBit) const
    {
        flagReg = F;
        return flagReg[static_cast<uint8_t>(eBit)];
    }

    /// \brief Set a flag register's bit.
    ///
    /// \param eBit Bit to set.
    /// \param status Bit status (set or not).
    void setFlagRegisterBit(const FlagRegisterBits eBit, const bool status)
    {
        flagReg = F;
        flagReg[static_cast<uint8_t>(eBit)] = status;
        F = flagReg.to_ulong();
    }

    /// \brief Set flag register.
    ///
    /// \param status New bit values.
    void setFlagRegisterBytes(const uint8_t status) { flagReg = status; }

    /// \brief Representation of the CPU state.
    enum class InstructionCycleState : uint8_t
    {
        eCYCLE_stop = 0,
        eCYCLE_checkint,
        eCYCLE_fetch,
        eCYCLE_decode,
        eCYCLE_execute
    };

    /// \brief Enable the CPU's interrupts.
    void enableInterrupts() { IME = true; }

    /// \brief Disaable the CPU's interrupts.
    void disableInterrupts() { IME = false; }

    /// \brief Check if there are activated interrupts.
    bool checkForInterrupts();

    /// \brief Stop the CPU until an interrupt occurs.
    void waitForInterrupt();

    /// \brief Fetch the next instruction from memory.
    void fetch();

    /// \brief Identify a previously fetched instruction from memory.
    void decode();

    /// \brief Execute a previously fetched and decoded instruction.
    void execute();

    /// \brief Switch the CPU to its next state (Skip the stop state).
    void switchState();

    /// \brief Switch the CPU state. \see InstructionCycleState for possible states.
    ///
    /// \param state the next CPU state.
    void switchState(const InstructionCycleState state);

    // Memory access methods. ======================================================================

    /// \brief Get the next byte pointed by the PC from the from memory.
    uint8_t fetchNextByte();

    /// \brief Get a byte from a specific memory address.
    ///
    /// \param addr address of the memory location to read from.
    ///
    /// \return the byte stored at the specified memory address.
    uint8_t fetchByteFromAddress(const uint16_t addr);

    /// \brief Store a byte in a specific memory address.
    ///
    /// \param data the byte to store.
    /// \param addr address of the memory location where the byte will be stored.
    void loadByteToAddress(const uint8_t data, const uint16_t addr);

    /// \brief Check if the addition of two numeric values generates a half-carry.
    ///
    /// \param data byte or word to check.
    ///
    /// \return true if half-carry present, false otherwise.
    template<typename T, typename U = uint8_t>
    bool hasHalfCarry(const T data1, const U data2 = 1) const
    {
        static_assert(std::is_integral<T>() == true);
        static_assert(std::is_integral<U>() == true);
        static_assert(sizeof(T) <= sizeof(uint16_t));
        static_assert(sizeof(U) <= sizeof(uint16_t));

        if (sizeof(T) == sizeof(uint8_t))
        {
            // Check bit 3 for half-carry.
            return ((((data1 & 0x0F) + (data2 & 0x0F)) & 0x10) == 0x10);
        }
        else
        {
            // Check bit 11 for half-carry.
            return ((((data1 & 0x0FFF) + (data2 & 0x0FFF)) & 0x1000) == 0x1000);
        }
    }

    /// \brief Check if the addition of two numeric values generates a carry.
    ///
    /// \param data byte or word to check.
    ///
    /// \return true if carry present, false otherwise.
    template<typename T, typename U = uint8_t>
    bool hasCarry(const T data1, const U data2 = 1) const
    {
        static_assert(std::is_integral<T>() == true);
        static_assert(std::is_integral<U>() == true);
        static_assert(sizeof(T) <= sizeof(uint16_t));
        static_assert(sizeof(U) <= sizeof(uint16_t));

        if (sizeof(T) == sizeof(uint8_t))
        {
            // Check bit 3 for half-carry.
            return (((data1 + data2) & 0x100) == 0x100);
        }
        else
        {
            // Check bit 11 for half-carry.
            return (((data1 + data2) & 0x10000) == 0x10000);
        }
    }

    /// Check if the substraction of two numeric values generates a half-borrow (borrow from bit 4).
    ///
    /// \param data1 first byte.
    /// \param data2 second byte.
    ///
    /// \return true if half-borrow present, false otherwise.
    bool hasHalfBorrow(const uint8_t data1, const uint8_t data2 = 1) const
    {
        // Check bit 4 for half-borrow.
        return ((data1 & 0x0F) < (data2 & 0x0F));
    }

    /// Check if the substraction of two numeric values generates a borrow (borrow from bit 16).
    ///
    /// \param data1 first byte.
    /// \param data2 second byte.
    ///
    /// \return true if borrow present, false otherwise.
    bool hasBorrow(const uint8_t data1, const uint8_t data2 = 1) const
    {
        // Check for borrow.
        return (data1 < data2);
    }

    std::array<uint8_t, 12> m_registers;     ///< Representation of the CPU's 12 internal registers
    uint8_t &A, &B, &C, &D, &E, &F, &H, &L;  ///< References to each individual 8 bits CPU register.
    uint16_t &AF, &BC, &DE, &HL, &SP, &PC;  ///< References to each individual 16 bits CPU register.
    mutable std::bitset<8> flagReg;  ///< Representation of the flag register as a std::bitset.

    uint8_t IR;      ///< Instruction register.
    uint8_t MBR[2];  ///< Memory buffer register.

    bool IME;  ///< Interrupt Master Enable.

    uint16_t m_currentInstructionAddr;  ///< The address in memory of the current instruction.

    Mmu& m_mmu;  ///< Memory management unit.

    uint8_t m_opLength = 0;    ///< Current instruction length.
    uint32_t m_cpuCycles = 0;  ///< Total CPU cycles.

    InstructionCycleState m_cpuCycleState;       ///< Current CPU cycle state.
    std::stack<uint8_t> m_unfinishedLastOpData;  ///< Any data left from an unfinished op.
    bool m_unfinishedLastOp;                     ///< Is the last CPU op completed?

    bool m_inPrefixCBOp;  ///< Is a prefix CB op running?

    std::array<uint8_t, 256> m_CPUROM =
        {0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF,
         0x0E, 0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E,
         0xFC, 0xE0, 0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96,
         0x00, 0x13, 0x7B, 0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22,
         0x23, 0x05, 0x20, 0xF9, 0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D,
         0x28, 0x08, 0x32, 0x0D, 0x20, 0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0,
         0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04, 0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20,
         0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2, 0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62,
         0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06, 0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0,
         0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20, 0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F,
         0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17, 0x05, 0x20, 0xF5, 0x22, 0x23,
         0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
         0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E,
         0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC,
         0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C, 0x21,
         0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
         0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0,
         0x50};

    ///< Length in byte of all the CPU's instructions.
    const std::array<uint8_t, 256> m_opsLengths =
        {1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1, 2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1,
         1, 2, 1, 2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 3, 1, 1, 1, 1, 2, 1, 2, 1,
         1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3,
         1, 3, 3, 2, 1, 1, 1, 3, 0, 3, 1, 2, 1, 1, 1, 3, 0, 3, 0, 2, 1, 2, 1, 1, 0, 0, 1, 2, 1,
         2, 1, 3, 0, 0, 0, 2, 1, 2, 1, 1, 1, 0, 1, 2, 1, 2, 1, 3, 1, 0, 0, 2, 1};

    ///< std::function binding for each prefix CB CPU instructions's method.
    std::array<std::function<void()>, 0x100> m_opsFunctions =
        {std::bind(&Cpu::op_NOP, this),
         std::bind(&Cpu::op_LD_BC_d16, this),
         std::bind(&Cpu::op_LD__BC__A, this),
         std::bind(&Cpu::op_INC_BC, this),
         std::bind(&Cpu::op_INC_B, this),
         std::bind(&Cpu::op_DEC_B, this),
         std::bind(&Cpu::op_LD_B_d8, this),
         std::bind(&Cpu::op_RLCA, this),
         std::bind(&Cpu::op_LD__a16__SP, this),
         std::bind(&Cpu::op_ADD_HL_BC, this),
         std::bind(&Cpu::op_LD_A__BC__, this),
         std::bind(&Cpu::op_DEC_BC, this),
         std::bind(&Cpu::op_INC_C, this),
         std::bind(&Cpu::op_DEC_C, this),
         std::bind(&Cpu::op_LD_C_d8, this),
         std::bind(&Cpu::op_RRCA, this),
         std::bind(&Cpu::op_STOP, this),
         std::bind(&Cpu::op_LD_DE_d16, this),
         std::bind(&Cpu::op_LD__DE__A, this),
         std::bind(&Cpu::op_INC_DE, this),
         std::bind(&Cpu::op_INC_D, this),
         std::bind(&Cpu::op_DEC_D, this),
         std::bind(&Cpu::op_LD_D_d8, this),
         std::bind(&Cpu::op_RLA, this),
         std::bind(&Cpu::op_JR_r8, this),
         std::bind(&Cpu::op_ADD_HL_DE, this),
         std::bind(&Cpu::op_LD_A__DE__, this),
         std::bind(&Cpu::op_DEC_DE, this),
         std::bind(&Cpu::op_INC_E, this),
         std::bind(&Cpu::op_DEC_E, this),
         std::bind(&Cpu::op_LD_E_d8, this),
         std::bind(&Cpu::op_RRA, this),
         std::bind(&Cpu::op_JR_NZ_r8, this),
         std::bind(&Cpu::op_LD_HL_d16, this),
         std::bind(&Cpu::op_LD__HLplus__A, this),
         std::bind(&Cpu::op_INC_HL, this),
         std::bind(&Cpu::op_INC_H, this),
         std::bind(&Cpu::op_DEC_H, this),
         std::bind(&Cpu::op_LD_H_d8, this),
         std::bind(&Cpu::op_DAA, this),
         std::bind(&Cpu::op_JR_Z_r8, this),
         std::bind(&Cpu::op_ADD_HL_HL, this),
         std::bind(&Cpu::op_LD_A__HLplus__, this),
         std::bind(&Cpu::op_DEC_HL, this),
         std::bind(&Cpu::op_INC_L, this),
         std::bind(&Cpu::op_DEC_L, this),
         std::bind(&Cpu::op_LD_L_d8, this),
         std::bind(&Cpu::op_CPL, this),
         std::bind(&Cpu::op_JR_NC_r8, this),
         std::bind(&Cpu::op_LD_SP_d16, this),
         std::bind(&Cpu::op_LD__HLminus__A, this),
         std::bind(&Cpu::op_INC_SP, this),
         std::bind(&Cpu::op_INC__HL__, this),
         std::bind(&Cpu::op_DEC__HL__, this),
         std::bind(&Cpu::op_LD__HL__d8, this),
         std::bind(&Cpu::op_SCF, this),
         std::bind(&Cpu::op_JR_C_r8, this),
         std::bind(&Cpu::op_ADD_HL_SP, this),
         std::bind(&Cpu::op_LD_A__HLminus__, this),
         std::bind(&Cpu::op_DEC_SP, this),
         std::bind(&Cpu::op_INC_A, this),
         std::bind(&Cpu::op_DEC_A, this),
         std::bind(&Cpu::op_LD_A_d8, this),
         std::bind(&Cpu::op_CCF, this),
         std::bind(&Cpu::op_LD_B_B, this),
         std::bind(&Cpu::op_LD_B_C, this),
         std::bind(&Cpu::op_LD_B_D, this),
         std::bind(&Cpu::op_LD_B_E, this),
         std::bind(&Cpu::op_LD_B_H, this),
         std::bind(&Cpu::op_LD_B_L, this),
         std::bind(&Cpu::op_LD_B__HL__, this),
         std::bind(&Cpu::op_LD_B_A, this),
         std::bind(&Cpu::op_LD_C_B, this),
         std::bind(&Cpu::op_LD_C_C, this),
         std::bind(&Cpu::op_LD_C_D, this),
         std::bind(&Cpu::op_LD_C_E, this),
         std::bind(&Cpu::op_LD_C_H, this),
         std::bind(&Cpu::op_LD_C_L, this),
         std::bind(&Cpu::op_LD_C__HL__, this),
         std::bind(&Cpu::op_LD_C_A, this),
         std::bind(&Cpu::op_LD_D_B, this),
         std::bind(&Cpu::op_LD_D_C, this),
         std::bind(&Cpu::op_LD_D_D, this),
         std::bind(&Cpu::op_LD_D_E, this),
         std::bind(&Cpu::op_LD_D_H, this),
         std::bind(&Cpu::op_LD_D_L, this),
         std::bind(&Cpu::op_LD_D__HL__, this),
         std::bind(&Cpu::op_LD_D_A, this),
         std::bind(&Cpu::op_LD_E_B, this),
         std::bind(&Cpu::op_LD_E_C, this),
         std::bind(&Cpu::op_LD_E_D, this),
         std::bind(&Cpu::op_LD_E_E, this),
         std::bind(&Cpu::op_LD_E_H, this),
         std::bind(&Cpu::op_LD_E_L, this),
         std::bind(&Cpu::op_LD_E__HL__, this),
         std::bind(&Cpu::op_LD_E_A, this),
         std::bind(&Cpu::op_LD_H_B, this),
         std::bind(&Cpu::op_LD_H_C, this),
         std::bind(&Cpu::op_LD_H_D, this),
         std::bind(&Cpu::op_LD_H_E, this),
         std::bind(&Cpu::op_LD_H_H, this),
         std::bind(&Cpu::op_LD_H_L, this),
         std::bind(&Cpu::op_LD_H__HL__, this),
         std::bind(&Cpu::op_LD_H_A, this),
         std::bind(&Cpu::op_LD_L_B, this),
         std::bind(&Cpu::op_LD_L_C, this),
         std::bind(&Cpu::op_LD_L_D, this),
         std::bind(&Cpu::op_LD_L_E, this),
         std::bind(&Cpu::op_LD_L_H, this),
         std::bind(&Cpu::op_LD_L_L, this),
         std::bind(&Cpu::op_LD_L__HL__, this),
         std::bind(&Cpu::op_LD_L_A, this),
         std::bind(&Cpu::op_LD__HL__B, this),
         std::bind(&Cpu::op_LD__HL__C, this),
         std::bind(&Cpu::op_LD__HL__D, this),
         std::bind(&Cpu::op_LD__HL__E, this),
         std::bind(&Cpu::op_LD__HL__H, this),
         std::bind(&Cpu::op_LD__HL__L, this),
         std::bind(&Cpu::op_HALT, this),
         std::bind(&Cpu::op_LD__HL__A, this),
         std::bind(&Cpu::op_LD_A_B, this),
         std::bind(&Cpu::op_LD_A_C, this),
         std::bind(&Cpu::op_LD_A_D, this),
         std::bind(&Cpu::op_LD_A_E, this),
         std::bind(&Cpu::op_LD_A_H, this),
         std::bind(&Cpu::op_LD_A_L, this),
         std::bind(&Cpu::op_LD_A__HL__, this),
         std::bind(&Cpu::op_LD_A_A, this),
         std::bind(&Cpu::op_ADD_A_B, this),
         std::bind(&Cpu::op_ADD_A_C, this),
         std::bind(&Cpu::op_ADD_A_D, this),
         std::bind(&Cpu::op_ADD_A_E, this),
         std::bind(&Cpu::op_ADD_A_H, this),
         std::bind(&Cpu::op_ADD_A_L, this),
         std::bind(&Cpu::op_ADD_A__HL__, this),
         std::bind(&Cpu::op_ADD_A_A, this),
         std::bind(&Cpu::op_ADC_A_B, this),
         std::bind(&Cpu::op_ADC_A_C, this),
         std::bind(&Cpu::op_ADC_A_D, this),
         std::bind(&Cpu::op_ADC_A_E, this),
         std::bind(&Cpu::op_ADC_A_H, this),
         std::bind(&Cpu::op_ADC_A_L, this),
         std::bind(&Cpu::op_ADC_A__HL__, this),
         std::bind(&Cpu::op_ADC_A_A, this),
         std::bind(&Cpu::op_SUB_B, this),
         std::bind(&Cpu::op_SUB_C, this),
         std::bind(&Cpu::op_SUB_D, this),
         std::bind(&Cpu::op_SUB_E, this),
         std::bind(&Cpu::op_SUB_H, this),
         std::bind(&Cpu::op_SUB_L, this),
         std::bind(&Cpu::op_SUB__HL__, this),
         std::bind(&Cpu::op_SUB_A, this),
         std::bind(&Cpu::op_SBC_A_B, this),
         std::bind(&Cpu::op_SBC_A_C, this),
         std::bind(&Cpu::op_SBC_A_D, this),
         std::bind(&Cpu::op_SBC_A_E, this),
         std::bind(&Cpu::op_SBC_A_H, this),
         std::bind(&Cpu::op_SBC_A_L, this),
         std::bind(&Cpu::op_SBC_A__HL__, this),
         std::bind(&Cpu::op_SBC_A_A, this),
         std::bind(&Cpu::op_AND_B, this),
         std::bind(&Cpu::op_AND_C, this),
         std::bind(&Cpu::op_AND_D, this),
         std::bind(&Cpu::op_AND_E, this),
         std::bind(&Cpu::op_AND_H, this),
         std::bind(&Cpu::op_AND_L, this),
         std::bind(&Cpu::op_AND__HL__, this),
         std::bind(&Cpu::op_AND_A, this),
         std::bind(&Cpu::op_XOR_B, this),
         std::bind(&Cpu::op_XOR_C, this),
         std::bind(&Cpu::op_XOR_D, this),
         std::bind(&Cpu::op_XOR_E, this),
         std::bind(&Cpu::op_XOR_H, this),
         std::bind(&Cpu::op_XOR_L, this),
         std::bind(&Cpu::op_XOR__HL__, this),
         std::bind(&Cpu::op_XOR_A, this),
         std::bind(&Cpu::op_OR_B, this),
         std::bind(&Cpu::op_OR_C, this),
         std::bind(&Cpu::op_OR_D, this),
         std::bind(&Cpu::op_OR_E, this),
         std::bind(&Cpu::op_OR_H, this),
         std::bind(&Cpu::op_OR_L, this),
         std::bind(&Cpu::op_OR__HL__, this),
         std::bind(&Cpu::op_OR_A, this),
         std::bind(&Cpu::op_CP_B, this),
         std::bind(&Cpu::op_CP_C, this),
         std::bind(&Cpu::op_CP_D, this),
         std::bind(&Cpu::op_CP_E, this),
         std::bind(&Cpu::op_CP_H, this),
         std::bind(&Cpu::op_CP_L, this),
         std::bind(&Cpu::op_CP__HL__, this),
         std::bind(&Cpu::op_CP_A, this),
         std::bind(&Cpu::op_RET_NZ, this),
         std::bind(&Cpu::op_POP_BC, this),
         std::bind(&Cpu::op_JP_NZ_a16, this),
         std::bind(&Cpu::op_JP_a16, this),
         std::bind(&Cpu::op_CALL_NZ_a16, this),
         std::bind(&Cpu::op_PUSH_BC, this),
         std::bind(&Cpu::op_ADD_A_d8, this),
         std::bind(&Cpu::op_RST_00H, this),
         std::bind(&Cpu::op_RET_Z, this),
         std::bind(&Cpu::op_RET, this),
         std::bind(&Cpu::op_JP_Z_a16, this),
         std::bind(&Cpu::op_PREFIX_CB, this),
         std::bind(&Cpu::op_CALL_Z_a16, this),
         std::bind(&Cpu::op_CALL_a16, this),
         std::bind(&Cpu::op_ADC_A_d8, this),
         std::bind(&Cpu::op_RST_08H, this),
         std::bind(&Cpu::op_RET_NC, this),
         std::bind(&Cpu::op_POP_DE, this),
         std::bind(&Cpu::op_JP_NC_a16, this),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_CALL_NC_a16, this),
         std::bind(&Cpu::op_PUSH_DE, this),
         std::bind(&Cpu::op_SUB_d8, this),
         std::bind(&Cpu::op_RST_10H, this),
         std::bind(&Cpu::op_RET_C, this),
         std::bind(&Cpu::op_RETI, this),
         std::bind(&Cpu::op_JP_C_a16, this),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_CALL_C_a16, this),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_SBC_A_d8, this),
         std::bind(&Cpu::op_RST_18H, this),
         std::bind(&Cpu::op_LDH__a8__A, this),
         std::bind(&Cpu::op_POP_HL, this),
         std::bind(&Cpu::op_LD__C__A, this),
         std::function<void()>(nullptr),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_PUSH_HL, this),
         std::bind(&Cpu::op_AND_d8, this),
         std::bind(&Cpu::op_RST_20H, this),
         std::bind(&Cpu::op_ADD_SP_r8, this),
         std::bind(&Cpu::op_JP__HL__, this),
         std::bind(&Cpu::op_LD__a16__A, this),
         std::function<void()>(nullptr),
         std::function<void()>(nullptr),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_XOR_d8, this),
         std::bind(&Cpu::op_RST_28H, this),
         std::bind(&Cpu::op_LDH_A__a8__, this),
         std::bind(&Cpu::op_POP_AF, this),
         std::bind(&Cpu::op_LD_A__C__, this),
         std::bind(&Cpu::op_DI, this),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_PUSH_AF, this),
         std::bind(&Cpu::op_OR_d8, this),
         std::bind(&Cpu::op_RST_30H, this),
         std::bind(&Cpu::op_LD_HL_SP_plus_r8, this),
         std::bind(&Cpu::op_LD_SP_HL, this),
         std::bind(&Cpu::op_LD_A__a16__, this),
         std::bind(&Cpu::op_EI, this),
         std::function<void()>(nullptr),
         std::function<void()>(nullptr),
         std::bind(&Cpu::op_CP_d8, this),
         std::bind(&Cpu::op_RST_38H, this)};

    ///< std::function binding for each CPU instructions's method.
    std::array<std::function<void()>, 0x100> m_opsPrefixCBFunctions =
        {std::bind(&Cpu::op_RLC_B, this),       std::bind(&Cpu::op_RLC_C, this),
         std::bind(&Cpu::op_RLC_D, this),       std::bind(&Cpu::op_RLC_E, this),
         std::bind(&Cpu::op_RLC_H, this),       std::bind(&Cpu::op_RLC_L, this),
         std::bind(&Cpu::op_RLC__HL__, this),   std::bind(&Cpu::op_RLC_A, this),
         std::bind(&Cpu::op_RRC_B, this),       std::bind(&Cpu::op_RRC_C, this),
         std::bind(&Cpu::op_RRC_D, this),       std::bind(&Cpu::op_RRC_E, this),
         std::bind(&Cpu::op_RRC_H, this),       std::bind(&Cpu::op_RRC_L, this),
         std::bind(&Cpu::op_RRC__HL__, this),   std::bind(&Cpu::op_RRC_A, this),
         std::bind(&Cpu::op_RL_B, this),        std::bind(&Cpu::op_RL_C, this),
         std::bind(&Cpu::op_RL_D, this),        std::bind(&Cpu::op_RL_E, this),
         std::bind(&Cpu::op_RL_H, this),        std::bind(&Cpu::op_RL_L, this),
         std::bind(&Cpu::op_RL__HL__, this),    std::bind(&Cpu::op_RL_A, this),
         std::bind(&Cpu::op_RR_B, this),        std::bind(&Cpu::op_RR_C, this),
         std::bind(&Cpu::op_RR_D, this),        std::bind(&Cpu::op_RR_E, this),
         std::bind(&Cpu::op_RR_H, this),        std::bind(&Cpu::op_RR_L, this),
         std::bind(&Cpu::op_RR__HL__, this),    std::bind(&Cpu::op_RR_A, this),
         std::bind(&Cpu::op_SLA_B, this),       std::bind(&Cpu::op_SLA_C, this),
         std::bind(&Cpu::op_SLA_D, this),       std::bind(&Cpu::op_SLA_E, this),
         std::bind(&Cpu::op_SLA_H, this),       std::bind(&Cpu::op_SLA_L, this),
         std::bind(&Cpu::op_SLA__HL__, this),   std::bind(&Cpu::op_SLA_A, this),
         std::bind(&Cpu::op_SRA_B, this),       std::bind(&Cpu::op_SRA_C, this),
         std::bind(&Cpu::op_SRA_D, this),       std::bind(&Cpu::op_SRA_E, this),
         std::bind(&Cpu::op_SRA_H, this),       std::bind(&Cpu::op_SRA_L, this),
         std::bind(&Cpu::op_SRA__HL__, this),   std::bind(&Cpu::op_SRA_A, this),
         std::bind(&Cpu::op_SWAP_B, this),      std::bind(&Cpu::op_SWAP_C, this),
         std::bind(&Cpu::op_SWAP_D, this),      std::bind(&Cpu::op_SWAP_E, this),
         std::bind(&Cpu::op_SWAP_H, this),      std::bind(&Cpu::op_SWAP_L, this),
         std::bind(&Cpu::op_SWAP__HL__, this),  std::bind(&Cpu::op_SWAP_A, this),
         std::bind(&Cpu::op_SRL_B, this),       std::bind(&Cpu::op_SRL_C, this),
         std::bind(&Cpu::op_SRL_D, this),       std::bind(&Cpu::op_SRL_E, this),
         std::bind(&Cpu::op_SRL_H, this),       std::bind(&Cpu::op_SRL_L, this),
         std::bind(&Cpu::op_SRL__HL__, this),   std::bind(&Cpu::op_SRL_A, this),
         std::bind(&Cpu::op_BIT_0_B, this),     std::bind(&Cpu::op_BIT_0_C, this),
         std::bind(&Cpu::op_BIT_0_D, this),     std::bind(&Cpu::op_BIT_0_E, this),
         std::bind(&Cpu::op_BIT_0_H, this),     std::bind(&Cpu::op_BIT_0_L, this),
         std::bind(&Cpu::op_BIT_0__HL__, this), std::bind(&Cpu::op_BIT_0_A, this),
         std::bind(&Cpu::op_BIT_1_B, this),     std::bind(&Cpu::op_BIT_1_C, this),
         std::bind(&Cpu::op_BIT_1_D, this),     std::bind(&Cpu::op_BIT_1_E, this),
         std::bind(&Cpu::op_BIT_1_H, this),     std::bind(&Cpu::op_BIT_1_L, this),
         std::bind(&Cpu::op_BIT_1__HL__, this), std::bind(&Cpu::op_BIT_1_A, this),
         std::bind(&Cpu::op_BIT_2_B, this),     std::bind(&Cpu::op_BIT_2_C, this),
         std::bind(&Cpu::op_BIT_2_D, this),     std::bind(&Cpu::op_BIT_2_E, this),
         std::bind(&Cpu::op_BIT_2_H, this),     std::bind(&Cpu::op_BIT_2_L, this),
         std::bind(&Cpu::op_BIT_2__HL__, this), std::bind(&Cpu::op_BIT_2_A, this),
         std::bind(&Cpu::op_BIT_3_B, this),     std::bind(&Cpu::op_BIT_3_C, this),
         std::bind(&Cpu::op_BIT_3_D, this),     std::bind(&Cpu::op_BIT_3_E, this),
         std::bind(&Cpu::op_BIT_3_H, this),     std::bind(&Cpu::op_BIT_3_L, this),
         std::bind(&Cpu::op_BIT_3__HL__, this), std::bind(&Cpu::op_BIT_3_A, this),
         std::bind(&Cpu::op_BIT_4_B, this),     std::bind(&Cpu::op_BIT_4_C, this),
         std::bind(&Cpu::op_BIT_4_D, this),     std::bind(&Cpu::op_BIT_4_E, this),
         std::bind(&Cpu::op_BIT_4_H, this),     std::bind(&Cpu::op_BIT_4_L, this),
         std::bind(&Cpu::op_BIT_4__HL__, this), std::bind(&Cpu::op_BIT_4_A, this),
         std::bind(&Cpu::op_BIT_5_B, this),     std::bind(&Cpu::op_BIT_5_C, this),
         std::bind(&Cpu::op_BIT_5_D, this),     std::bind(&Cpu::op_BIT_5_E, this),
         std::bind(&Cpu::op_BIT_5_H, this),     std::bind(&Cpu::op_BIT_5_L, this),
         std::bind(&Cpu::op_BIT_5__HL__, this), std::bind(&Cpu::op_BIT_5_A, this),
         std::bind(&Cpu::op_BIT_6_B, this),     std::bind(&Cpu::op_BIT_6_C, this),
         std::bind(&Cpu::op_BIT_6_D, this),     std::bind(&Cpu::op_BIT_6_E, this),
         std::bind(&Cpu::op_BIT_6_H, this),     std::bind(&Cpu::op_BIT_6_L, this),
         std::bind(&Cpu::op_BIT_6__HL__, this), std::bind(&Cpu::op_BIT_6_A, this),
         std::bind(&Cpu::op_BIT_7_B, this),     std::bind(&Cpu::op_BIT_7_C, this),
         std::bind(&Cpu::op_BIT_7_D, this),     std::bind(&Cpu::op_BIT_7_E, this),
         std::bind(&Cpu::op_BIT_7_H, this),     std::bind(&Cpu::op_BIT_7_L, this),
         std::bind(&Cpu::op_BIT_7__HL__, this), std::bind(&Cpu::op_BIT_7_A, this),
         std::bind(&Cpu::op_RES_0_B, this),     std::bind(&Cpu::op_RES_0_C, this),
         std::bind(&Cpu::op_RES_0_D, this),     std::bind(&Cpu::op_RES_0_E, this),
         std::bind(&Cpu::op_RES_0_H, this),     std::bind(&Cpu::op_RES_0_L, this),
         std::bind(&Cpu::op_RES_0__HL__, this), std::bind(&Cpu::op_RES_0_A, this),
         std::bind(&Cpu::op_RES_1_B, this),     std::bind(&Cpu::op_RES_1_C, this),
         std::bind(&Cpu::op_RES_1_D, this),     std::bind(&Cpu::op_RES_1_E, this),
         std::bind(&Cpu::op_RES_1_H, this),     std::bind(&Cpu::op_RES_1_L, this),
         std::bind(&Cpu::op_RES_1__HL__, this), std::bind(&Cpu::op_RES_1_A, this),
         std::bind(&Cpu::op_RES_2_B, this),     std::bind(&Cpu::op_RES_2_C, this),
         std::bind(&Cpu::op_RES_2_D, this),     std::bind(&Cpu::op_RES_2_E, this),
         std::bind(&Cpu::op_RES_2_H, this),     std::bind(&Cpu::op_RES_2_L, this),
         std::bind(&Cpu::op_RES_2__HL__, this), std::bind(&Cpu::op_RES_2_A, this),
         std::bind(&Cpu::op_RES_3_B, this),     std::bind(&Cpu::op_RES_3_C, this),
         std::bind(&Cpu::op_RES_3_D, this),     std::bind(&Cpu::op_RES_3_E, this),
         std::bind(&Cpu::op_RES_3_H, this),     std::bind(&Cpu::op_RES_3_L, this),
         std::bind(&Cpu::op_RES_3__HL__, this), std::bind(&Cpu::op_RES_3_A, this),
         std::bind(&Cpu::op_RES_4_B, this),     std::bind(&Cpu::op_RES_4_C, this),
         std::bind(&Cpu::op_RES_4_D, this),     std::bind(&Cpu::op_RES_4_E, this),
         std::bind(&Cpu::op_RES_4_H, this),     std::bind(&Cpu::op_RES_4_L, this),
         std::bind(&Cpu::op_RES_4__HL__, this), std::bind(&Cpu::op_RES_4_A, this),
         std::bind(&Cpu::op_RES_5_B, this),     std::bind(&Cpu::op_RES_5_C, this),
         std::bind(&Cpu::op_RES_5_D, this),     std::bind(&Cpu::op_RES_5_E, this),
         std::bind(&Cpu::op_RES_5_H, this),     std::bind(&Cpu::op_RES_5_L, this),
         std::bind(&Cpu::op_RES_5__HL__, this), std::bind(&Cpu::op_RES_5_A, this),
         std::bind(&Cpu::op_RES_6_B, this),     std::bind(&Cpu::op_RES_6_C, this),
         std::bind(&Cpu::op_RES_6_D, this),     std::bind(&Cpu::op_RES_6_E, this),
         std::bind(&Cpu::op_RES_6_H, this),     std::bind(&Cpu::op_RES_6_L, this),
         std::bind(&Cpu::op_RES_6__HL__, this), std::bind(&Cpu::op_RES_6_A, this),
         std::bind(&Cpu::op_RES_7_B, this),     std::bind(&Cpu::op_RES_7_C, this),
         std::bind(&Cpu::op_RES_7_D, this),     std::bind(&Cpu::op_RES_7_E, this),
         std::bind(&Cpu::op_RES_7_H, this),     std::bind(&Cpu::op_RES_7_L, this),
         std::bind(&Cpu::op_RES_7__HL__, this), std::bind(&Cpu::op_RES_7_A, this),
         std::bind(&Cpu::op_SET_0_B, this),     std::bind(&Cpu::op_SET_0_C, this),
         std::bind(&Cpu::op_SET_0_D, this),     std::bind(&Cpu::op_SET_0_E, this),
         std::bind(&Cpu::op_SET_0_H, this),     std::bind(&Cpu::op_SET_0_L, this),
         std::bind(&Cpu::op_SET_0__HL__, this), std::bind(&Cpu::op_SET_0_A, this),
         std::bind(&Cpu::op_SET_1_B, this),     std::bind(&Cpu::op_SET_1_C, this),
         std::bind(&Cpu::op_SET_1_D, this),     std::bind(&Cpu::op_SET_1_E, this),
         std::bind(&Cpu::op_SET_1_H, this),     std::bind(&Cpu::op_SET_1_L, this),
         std::bind(&Cpu::op_SET_1__HL__, this), std::bind(&Cpu::op_SET_1_A, this),
         std::bind(&Cpu::op_SET_2_B, this),     std::bind(&Cpu::op_SET_2_C, this),
         std::bind(&Cpu::op_SET_2_D, this),     std::bind(&Cpu::op_SET_2_E, this),
         std::bind(&Cpu::op_SET_2_H, this),     std::bind(&Cpu::op_SET_2_L, this),
         std::bind(&Cpu::op_SET_2__HL__, this), std::bind(&Cpu::op_SET_2_A, this),
         std::bind(&Cpu::op_SET_3_B, this),     std::bind(&Cpu::op_SET_3_C, this),
         std::bind(&Cpu::op_SET_3_D, this),     std::bind(&Cpu::op_SET_3_E, this),
         std::bind(&Cpu::op_SET_3_H, this),     std::bind(&Cpu::op_SET_3_L, this),
         std::bind(&Cpu::op_SET_3__HL__, this), std::bind(&Cpu::op_SET_3_A, this),
         std::bind(&Cpu::op_SET_4_B, this),     std::bind(&Cpu::op_SET_4_C, this),
         std::bind(&Cpu::op_SET_4_D, this),     std::bind(&Cpu::op_SET_4_E, this),
         std::bind(&Cpu::op_SET_4_H, this),     std::bind(&Cpu::op_SET_4_L, this),
         std::bind(&Cpu::op_SET_4__HL__, this), std::bind(&Cpu::op_SET_4_A, this),
         std::bind(&Cpu::op_SET_5_B, this),     std::bind(&Cpu::op_SET_5_C, this),
         std::bind(&Cpu::op_SET_5_D, this),     std::bind(&Cpu::op_SET_5_E, this),
         std::bind(&Cpu::op_SET_5_H, this),     std::bind(&Cpu::op_SET_5_L, this),
         std::bind(&Cpu::op_SET_5__HL__, this), std::bind(&Cpu::op_SET_5_A, this),
         std::bind(&Cpu::op_SET_6_B, this),     std::bind(&Cpu::op_SET_6_C, this),
         std::bind(&Cpu::op_SET_6_D, this),     std::bind(&Cpu::op_SET_6_E, this),
         std::bind(&Cpu::op_SET_6_H, this),     std::bind(&Cpu::op_SET_6_L, this),
         std::bind(&Cpu::op_SET_6__HL__, this), std::bind(&Cpu::op_SET_6_A, this),
         std::bind(&Cpu::op_SET_7_B, this),     std::bind(&Cpu::op_SET_7_C, this),
         std::bind(&Cpu::op_SET_7_D, this),     std::bind(&Cpu::op_SET_7_E, this),
         std::bind(&Cpu::op_SET_7_H, this),     std::bind(&Cpu::op_SET_7_L, this),
         std::bind(&Cpu::op_SET_7__HL__, this), std::bind(&Cpu::op_SET_7_A, this)};
};

#endif /* CPU_H_ */
