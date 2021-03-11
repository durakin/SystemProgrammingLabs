/*! \file   input.h
 *  \brief  Header file of function to read integer with additional check
 */

#include <stdbool.h>

#ifndef LAB1_INPUT_H
#define LAB1_INPUT_H

/*! \enum
 *  \brief  Size of string for input
 */
enum Sizes
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


#endif //LAB1_INPUT_H