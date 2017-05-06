/******************************************************************
*
*CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_HTTPMESSAGEQUEUE_H_
#define _UHTTP_HTTPMESSAGEQUEUE_H_

#include <queue>
#include <platform.h>
#include <util/MessageQueue.h>

namespace CyberLink {

class Socket;
  
class HTTPMessage : public Message {
  
public:
  
  HTTPMessage(cyber_shared_ptr<Socket> socket) {
    this->socket = socket;
  }

  ~HTTPMessage() {
	  this->socket = NULL;
  }

  cyber_shared_ptr<Socket> getSocket() {
    return this->socket;
  }
  
private:

	cyber_shared_ptr<Socket> socket;
};

class HTTPMessageQueue : private MessageQueue {
  
public:
  
  HTTPMessageQueue();
  ~HTTPMessageQueue();
  
  bool pushMessage(HTTPMessage *httpMsg);
  bool waitMessage(HTTPMessage **httpMsg, time_t timeoutSec = 0);
  bool reset();
  bool clear();
};

}

#endif
