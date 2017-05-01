/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <Service.h>
#include <Argument.h>
#include <util/StringUtil.h>

using namespace std;
using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *Argument::ELEM_NAME = "argument";

const char *Argument::IN_DIR = "in";
const char *Argument::OUT_DIR = "out";
const char *Argument::NAME = "name";
const char *Argument::DIRECTION = "direction";
const char *Argument::RELATED_STATE_VARIABLE = "relatedStateVariable";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Argument::Argument() {
  argumentNode = cyber_shared_ptr<uXML::Node>(new uXML::Node());
  serviceNode = cyber_shared_ptr<uXML::Node>(new uXML::Node());
}
  
Argument::Argument(cyber_shared_ptr<uXML::Node> servNode, cyber_shared_ptr<uXML::Node> argNode) {
  argumentNode = argNode;
  serviceNode = servNode;
}

Argument::Argument(const std::string &name, const std::string &value) {
  argumentNode = cyber_shared_ptr<uXML::Node>(new uXML::Node());
  serviceNode = cyber_shared_ptr<uXML::Node>(new uXML::Node());
  setName(name);
  setValue(value);
}

Argument::~Argument() {
}

////////////////////////////////////////////////
// setValue
////////////////////////////////////////////////

void Argument::setValue(int value) {
  string valueStr;
  Integer2String(value, valueStr);
  setValue(valueStr.c_str());
}

////////////////////////////////////////////////
// getService
////////////////////////////////////////////////

Service *Argument::getService() {
  cyber_shared_ptr<uXML::Node> node = getServiceNode();
  ServiceData *data = dynamic_cast<ServiceData *>(node->getUserData());
  if (!data)
    return nullptr;
  return data->getService();
}

////////////////////////////////////////////////
// relatedStateVariable
////////////////////////////////////////////////

StateVariable *Argument::getRelatedStateVariable() {
  Service *service = getService();
  if (!service)
    return nullptr;
  const char *relatedStatVarName = getRelatedStateVariableName();
  return service->getStateVariable(relatedStatVarName);
}

