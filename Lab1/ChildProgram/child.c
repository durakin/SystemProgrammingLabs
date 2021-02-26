#include <stdio.h>
#include "task14.h"
#include <string.h>

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
        printf("Input error!\n");
    }
    char reversedNumber[INPUT_SIZE];
    for (int i = strlen(number) - 1; i >= 0; i--)
    {
        reversedNumber[strlen(number) - (i + 1)] = number[i];
    }
    reversedNumber[strlen(number)] = '\0';
    while (reversedNumber[strlen(reversedNumber)-1] == '0')
    {
        reversedNumber[strlen(reversedNumber)-1] = '\0';
    }
    printf("Original: %s\n", number);
    printf("To decimal: %lli\n", AnyNumeralSystemToDecimal(number, radix));
    printf("Reversed: %s\n", reversedNumber);
    if (CheckIntOverflow(reversedNumber, radix))
    {
        printf("Reversed to decimal: %lli\n",
               AnyNumeralSystemToDecimal(reversedNumber, radix));
    }
    else
    {
        printf("Reversed number is too big");
    }
    return 0;
}

