/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <util/Semaphore.h>

CyberLink::Semaphore::Semaphore(size_t maxCount) {
  this->isInitialized = false;
  this->maxCount = maxCount;
  
  init(maxCount);
}

CyberLink::Semaphore::~Semaphore() {
  destory();
}

bool CyberLink::Semaphore::init(size_t maxCount) {
  if (this->isInitialized)
    return true;

#if defined(WIN32)
  this->semId = NULL;
  this->semId = CreateSemaphore(NULL, 0, maxCount> 0 ? maxCount: 1, NULL);
#ifdef _DEBUG
  if (this->semId == NULL) {
	  printf("CreateSemaphore error: %d\n", GetLastError());
  }
#endif
  this->isInitialized = this->semId != NULL;
#elif defined(__APPLE__)
  this->isInitialized = (semaphore_create(mach_task_self(), &semId, SYNC_POLICY_FIFO, (int)maxCount) == KERN_SUCCESS) ? true : false;
#else
  this->isInitialized = (sem_init(&semId, 0, maxCount) == 0)  ? true : false;
#endif
  return this->isInitialized;
}

bool CyberLink::Semaphore::destory() {
  if (!this->isInitialized)
    return true;
#if defined(WIN32)
  CloseHandle(this->semId);
  this->semId = NULL;
  this->isInitialized = this->semId != NULL;
#elif defined(__APPLE__)
  this->isInitialized = (semaphore_destroy(mach_task_self(), semId) == KERN_SUCCESS) ? false : true;
#else
  this->isInitialized = (sem_destroy(&semId) == 0)  ? false : true;
#endif
  
  return !this->isInitialized;
}

bool CyberLink::Semaphore::post() {
  if (!this->isInitialized)
    return false;
  
  bool isSuccess = true;
#if defined (WIN32)
  isSuccess = ReleaseSemaphore(this->semId, 1, NULL) == TRUE;
#ifdef _DEBUG
  if (!isSuccess) {
	  printf("ReleaseSemaphore error: %d\n", GetLastError());
  }
#endif
#elif defined(__APPLE__)
  isSuccess = (semaphore_signal(semId) == KERN_SUCCESS) ? true : false;
#else
  isSuccess = (sem_post(&semId) == 0)  ? true : false;
#endif

  return isSuccess;
}

bool CyberLink::Semaphore::wait(time_t timeoutSec) {
  if (!this->isInitialized)
    return false;
  
  bool isSuccess = true;
#if defined(WIN32)
  DWORD dwTimeOutVal = timeoutSec > 0 ? timeoutSec * 1000 : INFINITE;
  DWORD dwWaitResult = WaitForSingleObject(this->semId, dwTimeOutVal);
  switch (dwWaitResult)
  {
  case WAIT_OBJECT_0:
	  isSuccess = true;
	  break;
  default:
	  isSuccess = false;
	  break;
  }
#elif defined(__APPLE__)
  if (0 < timeoutSec) {
    mach_timespec_t machTimeout;
    machTimeout.tv_sec = (unsigned int)timeoutSec;
    machTimeout.tv_nsec = 0;
    isSuccess = (semaphore_timedwait(semId, machTimeout) == KERN_SUCCESS) ? true : false;
  }
  else {
    isSuccess = (semaphore_wait(semId) == KERN_SUCCESS) ? true : false;
  }
#else
  if (0 < timeoutSec) {
    timespec absTimeout;
    absTimeout.tv_sec = timeoutSec;
    absTimeout.tv_nsec = 0;
    isSuccess = (sem_timedwait(&semId, &absTimeout) == 0)  ? true : false;
  }
  else {
    isSuccess = (sem_wait(&semId) == 0)  ? true : false;
  }
#endif
  
  return isSuccess;
}

bool CyberLink::Semaphore::reset() {
  if (!destory())
    return false;
  return init(this->maxCount);
}

bool CyberLink::Semaphore::cancel() {
  return destory();
}
