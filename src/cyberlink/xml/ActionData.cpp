/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <control/ControlResponse.h>
#include <xml/ActionData.h>

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

CyberLink::ActionData::ActionData()  {
  setActionListener(NULL);
  ctrlRes = NULL;
}

CyberLink::ActionData::~ActionData()  {
  if (ctrlRes)
    delete ctrlRes;
}

////////////////////////////////////////////////
// ControlResponse
////////////////////////////////////////////////

void CyberLink::ActionData::setControlResponse(ControlResponse *res)  {
  if (ctrlRes)
    delete ctrlRes;
  ctrlRes = res;
}
