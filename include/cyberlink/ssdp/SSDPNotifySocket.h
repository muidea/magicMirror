/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPNOTIFYSOCKET_H_
#define _MUPMPCC_SSDPNOTIFYSOCKET_H_

#include <net/HostInterface.h>
#include <util/Thread.h>
#include <ssdp/SSDP.h>
#include <ssdp/HTTPMUSocket.h>
#include <ssdp/SSDPNotifyRequest.h>

namespace CyberLink {
class ControlPoint;

class SSDPNotifySocket : public HTTPMUSocket, public CyberLink::Thread {
  ControlPoint *controlPoint;

 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SSDPNotifySocket();
  ~SSDPNotifySocket();

  ////////////////////////////////////////////////
  // ControlPoint  
  ////////////////////////////////////////////////
  
  void setControlPoint(ControlPoint *ctrlp) {
    controlPoint = ctrlp;
  }

  ControlPoint *getControlPoint() {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  // open
  ////////////////////////////////////////////////
  
  bool open(const std::string &bindAddr);
  
  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

  bool post(SSDPNotifyRequest *req, const std::string &ifAddr);

  ////////////////////////////////////////////////
  // run  
  ////////////////////////////////////////////////

  void run();
  
};

}

#endif


