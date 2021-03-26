/*! \file   input.c
 *  \brief  Implements functions of input.h
 */

#include "Input.h"


int checkedInputInt(bool(* additionalCheck)(int))
{
    int result;
    char inputString[INPUT_SIZE];

    while (true)
    {
        scanf("%s", inputString);
        int flag = sscanf(inputString, "%d", &result);
        if (flag == 0 || flag == EOF)
        {
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

