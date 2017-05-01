/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <soap/SOAPRequest.h>
#include <util/StringUtil.h>
#include <xml/Parser.h>

using namespace CyberLink;
using namespace uSOAP;
using namespace std;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
SOAPRequest::SOAPRequest() {
  setContentType(uXML::XML::CONTENT_TYPE);
  setMethod(CyberLink::HTTP::POST);
}

SOAPRequest::SOAPRequest(CyberLink::HTTPRequest *httpReq) {
  set(httpReq);
}

SOAPRequest::~SOAPRequest() {
}

////////////////////////////////////////////////
// SOAPACTION
////////////////////////////////////////////////

bool SOAPRequest::isSOAPAction(const std::string &value) {
  const char *headerValue = getHeaderValue(SOAPACTION);
  if (!headerValue)
    return false;
  if (CyberLink::StringEquals(headerValue, value) == true)
    return true;
  std::string buf;
  const char *soapAction = getSOAPAction(buf);
  if (!soapAction)
    return false;
  return CyberLink::StringEquals(soapAction, value);
}

////////////////////////////////////////////////
// parseMessage
////////////////////////////////////////////////

cyber_shared_ptr<uXML::Node> SOAPRequest::parseMessage(const std::string &content, size_t contentLen) {
  if (contentLen <= 0)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);

  uXML::Parser xmlParser;
  return xmlParser.parse(content, contentLen);
}

////////////////////////////////////////////////
// Node
////////////////////////////////////////////////

cyber_shared_ptr<uXML::Node> SOAPRequest::getRootNode() {
  if (rootNode)
    return rootNode;
      
  const char *content = getContent();
  size_t contentLen = getContentLength();

  rootNode = parseMessage(content, contentLen);

  return rootNode;
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

SOAPResponse *SOAPRequest::postMessage(const std::string &host, int port, SOAPResponse *soapRes) {
  post(host, port, soapRes);

  const char *content = soapRes->getContent();
  size_t contentLen = soapRes->getContentLength();
  if (contentLen <= 0)
    return soapRes;

  cyber_shared_ptr<uXML::Node> retNode = parseMessage(content, contentLen);
  soapRes->setEnvelopeNode(retNode);

  return soapRes;
}

////////////////////////////////////////////////
// setContent
////////////////////////////////////////////////

void SOAPRequest::setContent(uXML::Node *node) {
  string nodeBuf;
  node->toString(nodeBuf);
  string buf;
  buf.append(uSOAP::SOAP::VERSION_HEADER);
  buf.append("\n");
  buf.append(nodeBuf);
  HTTPRequest::setContent(buf.c_str());
}
