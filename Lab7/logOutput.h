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

/*! \brief Returns free size of file system
 *
 *  \param vfsPath Path to vfs
 *
 *  \return Number of free blocks
 */
unsigned long FsFreeSize(char* vfsPath);

#endif //LOGOUTPUT_H
