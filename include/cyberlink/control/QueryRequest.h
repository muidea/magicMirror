/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_QUERYREQUEST_H_
#define _MUPMPCC_QUERYREQUEST_H_

#include <control/ControlRequest.h>
#include <control/QueryResponse.h>
#include <soap/SOAP.h>

#include <sstream>

namespace CyberLink {
class Service;
class StateVariable;

class QueryRequest : public ControlRequest {
  QueryResponse queryRes;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  QueryRequest() {
  }

  QueryRequest(CyberLink::HTTPRequest *httpReq) {
    set(httpReq);
  }

  ////////////////////////////////////////////////
  // Qyery
  ////////////////////////////////////////////////

private:

  cyber_shared_ptr<uXML::Node> getVarNameNode();
  
 public:
  const char *getVarName();

  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////
  
  void setRequest(StateVariable *stateVar);

  ////////////////////////////////////////////////
  // Contents
  ////////////////////////////////////////////////

private:

  uXML::Node *createContentNode(StateVariable *stateVar);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

 public:
  QueryResponse *post(QueryResponse *actionRes);

  QueryResponse *post() {
    return post(&queryRes);
  }

};

}

#endif
