/*! \file   thread.h
 *  \brief  Header file of function which is used as thread function
 */

#ifndef THREAD_H
#define THREAD_H

#include "task11.h"

/*! \brief Used as a thread function. Provides landing, waiting and parking
 * for the aircraft, implementing required thread control action
 *
 *  \param arg void* pointer. Must point to the Aircraft*
 *
 *  \return NULL
 */
void* aircraftThreadFunction(void* arg);


#endif //THREAD_H
