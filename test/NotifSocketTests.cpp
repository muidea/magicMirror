/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include <mUPnP.h>
#include "NotifSocketTests.h"

using namespace CyberLink;
using namespace std;

bool CyberLinkTest::TestNotifSocket()
{
  NetworkInterfaceList netIfList;
  GetHostAddresses(netIfList);
  if (0 >= netIfList.size()) {
	  std::cout << "GetHostAddresses failed, :" << __LINE__ << std::endl;
  }
  
  NetworkInterface *netIf = netIfList.getNetworkInterface(0);
  string ifAddr = netIf->getAddress();

  for (int n=0; n<10; n++) {
    SSDPNotifySocket ssdpSock;
    SSDPNotifyRequest ssdpReq;
    ssdpReq.setNTS(NTS::ALIVE);
	if (!ssdpSock.post(&ssdpReq, ifAddr)) {
		std::cout << "ssdpSock.post failed, :" << __LINE__ << std::endl;
	}
  }

  return true;
}
