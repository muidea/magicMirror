/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/


#ifndef _MUPMPCC_ACTONDATA_H_
#define _MUPMPCC_ACTONDATA_H_

#include <string>
#include <xml/NodeData.h>

namespace CyberLink {

class ActionListener;
class ControlResponse;

class ActionData : public uXML::NodeData {
  ActionListener *actionListener;
  ControlResponse *ctrlRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  ActionData();

  ~ActionData();

  ////////////////////////////////////////////////
  // ActionListener
  ////////////////////////////////////////////////

 public:
  ActionListener *getActionListener() 
  {
    return actionListener;
  }

  void setActionListener(ActionListener *listener) 
  {
    actionListener = listener;
  }

  ////////////////////////////////////////////////
  // ControlResponse
  ////////////////////////////////////////////////

 public:
  ControlResponse *getControlResponse() 
  {
    return ctrlRes;
  }

  void setControlResponse(ControlResponse *res);
};

}

#endif


