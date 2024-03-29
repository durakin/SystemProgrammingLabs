/*! \file   task14.h
 *  \brief  Header file of functions with numeral systems
 *          essential for task 14
 */

#ifndef LAB1_TASK14_H
#define LAB1_TASK14_H

#include <stdbool.h>
#include "input.h"
#include <inttypes.h>


/*! \struct taskData
 *  \brief Struct for PerformTask() function
 *
 *  \details Keeps data that is used as PerformTask() argument
 */
typedef struct
{
    /*!
     * Number in required numeric system
     */
    char number[INPUT_SIZE];
    /*!
     * Radix of numeric system
     */
    int8_t radix;
} taskData;

/*! \brief Performs task14 with required output
 *
 *  \param data argument for task 14
 */
void PerformTask(taskData* data);

/*! \brief Converts number in any (2-20) numeral system to decimal
 *
 *  \param number number to convert.
 *  \param radix radix of numeral system.
 *  \return Integer conversion result.
 */
int AnyNumeralSystemToDecimal(char* number, int radix);

/*! \brief Checks if number only contains digits, allowed for this numeral
 *  system
 *
 *  \param numberToCheck number to check.
 *  \param radix radix of numeral system.
 *  \return true if number only contains digits, allowed for this numeral
 *  system, false - otherwise.
 */
bool CheckRadixMatch(char* numberToCheck, int radix);

/*! \brief Checks if number is not too big to be written to int after
 *  conversion
 *
 *  \param numberToCheck number to check.
 *  \param radix radix of numeral system.
 *  \return true if number is not too big to be written to int after
 *  conversion, false - otherwise
 */
bool CheckIntOverflow(char* numberToCheck, int radix);

/*! \brief Checks if number can be numeral system radix for task 14
 *
 *  \param intToCheck number to check.
 *  \return true if number can be numeral system radix for task 14
 *  false - otherwise
 */
bool RadixInputCheck(int intToCheck);


#endif //LAB1_TASK14_H
