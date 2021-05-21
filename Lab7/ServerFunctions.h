/*! \file   ServerFunctions.h
 *  \brief  Header for function that checks if server is running and defines
 *  a few essential constants
 */

#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#define PATH_TO_CHECK_FILE "/tmp/lab7"
#define MIN_PORT 1024
#define MAX_PORT 65635
#define PORT_LENGTH 5


/*!
 * \brief Checks if server is running, if not - writes information for further
 * checks, if running - exits program.
 * \details Checks if server is running on ANY port
 * \param port Port of server
*/
void ServerCheckRunning(int port);


#endif //SERVERFUNCTIONS_H
