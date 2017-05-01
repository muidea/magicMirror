/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROLREQUEST_H_
#define _MUPMPCC_CONTROLREQUEST_H_

#include <soap/SOAPRequest.h>
#include <control/Control.h>

#include <sstream>

namespace CyberLink {
class Service;

class ControlRequest : public uSOAP::SOAPRequest {
public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ControlRequest() {
  }

  ControlRequest(CyberLink::HTTPRequest *httpReq) : uSOAP::SOAPRequest(httpReq) {
  }

  ////////////////////////////////////////////////
  // Query
  ////////////////////////////////////////////////

  bool isQueryControl() {
    return isSOAPAction(Control::QUERY_SOAPACTION);
  }
  
  bool isActionControl() {
    return !isQueryControl();
  }

  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

protected:
  
  void setRequestHost(Service *service);

};

}

#endif


