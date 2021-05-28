/*! \file   securityFunctions.h
 *  \brief  Header for security functions
 */

#ifndef SECURITYFUNCTIONS_H
#define SECURITYFUNCTIONS_H

#endif //SECURITYFUNCTIONS_H


/*!
 * \brief Checks if process is running by root user,
 * exits if not
*/
void CheckRoot();

/*!
 * \brief Authenticates user, exits on failure
*/
void CheckAuthentication();