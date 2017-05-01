/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIPTIONREQUEST_H_
#define _MUPMPCC_SUBSCRIPTIONREQUEST_H_

#include <http/HTTPRequest.h>
#include <http/HTTP.h>
#include <event/Subscription.h>
#include <device/NT.h>
#include <event/SubscriptionRequest.h>
#include <event/SubscriptionResponse.h>

#include <string>

namespace CyberLink {
class Service;

class SubscriptionRequest : public CyberLink::HTTPRequest {
  SubscriptionResponse subRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  SubscriptionRequest() {
  }

  SubscriptionRequest(CyberLink::HTTPRequest *httpReq) {
    set(httpReq);
  }
  
  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

private:

  void setService(Service *service);

 public:
  void setSubscribeRequest(Service *service, const std::string &callback, long timeout);
  void setRenewRequest(Service *service, const std::string &uuid, long timeout);
  void setUnsubscribeRequest(Service *service);

  ////////////////////////////////////////////////
  // NT
  ////////////////////////////////////////////////

 public:
  void setNT(const std::string &value) {
    setHeader(CyberLink::HTTP::NT, value);
  }

  const char *getNT() {
    return getHeaderValue(CyberLink::HTTP::NT);
  }
  
  ////////////////////////////////////////////////
  // CALLBACK
  ////////////////////////////////////////////////

private:

  static const char CALLBACK_START_WITH;
  static const char CALLBACK_END_WITH;

 public:
  void setCallback(const std::string &value) {
    setStringHeader(CyberLink::HTTP::CALBACK, value, CALLBACK_START_WITH, CALLBACK_END_WITH);
  }
  
  const char *getCallback(std::string &buf) {
    return getStringHeaderValue(CyberLink::HTTP::CALBACK, CALLBACK_START_WITH, CALLBACK_END_WITH, buf);
  }

  bool hasCallback() {
    std::string callback;
    getCallback(callback);
    return (0 < callback.length()) ? true : false;
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
  
  bool hasSID() {
    std::string sid;
    getSID(sid);
    return (0 < sid.length()) ? true : false;
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

  ////////////////////////////////////////////////
  // post (Response)
  ////////////////////////////////////////////////

 public:
  CyberLink::HTTP::StatusCode post(SubscriptionResponse *subRes) {
    return HTTPRequest::post(subRes);
  }

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

 public:
  SubscriptionResponse *post() {
    CyberLink::HTTPResponse *httpRes = HTTPRequest::post(getRequestHost(), getRequestPort());
    subRes.set(httpRes);
    return &subRes;
  }
};

}

#endif

