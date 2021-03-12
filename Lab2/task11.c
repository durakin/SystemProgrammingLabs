/*! \file   task11.c
 *  \brief  Implements functions of task11.h
 */

#include "task11.h"

void landAircraft(Aircraft* aircraftToLand)
{
    for (int i = 0; i < aircraftToLand->airfieldObject->numberOfStrips; i++)
    {
        if (aircraftToLand->airfieldObject->landingStrips[i] == -1)
        {
            aircraftToLand->airfieldObject->landingStrips[i] = aircraftToLand->number;
            aircraftToLand->strip = &(aircraftToLand->airfieldObject->landingStrips[i]);
            break;
        }
    }
}

bool numberOfStripsInputCheck(int intToCheck)
{
    return intToCheck >= N_MIN && intToCheck <= N_MAX;
}

void randomNanosleep(int minSeconds, int maxSeconds)
{
    struct timespec time;
    int sec = (int) random() % maxSeconds + minSeconds;
    time.tv_sec = sec;
    time.tv_nsec = 0;
    nanosleep(&time, NULL);
}