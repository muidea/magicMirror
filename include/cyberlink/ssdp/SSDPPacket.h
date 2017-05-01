/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPPACKET_H_
#define _MUPMPCC_SSDPPACKET_H_

#include <iostream>
#include <string>

#include <net/DatagramPacket.h>
#include <http/HTTP.h>
#include <http/HTTPHeader.h>
#include <ssdp/SSDP.h>
#include <device/NTS.h>
#include <device/MAN.h>
#include <device/NT.h>
#include <device/ST.h>
#include <device/USN.h>

namespace CyberLink {
class SSDPPacket  {
  CyberLink::DatagramPacket  dgmPacket;
  std::string localAddr;
  long timeStamp;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  SSDPPacket() {
  }

  ////////////////////////////////////////////////
  // DatagramPacket
  ////////////////////////////////////////////////
  
 public:
  void setDatagramPacket(CyberLink::DatagramPacket *packet) {
    dgmPacket.set(packet);
  }

  CyberLink::DatagramPacket &getDatagramPacket() {
    return dgmPacket;
  }

  ////////////////////////////////////////////////
  // addr
  ////////////////////////////////////////////////
  
 public:
  void setLocalAddress(const std::string & addr) {
    localAddr = addr;
  }
  
  const char *getLocalAddress() {
    return localAddr.c_str();
  }

  ////////////////////////////////////////////////
  // Time
  ////////////////////////////////////////////////

 public:
  void setTimeStamp(long value) {
    timeStamp = value;
  }
    
  long getTimeStamp() {
    return timeStamp;
  }

  ////////////////////////////////////////////////
  // Remote host
  ////////////////////////////////////////////////

 public:
  const char *getRemoteAddress() {
    return dgmPacket.getAddress();
  }

  int getRemotePort() {
    return dgmPacket.getPort();
  }
  
  ////////////////////////////////////////////////
  // Access Methods
  ////////////////////////////////////////////////

 public:
  const char *getData() {
    return dgmPacket.getData();
  }

  ////////////////////////////////////////////////
  // First Line Methods
  ////////////////////////////////////////////////
  
public:
  
  bool isNotifyRequest();
  bool isSearchRequest();
  
  ////////////////////////////////////////////////
  // Access Methods
  ////////////////////////////////////////////////

 public:
  const char *getHost(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::HOST, buf);
  }

  const char *getCacheControl(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::CACHE_CONTROL, buf);
  }
  
  const char *getLocation(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::LOCATION, buf);
  }

  const char *getMAN(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::MAN, buf);
  }

  const char *getST(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::ST, buf);
  }

  const char *getNT(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::NT, buf);
  }

  const char *getNTS(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::NTS, buf);
  }

  const char *getServer(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::SERVER, buf);
  }

  const char *getUSN(std::string &buf) {
    return CyberLink::HTTPHeaderGetValue(getData(), CyberLink::HTTP::USN, buf);
  }

  int getMX() {
    return CyberLink::HTTPHeaderGetIntegerValue(getData(), CyberLink::HTTP::MX);
  }

  ////////////////////////////////////////////////
  // Access Methods (Extension)
  ////////////////////////////////////////////////

 public:
  bool isRootDevice();

  bool isDiscover() {
    std::string buf;
    return MAN::IsDiscover(getMAN(buf));
  }

  bool isAlive() {
    std::string buf;
    return NTS::IsAlive(getNTS(buf));
  }

  bool isByeBye() {
    std::string buf;
    return NTS::IsByeBye(getNTS(buf));
  }

  int getLeaseTime() {
    std::string buf;
    return SSDP::GetLeaseTime(getCacheControl(buf));
  }

  ////////////////////////////////////////////////
  // set
  ////////////////////////////////////////////////

 public:
  void set(SSDPPacket *ssdpPacket);
  
  bool isNull() {
    return (timeStamp == 0) ? true : false;
  }

  ////////////////////////////////////////////////
  // toString
  ////////////////////////////////////////////////

 public:
  const char *toString() {
    return getData();
  }

  void print() {
    std::cout << toString() << std::endl;
  }  
};

}

#endif


