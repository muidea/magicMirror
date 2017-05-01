/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPNOTIFYREQUEST_H_
#define _MUPMPCC_SSDPNOTIFYREQUEST_H_

#include <sstream>

#include <ssdp/SSDPRequest.h>

namespace CyberLink {

class SSDPNotifyRequest : public SSDPRequest {
public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SSDPNotifyRequest() {
    setMethod(CyberLink::HTTP::NOTIFY);
    setURI("*");
  }
};

}

#endif

