/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_HTTPSOCKET_H_
#define _UHTTP_HTTPSOCKET_H_

#include <net/Socket.h>
#include <io/InputStream.h>

namespace CyberLink {
class HTTPResponse;

class HTTPSocket {
	cyber_shared_ptr<Socket> socket;
  
 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  HTTPSocket(cyber_shared_ptr<Socket> socket);
  HTTPSocket(HTTPSocket *socket);
  ~HTTPSocket();
  
  ////////////////////////////////////////////////
  //  Socket
  ////////////////////////////////////////////////

  void setSocket(cyber_shared_ptr<Socket> socket) {
    this->socket = socket;
  }

  cyber_shared_ptr<Socket> getSocket() {
    return socket;
  }

  ////////////////////////////////////////////////
  //  local address/port
  ////////////////////////////////////////////////
  
 public:
  const char *getLocalAddress() {
    return getSocket()->getLocalAddress();  
  }

  int getLocalPort() {
    return getSocket()->getLocalPort();  
  }

  ////////////////////////////////////////////////
  //  open/close
  ////////////////////////////////////////////////

 public:
  bool open();
  bool close();
  
  ////////////////////////////////////////////////
  //  post
  ////////////////////////////////////////////////

private:

  bool post(HTTPResponse *httpRes, const std::string &content, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked);
  bool post(HTTPResponse *httpRes, CyberLink::InputStream *in, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked);

 public:
  bool post(HTTPResponse *httpRes, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked);
  bool post(HTTPResponse *httpRes);
  bool post(const std::string &content);
  bool post(const char c);
};

}

#endif

