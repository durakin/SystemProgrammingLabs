/*! \file   task11.h
 *  \brief  Header file of functions essential for task 11
 */

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef TASK11_H
#define TASK11_H

/*! \enum
 *  \brief  Essential constants for task 11
 */
enum constants
{
    EMPTY_STRIP = -1,
    SMALL_SLEEP = 2,
    BIG_SLEEP = 30,
    MIN_SLEEP = 1,
    N_MIN = 1,
    N_MAX = 1000,
    FIRST_AIRCRAFT_NUMBER = 1
};


/*! \struct Airfield
 *  \brief Airfield struct
 *
 *  \details Keeps information about landing strips, semaphore, and mutex
 */
typedef struct
{
    /*!
     * Number of landing strips
     */
    int numberOfStrips;
    /*!
     * Array of 'codes' of planes at each landing strip
     */
    int* landingStrips;
    /*!
     * Semaphore object
     */
    sem_t airfieldQueueSem;
    /*!
     * Mutex object
     */
    pthread_mutex_t airfieldBusyMutex;
} Airfield;


/*! \struct Aircraft
 *  \brief Aircraft and pthread arg struct
 *
 *  \details Keeps information about aircraft and os also used as
 *  pthread_create arg
 */
typedef struct
{
    /*!
     * Aircraft's number
     */
    int number;
    /*!
     * Pointer to landing strip's array of parked aircraft element, where
     * this aircraft is parked
     */
    int* strip;
    /*!
     * Pointer to destination airfield
     */
    Airfield* airfieldObject;
} Aircraft;

/*! \brief Provides a procedure of landing an aircraft, by finding an empty
 * landing strip and changing necessary variables
 *
 *  \param aircraftToLand pointer to aircraft object which is up to landing
 */
void landAircraft(Aircraft* aircraftToLand);

/*! \brief Checks if number can be a number of landing strips for task 11
 *
 *  \param intToCheck number to check.
 *  \return true if number can be a number of landing strips for task 11
 *  false - otherwise
 */
bool numberOfStripsInputCheck(int intToCheck);

/*! \brief Calls nanosleep function with random amount of seconds and 0
 *  nanoseconds
 *
 *  \param minSeconds minimal number of seconds to sleep.
 *  \param maxSeconds maximal number of seconds to sleep.
 */
void randomNanosleep(int minSeconds, int maxSeconds);


#endif //TASK11_H
