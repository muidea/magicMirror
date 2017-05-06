/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <util/Logger.h>
#include <ctime>

static CyberLink::Logger *gUHttpLoggerSharedInstance = NULL;

const int CyberLink::Logger::MAX_LINE_STRING = 512;
const char *CyberLink::Logger::SEPARATOR = " ";

CyberLink::Logger *CyberLink::Logger::GetSharedInstance() {
  if (!HasSharedInstance()) {
    gUHttpLoggerSharedInstance = new Logger();
  }
  return gUHttpLoggerSharedInstance;
}

void CyberLink::Logger::SetSharedInstance(CyberLink::Logger *logger) {
  if (HasSharedInstance()) {
    delete gUHttpLoggerSharedInstance;
    gUHttpLoggerSharedInstance = NULL;
  }
  gUHttpLoggerSharedInstance = logger;
}

bool CyberLink::Logger::HasSharedInstance() {
  return (gUHttpLoggerSharedInstance) ? true : false;
}

const char *CyberLink::Logger::GetMaskString(int outputType) {
  switch (outputType) {
  case LoggerTarget::TRACE:
    return "TRACE";
  case LoggerTarget::DBG:
    return "DEBUG";
  case LoggerTarget::INFO:
    return "INFO";
  case LoggerTarget::WARN:
    return "WARN";
  case LoggerTarget::ERR:
    return "ERROR";
  case LoggerTarget::FATAL:
    return "FATAL";
  }
  
  return "UNKNOWN";
}

CyberLink::Logger::Logger() {
  setLevel(LoggerTarget::INFO);
}

CyberLink::Logger::~Logger() {
}

bool CyberLink::Logger::addTarget(LoggerTarget *target) {
  return this->targetList.addTarget(target);
}

bool CyberLink::Logger::clearAllTargets() {
  this->targetList.clear();
  return true;
}

int CyberLink::Logger::output(int outputType, const char *outputMessage) {
  if (outputType < getLevel())
    return 0;

  char logLineMessage[MAX_LINE_STRING];
  char localTimestampString[MAX_LINE_STRING];
  
  this->outputMutex.lock();
  
  time_t timestamp = time(NULL);
  struct tm *localTimestamp = localtime(&timestamp);
  strftime(localTimestampString, MAX_LINE_STRING, "%c", localTimestamp);
  
  snprintf(logLineMessage, MAX_LINE_STRING, "%s%s[%s] %s",
      localTimestampString,
      SEPARATOR,
      GetMaskString(outputType), 
      outputMessage);

  int outputedTargetCount = 0;
  
  for (LoggerTargetList::iterator outputTarget = this->targetList.begin(); outputTarget != this->targetList.end(); outputTarget++) {
    if (!(outputType & (*outputTarget)->getMask()))
      continue;
    if ((*outputTarget)->outputMessage(logLineMessage))
      outputedTargetCount++;
  }
  
  outputMutex.unlock();
  
  return outputedTargetCount;
}
