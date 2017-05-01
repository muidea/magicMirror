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
#include <util/TimeUtil.h>

#include "TestDevice.h"
#include "TestCtrlPoint.h"
#include "UPnPDeviceTests.h"

using namespace CyberLink;
using namespace std;

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

void CyberLinkTest::TestDeviceTests() {
  /////////////////////////////
  // Init Device
  /////////////////////////////

  TestDevice *testDev = new TestDevice();
  testDev->start();

  /////////////////////////////
  // VariableTest
  /////////////////////////////
    
  StateVariable *statVal = testDev->getStateVariable("Count");
  statVal->setValue(10);
  statVal->setValue("");
  statVal->setValue(10);

  /////////////////////////////
  // Init ControlPoint
  /////////////////////////////

  TestCtrlPoint *ctrlp = new TestCtrlPoint();
  ctrlp->start();
  ctrlp->search();

  /////////////////////////////
  // Search Device
  /////////////////////////////
  
  cyber_shared_ptr<Device> ctrlpDev;
  
  while (!ctrlpDev) {
    ctrlp->search();
    Wait((SSDP::DEFAULT_MSEARCH_MX * 1000));
    testDev->announce();
    Wait((SSDP::DEFAULT_MSEARCH_MX * 1000));
    ctrlpDev = ctrlp->getDevice("CyberGarageCountDevice");
  }
      
  /////////////////////////////
  // Action Test
  /////////////////////////////
    
  Action *ctrlpSetCountAction = ctrlpDev->getAction("SetCount");
  ctrlpSetCountAction->setArgumentValue("NewCount", 12);
  ctrlpSetCountAction->postControlAction();
    
  Action *ctrlpGetCountAction = ctrlpDev->getAction("GetCount");
  ctrlpGetCountAction->postControlAction();
  if (ctrlpGetCountAction->getArgumentIntegerValue("CurrentCount") != 12) {
	  std::cout << "getArgumentIntegerValue failed, :" << __LINE__ << std::endl;
  }

  /////////////////////////////
  // Event Test
  /////////////////////////////

  Service *ctrlpCountService = ctrlpDev->getService("urn:schemas-upnp-org:service:count:1");
  ctrlp->subscribe(ctrlpCountService);
  ctrlp->unsubscribe(ctrlpCountService);

  /////////////////////////////
  // Exit
  /////////////////////////////

  ctrlp->stop();
  delete ctrlp;
    
  testDev->stop();
  delete testDev;
}
