/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIPTIONRESPONSE_H_
#define _MUPMPCC_SUBSCRIPTIONRESPONSE_H_

#include <http/HTTPResponse.h>
#include <UPnP.h>
#include <event/Subscription.h>

#include <string>

namespace CyberLink {
class SubscriptionResponse : public CyberLink::HTTPResponse {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  SubscriptionResponse() {
    std::string serverName;
    setServer(UPnP::GetServerName(serverName));
  }

  SubscriptionResponse(CyberLink::HTTPResponse *httpRes) {
    set(httpRes);
  }

  ////////////////////////////////////////////////
  // Error
  ////////////////////////////////////////////////

public:
  
  void setResponse(int code) {
    setStatusCode(code);
    setContentLength(0);
  }
  
  ////////////////////////////////////////////////
  // Error
  ////////////////////////////////////////////////

 public:
  void setErrorResponse(int code) {
    setStatusCode(code);
    setContentLength(0);
  }
    
  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

 public:
  void setSID(const std::string &sid) {
    std::string buf;
    setHeader(CyberLink::HTTP::SID, Subscription::toSIDHeaderString(sid, buf));
  }

  const char *getSID(std::string &buf) {
    return Subscription::GetSID(getHeaderValue(CyberLink::HTTP::SID), buf);
  }

  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

 public:
  void setTimeout(long value) {
    std::string buf;
    setHeader(CyberLink::HTTP::TIMEOUT, Subscription::toTimeoutHeaderString(value, buf));
  }

  long getTimeout() {
    return Subscription::GetTimeout(getHeaderValue(CyberLink::HTTP::TIMEOUT));
  }
};

}

#endif

