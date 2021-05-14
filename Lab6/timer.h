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
 * \brief Возвращает текущее время в строковом представлении.
 * \return char* Время
*/
char* GetTimeString();


/*!
 * \brief Создает таймер.
 * \param[in] sec Количество секунд.
 * \param[in] usec Количество микросекунд
 * \return Таймер struct itimerval
*/
struct itimerval InitTimer(int sec, int usec);


/*!
 * \brief Откатывает таймер на определенное время.
 * \param[in] sec Количество секунд, через которые таймер сработает.
 * \param[in] usec Количество микросекунд.
 * \return void
*/
void RollbackTimer(struct itimerval *timer, int sec, int usec);


/*!
 * \brief Создает обработчик сигналов.
 * \param[in] TimerHandler Функция обработчик sa_handler, принимает один аргумент.
 * \return struct sigaction
*/
struct sigaction CreateSAHandler(void *TimerHandler);


#endif