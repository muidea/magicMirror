/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHREQUEST_H_
#define _MUPMPCC_SSDPSEARCHREQUEST_H_

#include <string>

#include <ssdp/SSDP.h>
#include <ssdp/SSDPRequest.h>
#include <device/ST.h>
#include <device/MAN.h>
#include <net/HostInterface.h>
#include <event/SubscriptionResponse.h>

namespace CyberLink {
class SSDPSearchRequest : public SSDPRequest {
public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchRequest(const std::string &serachTarget, int mx) {
    init(serachTarget, mx);
  }
  
  SSDPSearchRequest(const std::string &serachTarget) {
    init(serachTarget, SSDP::DEFAULT_MSEARCH_MX);
  }
  
  SSDPSearchRequest() {
    init(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

private:

  void init(const std::string &serachTarget, int mx) {
    setMethod(CyberLink::HTTP::M_SEARCH);
    setURI("*");

    setHeader(CyberLink::HTTP::ST, serachTarget);
    setHeader(CyberLink::HTTP::MX, mx);
    std::string man;
    man = "\"";
    man += MAN::DISCOVER;
    man += "\"";
    setHeader(CyberLink::HTTP::MAN, man.c_str());
  }

  ////////////////////////////////////////////////
  // HOST
  ////////////////////////////////////////////////

public:
  
  void setLocalAddress(const std::string &bindAddr) {
    const char *ssdpAddr = SSDP::ADDRESS;
    if (CyberLink::IsIPv6Address(bindAddr) == true)
      ssdpAddr = SSDP::GetIPv6Address();
    setHost(ssdpAddr, SSDP::PORT);
  }

};

}

#endif
