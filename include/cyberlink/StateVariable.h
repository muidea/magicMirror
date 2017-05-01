/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_STATEVARIABLE_H_
#define _MUPMPCC_STATEVARIABLE_H_

#include <net/HostInterface.h>
#include <util/StringUtil.h>
#include <xml/Node.h>
#include <UPnPStatus.h>
#include <AllowedValueList.h>
#include <AllowedValueRange.h>
#include <xml/ServiceData.h>
#include <xml/StateVariableData.h>
#include <control/QueryResponse.h>
#include <control/QueryRequest.h>

#include <sstream>

namespace CyberLink {
class Service;

class StateVariable {
  cyber_shared_ptr<uXML::Node> stateVariableNode;
  cyber_shared_ptr<uXML::Node> serviceNode;
  
  UPnPStatus upnpStatus;
  
  AllowedValueList allowedValueList;
  AllowedValueRange allowedValueRange;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
 public:
  static const char *ELEM_NAME;
  static const char *NAME;
  static const char *DATATYPE;
  static const char *SENDEVENTS;
  static const char *SENDEVENTS_YES;
  static const char *SENDEVENTS_NO;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

 public:
  cyber_shared_ptr<uXML::Node> getServiceNode() {
    return serviceNode;
  }

  Service *getService();

  cyber_shared_ptr<uXML::Node> getStateVariableNode() {
    return stateVariableNode;
  }
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  StateVariable();
  StateVariable(cyber_shared_ptr<uXML::Node> serviceNode, cyber_shared_ptr<uXML::Node> stateVarNode);

  ~StateVariable();

  ////////////////////////////////////////////////
  // isStateVariableNode
  ////////////////////////////////////////////////

 public:
  static bool isStateVariableNode(cyber_shared_ptr<uXML::Node> node) {
    return node->isName(ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // AllowedValueList
  ////////////////////////////////////////////////

private:

  void initAllowedValueList();

 public:
  AllowedValueList *getAllowedValueList() {
    return &allowedValueList;
  }

  bool hasAllowedValueList() {
    return (0 < allowedValueList.size()) ? true : false;
  }

  ////////////////////////////////////////////////
  // AllowedValueRange
  ////////////////////////////////////////////////

private:

  void initAllowedValueRange();

 public:
  AllowedValueRange *getAllowedValueRange() {
    if (!allowedValueRange.getAllowedValueRangeNode())
        return nullptr;
    return &allowedValueRange;
  }

  bool hasAllowedValueRange() {
    return (getAllowedValueRange()) ? true : false;
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

 public:
  void setName(const std::string &value) {
    getStateVariableNode()->setNode(NAME, value);
  }

  const char *getName() {
    return getStateVariableNode()->getNodeValue(NAME);
  }

  ////////////////////////////////////////////////
  // dataType
  ////////////////////////////////////////////////

 public:
  void setDataType(const std::string &value) {
    getStateVariableNode()->setNode(DATATYPE, value);
  }

  const char *getDataType() {
    return getStateVariableNode()->getNodeValue(DATATYPE);
  }

  ////////////////////////////////////////////////
  // dataType
  ////////////////////////////////////////////////

 public:
  void setSendEvents(bool state) {
    getStateVariableNode()->setAttribute(SENDEVENTS, (state == true) ? SENDEVENTS_YES : SENDEVENTS_NO);
  }
  
  bool isSendEvents() {
    const char *state = getStateVariableNode()->getAttributeValue(SENDEVENTS);
    if (!state)
      return false;
    CyberLink::String stateStr(state);
    if (stateStr.equalsIgnoreCase(SENDEVENTS_YES) == true)
      return true;
    return false;
  }
  
  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

 public:
  StateVariableData *getStateVariableData ();

  ////////////////////////////////////////////////
  // Value
  ////////////////////////////////////////////////

 public:
  void setValue(const std::string &value);
  void setValue(int value);
  void setValue(long value);

  const char *getValue() 
  {
    return getStateVariableData()->getValue();
  }

  ////////////////////////////////////////////////
  // set
  ////////////////////////////////////////////////

 public:
  void set(StateVariable *stateVar);

  ////////////////////////////////////////////////
  // queryAction
  ////////////////////////////////////////////////

 public:
  QueryListener *getQueryListener() 
  {
    return getStateVariableData()->getQueryListener();
  }

  void setQueryListener(QueryListener *listener) 
  {
    getStateVariableData()->setQueryListener(listener);
  }

  bool performQueryListener(QueryRequest *queryReq);

  ////////////////////////////////////////////////
  // ActionControl
  ////////////////////////////////////////////////

 public:
  QueryResponse *getQueryResponse() 
  {
    return getStateVariableData()->getQueryResponse();
  }

  void setQueryResponse(QueryResponse *res) 
  {
    getStateVariableData()->setQueryResponse(res);
  }

  UPnPStatus *getQueryStatus() {
    return getQueryResponse()->getUPnPError();
  }
  
  ////////////////////////////////////////////////
  // ActionControl
  ////////////////////////////////////////////////

 public:
  bool postQuerylAction();

  ////////////////////////////////////////////////
  // UPnPStatus
  ////////////////////////////////////////////////

 public:
  void setStatus(int code, const std::string &descr) {
    upnpStatus.setCode(code);
    upnpStatus.setDescription(descr);
  }

  void setStatus(int code) {
    setStatus(code, UPnP::StatusCodeToString(code));
  }
  
  UPnPStatus *getStatus() {
    return &upnpStatus;
  }

};

}

#endif
