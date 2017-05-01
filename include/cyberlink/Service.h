/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SERVICE_H_
#define _MUPMPCC_SERVICE_H_

#include <net/HostInterface.h>
#include <io/File.h>
#include <net/URL.h>

#include <xml/DeviceData.h>
#include <ActionList.h>
#include <StateVariable.h>
#include <ServiceStateTable.h>
#include <xml/ServiceData.h>
#include <event/NotifyRequest.h>
#include <event/SubscriberList.h>
#include <control/QueryRequest.h>
#include <control/ActionListener.h>
#include <util/Mutex.h>
#include <util/Vector.h>
#include <util/StringUtil.h>
#include <xml/Node.h>

namespace CyberLink {
class Device;

class Service {
  cyber_shared_ptr<uXML::Node> serviceNode;
  
  ActionList actionList;
  ServiceStateTable serviceStateTable;

  CyberLink::Mutex mutex;

public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;
  static const char *SERVICE_TYPE;
  static const char *SERVICE_ID;
  static const char *SCPDURL;
  static const char *CONTROL_URL;
  static const char *EVENT_SUB_URL;

 public:
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  cyber_shared_ptr<uXML::Node> getServiceNode() {
    return serviceNode;
  }

  bool hasServiceNode() {
    return (serviceNode) ? true : false;
  }
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  Service(cyber_shared_ptr<uXML::Node> node);

  ~Service();

private:

  void initServiceData() {
    ServiceData *data = getServiceData();
    if (data)
      data->setService(this);
  }

  ////////////////////////////////////////////////
  // Mutex
  ////////////////////////////////////////////////
  
 public:
  void lock() {
    mutex.lock();
  }
  
  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // isServiceNode
  ////////////////////////////////////////////////

 public:
  static bool isServiceNode(cyber_shared_ptr<uXML::Node> node) {
    if (!node)
      return false;
    return node->isName(Service::ELEM_NAME);
  }
  
  ////////////////////////////////////////////////
  // Device/Root Node
  ////////////////////////////////////////////////

private:

	cyber_shared_ptr<uXML::Node> getDeviceNode() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return nullptr;
	cyber_shared_ptr<uXML::Node> parentNode = serviceNode->getParentNode();
    if (!parentNode)
      return nullptr;
    return parentNode->getParentNode();
  }

	cyber_shared_ptr<uXML::Node> getRootNode() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return nullptr;
    return serviceNode->getRootNode();
  }

  ////////////////////////////////////////////////
  // Device
  ////////////////////////////////////////////////

 public:
  
  Device *getDevice() {
	  cyber_shared_ptr<uXML::Node> node = getDeviceNode();
    if (!node)
      return nullptr;
    DeviceData *data = dynamic_cast<DeviceData *>(node->getUserData());
    if (!data)
      return nullptr;
    return data->getDevice();
  }

  Device *getRootDevice();

  ////////////////////////////////////////////////
  // serviceType
  ////////////////////////////////////////////////

 public:
  void setServiceType(const std::string &value) {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return;
    serviceNode->setNode(SERVICE_TYPE, value);
  }

  const char *getServiceType() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return "";
    return serviceNode->getNodeValue(SERVICE_TYPE);
  }

  ////////////////////////////////////////////////
  // serviceID
  ////////////////////////////////////////////////

 public:
  void setServiceID(const std::string &value) {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return;
    serviceNode->setNode(SERVICE_ID, value);
  }

  const char *getServiceID() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return "";
    return serviceNode->getNodeValue(SERVICE_ID);
  }

  ////////////////////////////////////////////////
  // isURL
  ////////////////////////////////////////////////

private:

  bool isURL(const std::string &referenceUrl, const std::string &url);

  ////////////////////////////////////////////////
  // SCPDURL
  ////////////////////////////////////////////////

 public:
  void setSCPDURL(const std::string &value) {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return;
   serviceNode->setNode(SCPDURL, value);
  }

  const char *getSCPDURL() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return "";
    return serviceNode->getNodeValue(SCPDURL);
  }

  bool isSCPDURL(const std::string &url) {
    return isURL(getSCPDURL(), url);
  }
  
  const char *getSCPDData(std::string &buf);

  ////////////////////////////////////////////////
  // controlURL
  ////////////////////////////////////////////////

 public:
  void setControlURL(const std::string &value) {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return;
    serviceNode->setNode(CONTROL_URL, value);
  }

  const char *getControlURL() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return "";
    return serviceNode->getNodeValue(CONTROL_URL);
  }

  bool isControlURL(const std::string &url) {
    return isURL(getControlURL(), url);
  }

  ////////////////////////////////////////////////
  // eventSubURL
  ////////////////////////////////////////////////

 public:
  void setEventSubURL(const std::string &value) {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return;
    serviceNode->setNode(EVENT_SUB_URL, value);
  }

  const char *getEventSubURL() {
    cyber_shared_ptr<uXML::Node> serviceNode = getServiceNode();
    if (!serviceNode)
      return "";
    return serviceNode->getNodeValue(EVENT_SUB_URL);
  }

  bool isEventSubURL(const std::string &url) {
    return isURL(getEventSubURL(), url);
  }

  ////////////////////////////////////////////////
  // SCPD node
  ////////////////////////////////////////////////

 public:
  bool loadSCPD(const std::string &descString);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  bool loadSCPD(CyberLink::File *file);
#endif

private:
  cyber_shared_ptr<uXML::Node> getSCPDNode(CyberLink::URL *url);
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  cyber_shared_ptr<uXML::Node> getSCPDNode(CyberLink::File *file);
#endif
  cyber_shared_ptr<uXML::Node> getSCPDNode(const std::string &description);
  cyber_shared_ptr<uXML::Node> getSCPDNode();

public:
  ////////////////////////////////////////////////
  // actionList
  ////////////////////////////////////////////////

private:

  void initActionList();

 public:
  ActionList *getActionList() {
    return &actionList;
  }

  Action *getAction(const std::string &actionName);
  
  ////////////////////////////////////////////////
  // serviceStateTable
  ////////////////////////////////////////////////

private:

  void initServiceStateTable();

 public:
  ServiceStateTable *getServiceStateTable() {
    return &serviceStateTable;
  }

  StateVariable *getStateVariable(const std::string &name);
  
  bool hasStateVariable(const std::string &name) {
    return (getStateVariable(name)) ? true : false;
  }

  ////////////////////////////////////////////////
  // isService
  ////////////////////////////////////////////////
  
  bool isService(const std::string &name) {
    CyberLink::String nameStr(name);
    if (nameStr.endsWith(getServiceType()) == true)
      return true;
    if (nameStr.endsWith(getServiceID()) == true)
      return true;
    return false;
  }
   
  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

  ServiceData *getServiceData() {
    cyber_shared_ptr<uXML::Node> node = getServiceNode();
    if (!node)
      return nullptr;
    ServiceData *userData = dynamic_cast<ServiceData *>(node->getUserData());
    if (!userData) {
      userData = new ServiceData();
      node->setUserData(userData);
    }
    return userData;
  }

  ////////////////////////////////////////////////
  // Notify
  ////////////////////////////////////////////////

private:

  const char *getNotifyServiceTypeNT(std::string &buf);
  const char *getNotifyServiceTypeUSN(std::string &buf);

 public:
  bool announce(const std::string &ifAddr);
  bool byebye(const std::string &ifAddr);

  ////////////////////////////////////////////////
  // serviceSearchResponse  
  ////////////////////////////////////////////////

 public:
  bool serviceSearchResponse(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // queryAction
  ////////////////////////////////////////////////

 public:
  void setQueryListener(QueryListener *listener);

  ////////////////////////////////////////////////
  // Subscription
  ////////////////////////////////////////////////

 public:
  SubscriberList *getSubscriberList() 
  {
    return getServiceData()->getSubscriberList();
  }

  void addSubscriber(Subscriber *sub);
  void removeSubscriber(Subscriber *sub);

  Subscriber *getSubscriberBySID(const std::string &name);
  Subscriber *getSubscriberByDeliveryURL(const std::string &name);

private:
  
  bool notify(Subscriber *sub, StateVariable *stateVar);

 public:
  void notify(StateVariable *stateVar);
  void notifyAllStateVariables();
  
  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

  const char *getSID() 
  {
    return getServiceData()->getSID();
  }

  void setSID(const std::string &sid) 
  {
    getServiceData()->setSID(sid);
  }

  void clearSID() {
    setSID("");
    setTimeout(0);
  }
  
  bool hasSID() {
    return CyberLink::StringHasData(getSID());
  }    

  bool isSubscribed() {
    return hasSID();
  }
  
  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

 public:
  long getTimeout() 
  {
    return getServiceData()->getTimeout();
  }

  void setTimeout(long value) 
  {
    getServiceData()->setTimeout(value);
  }

  ////////////////////////////////////////////////
  // AcionListener
  ////////////////////////////////////////////////
  
public:
  
  void setActionListener(ActionListener *listener);

};

}

#endif

