/*! \file   input.c
 *  \brief  Implements functions of task14.h
 */

#include "task14.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*! \enum
 *  \brief  Essential constants for task 14
 */
enum NumeralSystemsConstants
{
    VIGESIMAL_A = 'A', /** Digit next to 9 */
    MIN_RADIX = 2,     /** Minimal numeral system radix */
    MAX_RADIX = 20     /** Maximal numeral system radix for task */
};

void PerformTask(taskData* data)
{
    char reversedNumber[INPUT_SIZE];
    char* number = data->number;
    int8_t radix = data->radix;

    for (int i = (int) strlen(number) - 1; i >= 0; i--)
    {
        reversedNumber[strlen(number) - (i + 1)] = number[i];
    }
    reversedNumber[strlen(number)] = '\0';

    while (reversedNumber[strlen(reversedNumber) - 1] == '0')
    {
        reversedNumber[strlen(reversedNumber) - 1] = '\0';
    }

    printf("Original: %s\n", number);
    printf("To decimal: %d\n",
           AnyNumeralSystemToDecimal(number, radix));
    printf("Reversed: %s\n", reversedNumber);
    if (CheckIntOverflow(reversedNumber, radix))
    {
        printf("Reversed to decimal: %d\n",
               AnyNumeralSystemToDecimal(reversedNumber, radix));
    }
    else
    {
        printf("Reversed number is too big");
    }
}

int AnyNumeralSystemToDecimal(char* number, int radix)
{
    int result = 0;
    int multiplier = 1;
    int currentDigit;
    for (int i = (int) strlen(number) - 1; i >= 0; i--)
    {
        if (number[i] >= VIGESIMAL_A)
        {
            currentDigit = 10 + number[i] - VIGESIMAL_A;
        }
        else
        {
            currentDigit = number[i] - '0';
        }
        result += currentDigit * multiplier;
        multiplier *= radix;
    }
    return result;
}

bool CheckRadixMatch(char* numberToCheck, int radix)
{
    int currentDigit;
    for (int i = 0; i < strlen(numberToCheck); i++)
    {
        if (numberToCheck[i] >= VIGESIMAL_A)
        {
            currentDigit = 10 + numberToCheck[i] - VIGESIMAL_A;
        }
        else
        {
            currentDigit = numberToCheck[i] - '0';
        }
        if (currentDigit >= radix || currentDigit < 0)
        {
            return false;
        }
    }
    return true;
}

bool CheckIntOverflow(char* numberToCheck, int radix)
{
    return (double) strlen(numberToCheck) <
           (log((double) __INT_MAX__) / log((double) radix) - 1);
}

bool RadixInputCheck(int intToCheck)
{
    if (intToCheck < MIN_RADIX || intToCheck > MAX_RADIX)
    {
        return false;
    }
    return true;
}
