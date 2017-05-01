/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPNOTIFYSOCKETLIST_H_
#define _MUPMPCC_SSDPNOTIFYSOCKETLIST_H_

#include <util/Vector.h>
#include <ssdp/SSDPNotifySocket.h>

namespace CyberLink {
class ControlPoint;

class SSDPNotifySocketList : public Vector<SSDPNotifySocket>  {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  SSDPNotifySocketList();
  ~SSDPNotifySocketList();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
 public:
  SSDPNotifySocket *getSSDPNotifySocket(size_t n) {
    return get(n);
  }

  ////////////////////////////////////////////////
  // ControlPoint
  ////////////////////////////////////////////////

 public:
  void setControlPoint(ControlPoint *ctrlPoint);

  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////
  
 public:
  bool open();
  bool close();
  
  ////////////////////////////////////////////////
  // start/stop
  ////////////////////////////////////////////////
  
 public:
  bool start();
  bool stop();
};

}

#endif


