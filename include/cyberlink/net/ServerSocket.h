/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_NET_SERVERSOCKET_H_
#define _UHTTP_NET_SERVERSOCKET_H_

#include <net/Socket.h>

namespace CyberLink {
class ServerSocket : public ::CyberLink::Socket {
 public:
  ServerSocket();
  ~ServerSocket();

};

}

#endif
