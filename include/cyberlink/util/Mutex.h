/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_UTIL_MUTEX_H_
#define _UHTTP_UTIL_MUTEX_H_

#if defined(WIN32)
#include <winsock2.h>
#else
#include <pthread.h>
#endif

namespace CyberLink {
class Mutex {
#if defined(WIN32)
  HANDLE  mutexID;
#else
  pthread_mutex_t mutexID;
#endif

 public:
  Mutex();
  ~Mutex();

  bool lock();
  bool unlock();
};

}

#endif
