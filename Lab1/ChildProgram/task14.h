#include <malloc.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#ifndef LAB1_TASK14_H
#define LAB1_TASK14_H


enum Sizes
{
    INPUT_SIZE = 200
};

int CheckedInputInt(bool(* additionalCheck)(int));

long long AnyNumeralSystemToDecimal(char* number, int radix);

bool CheckRadixMatch(char* numberToCheck, int radix);

bool CheckIntOverflow(char* numberToCheck, int radix);

bool RadixInputCheck(int intToCheck);


#endif //LAB1_TASK14_H
