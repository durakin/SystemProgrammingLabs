/*! \file   Input.h
 *  \brief  Header file of function to read integer and string with additional
 *          check
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/*! \enum
 *  \brief  Sizes of strings for input and output
 */
enum sizes
{
    MAX_INPUT_SIZE = 64
};

/*! \brief Reads int
 *
 *  \details Reads int with additional check. Continues reading until
 *  correct value is read.
 *
 *  \param bool* Pointer to the function that checks additional condition
 *
 *  \return Integer read correct integer
 */
int CheckedInputInt(bool(* additionalCheck)(int));

/*! \brief Reads string
 *
 *  \details Reads string with additional check. Continues reading until
 *  correct value is read.
 *
 *  \param destination  Pointer to buffer for saving read string
 *  \param bool*        Pointer to the additional check function
 *  \param inputSize    Maximal size of read string
 */
void CheckedInputString(char* destination, bool(* additionalCheck)(char*),
                        int inputSize);


#endif //INPUT_H
