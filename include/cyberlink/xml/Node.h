/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_NODE_H_
#define _MUPMPCC_NODE_H_

#include <iostream>
#include <sstream>
#include <string>

#include <xml/NodeList.h>
#include <xml/NodeData.h>
#include <xml/AttributeList.h>

namespace uXML {

class Node  {
  cyber_shared_ptr<Node> parentNode;

  std::string name;
  std::string value;
  
  AttributeList attrList;
  NodeList nodeList;
  
  NodeData *userData; 
  
public:
  
  Node();

  Node(const std::string &name);

  Node(const std::string &ns, const std::string &name);

  virtual ~Node();

  ////////////////////////////////////////////////
  // parent node
  ////////////////////////////////////////////////

  void setParentNode(cyber_shared_ptr<Node> node)
  {
    this->parentNode = node;
  }

  cyber_shared_ptr<Node> getParentNode()
  {
    return this->parentNode;
  }

  ////////////////////////////////////////////////
  // root node
  ////////////////////////////////////////////////

  cyber_shared_ptr<Node> getRootNode() {
	cyber_shared_ptr<Node> rootNode = NULL;
	cyber_shared_ptr<Node> parentNode = getParentNode();
    while (parentNode) {
       rootNode = parentNode;
       parentNode = rootNode->getParentNode();
    }
    return rootNode;
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

  void setName(const std::string &val) 
  {
    name = val;
  }

  void setName(const std::string &ns, const std::string &val) 
  {
    name = ns;
    name += ":";
    name += val;
  }

  const char *getName() {
    return name.c_str();
  }

  bool isName(const std::string &val) {
    return (name.compare(val) == 0) ? true : false;
  }

  ////////////////////////////////////////////////
  // value (set)
  ////////////////////////////////////////////////

  void setValue(const std::string &val) {
    value = val;
  }

  void setValue(int val);

  const char *getValue() {
    return value.c_str();
  }

  bool isValue(const std::string &val) {
    return (value.compare(val) == 0) ? true : false;
  }

  ////////////////////////////////////////////////
  // value (add)
  ////////////////////////////////////////////////

  void addValue(const std::string &val) {
    value.append(val);
  }

  void addValue(const std::string &val, int len) {
    value.append(val, 0, len);
  }

  ////////////////////////////////////////////////
  // Attribute (Basic)
  ////////////////////////////////////////////////

  int getNAttributes() {
    return (int)attrList.size();
  }

  Attribute *getAttribute(int index) {
    return attrList.getAttribute(index);
  }

  Attribute *getAttribute(const std::string & name) {
    return attrList.getAttribute(name);
  }

  void addAttribute(Attribute *attr) {
    attrList.addAttribute(attr);
  }

  void insertAttributeAt(Attribute *attr, int index) {
    attrList.insertAttribute(attr, index);
  }

  void addAttribute(const std::string & name, const std::string & value) {
    Attribute *attr = new Attribute(name, value);
    addAttribute(attr);
  }

  bool removeAttribute(Attribute *attr) {
    return attrList.removeAttribute(attr);
  }

  bool removeAttribute(const std::string & name) {
    return removeAttribute(getAttribute(name));
  }

  bool hasAttributes() {
    if (0 < getNAttributes())
      return true;
    return false;
  }

  ////////////////////////////////////////////////
  // Attribute (Extention)
  ////////////////////////////////////////////////

 public:
  void setAttribute(const std::string & name, const std::string & value);

  void setAttribute(const std::string &name, int value);

  const char *getAttributeValue(const std::string & name);

  int getAttributeIntegerValue(const std::string &name);

  ////////////////////////////////////////////////
  // Attribute (xmlns)
  ////////////////////////////////////////////////

  void setNameSpace(const std::string & ns, const std::string & val) {
    std::string nspace;
    nspace = "xmlns:";
    nspace += ns;
    setAttribute(nspace.c_str(), val);
  }

  ////////////////////////////////////////////////
  // Child node
  ////////////////////////////////////////////////

  size_t getNNodes() {
    return nodeList.size();
  }

  cyber_shared_ptr<Node> getNode(size_t index) {
    return nodeList.getNode(index);
  }

  cyber_shared_ptr<Node> getNode(const std::string & name) {
    return nodeList.getNode(name);
  }

  cyber_shared_ptr<Node> getNode(const std::string & name, const std::string &value) {
    return nodeList.getNode(name, value);
  }

  cyber_shared_ptr<Node> getNodeEndsWith(const std::string & name) {
    return nodeList.getEndsWith(name);
  }

  bool addNode(cyber_shared_ptr<Node> node) {
	cyber_shared_ptr<Node> ptr(this);
    node->setParentNode(ptr);
    nodeList.addNode(node);
    return true;
  }

  bool insertNode(cyber_shared_ptr<Node> node, size_t index) {
	  cyber_shared_ptr<Node> ptr(this);
	  node->setParentNode(ptr);
    nodeList.insertNode(node, index);
    return true;
  }

  bool removeNode(cyber_shared_ptr<Node> node) {
    node->setParentNode(NULL);
    return nodeList.removeNode(node);
  }

  bool removeNode(const std::string & name) {
    return nodeList.removeNode(getNode(name));
  }

  bool hasNodes() {
    if (0 < getNNodes())
      return true;
    return false;
  }

  void removeAllNodes(void) {
    nodeList.clear();
  }

  ////////////////////////////////////////////////
  // Element (Child Node)
  ////////////////////////////////////////////////

  bool setNode(const std::string & name, const std::string & value) {
    cyber_shared_ptr<Node> node = getNode(name);
    if (node) {
      node->setValue(value);
      return false;
    }

	cyber_shared_ptr<Node> newNode(new Node(name));
    newNode->setValue(value);
    return addNode(newNode);
  }

  const char *getNodeValue(const std::string & name) {
    cyber_shared_ptr<Node> node = getNode(name);
    if (node)
      return node->getValue();
    return "";
  }

  ////////////////////////////////////////////////
  // userData
  ////////////////////////////////////////////////

  void setUserData(NodeData *data);

  NodeData *getUserData() {
    return userData;
  }

  ////////////////////////////////////////////////
  // toString
  ////////////////////////////////////////////////

protected:

  const char *getIndentLevelString(int nIndentLevel, std::string &buf) {
    buf = "";
    for (int n = 0; n < nIndentLevel; n++)
      buf.append("\t");
    return buf.c_str();
  }

 public:
#ifndef NO_USE_OSTRINGSTREAM
  void outputAttributes(std::ostream& ps);
#else
  void outputAttributes(std::string& ps);
#endif

 public:
#ifndef NO_USE_OSTRINGSTREAM
  virtual void output(std::ostream& ps, int indentLevel, bool hasChildNode);
#else
  virtual void output(std::string& ps, int indentLevel, bool hasChildNode);
#endif

  const char *toString(std::string &buf, bool hasChildNode = true);

  void print(bool hasChildNode = true);

};

}

#endif
