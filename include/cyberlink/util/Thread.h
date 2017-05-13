/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_THREAD_H_
#define _UHTTP_THREAD_H_

#if defined(WIN32)
#include <WinSock2.h>
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

#include <util/Vector.h>
#include <util/Mutex.h>
#include <util/Semaphore.h>

namespace CyberLink {
  
class Thread {
public:
  Thread();
  virtual ~Thread();

  virtual bool start();
  virtual void run() = 0;
  bool isRunnable();
  virtual bool stop();

  void setObject(void *object) {
    this->runObject = object;
  }
  
  void *getObject() {
    return this->runObject;
  }
  
  bool restart() {
    stop();
	this->runningSemaphore.reset();
    start();
    return true;
  }

  void invokeRun() {
	  this->runningSemaphore.post();

	  this->run();
  }

private:  
  void setRunnableFlag(bool flag);
  
private:

#if defined(WIN32)
  HANDLE  hThread;
  DWORD  threadID;
#else
  pthread_t thread;
#endif
  Semaphore runningSemaphore;

  Mutex mutex;
  volatile bool runnableFlag;
  void *runObject;
};

  
class ThreadList : public ::CyberLink::SharedVector<Thread> {
    
  public:
    
    ThreadList();
    virtual ~ThreadList();
    
    bool start();
    bool stop();
};

}

#endif
