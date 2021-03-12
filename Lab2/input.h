/*! \file   input.h
 *  \brief  Header file of function to read integer with additional check
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>

/*! \enum
 *  \brief  Size of string for input
 */
enum sizes
{
    INPUT_SIZE = 200
};

/*! \brief Reads int
 *
 *  \details Reads int with additional check. Continues reading until
 *  correct value is read.
 *
 *  \param bool* Pointer to the function that checks additional condition.
 *  \return Integer read correct integer.
 */
int CheckedInputInt(bool(* additionalCheck)(int));


#endif //INPUT_H
