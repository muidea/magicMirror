/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <control/QueryResponse.h>
#include <xml/StateVariableData.h>

using namespace CyberLink;

////////////////////////////////////////////////
// value
////////////////////////////////////////////////

StateVariableData::StateVariableData()  {
  queryRes = NULL;
}

StateVariableData::~StateVariableData() {
  if (queryRes)
    delete queryRes;
}

////////////////////////////////////////////////
// QueryResponse
////////////////////////////////////////////////

void StateVariableData::setQueryResponse(QueryResponse *res)  {
  if (queryRes)
    delete queryRes;
  queryRes = res;
}


