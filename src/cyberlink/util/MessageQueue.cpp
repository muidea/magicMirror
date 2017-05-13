/******************************************************************
*
*CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#if defined (WIN32)
#else
#include <unistd.h>
#include <sys/msg.h>
#endif

#include <util/MessageQueue.h>

CyberLink::MessageQueue::MessageQueue() {
  this->sem = new Semaphore(10);
  this->mutex = new Mutex();
}

CyberLink::MessageQueue::~MessageQueue() {
  clear();
  delete this->sem;
  delete this->mutex;
}

bool CyberLink::MessageQueue::pushMessage(Message *message) {
  this->mutex->lock();
  
  push(message);
  this->sem->post();
  
  this->mutex->unlock();

  return true;
}

bool CyberLink::MessageQueue::popMessage(Message **message) {
  *message = NULL;
  
  if (empty())
    return false;

  *message = front();
  pop();
  
  return true;
}

bool CyberLink::MessageQueue::waitMessage(Message **message, time_t timeoutSec) {
  if (!this->sem)
    return false;
  
  if (!this->sem->wait(timeoutSec))
    return false;

  if (this->mutex) {
    this->mutex->lock();
  }
  
  bool popSucces = popMessage(message);
  
  if (this->mutex) {
    this->mutex->unlock();
  }
  
  return popSucces;
}

bool CyberLink::MessageQueue::reset() {
  
  bool areAllOperationSuccess = true;
  if (clear() == false) {
    areAllOperationSuccess = false;
  }
  
  if (this->sem->reset() == false) {
    areAllOperationSuccess = false;
  }

  return areAllOperationSuccess;
}

bool CyberLink::MessageQueue::clear() {
  
  if (this->sem) {
    this->sem->cancel();
  }
  
  Message *message;
  while (popMessage(&message)) {
    delete message;
  }
    
  return true;
}
