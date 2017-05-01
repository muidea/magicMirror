/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NODELIST_H_
#define _MUPMPCC_NODELIST_H_

#include <util/Vector.h>
#include <util/StringUtil.h>

namespace uXML {

class Node;

class NodeList : public CyberLink::SharedVector<Node> {
public:
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  NodeList() {
  }
  
public:
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  bool addNode(cyber_shared_ptr<Node> node) {
    return add(node);
  }
  
  bool removeNode(cyber_shared_ptr<Node> node) {
    return remove(node);
  }
  
  bool insertNode(cyber_shared_ptr<Node> node, size_t index) {
    return insertAt(node, index);
  }
  
  cyber_shared_ptr<Node> getNode(size_t n) {
    return get(n);
  }
  
  cyber_shared_ptr<Node> getNode(const std::string &name);
  cyber_shared_ptr<Node> getEndsWith(const std::string &name);
  cyber_shared_ptr<Node> getNode(const std::string &name, const std::string &value);
};

}

#endif
