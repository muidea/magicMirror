/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_HTTPMUSOCKET_H_
#define _MUPMPCC_HTTPMUSOCKET_H_

#include <net/MulticastSocket.h>
#include <net/InetSocketAddress.h>
#include <net/NetworkInterface.h>
#include <http/HTTPRequest.h>
#include <ssdp/SSDPPacket.h>

namespace CyberLink {
class HTTPMUSocket {
  CyberLink::InetSocketAddress ssdpMultiGroup;
  CyberLink::MulticastSocket ssdpMultiSock;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  HTTPMUSocket();  
  ~HTTPMUSocket();

  ////////////////////////////////////////////////
  // bindAddr
  ////////////////////////////////////////////////

  const char *getLocalAddress() {
    return ssdpMultiSock.getLocalAddress();
  }

  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////

  bool open(const std::string &addr, int port, const std::string &bindAddr);
  bool close();

  ////////////////////////////////////////////////
  // send
  ////////////////////////////////////////////////

  bool send(const std::string &host, int port, const std::string &msg);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////
  
  bool post(const std::string &host, int port, CyberLink::HTTPRequest *req) {
    std::string reqStr;
    return send(host, port, req->toString(reqStr));
  }
  
  ////////////////////////////////////////////////
  // reveive
  ////////////////////////////////////////////////

   bool receive(SSDPPacket *ssdpPacket);
};

}

#endif


