#include "task14.h"


enum NumeralSystemsConstants
{
    VEGESIMAL_A = 'A',
    MIN_RADIX = 2,
    MAX_RADIX = 20
};

int CheckedInputInt(bool(* additionalCheck)(int))
{
    int result;
    char inputString[INPUT_SIZE];

    while(true) {
        scanf("%s", inputString);
        int flag = sscanf(inputString, "%d", &result);
        if (flag == 0 || flag == EOF) {
            printf("Input error!\n");
            continue;
        }
        if (!additionalCheck(result))
        {
            printf("Input error!\n");
            continue;
        }
        return result;
    }
}

bool RadixInputCheck(int intToCheck)
{
    if(intToCheck < MIN_RADIX || intToCheck > MAX_RADIX)
    {
        return false;
    }
    return true;
}

bool CheckIntOverflow(char* numberToCheck, int radix)
{
    return strlen(numberToCheck) < (log((double)__INT_MAX__) / log((double)radix) - 1);
}

bool CheckRadixMatch(char* numberToCheck, int radix)
{
    int currentDigit;
    for(int i = 0; i < strlen(numberToCheck); i++)
    {
        if(numberToCheck[i] >= VEGESIMAL_A)
        {
            currentDigit = 10 + numberToCheck[i] - VEGESIMAL_A;
        }
        else
        {
            currentDigit = numberToCheck[i] - '0';
        }
        if(currentDigit >= radix || currentDigit < 0)
        {
            return false;
        }
    }
    return true;
}

long long AnyNumeralSystemToDecimal(char* number, int radix)
{
    long long result = 0;
    int multiplier = 1;
    int currentDigit;
    for (int i = strlen(number) - 1; i >= 0; i--)
    {
        if(number[i] >= VEGESIMAL_A)
        {
            currentDigit = 10 + number[i] - VEGESIMAL_A;
        }
        else
        {
            currentDigit = number[i] - '0';
        }
        result+=currentDigit*multiplier;
        multiplier*=radix;
    }
    return result;
}
