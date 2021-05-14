/*! \file   logOutput.h
 *  \brief  Header for function to make an entry to the log
 */

#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H


/*! \brief Writes an entry to log by path
 *
 *  \param logPath  Path for log file
 *  \param info     String that will be written to log
 */
void WriteLogEntry(char* logPath, char* info);

#endif //LOGOUTPUT_H
