/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPREQUEST_H_
#define _MUPMPCC_SSDPREQUEST_H_

#include <http/HTTP.h>
#include <http/HTTPRequest.h>
#include <ssdp/SSDP.h>

#include <util/StringUtil.h>

namespace CyberLink {

class SSDPRequest : public CyberLink::HTTPRequest {
 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SSDPRequest() {
    setVersion(CyberLink::HTTP::VER_11);
  }

  ////////////////////////////////////////////////
  // NT
  ////////////////////////////////////////////////

  void setNT(const std::string &value) {
    setHeader(CyberLink::HTTP::NT, value);
  }

  const char *getNT() {
    return getHeaderValue(CyberLink::HTTP::NT);
  }

  ////////////////////////////////////////////////
  // NTS
  ////////////////////////////////////////////////

  void setNTS(const std::string &value) {
    setHeader(CyberLink::HTTP::NTS, value);
  }

  const char *getNTS() {
    return getHeaderValue(CyberLink::HTTP::NTS);
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
  // CacheControl
  ////////////////////////////////////////////////

  void setLeaseTime(int value) {
    std::string leaseTime;
    std::string buf;
    leaseTime = "max-age=";
    leaseTime += CyberLink::Integer2String(value, buf);
    setHeader(CyberLink::HTTP::CACHE_CONTROL,  leaseTime.c_str());
  }

  int getLeaseTime() {
    const char *cacheCtrl = getHeaderValue(CyberLink::HTTP::CACHE_CONTROL);
    return SSDP::GetLeaseTime(cacheCtrl);
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

};

}

#endif

