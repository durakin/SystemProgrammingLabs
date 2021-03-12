#include "task11.h"

void landAircraft(aircraft* aircraftToLand)
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


void randomNanosleep(int minSeconds, int maxSeconds) {
    struct timespec time;
    int sec = (int) random() % maxSeconds + minSeconds;
    time.tv_sec = sec;
    time.tv_nsec = 0;
    nanosleep(&time, NULL);
}