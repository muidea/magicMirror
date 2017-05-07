/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#include <util/Mutex.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Mutex
////////////////////////////////////////////////

Mutex::Mutex() {
#if defined(WIN32)
  mutexID = CreateMutex(NULL, FALSE, NULL);
#else
  pthread_mutex_init(&mutexID, NULL);
#endif
}

Mutex::~Mutex() {
#if defined(WIN32)
  CloseHandle(mutexID);
#else
  pthread_mutex_destroy(&mutexID);
#endif
}

bool Mutex::lock() {
#if defined(WIN32)
  WaitForSingleObject(mutexID, INFINITE);
#else
  pthread_mutex_lock(&mutexID);
#endif
  return true;
}

bool Mutex::unlock() {
#if defined(WIN32)
  ReleaseMutex(mutexID);
#else
  pthread_mutex_unlock(&mutexID);
#endif
  return true;
}
