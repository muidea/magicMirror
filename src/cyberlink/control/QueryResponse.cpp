/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: QueryResponse.cpp
*
*  Revision;
*
*  08/15/03
*    - first revision
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <control/QueryResponse.h>
#include <StateVariable.h>

using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

void QueryResponse::setResponse(StateVariable *stateVar) {
  setStatusCode(CyberLink::HTTP::OK_REQUEST);
    
  const char *value = stateVar->getValue();
  cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  uXML::Node *resNode = createResponseNode(value);
  cyber_shared_ptr<uXML::Node> newNode(resNode);
  bodyNode->addNode(newNode);
    
  cyber_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
  setContent(envNode.get());
}

////////////////////////////////////////////////
// getReturn
////////////////////////////////////////////////

cyber_shared_ptr<uXML::Node> QueryResponse::getReturnNode() {
  cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  if (!bodyNode)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  if (bodyNode->hasNodes() == false)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  cyber_shared_ptr<uXML::Node> queryResNode = bodyNode->getNode(0);
  if (!queryResNode)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  if (queryResNode->hasNodes() == false)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  return queryResNode->getNode(0);
}
  
const char *QueryResponse::getReturnValue() {
  cyber_shared_ptr<uXML::Node> node = getReturnNode();
  if (!node)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

uXML::Node *QueryResponse::createResponseNode(const std::string &value) {
  uXML::Node *queryResNode = new uXML::Node();
  queryResNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE_RESPONSE);
  queryResNode->setNameSpace(Control::NS, Control::XMLNS);
    
  cyber_shared_ptr<uXML::Node> returnNode(new uXML::Node());
  returnNode->setName(Control::RETURN);
  returnNode->setValue(value);
  queryResNode->addNode(returnNode);
    
  return queryResNode;
}
