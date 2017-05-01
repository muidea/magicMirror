/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_HTTPWORKERTHREAD_H_
#define _UHTTP_HTTPWORKERTHREAD_H_

#include <util/Thread.h>
#include <http/HTTPServer.h>

namespace CyberLink {
  
class HTTPWorkerThread : public CyberLink::Thread {
  CyberLink::HTTPServer *httpServer;

public:
  
  HTTPWorkerThread(CyberLink::HTTPServer *server);
  ~HTTPWorkerThread();

  ////////////////////////////////////////////////
  //  run  
  ////////////////////////////////////////////////

  void run();

};


}

#endif
