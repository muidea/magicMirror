/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <device/MAN.h>
#include <util/StringUtil.h>

using namespace std;
using namespace CyberLink;

bool CyberLink::MAN::IsDiscover(const std::string &value) {
  CyberLink::String manStr = value;
  if (manStr.equals(DISCOVER) == true)
    return true;
  string quoteDiscoverStr;
  quoteDiscoverStr.append("\"");
  quoteDiscoverStr.append(DISCOVER);
  quoteDiscoverStr.append("\"");
  return manStr.equals(quoteDiscoverStr.c_str());
}
