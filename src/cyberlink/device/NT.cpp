/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <device/NT.h>
#include <util/StringUtil.h>

bool CyberLink::NT::IsRootDevice(const std::string &ntValue) {
  CyberLink::String ntStr = ntValue;
  return ntStr.startsWith(ROOTDEVICE);
}
