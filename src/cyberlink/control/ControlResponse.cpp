/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ControlResponse.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <control/ControlResponse.h>
#include <Device.h>

#include <string>

using namespace std;
using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ControlResponse::FAULT_CODE = "Client";
const char *ControlResponse::FAULT_STRING = "UPnPError";

////////////////////////////////////////////////
// FaultResponse
////////////////////////////////////////////////

void ControlResponse::setFaultResponse(int errCode, const std::string &errDescr) {
  setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
  
  cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  uXML::Node *faultNode = createFaultResponseNode(errCode, errDescr);
  cyber_shared_ptr<uXML::Node> newNode(faultNode);
  bodyNode->addNode(newNode);

  cyber_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
  setContent(envNode.get());
}

uXML::Node *ControlResponse::createFaultResponseNode(int errCode, const std::string &errDescr) {
  // <s:Fault>
  string faultNodeName;
  faultNodeName = uSOAP::SOAP::XMLNS;
  faultNodeName += uSOAP::SOAP::DELIM;
  faultNodeName += uSOAP::SOAP::FAULT;
  uXML::Node *faultNode = new uXML::Node(faultNodeName.c_str());

  // <faultcode>s:Client</faultcode>
  uXML::Node *faultCodeNode = new uXML::Node(uSOAP::SOAP::FAULT_CODE);
  string faultCodeNodeValue;
  faultCodeNodeValue = uSOAP::SOAP::XMLNS;
  faultCodeNodeValue += uSOAP::SOAP::DELIM;
  faultCodeNodeValue += FAULT_CODE;
  faultCodeNode->setValue(faultCodeNodeValue.c_str());
  cyber_shared_ptr<uXML::Node> newNode(faultCodeNode);
  faultNode->addNode(newNode);
    
  // <faultstring>UPnPError</faultstring>
  cyber_shared_ptr<uXML::Node> faultStringNode(new uXML::Node(uSOAP::SOAP::FAULT_STRING));
  faultStringNode->setValue(FAULT_STRING);
  faultNode->addNode(faultStringNode);

  // <detail>
  cyber_shared_ptr<uXML::Node> detailNode(new uXML::Node(uSOAP::SOAP::DETAIL));
  faultNode->addNode(detailNode);

  // <UPnPError xmlns="urn:schemas-upnp-org:control-1-0">
  cyber_shared_ptr<uXML::Node> upnpErrorNode(new uXML::Node(FAULT_STRING));
  upnpErrorNode->setAttribute("xmlns", Control::XMLNS);
  detailNode->addNode(upnpErrorNode);

  // <errorCode>error code</errorCode>
  cyber_shared_ptr<uXML::Node> errorCodeNode(new uXML::Node(uSOAP::SOAP::ERROR_CODE));
  errorCodeNode->setValue(errCode);
  upnpErrorNode->addNode(errorCodeNode);

  // <errorDescription>error string</errorDescription>
  cyber_shared_ptr<uXML::Node> errorDesctiprionNode(new uXML::Node(uSOAP::SOAP::ERROR_DESCRIPTION));
  errorDesctiprionNode->setValue(errDescr);
  upnpErrorNode->addNode(errorDesctiprionNode);
    
  return faultNode;
}

