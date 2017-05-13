/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include <util/Thread.h>
#include <util/Semaphore.h>
#include <util/TimeUtil.h>
#include "SemaphoreTests.h"
#include <iostream>

using namespace std;
using namespace CyberLink;

bool CyberLinkTest::TestBasicSemaphore() {
  Semaphore *sem = new Semaphore(2);

  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }

  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }

  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }

  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }

  delete sem;

  return true;
}

bool CyberLinkTest::TestWaitSemaphore() {
  const time_t TEST_WAIT_TIME = 1;
  
  Semaphore *sem = new Semaphore(3);
  
  if (sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }

  if (sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  if (sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait(TEST_WAIT_TIME)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  delete sem;
  return true;
}

static const int SEMAPHORE_THREAD_TEST_LOOP_NUM = 5;

class SemaphorePostThread : public Thread {
 public:
  SemaphorePostThread() {
  }

  void run() {
    Semaphore *sem = (Semaphore *)getObject();
    for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
		if (!sem->post()) {
			std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
	  }
    }
  }
};

bool CyberLinkTest::TestPostThreadSemaphore() {
  Semaphore *sem = new Semaphore(10);
  
  SemaphorePostThread semThread;
  semThread.setObject(sem);
  semThread.start();
  
  for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
	  if (!sem->wait()) {
		  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
	}
  }
  
  delete sem;
  return true;
}

void CyberLinkTest::TestCancelSemaphore() {
  Semaphore *sem = new Semaphore(10);
  
  if (!sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  if (!sem->cancel()) {
	  std::cout << "sem->cancel() failed, :" << __LINE__ << std::endl;
  }
  
  if (sem->post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (sem->wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  
  delete sem;
}

class SemaphoreCancelThread : public Thread {
public:
  SemaphoreCancelThread() {
  }
  
  void run() {
    Wait(1000);
    ((Semaphore *)getObject())->cancel();
  }
};

void CyberLinkTest::TestCancelThreadSemaphore() {
  Semaphore sem(10);
  
  SemaphoreCancelThread semThread;
  semThread.setObject(&sem);
  semThread.start();
  
  if (!sem.post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (!sem.wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (sem.wait(1)) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
  if (sem.post()) {
	  std::cout << "sem->post() failed, :" << __LINE__ << std::endl;
  }
  if (sem.wait()) {
	  std::cout << "sem->wait() failed, :" << __LINE__ << std::endl;
  }
}
