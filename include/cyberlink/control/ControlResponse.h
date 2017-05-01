/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROLRESPONSE_H_
#define _MUPMPCC_CONTROLRESPONSE_H_

#include <soap/SOAPResponse.h>
#include <xml/Node.h>
#include <soap/SOAP.h>
#include <UPnP.h>
#include <UPnPStatus.h>

#include <sstream>

namespace CyberLink {
class ControlResponse : public uSOAP::SOAPResponse {
  UPnPStatus upnpErr;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  static const char *FAULT_CODE;
  static const char *FAULT_STRING;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ControlResponse() {
    std::string serverName;
    setServer(UPnP::GetServerName(serverName));
  }

  ControlResponse(SOAPResponse *soapRes) {
    set(soapRes);
  }

  ////////////////////////////////////////////////
  // FaultResponse
  ////////////////////////////////////////////////

public:
  
  void setFaultResponse(int errCode, const std::string &errDescr);
  void setFaultResponse(int errCode) {
    setFaultResponse(errCode, UPnP::StatusCodeToString(errCode));
  }

private:
  
  uXML::Node *createFaultResponseNode(int errCode, const std::string &errDescr);

  ////////////////////////////////////////////////
  // UPnP Error
  ////////////////////////////////////////////////

private:

  cyber_shared_ptr<uXML::Node> getUPnPErrorNode() {
    cyber_shared_ptr<uXML::Node> detailNode = getFaultDetailNode();
    if (!detailNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return detailNode->getNodeEndsWith(uSOAP::SOAP::UPNP_ERROR);
  }

  cyber_shared_ptr<uXML::Node> getUPnPErrorCodeNode() {
    cyber_shared_ptr<uXML::Node> errorNode = getUPnPErrorNode();
    if (!errorNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return errorNode->getNodeEndsWith(uSOAP::SOAP::ERROR_CODE);
  }

  cyber_shared_ptr<uXML::Node> getUPnPErrorDescriptionNode() {
    cyber_shared_ptr<uXML::Node> errorNode = getUPnPErrorNode();
    if (!errorNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return errorNode->getNodeEndsWith(uSOAP::SOAP::ERROR_DESCRIPTION);
  }

 public:
  int getUPnPErrorCode() {
    cyber_shared_ptr<uXML::Node> errorCodeNode = getUPnPErrorCodeNode();
    if (!errorCodeNode)
      return -1;
    const char *errorCodeStr = errorCodeNode->getValue();
    return atoi(errorCodeStr);
  }

  const char *getUPnPErrorDescription() {
    cyber_shared_ptr<uXML::Node> errorDescNode = getUPnPErrorDescriptionNode();
    if (!errorDescNode)
      return "";
    return errorDescNode->getValue();
  }

  UPnPStatus *getUPnPError() {
    upnpErr.setCode(getUPnPErrorCode());
    upnpErr.setDescription(getUPnPErrorDescription());
    return &upnpErr;
  }

};

}

#endif

