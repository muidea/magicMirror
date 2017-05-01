/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNP_SOAPRESPONSE_H_
#define _MUPNP_SOAPRESPONSE_H_

#include <http/HTTPResponse.h>
#include <xml/XML.h>
#include <soap/SOAP.h>

namespace uSOAP {
class SOAPResponse : public CyberLink::HTTPResponse {
  cyber_shared_ptr<uXML::Node> rootNode;
  
 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SOAPResponse();
  ~SOAPResponse();

  ////////////////////////////////////////////////
  // Header
  ////////////////////////////////////////////////

 public:
  const char *getHeader(std::string &buf) {
    return SOAP::GetHeader(getContent(), buf);
  }

  ////////////////////////////////////////////////
  // Encoding
  ////////////////////////////////////////////////

 public:
  const char *getEncording(std::string &buf) {
    return SOAP::GetEncording(getContent(), buf);
  }

  bool isEncording(const std::string &encType) {
    return SOAP::IsEncording(getContent(), encType);
  }

  ////////////////////////////////////////////////
  // Node
  ////////////////////////////////////////////////

private:

  void setRootNode(cyber_shared_ptr<uXML::Node> node) {
    rootNode = node;
  }
  
  cyber_shared_ptr<uXML::Node> getRootNode() {
    return rootNode;
  }
  
  ////////////////////////////////////////////////
  // SOAP Basic
  ////////////////////////////////////////////////

 public:
  void setEnvelopeNode(cyber_shared_ptr<uXML::Node> node) {
    setRootNode(node);
  }

  cyber_shared_ptr<uXML::Node> getEnvelopeNode() {
    return getRootNode();
  }
  
  cyber_shared_ptr<uXML::Node> getBodyNode() {
    cyber_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
    if (!envNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return envNode->getNodeEndsWith(uSOAP::SOAP::BODY);
  }

  cyber_shared_ptr<uXML::Node> getMethodResponseNode(const std::string & name) {
    cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
    if (!bodyNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    std::string methodResName;
    methodResName = name;
    methodResName += SOAP::RESPONSE;
    return bodyNode->getNodeEndsWith(methodResName.c_str());
  }

  cyber_shared_ptr<uXML::Node> getFaultNode() {
    cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
    if (!bodyNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return bodyNode->getNodeEndsWith(uSOAP::SOAP::FAULT);
  }

  cyber_shared_ptr<uXML::Node> getFaultCodeNode() {
    cyber_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULT_CODE);
  }

  cyber_shared_ptr<uXML::Node> getFaultStringNode() {
    cyber_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULT_STRING);
  }

  cyber_shared_ptr<uXML::Node> getFaultActorNode() {
    cyber_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULTACTOR);
  }

  cyber_shared_ptr<uXML::Node> getFaultDetailNode() {
    cyber_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::DETAIL);
  }

  const char *getFaultCode() {
    cyber_shared_ptr<uXML::Node> node = getFaultCodeNode();
    if (!node)
      return "";
    return node->getValue();
  }
  
  const char *getFaultString() {
    cyber_shared_ptr<uXML::Node> node = getFaultStringNode();
    if (!node)
      return "";
    return node->getValue();
  }
  
  const char *getFaultActor() {
    cyber_shared_ptr<uXML::Node> node = getFaultActorNode();
    if (!node)
      return "";
    return node->getValue();
  }

  ////////////////////////////////////////////////
  // setContent
  ////////////////////////////////////////////////
  
 public:
  void setContent(uXML::Node *node);

};

}

#endif
