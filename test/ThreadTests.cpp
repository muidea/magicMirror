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
#include <iostream>
#include "ThreadTests.h"

using namespace CyberLink;

const int THREAD_TEST_LOOP_NUM = 10;

class TestThread : public Thread
{
public:
  
  int value;
    
  TestThread()
  {
    value = 0;
  }
    
  void run()
  {
    for (int n=0; n<THREAD_TEST_LOOP_NUM; n++)
      value++;
  }
};

void CyberLinkTest::TestThreadFun()
{
  TestThread *thread = new TestThread();
  if (!thread->start()) {
	  std::cout << "thread->start failed, :" << __LINE__ << std::endl;
  }
  while (thread->value != THREAD_TEST_LOOP_NUM) {
	  ::Sleep(1000);
  }
  if (!thread->stop()) {
	  std::cout << "thread->stop failed, :" << __LINE__ << std::endl;
  }
  delete thread;
}
