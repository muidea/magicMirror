/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <ssdp/SSDPSearchResponseSocket.h>

#include <ControlPoint.h>
#include <Log.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

SSDPSearchResponseSocket::SSDPSearchResponseSocket() {
  setControlPoint(NULL);
}
  
SSDPSearchResponseSocket::~SSDPSearchResponseSocket() {
  stop();
  close();
}

////////////////////////////////////////////////
// run  
////////////////////////////////////////////////

void SSDPSearchResponseSocket::run() {
  while (isRunnable() == true) {
    SSDPPacket ssdpPacket;
    
    if (!receive(&ssdpPacket))
      break;
    
    ControlPoint *ctrlPoint = getControlPoint();
    if (!ctrlPoint)
      break;
    
    std::string ssdpSt, ssdpNTS, ssdpNT, ssdpLocation;
    ssdpPacket.getST(ssdpSt);
    ssdpPacket.getNTS(ssdpNTS);
    ssdpPacket.getNT(ssdpNT);
    ssdpPacket.getLocation(ssdpLocation);
    LogTrace("SSDP Search Response Received : %s %s %s %s", ssdpSt.c_str(), ssdpNTS.c_str(), ssdpNT.c_str(), ssdpLocation.c_str());
    
    ctrlPoint->searchResponseReceived(&ssdpPacket);
  }
}
