/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <device/USN.h>
#include <util/StringUtil.h>

bool CyberLink::USN::IsRootDevice(const std::string &usnValue) {
  CyberLink::String usnStr = usnValue;
  return usnStr.endsWith(ROOTDEVICE);
}
  
const char *CyberLink::USN::GetUDN(const std::string &usnValue, std::string &udn) {
  CyberLink::String usnStr = usnValue;
  int idx = usnStr.indexOf("::");
  if (idx < 0)
    return usnStr.trim();
  CyberLink::String udnStr(usnStr.getValue(), 0, idx);
  udn = udnStr.trim();
  return udn.c_str();
}
