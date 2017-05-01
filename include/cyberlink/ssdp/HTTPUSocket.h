/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_HTTPUSOCKET_H_
#define _MUPMPCC_HTTPUSOCKET_H_

#include <net/DatagramSocket.h>
#include <ssdp/SSDPPacket.h>

namespace CyberLink {
class HTTPUSocket  {
  CyberLink::DatagramSocket ssdpUniSock;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  HTTPUSocket();
  
  ~HTTPUSocket();

  ////////////////////////////////////////////////
  // open
  ////////////////////////////////////////////////
  
  bool open(int bindPort = -1, const std::string &bindAddr = "");

  ////////////////////////////////////////////////
  // close
  ////////////////////////////////////////////////

  bool close();

  ////////////////////////////////////////////////
  // DatagramSocket
  ////////////////////////////////////////////////

  CyberLink::DatagramSocket &getDatagramSocket() {
    return ssdpUniSock;
  }

  ////////////////////////////////////////////////
  // bindAddr
  ////////////////////////////////////////////////

  const char *getLocalAddress() {
    return ssdpUniSock.getLocalAddress();
  }

  ////////////////////////////////////////////////
  // post/receive
  ////////////////////////////////////////////////
  
  bool post(const std::string &addr, int port, const std::string &msg);

  bool receive(SSDPPacket *ssdpPacket);

};

}

#endif


