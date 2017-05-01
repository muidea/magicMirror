/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHRESPONSE_H_
#define _MUPMPCC_SSDPSEARCHRESPONSE_H_

#include <sstream>

#include <UPnP.h>
#include <Device.h>
#include <ssdp/SSDPResponse.h>

namespace CyberLink {
class SSDPSearchResponse : public SSDPResponse {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

public:
  
  SSDPSearchResponse() {
    setStatusCode(CyberLink::HTTP::OK_REQUEST);
    setCacheControl(Device::DEFAULT_LEASE_TIME);
    std::string buf;
    setHeader(CyberLink::HTTP::SERVER, UPnP::GetServerName(buf));
    setHeader(CyberLink::HTTP::EXT, "");
  }
};

}

#endif
