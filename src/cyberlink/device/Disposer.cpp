/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <ControlPoint.h>
#include <device/Disposer.h>
#include <util/TimeUtil.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////
  
void Disposer::run()  {
  ControlPoint *ctrlPoint = getControlPoint();
  long monitorInterval = ctrlPoint->getExpiredDeviceMonitoringInterval() * 1000;
  
  while (isRunnable() == true) {
    CyberLink::Wait(monitorInterval);
    ControlPoint *ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      break;
    ctrlPoint->removeExpiredDevices();
  }
}

