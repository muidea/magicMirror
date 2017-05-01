/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPRESPONSE_H_
#define _MUPMPCC_SSDPRESPONSE_H_

#include <http/HTTPResponse.h>
#include <http/HTTP.h>
#include <ssdp/SSDP.h>

namespace CyberLink {
class SSDPResponse : public CyberLink::HTTPResponse {
 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SSDPResponse() {
    setVersion(CyberLink::HTTP::VER_11);
  }

  ////////////////////////////////////////////////
  // ST (SearchTarget)
  ////////////////////////////////////////////////

  void setST(const std::string &value) {
    setHeader(CyberLink::HTTP::ST, value);
  }

  const char *getST() {
    return getHeaderValue(CyberLink::HTTP::ST);
  }

  ////////////////////////////////////////////////
  // Location
  ////////////////////////////////////////////////

  void setLocation(const std::string &value) {
    setHeader(CyberLink::HTTP::LOCATION, value);
  }

  const char *getLocation() {
    return getHeaderValue(CyberLink::HTTP::LOCATION);
  }

  ////////////////////////////////////////////////
  // USN
  ////////////////////////////////////////////////

  void setUSN(const std::string &value) {
    setHeader(CyberLink::HTTP::USN, value);
  }

  const char *getUSN() {
    return getHeaderValue(CyberLink::HTTP::USN);
  }

  ////////////////////////////////////////////////
  // BOOTID.UPNP.ORG
  ////////////////////////////////////////////////

  void setBootID(int value) {
    setHeader(SSDP::BOOTID_UPNP_ORG, value);
  }

  int getBootID() {
    return getIntegerHeaderValue(SSDP::BOOTID_UPNP_ORG);
  }

  ////////////////////////////////////////////////
  // MYNAME
  ////////////////////////////////////////////////
  
  void setMYNAME(const std::string &value) {
    setHeader(CyberLink::HTTP::MYNAME, value);
  }

  const char *getMYNAME() {
    return getHeaderValue(CyberLink::HTTP::MYNAME);
  }

  ////////////////////////////////////////////////
  // CacheControl
  ////////////////////////////////////////////////

  void setLeaseTime(int value);

  int getLeaseTime();

  ////////////////////////////////////////////////
  // getHeader
  ////////////////////////////////////////////////

  const char *getHeader(std::string &headerStr);

};

}

#endif

