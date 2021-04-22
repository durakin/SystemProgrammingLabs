//
// Created by Albert Nepomnyashiy on 4/15/2021.
//

#include "Input.h"
#include "malloc.h"

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


void checkedInputString(char* destination, bool(* additionalCheck)(char*), int inputSize)
{
    char* input;
    while (true)
    {
        input = (char*) malloc(inputSize * sizeof(char));
        scanf("%s", input);
        if (additionalCheck(input))
        {
            break;
        }
        printf("Wrong format!\n");
        free(input);
    }
    strcpy(destination, input);
}