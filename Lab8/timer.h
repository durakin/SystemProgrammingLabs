/*! \file   timer.h
 *  \brief  Header for functions for working with system time
 *  essential functions for it.
 */

#ifndef LR6_TIMER_UTIL_H
#define LR6_TIMER_UTIL_H

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>


/*!
 * \brief  Returns string representation of current time
 * \return String with current time
*/
char* GetTimeString();

/*!
 * \brief Initiates timer
 * \param seconds   Seconds
 * \param microSeconds  Microseconds
 * \return timer itimerval
*/
struct itimerval InitTimer(int seconds, int microSeconds);

/*!
 * \brief Rolls timer back to value
 * \param timer   timer itimerval
 * \param seconds     Seconds
 * \param microSeconds    Microseconds
*/
void RollbackTimer(struct itimerval* timer, int seconds, int microSeconds);

/*!
 * \brief Creates signal handler
 * \param sa_handler function
 * \return struct sigaction
*/
struct sigaction CreateSAHandler(void* TimerHandler);


#endif