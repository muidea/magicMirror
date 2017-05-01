/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <limits.h>

#include <mUPnP.h>
#include "UPnPMiscTests.h"

using namespace CyberLink;
using namespace std;

void CyberLinkTest::TestSSDPRequest()
{
  // SSDPRequest::setLeaseTime
  SSDPRequest *ssdpReq = new SSDPRequest();
  ssdpReq->setLeaseTime(300);
  if (ssdpReq->getLeaseTime() != 300) {
	  std::cout << "getLeaseTime failed, :" << __LINE__ << std::endl;
  }
  delete ssdpReq;
}

void CyberLinkTest::TestST()
{
	if (!ST::IsAllDevice("ssdp:all")) {
		std::cout << "IsAllDevice failed, :" << __LINE__ << std::endl;
  }
	if (!ST::IsRootDevice("upnp:rootdevice")) {
		std::cout << "IsRootDevice failed, :" << __LINE__ << std::endl;
  }
	if (!ST::IsUUIDDevice("uuid:fdfasdfaf")) {
		std::cout << "IsUUIDDevice failed, :" << __LINE__ << std::endl;
  }
	if (!ST::IsURNDevice("urn:schemas-upnp-org:device:clock:1")) {
		std::cout << "IsURNDevice failed, :" << __LINE__ << std::endl;
  }
	if (!ST::IsURNService("urn:schemas-upnp-org:service:timer:1")) {
		std::cout << "IsURNService failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestSSDP()
{
  const char *UPNP_TEST_MAXAGE_STR = "max-age=60";
  const int UPNP_TEST_MAXAGE = 60;
    
  int mx = SSDP::GetLeaseTime(UPNP_TEST_MAXAGE_STR);
  if (UPNP_TEST_MAXAGE != mx) {
	  std::cout << "GetLeaseTime failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestBootID()
{
  int bootId = UPnP::CreateBootID();
  if (0 >= bootId) {
	  std::cout << "CreateBootID failed, :" << __LINE__ << std::endl;
  }
  if (bootId >= INT_MAX) {
	  std::cout << "CreateBootID failed, :" << __LINE__ << std::endl;
  }
}

