/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <http/HTTPMessageQueue.h>
#include <net/Socket.h>

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

CyberLink::HTTPMessageQueue::HTTPMessageQueue() {
}

CyberLink::HTTPMessageQueue::~HTTPMessageQueue() {
}

////////////////////////////////////////////////
//  pushMessage
////////////////////////////////////////////////

bool CyberLink::HTTPMessageQueue::pushMessage(HTTPMessage *httpMsg) {
  return MessageQueue::pushMessage(httpMsg);
}

////////////////////////////////////////////////
//  waitMessage
////////////////////////////////////////////////

bool CyberLink::HTTPMessageQueue::waitMessage(HTTPMessage **httpMsg, time_t timeoutSec) {
  Message *msg;
  if (!MessageQueue::waitMessage(&msg, timeoutSec))
    return false;
  *httpMsg = dynamic_cast<HTTPMessage *>(msg);
  return (*httpMsg) ? true : false;
}

////////////////////////////////////////////////
//  reset
////////////////////////////////////////////////

bool CyberLink::HTTPMessageQueue::reset() {
  return MessageQueue::reset();
}

////////////////////////////////////////////////
//  clear
////////////////////////////////////////////////

bool CyberLink::HTTPMessageQueue::clear() {
  return MessageQueue::clear();
}
