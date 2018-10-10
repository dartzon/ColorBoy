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
        printf("[ASSERTION FAILED] - [%s @ Line %d] : %s\n", fctName, lineNum, errorMsg);
    }
}

inline void logMessage(const char* fctName, const int lineNum, const char* msg)
{
    printf("[INFO] - [%s @ Line %d] : %s\n", fctName, lineNum, msg);
}

/// \def  GBASSERT(TEST, MSG)
///
/// Checks assertion based on the result of @a TEST and displays @a MSG.
#define GBASSERT(TEST, MSG) assertWithMessage(TEST, __func__, __LINE__, "\n\t> DETAILS : " MSG)

/// \def  GBLOG(MSG)
///
/// Displays information message in @a MSG.
#define GBLOG(MSG) assertWithMessage(__func__, __LINE__, "\n\t> DETAILS : " MSG)

/// \def  NOTYETIMPLEMENTED()
///
/// Used in unimplemented functions to halt execution if encountered in debug mode.
#define NOTYETIMPLEMENTED()                                                                        \
    assertWithMessage(false, __func__, __LINE__, "Function not yet implemented!\n")

#else

#define GBASSERT(TEST, MSG)
#define GBLOG(MSG)
#define NOTYETIMPLEMENTED()

#endif

#endif /* UTILS_H_ */
