/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_NET_MULTICASTSOCKET_H_
#define _UHTTP_NET_MULTICASTSOCKET_H_

#include <net/DatagramSocket.h>
#include <net/InetSocketAddress.h>
#include <net/NetworkInterface.h>

namespace CyberLink {
class MulticastSocket : public DatagramSocket {
 public:
  MulticastSocket();
  MulticastSocket(int port, const std::string &bindAddr);
  ~MulticastSocket();

  bool bind(int port, const std::string &addr);
  
  bool joinGroup(const std::string &mcastAddr, const std::string &ifAddr = NULL);
  bool joinGroup(InetSocketAddress *mcastAddr, NetworkInterface *ifAddr) {
    return joinGroup(mcastAddr->getAddress(), ifAddr->getAddress());
  }

  void setTimeToLive(int ttl);
};

}

#endif
