/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ALLOWEDVALUE_H_
#define _MUPMPCC_ALLOWEDVALUE_H_

#include <xml/Node.h>

namespace CyberLink{
class AllowedValue {
  cyber_shared_ptr<uXML::Node> allowedValueNode;
  
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

 public:
  void setAllowedValueNode(cyber_shared_ptr<uXML::Node> node) {
    allowedValueNode = node;
  }

  cyber_shared_ptr<uXML::Node> getAllowedValueNode() {
    return allowedValueNode;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

public:
  
  AllowedValue() {
    setAllowedValueNode(cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr));
  }

  AllowedValue(cyber_shared_ptr<uXML::Node> node) {
    setAllowedValueNode(node);
  }

  ////////////////////////////////////////////////
  // isAllowedValueNode
  ////////////////////////////////////////////////

 public:
  static bool isAllowedValueNode(cyber_shared_ptr<uXML::Node> node) {
    return node->isName(AllowedValue::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // minimum
  ////////////////////////////////////////////////

 public:
  void setValue(const std::string &value) {
    getAllowedValueNode()->setValue(value);
  }

  const char *getValue() {
    return getAllowedValueNode()->getValue();
  }
  
};

}

#endif

