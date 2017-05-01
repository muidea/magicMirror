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
#include "ParameterTests.h"


using namespace CyberLink;

bool CyberLinkTest::TestParameter()
{
  size_t TEST_PARAM_LOOP_COUNT = 10;
  
  ParameterList paramList;
  
  if (paramList.size() != 0) {
	  std::cout << "paramList.size() failed, :" << __LINE__ << std::endl;
  }
  
  for (size_t n=0; n<TEST_PARAM_LOOP_COUNT; n++) {
	if (paramList.size() != n) {
		std::cout << "paramList.size() failed, :" << __LINE__ << std::endl;
	}
    
    char paramName[32], paramValue[32];
    snprintf(paramName, sizeof(paramName), "param%d", (int)n);
    snprintf(paramValue, sizeof(paramValue), "value%d", (int)n);

    cyber_shared_ptr<Parameter> param(new Parameter(paramName, paramValue));
    paramList.add(param);
	if (paramList.size() != (n + 1)) {
		std::cout << "paramList.size() failed, :" << __LINE__ << std::endl;
	}
    
    std::string storedParamValue;
	if (!paramList.getParameterValue(paramName, &storedParamValue)) {
		std::cout << "getParameterValue failed, :" << __LINE__ << std::endl;
	}
	if (storedParamValue.compare(paramValue) != 0) {
		std::cout << "getParameterValue failed, :" << __LINE__ << std::endl;
	}
  }

  return true;
}
