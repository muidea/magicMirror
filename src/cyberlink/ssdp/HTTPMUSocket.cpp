/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <time.h>
#include <net/HostInterface.h>
#include <ssdp/HTTPMUSocket.h>

using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
HTTPMUSocket::HTTPMUSocket() {
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

HTTPMUSocket::~HTTPMUSocket() {
  close();
}

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////

bool HTTPMUSocket::open(const std::string &addr, int port, const std::string &bindAddr) {
  ssdpMultiGroup.setAddress(addr);
  ssdpMultiGroup.setPort(port);

  if (ssdpMultiSock.bind(port, bindAddr) == false) {
    return false;
  }
  
  if (ssdpMultiSock.joinGroup(addr, bindAddr) == false) {
    ssdpMultiSock.close();
    return false;
  }    

  return true;
}

bool HTTPMUSocket::close() {
  if (ssdpMultiSock.close() == false)
    return false;
  return true;
}

////////////////////////////////////////////////
// send
////////////////////////////////////////////////

bool HTTPMUSocket::send(const std::string &host, int port, const std::string &msg) {
  InetSocketAddress inetAddr(host, port);
  
  DatagramPacket dgmPacket(msg, &inetAddr);
  
  MulticastSocket msock;
  msock.setTimeToLive(4);
  return (0 < msock.send(&dgmPacket)) ? true : false;
}

////////////////////////////////////////////////
// reveive
////////////////////////////////////////////////

bool HTTPMUSocket::receive(SSDPPacket *ssdpPacket) {
  ssdpPacket->setLocalAddress(getLocalAddress());
  ssize_t nRecv = ssdpMultiSock.receive(ssdpPacket->getDatagramPacket());
  if (nRecv <= 0)
    return false;
  ssdpPacket->setTimeStamp((long)time(NULL));
  return true;
}
