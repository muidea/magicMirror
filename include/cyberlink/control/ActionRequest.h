/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ACTIONREQUEST_H_
#define _MUPMPCC_ACTIONREQUEST_H_

#include <control/ControlRequest.h>
#include <control/ActionResponse.h>
#include <ArgumentList.h>
#include <soap/SOAP.h>

#include <sstream>

namespace CyberLink {
class Action;

class ActionRequest : public ControlRequest {
  ArgumentList argumentList;
  ActionResponse actionRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  ActionRequest() {
  }

  ActionRequest(CyberLink::HTTPRequest *httpReq) : ControlRequest(httpReq) {
    initArgumentList();
  }

  ////////////////////////////////////////////////
  // Action
  ////////////////////////////////////////////////

 public:
  cyber_shared_ptr<uXML::Node> getActionNode();

  const char *getActionName(std::string &buf);

private:

  void initArgumentList();

 public:
  ArgumentList *getArgumentList() {
    return &argumentList;
  }

  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

 public:
  void setRequest(Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  // Contents
  ////////////////////////////////////////////////

private:

  uXML::Node *createContentNode(Service *service, Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

 public:
  ActionResponse *post(ActionResponse *actionRes);

  ActionResponse *post() {
    return post(&actionRes);
  }

};

}

#endif
