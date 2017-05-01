/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <xml/NodeList.h>
#include <xml/Node.h>

using namespace uXML;

////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

cyber_shared_ptr<uXML::Node> NodeList::getNode(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    cyber_shared_ptr<uXML::Node> node = getNode(n);
    const char *nodeName = node->getName();
    if (CyberLink::StringEquals(name, nodeName) == true)
      return node;
  }
  return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
}

cyber_shared_ptr<uXML::Node> NodeList::getEndsWith(const std::string &name)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    cyber_shared_ptr<uXML::Node> node = getNode(n);
    const char *nodeName = node->getName();
    if (!nodeName)
      continue;
    if (CyberLink::StringEndsWith(nodeName, name) == true)
      return node;
  }
  return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
}

cyber_shared_ptr<uXML::Node> NodeList::getNode(const std::string &name, const std::string &value)  {
  size_t nLists = size();
  for (size_t n = 0; n < nLists; n++) {
    cyber_shared_ptr<uXML::Node> node = getNode(n);
    const char *nodeName = node->getName();
    if (CyberLink::StringEquals(name, nodeName) == false)
      continue;
    const char *nodeValue = node->getValue();
    if (CyberLink::StringEquals(value, nodeValue) == true)
      return node;
  }
  return cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
}
