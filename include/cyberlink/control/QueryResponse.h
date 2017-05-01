/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_QUERYRESPONSE_H_
#define _MUPMPCC_QUERYRESPONSE_H_

#include <control/ControlResponse.h>
#include <soap/SOAP.h>

#include <sstream>

namespace CyberLink {
class StateVariable;

class QueryResponse : public ControlResponse {
public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  QueryResponse() {
  }

  QueryResponse(SOAPResponse *soapRes) {
    set(soapRes);
  }

  ////////////////////////////////////////////////
  // Qyery
  ////////////////////////////////////////////////

private:

  cyber_shared_ptr<uXML::Node> getReturnNode();
  
 public:
  const char *getReturnValue();

  ////////////////////////////////////////////////
  // Response
  ////////////////////////////////////////////////

 public:
  void setResponse(StateVariable *stateVar);

private:

  uXML::Node *createResponseNode(const std::string &value);
};

}

#endif
