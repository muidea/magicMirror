/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <vector>

#include <HTTP.h>
#include "NetworkInterfaceTests.h"

using namespace std;
using namespace CyberLink;

bool CyberLinkTest::TestNetworkInterface()
{
  NetworkInterfaceList ifList;
  GetHostAddresses(ifList);
  
  size_t ifCnt = ifList.size();
  if (0 >= ifCnt) {
	  std::cout << "GetHostAddresses failed, :" << __LINE__ << std::endl;
  }
  return true;
}
