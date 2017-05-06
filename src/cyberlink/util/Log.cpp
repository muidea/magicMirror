/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <stdarg.h>

#include <util/Log.h>
#include <util/Logger.h>

int CyberLink::Log(
Logger *logger,
int logType,
#if defined(DEBUG)
const char *fileName,
int lineNo,
const char *functionName,
#endif
const char *format, ...) {
  char* outputMessage = new char[CyberLink::Logger::MAX_LINE_STRING];
    
  va_list vaList;
  va_start(vaList, format);
  int outputMessageLength = vsnprintf(outputMessage, CyberLink::Logger::MAX_LINE_STRING, format, vaList);
  va_end(vaList);
  
#if defined(DEBUG)
  snprintf(outputMessage + outputMessageLength,
       (CyberLink::Logger::MAX_LINE_STRING  - outputMessageLength),
       " - %s%s%d%s%s",
       fileName,
       CyberLink::Logger::SEPARATOR,
       lineNo,
       CyberLink::Logger::SEPARATOR,
       functionName);
#endif
  
  int retVal = logger->output(logType, outputMessage);
  delete[]outputMessage;
  return retVal;
}
