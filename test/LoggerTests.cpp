/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <time.h>
#include <util/Log.h>
#include "LoggerTests.h"
#include <iostream>
using namespace CyberLink;

#define LOGGER_TEST_MESSAGE "Hello"

bool CyberLinkTest::TestLogger()
{
  Logger testLogger;
  testLogger.setLevel(LoggerLevel::TRACE);
  
  for (int n=0; n<10; n++) {
	if (testLogger.trace(LOGGER_TEST_MESSAGE) != n){
		  std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
	if (testLogger.message(LOGGER_TEST_MESSAGE) != n) {
		  std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
	if (testLogger.warning(LOGGER_TEST_MESSAGE) != n) {
		std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
	if (testLogger.error(LOGGER_TEST_MESSAGE) != n) {
		std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
	if (testLogger.fatal(LOGGER_TEST_MESSAGE) != n) {
		std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
	if (testLogger.debug(LOGGER_TEST_MESSAGE) != n) {
		std::cout << "trace failed, :" << __LINE__ << std::endl;
	}
    testLogger.addTarget(new LoggerNullTarget());
  }

  return true;
}

bool CyberLinkTest::TestLog()
{
  Logger *testLogger = Logger::GetSharedInstance();
  testLogger->setLevel(LoggerLevel::TRACE);
  testLogger->clearAllTargets();
  testLogger->addTarget(new LoggerNullTarget());
  
  if (LogTrace("%s", LOGGER_TEST_MESSAGE) != 1) {
	  std::cout << "trace failed, :" << __LINE__ << std::endl;
  }
  if (LogInfo("%s", LOGGER_TEST_MESSAGE) != 1) {
	  std::cout << "trace failed, :" << __LINE__ << std::endl;
  }
  if (LogWarn("%s", LOGGER_TEST_MESSAGE) != 1) {
	  std::cout << "trace failed, :" << __LINE__ << std::endl;
  }
  if (LogError("%s", LOGGER_TEST_MESSAGE) != 1) {
	  std::cout << "trace failed, :" << __LINE__ << std::endl;
  }
  if (LogFatal("%s", LOGGER_TEST_MESSAGE) != 1) {
	  std::cout << "trace failed, :" << __LINE__ << std::endl;
  }

  testLogger->clearAllTargets();
  return true;
}
