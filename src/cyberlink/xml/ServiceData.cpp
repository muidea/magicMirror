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
#include <xml/ServiceData.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ServiceData::ServiceData()  {
  service = nullptr;
  scpdNode = cyber_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
}
