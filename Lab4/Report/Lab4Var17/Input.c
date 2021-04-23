/*! \file   Input.c
 *  \brief  Implements functions of Input.h and functions required  by them
 */

#include "Input.h"
#include "malloc.h"


int CheckedInputInt(bool(* additionalCheck)(int))
{
    int result;
    char inputString[MAX_INPUT_SIZE];

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


void CheckedInputString(char* destination, bool(* additionalCheck)(char*),
                        int inputSize)
{
    char input[MAX_INPUT_SIZE];
    while (true)
    {
        scanf("%s", input);
        if (additionalCheck(input) && strlen(input) <= inputSize)
        {
            break;
        }
        printf("Wrong format!\n");
    }
    strcpy(destination, input);
}