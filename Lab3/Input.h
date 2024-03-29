/*! \file   input.h
 *  \brief  Header file of function to read integer and string with additional
 *          check
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>


/*! \enum
 *  \brief  Size of string for input and some chars' codes
 */
enum inputConstants
{
    INPUT_SIZE = 200,
    BACKSPACE_KEY = 8,
    START_CHAR_RANGE = 32,
    END_CHAR_RANGE = 126
};

/*! \brief Reads string
 *
 *  \details Reads string with additional check. Continues reading until
 *  correct value is read. Possible memory leak: returns a pointer to
 *  allocated memory.
 *
 *  \param bool* Pointer to the function that checks additional condition.
 *  \return char* read correct string.
 */
char* CycledCheckedInputString(bool(* additionalCheck)(char*));

/*! \brief Reads int
 *
 *  \details Reads int with additional check. Continues reading until
 *  correct value is read.
 *
 *  \param bool* Pointer to the function that checks additional condition.
 *  \return Integer read correct integer.
 */
int CycledCheckedInputInt(bool(* additionalCheck)(int));


#endif //INPUT_H
