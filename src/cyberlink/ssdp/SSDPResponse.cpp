/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <ssdp/SSDPResponse.h>
#include <util/StringUtil.h>

using namespace std;
using namespace CyberLink;
using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// CacheControl
////////////////////////////////////////////////

void SSDPResponse::setLeaseTime(int value) {
  string valueStr;
  string leaseTimeStr;
  leaseTimeStr= "max-age=";
  leaseTimeStr.append(Integer2String(value, valueStr));
  setHeader(CyberLink::HTTP::CACHE_CONTROL, leaseTimeStr.c_str());
}

int SSDPResponse::getLeaseTime() {
  const char *cacheCtrl = getHeaderValue(CyberLink::HTTP::CACHE_CONTROL);
  return SSDP::GetLeaseTime(cacheCtrl);
}


////////////////////////////////////////////////
// getHeader
////////////////////////////////////////////////

const char *SSDPResponse::getHeader(string &headerStr) {
  string statusLineBuf;
  string headerBuf;

  headerStr.append(getStatusLineString(statusLineBuf));
  headerStr.append(getHeaderString(headerBuf));
  headerStr.append(HTTP::CRLF); // for Intel UPnP control points

  return headerStr.c_str();
}

