/*! \file   child.c
 *  \brief  Main file of the child program which contains the main function
 */

#include <stdio.h>
#include <string.h>
#include "input.h"
#include "task14.h"


/*! \brief Main function
 *
 *  \details Main function. Reads radix and number in appropriate numeral
 *  system. Each input continue until correct value is read.
 *
 *  \param argc Count program arguments.
 *  \param argList Array string which contains args.
 *  \return Integer 0 upon successful exit.
 */
int main(int argc, char** argList)
{
    int radix;
    char number[INPUT_SIZE];

    printf("Enter base of numeral system (2 - 20)\n");
    radix = CheckedInputInt(RadixInputCheck);
    printf("Enter number in chosen system. Use \'A\' - \'J\' as"
           "digits for >10-based systems\n");
    while (true)
    {
        scanf("%s", number);
        if (CheckIntOverflow(number, radix) && CheckRadixMatch(number, radix))
        {
            break;
        }
        printf("Wrong format or too big number!\n");
    }

    char reversedNumber[INPUT_SIZE];
    for (int i = strlen(number) - 1; i >= 0; i--)
    {
        reversedNumber[strlen(number) - (i + 1)] = number[i];
    }
    reversedNumber[strlen(number)] = '\0';

    while (reversedNumber[strlen(reversedNumber) - 1] == '0')
    {
        reversedNumber[strlen(reversedNumber) - 1] = '\0';
    }

    printf("Original: %s\n", number);
    printf("To decimal: %d\n", AnyNumeralSystemToDecimal(number, radix));
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

    return 0;
}

