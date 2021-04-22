//
// Created by Albert Nepomnyashiy on 4/15/2021.
//

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum sizes
{
    INPUT_SIZE = 64,
    MAX_INPUT_SIZE = 64
};

/*! \brief Reads int
 *
 *  \details Reads int with additional check. Continues reading until
 *  correct value is read.
 *
 *  \param bool* Pointer to the function that checks additional condition.
 *  \return Integer read correct integer.
 */
int checkedInputInt(bool(* additionalCheck)(int));

void checkedInputString(char* destination, bool(* additionalCheck)(char*), int inputSize);


#endif //INPUT_H
