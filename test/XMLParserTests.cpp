/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include <UPnP.h>
#include <xml/Parser.h>

#include <iostream>
#include "XMLParserTests.h"
using namespace CyberLink;
using namespace std;

const std::string XML_TEST_SAMPLE_01 =
"<?xml version=\"1.0\" ?> \n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
"   <specVersion> \n"
"     <major>1</major>\n"
"     <minor>0</minor>\n"
"   </specVersion> \n"
"</root> \n";

void CyberLinkTest::TestXMLParser()
{
  uXML::Parser xmlParser;
    
  cyber_shared_ptr<uXML::Node> rootNode = xmlParser.parse(XML_TEST_SAMPLE_01);
  uXML::Attribute *rootAttr = rootNode->getAttribute("xmlns");
  string rootAttrValue = rootAttr->getValue();
  if (rootAttrValue.compare("urn:schemas-upnp-org:device-1-0") != 0) {
	  std::cout << "rootAttr->getValue() failed, :" << __LINE__ << std::endl;
  }
    
  cyber_shared_ptr<uXML::Node> specNode = rootNode->getNode("specVersion");    
  cyber_shared_ptr<uXML::Node> majorNode = specNode->getNode("major");
  string majorValue = majorNode->getValue();
  if (majorValue.compare("1") != 0) {
	  std::cout << "rootAttr->getValue() failed, :" << __LINE__ << std::endl;
  }
    
  cyber_shared_ptr<uXML::Node> minorNode = specNode->getNode("minor");
  string minorValue = minorNode->getValue();
  if (minorValue.compare("0") != 0) {
	  std::cout << "rootAttr->getValue() failed, :" << __LINE__ << std::endl;
  }
}
