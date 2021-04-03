/*! \file   input.c
 *  \brief  Implements functions of input.h and functions required  by them
 */

#include "Input.h"


int CycledCheckedInputInt(bool(* additionalCheck)(int))
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

/*! \brief Reads string dynamically allocating memory
*
*  \details Reads string. Possible memory leak: returns a pointer to
*  allocated memory.
*
*  \return char* read string.
*/
char* StrDynInput()
{
    char* userStr = (char*) malloc(sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;
    while (curChar != '\n')
    {
        curChar = getchar();
        int deltaVal;
        deltaVal = 0;
        int lengthDif;
        lengthDif = 0;
        if (curChar == BACKSPACE_KEY)
        {
            deltaVal = -1;
            lengthDif = 1;
        }
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <=
                                               END_CHAR_RANGE)
            {
                deltaVal = 1;
                lengthDif = 2;
            }
            else
            {
                continue;
            }
        }
        int newSize = curSize + deltaVal;
        if (newSize == 0)
        {
            continue;
        }
        char* tmpStr = (char*) malloc(newSize * sizeof(char));
        if (tmpStr)
        {
            for (int i = 0; i < newSize - lengthDif; ++i)
            {
                tmpStr[i] = userStr[i];
            }

            if (curChar != BACKSPACE_KEY)
            {
                tmpStr[newSize - 2] = curChar;
            }
            tmpStr[newSize - 1] = '\0';
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            perror("Couldn't allocate memory!");
            break;
        }
    }

    return userStr;
}

char* CycledCheckedInputString(bool(* additionalCheck)(char*))
{
    char* stringToReturn;
    bool init;
    init = true;
    while (true)
    {
        stringToReturn = StrDynInput();
        if (additionalCheck(stringToReturn))
        {
            return stringToReturn;
        }
        if (!init)
        {
            printf("Input error!\n");
        }
        init = false;
        free(stringToReturn);
    }
}


