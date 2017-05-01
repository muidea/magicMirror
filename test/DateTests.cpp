/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <vector>

#include <HTTP.h>
#include "DateTests.h"

using namespace CyberLink;


bool CyberLinkTest::TestDate()
{
  HTTPDate httpDate(1118220696);
  const char *dateStr = httpDate.getDateString();
  return strcmp(dateStr, "Wed, 08 Jun 2005 08:51:36 GMT") == 0;
}

