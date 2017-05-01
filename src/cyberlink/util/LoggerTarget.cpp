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

CyberLink::LoggerTarget::LoggerTarget() {
  setFD(NULL);
}

CyberLink::LoggerTarget::~LoggerTarget() {
}

bool CyberLink::LoggerTarget::outputMessage(const char *lineMessage) {
  int ouputLen = fputs(lineMessage, getFD());
  if (ouputLen < 0)
    return false;
  fputs("\n", getFD());
  return true;
}
