/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <device/NTS.h>
#include <util/StringUtil.h>
  
bool CyberLink::NTS::IsAlive(const std::string &ntsValue) {
  CyberLink::String ntsStr = ntsValue;
  return ntsStr.startsWith(ALIVE);
}

bool CyberLink::NTS::IsByeBye(const std::string &ntsValue) {
  CyberLink::String ntsStr = ntsValue;
  return ntsStr.startsWith(BYEBYE);
}

