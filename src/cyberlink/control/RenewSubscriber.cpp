/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: RenewSubscriber.cpp
*
*  Revision:
*
*  07/07/04
*    - first revision
*
******************************************************************/

#include <ControlPoint.h>
#include <util/TimeUtil.h>

using namespace CyberLink;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const long RenewSubscriber::INTERVAL= 120;

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////
  
void RenewSubscriber::run()  {
  ControlPoint *ctrlPoint = getControlPoint();
  long renewInterval = RenewSubscriber::INTERVAL * 1000;
  while (isRunnable() == true) {
    Wait(renewInterval);
    if (!ctrlPoint)
      break;
    ctrlPoint->renewSubscriberService();
  }
}

