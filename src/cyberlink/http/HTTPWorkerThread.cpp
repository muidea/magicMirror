/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/


#include <net/Socket.h>
#include <http/HTTPWorkerThread.h>

#include <sstream>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////
  
HTTPWorkerThread::HTTPWorkerThread(HTTPServer *server) {
  httpServer = server;
}

HTTPWorkerThread::~HTTPWorkerThread() {
}

////////////////////////////////////////////////
//  run  
////////////////////////////////////////////////

void HTTPWorkerThread::run() {
  
  while (isRunnable()) {
    HTTPMessage *httpMsg;
    if (!httpServer->waitMessage(&httpMsg))
      break;
    
    Socket *clientSock = httpMsg->getSocket();
    if (!clientSock) {
      delete httpMsg;
      continue;
    }
    
    cyber_shared_ptr<HTTPSocket> httpSock = cyber_shared_ptr<HTTPSocket>(new HTTPSocket(clientSock));
    if (!httpSock) {
      delete httpMsg;
      delete clientSock;
      continue;
    }
    
    if (httpSock->open() == false) {
      delete httpMsg;
      delete clientSock;
      continue;
    }
    
    HTTPRequest *httpReq = new HTTPRequest();
    if (!httpReq) {
      delete httpMsg;
      delete clientSock;
      continue;
    }
    httpReq->setSocket(httpSock);

    HTTP::StatusCode statusCode;
    while (httpReq->read() == true) {
      statusCode = httpServer->performRequestListener(httpReq);
      if (statusCode == HTTP::PROCESSING)
        break;
      if (httpReq->isKeepAlive() == false)
        break;
    }
    
    if (statusCode != HTTP::PROCESSING) {
      delete httpReq;
    }

    delete httpMsg;
  }
}
