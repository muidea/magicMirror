/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NOTIFYREQUEST_H_
#define _MUPMPCC_NOTIFYREQUEST_H_

#include <soap/SOAPRequest.h>
#include <device/NT.h>
#include <device/NTS.h>
#include <event/Property.h>
#include <event/Subscription.h>
#include <event/Subscriber.h>
#include <event/PropertyList.h>

#include <sstream>

namespace CyberLink {
class NotifyRequest : public uSOAP::SOAPRequest {
  PropertyList propList;

 public:
  static const char *XMLNS;
  static const char *PROPERTY;
  static const char *PROPERTYSET;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  NotifyRequest() {
  }

  NotifyRequest(CyberLink::HTTPRequest *httpReq) {
    set(httpReq);
  }

  ////////////////////////////////////////////////
  // NT
  ////////////////////////////////////////////////

 public:
  void setNT(const std::string &value) {
    setHeader(CyberLink::HTTP::NT, value);
  }

  ////////////////////////////////////////////////
  // NTS
  ////////////////////////////////////////////////

 public:
  void setNTS(const std::string &value) {
    setHeader(CyberLink::HTTP::NTS, value);
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
  // SEQ
  ////////////////////////////////////////////////

 public:
  void setSEQ(long value) {
    setHeader(CyberLink::HTTP::SEQ, value);
  }

  long getSEQ() {
    return getLongHeaderValue(CyberLink::HTTP::SEQ);
  }

  ////////////////////////////////////////////////
  // Request
  ////////////////////////////////////////////////

 public:
  bool setRequest(Subscriber *sub, const std::string &varName, const std::string &value);

private:
  
  uXML::Node *createPropertySetNode(const std::string &varName, const std::string &value);

  cyber_shared_ptr<uXML::Node> getVariableNode();

  ////////////////////////////////////////////////
  // Property
  ////////////////////////////////////////////////

private:
  
  Property *getProperty(uXML::Node *varNode);

 public:
  PropertyList *getPropertyList();
  
};

}

#endif

