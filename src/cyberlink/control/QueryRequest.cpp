/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: QueryRequest.cpp
*
*  Revision;
*
*  08/15/03
*    - first revision
*  09/02/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Error : redundant code, the setRequest method in QueryRequest invokes setURI even if after a couple of rows setRequestHost is invoked
*  04/26/04
*    - Added post(QueryResponse *queryRes);
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <control/QueryRequest.h>
#include <Device.h>
#include <Service.h>
#include <StateVariable.h>

using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////
  
void QueryRequest::setRequest(StateVariable *stateVar) {
  Service *service = stateVar->getService();    
    
  setRequestHost(service);

  setEnvelopeNode(uSOAP::SOAP::CreateEnvelopeBodyNode());
  cyber_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
  cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  uXML::Node *qeuryNode = createContentNode(stateVar);
  cyber_shared_ptr<uXML::Node> newNode(qeuryNode);
  bodyNode->addNode(newNode);
  setContent(envNode.get());

  setSOAPAction(Control::QUERY_SOAPACTION);
}

////////////////////////////////////////////////
// Contents
////////////////////////////////////////////////

uXML::Node *QueryRequest::createContentNode(StateVariable *stateVar) {
  uXML::Node *queryVarNode = new uXML::Node();
  queryVarNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE);
  queryVarNode->setNameSpace(Control::NS, Control::XMLNS);

  uXML::Node *varNode = new uXML::Node();
  varNode->setName(Control::NS, Control::VAR_NAME);
  varNode->setValue(stateVar->getName());
  cyber_shared_ptr<uXML::Node> newNode(varNode);
  queryVarNode->addNode(newNode);

  return queryVarNode;
}

////////////////////////////////////////////////
// getVarName
////////////////////////////////////////////////

cyber_shared_ptr<uXML::Node> QueryRequest::getVarNameNode() {
  cyber_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  if (!bodyNode)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  if (bodyNode->hasNodes() == false)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  cyber_shared_ptr<uXML::Node> queryStateVarNode = bodyNode->getNode(0);
  if (!queryStateVarNode)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  if (queryStateVarNode->hasNodes() == false)
    return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
  return queryStateVarNode->getNode(0);
}
  
const char *QueryRequest::getVarName() {
  cyber_shared_ptr<uXML::Node> node = getVarNameNode();
  if (!node)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

QueryResponse *QueryRequest::post(QueryResponse *queryRes) {
  postMessage(getRequestHost(), getRequestPort(), queryRes);
  return queryRes;
}
