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

/// \file      utils.h
///
/// \brief     Helper functions for logging and debugging.
///
/// \author    Othmane AIT EL CADI - <dartzon@gmail.com>
/// \date      20-09-2018

#ifndef UTILS_H_
#define UTILS_H_

// std includes.
#include <cstdint>

#include "units.h"

#ifdef COLORBOY_DEBUG

////////////////////////////////////////////////////////
//  Assert macro.
////////////////////////////////////////////////////////

/// \brief  Halts the execution and displays a message if test is false.
///
/// \param  test expression to evaluate.
/// \param  fctName caller function's name.
/// \param  lineNum line of the call in the caller function.
/// \param  errorMsg message to disply if test is false.
inline void
assertWithMessage(const bool test, const char* fctName, const int lineNum, const char* errorMsg)
{
    if (test == false)
    {
        printf("\033[1;31m[ASSERTION FAILED] - [%s @ Line %d] : %s\033[0m\n",
               fctName,
               lineNum,
               errorMsg);
        exit(1);
    }
}

inline void logMessage(const char* fctName, const int lineNum, const char* msg)
{
    printf("\033[1;34m[INFO] - [%s @ Line %d] : %s\033[0m\n", fctName, lineNum, msg);
}

/// \def  CBASSERT(TEST, MSG)
///
/// Checks assertion based on the result of @a TEST and displays @a MSG.
#define CBASSERT(TEST, MSG) assertWithMessage(TEST, __func__, __LINE__, "\n\t> DETAILS : " MSG)

/// \def  CBLOG(MSG)
///
/// Displays information message in @a MSG.
#define CBLOG(MSG) logMessage(__func__, __LINE__, "\n\t> DETAILS : " MSG)

/// \def  NOTYETIMPLEMENTED()
///
/// Used in unimplemented functions to halt execution if encountered in debug mode.
#define NOTYETIMPLEMENTED()                                                                        \
    assertWithMessage(false, __func__, __LINE__, "Function not yet implemented!\n")

template<typename T = uint8_t>
void printCPUOp(const uint16_t addr,
                const std::string& op,
                const uint16_t ir,
                const uint16_t pc,
                const std::initializer_list<T>& arg)
{
    std::string comment;

    switch (ir)
    {
    case 0x18:
    case 0x20:
    case 0x28:
    case 0x30:
    case 0x38:
    case 0xC2:
    case 0xC3:
    case 0xC4:
    case 0xCA:
    case 0xCC:
    case 0xCD:
    case 0xD2:
    case 0xD4:
    case 0xDA:
    case 0xDC:
    case 0xE9: comment = "\t; Jump to @0x%04x"; break;

    case 0xC0:
    case 0xC8:
    case 0xC9:
    case 0xD0:
    case 0xD8:
    case 0xD9: comment = "\t; Return to @0x%04x"; break;
    };

    const std::string format = std::string("\033[1;33m0x%04x\033[0m\t ") + op + "\033[1;32m" +
                               comment + "\033[0m\n";

    if (arg.size() > 0)
    {
        const T val = *std::cbegin(arg);

        printf(format.c_str(), addr, val, pc);
    }
    else
    {
        printf(format.c_str(), addr, pc);
    }
}

/// \def  PRINTOP(OP, ARG)
///
/// Prints the current CPU instruction being executed.
/// Only use withing the Cpu class as it uses its member variables.
#define PRINTOP(OP, ARG)                                                                           \
    printCPUOp(m_currentInstructionAddr - static_cast<const uint8_t>(m_inPrefixCBOp),              \
               OP,                                                                                 \
               IR,                                                                                 \
               PC,                                                                                 \
               ARG)

#else  // Not COLORBOY_DEBUG.

#define CBASSERT(TEST, MSG)
#define CBLOG(MSG)
#define NOTYETIMPLEMENTED()
#define PRINTOP(OP, ARG)

#endif

// =================================================================================================

namespace cbutil
{
/// \brief Combine two bytes into one word.
///
/// \param lByte Low byte.
/// \param hByte High byte.
///
/// \return A word where byte1 and byte2 are combined.
inline uint16_t combineTwoBytes(const uint8_t lByte, const uint8_t hByte)
{
    return (hByte << 8) | lByte;
}

/// \brief Split a word into two bytes.
///
/// \param word The word to split.
/// \param[out] lByte Low byte
/// \param[out] hByte High byte.
inline void splitWord(const uint16_t word, uint8_t& lByte, uint8_t& hByte)
{
    lByte = word & 0xFF;
    hByte = word >> 8;
}

/// \brief Convert a data unit literal to a numeric byte value.
///
/// \param val data unit literal.
///
/// \return numeric byte value.
template<typename DataType>
constexpr uint32_t toByteValue(const DataType val)
{
    return static_cast<uint32_t>(static_cast<units::data::byte_t>(val));
}

/// \brief Convert a frequency unit literal to a numeric Hertz value.
///
/// \param val frequency unit literal.
///
/// \return numeric Hertz value.
template<typename DataType>
constexpr uint32_t toHzValue(const DataType val)
{
    return static_cast<uint32_t>(static_cast<units::frequency::hertz_t>(val));
}

}  // namespace cbutil

#endif /* UTILS_H_ */
