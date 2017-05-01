/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_RENEWSUBSCRIBER_H_
#define _MUPMPCC_RENEWSUBSCRIBER_H_

#include <util/Thread.h>

namespace CyberLink {
class ControlPoint;

class RenewSubscriber : public CyberLink::Thread {
 public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const long INTERVAL;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  RenewSubscriber(ControlPoint *ctrlp) {
    setControlPoint(ctrlp);
  }
  
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

private:
  
  ControlPoint *controlPoint;

 public:
  void setControlPoint(ControlPoint *ctrlp) {
    controlPoint = ctrlp;
  }
  
  ControlPoint *getControlPoint() {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  // Thread
  ////////////////////////////////////////////////
  
 public:
  void run();

};

}

#endif

