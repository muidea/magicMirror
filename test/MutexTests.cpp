/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <vector>

#include <HTTP.h>

#include "MutexTests.h"
using namespace CyberLink;

bool CyberLinkTest::TestMutex()
{
  Mutex *mutex = new Mutex();
  if (mutex->lock() != true) {
	  std::cout << "mutex->lock() failed, :" << __LINE__ << std::endl;
  }
  if (mutex->unlock() != true) {
	  std::cout << "mutex->unlock() failed, :" << __LINE__ << std::endl;
  }
  delete mutex;
  return true;
}
