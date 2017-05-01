/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <util/LoggerFileTarget.h>

CyberLink::LoggerFileTarget::  LoggerFileTarget() {
}

CyberLink::LoggerFileTarget::~LoggerFileTarget() {
  close();
}
  
bool CyberLink::LoggerFileTarget::open(const std::string &filename) {
  FILE *fd = fopen(filename.c_str(), "a");
  if (!fd)
    return false;
  setFD(fd);
  return true;
}

bool CyberLink::LoggerFileTarget::close() {
  bool isClosed = false;
  if (hasFD()) {
    isClosed = (fclose(getFD()) == 0) ? true : false;
    setFD(NULL);
  }
  return isClosed;
}
