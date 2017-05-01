/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNP_SOAPREQUEST_H_
#define _MUPNP_SOAPREQUEST_H_

#include <http/HTTPRequest.h>
#include <http/HTTPResponse.h>
#include <http/HTTP.h>
#include <soap/SOAP.h>
#include <soap/SOAPResponse.h>
#include <xml/Node.h>

namespace uSOAP {
const char SOAPACTION[] = "SOAPACTION";

class SOAPRequest : public CyberLink::HTTPRequest {
  cyber_shared_ptr<uXML::Node> rootNode;
  SOAPResponse soapRes;
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  SOAPRequest();
  SOAPRequest(CyberLink::HTTPRequest *httpReq);

  ~SOAPRequest();

  ////////////////////////////////////////////////
  // SOAPACTION
  ////////////////////////////////////////////////

 public:
  void setSOAPAction(const std::string &action) {
    setStringHeader(SOAPACTION, action);
  }
  
  const char *getSOAPAction(std::string &buf) {
    return getStringHeaderValue(SOAPACTION, buf);
  }

  bool isSOAPAction(const std::string &value);
 
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
  // post
  ////////////////////////////////////////////////

private:

  cyber_shared_ptr<uXML::Node> parseMessage(const std::string &content, size_t contentLen);

 public:
  SOAPResponse *postMessage(const std::string &host, int port, SOAPResponse *soapRes);

  SOAPResponse *postMessage(const std::string &host, int port) {
    return postMessage(host, port, &soapRes);
  }

  ////////////////////////////////////////////////
  // Node
  ////////////////////////////////////////////////

private:

  void setRootNode(cyber_shared_ptr<uXML::Node> node) {
    rootNode = node;
  }

  cyber_shared_ptr<uXML::Node> getRootNode();
  
  ////////////////////////////////////////////////
  // XML
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
    if (envNode->hasNodes() == false)
      return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return envNode->getNode(0);
  }

  ////////////////////////////////////////////////
  // SOAP UPnP
  ////////////////////////////////////////////////
  
 public:
  void setContent(uXML::Node *node);
};

}

#endif
