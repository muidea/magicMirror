/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <util/MessageQueue.h>
#include <util/Thread.h>
#include <util/TimeUtil.h>
#include "MessageQueueTest.h"
#include <iostream>

using namespace std;
using namespace CyberLink;

#define FRACTAL_MESSAGE_BASIC_TEST_COUNT 10

class TestMessage : public Message {

public:
  
  TestMessage(int value = 0) {
    this->value = value;
  }
  
  int getValue() {
    return this->value;
  }
  
private:
  int value;
};

bool CyberLinkTest::TestPostMessage() {
  MessageQueue msgQueue;
  
  Message *popMsg;
  if (msgQueue.waitMessage(&popMsg, 1) != false) {
	  std::cout << "waitMessage failed, :" << __LINE__ << std::endl;
  }
  
  TestMessage *msg = new TestMessage();
  msgQueue.pushMessage(msg);
  
  if (msgQueue.waitMessage(&popMsg) != true) {
	  std::cout << "pushMessage failed, :" << __LINE__ << std::endl;
  }

  return true;
}

bool CyberLinkTest::TestClearMessage() {
  MessageQueue msgQueue;
  
  TestMessage *msg = new TestMessage();
  
  if (msgQueue.size() != 0) {
	  std::cout << "pushMessage failed, :" << __LINE__ << std::endl;
  }
  
  msgQueue.pushMessage(msg);
  if (msgQueue.size() != 1) {
	  std::cout << "(msgQueue.size failed, :" << __LINE__ << std::endl;
  }
  
  msgQueue.clear();
  if (msgQueue.size() != 0) {
	  std::cout << "pushMessage failed, :" << __LINE__ << std::endl;
  }
  return true;
}

bool CyberLinkTest::TestLoopMessage() {
  MessageQueue msgQueue;
  
  for (int n = 0; n < FRACTAL_MESSAGE_BASIC_TEST_COUNT; n++) {
    TestMessage *msg = new TestMessage(n);
    msgQueue.pushMessage(msg);
  }

  for (int n = 0; n < FRACTAL_MESSAGE_BASIC_TEST_COUNT; n++) {
    Message *msg;
    msgQueue.waitMessage(&msg);
    TestMessage *testMsg = dynamic_cast<TestMessage *>(msg);
    int msgValue = testMsg->getValue();
	if (n != msgValue) {
		std::cout << "getValue failed, :" << __LINE__ << std::endl;
	}
    delete msg;
  }

  return true;
}

class MessageCalcelThread : public Thread
{
public:
  
  MessageQueue *msgQueue;
  
  MessageCalcelThread(MessageQueue *msgQueue)
  {
    this->msgQueue = msgQueue;
  }
  
  void run()
  {
    Wait(1000);
    msgQueue->clear();
  }
};

bool CyberLinkTest::TestMessageCancelThread() {
  MessageQueue msgQueue;

  MessageCalcelThread msgCancelThread(&msgQueue);
  msgCancelThread.start();
  
  Message *msg = NULL;
  if (msgQueue.waitMessage(&msg, 1) != false) {
	  std::cout << "msgQueue.waitMessage failed, :" << __LINE__ << std::endl;
  }

  return true;
}
