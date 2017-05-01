/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROLPOINT_H_
#define _MUPMPCC_CONTROLPOINT_H_

#include <net/HostInterface.h>
#include <util/Listener.h>
#include <util/Mutex.h>
#include <http/HTTPRequestListener.h>
#include <http/HTTPServerList.h>
#include <xml/NodeList.h>
#include <ssdp/SSDPPacket.h>
#include <ssdp/SSDPNotifySocketList.h>
#include <ssdp/SSDPSearchResponseSocketList.h>
#include <device/SearchResponseListener.h>
#include <device/NotifyListener.h>
#include <device/Disposer.h>
#include <device/DeviceChangeListener.h>
#include <event/EventListener.h>
#include <control/RenewSubscriber.h>

namespace CyberLink {
  
typedef CyberLink::ListenerList<NotifyListener>         NotifyListenerList;
typedef CyberLink::ListenerList<SearchResponseListener> SearchResponseListenerList;
typedef CyberLink::ListenerList<DeviceChangeListener>   DeviceChangeListenerList;
typedef CyberLink::ListenerList<EventListener>   EventListenerList;
  
class ControlPoint : public CyberLink::HTTPRequestListener {
  SSDPNotifySocketList ssdpNotifySocketList;
  SSDPSearchResponseSocketList ssdpSearchResponseSocketList;

  int ssdpPort;
  int httpPort;
  size_t httpWorkerCount;
  
  uXML::NodeList  devNodeList;
  uXML::NodeList  removedDevNodeList;

  NotifyListenerList deviceNotifyListenerList;
  SearchResponseListenerList deviceSearchResponseListenerList;
  DeviceChangeListenerList deviceChangeListenerList;

  CyberLink::Mutex mutex;
  DeviceList deviceList;

  int searchMx;

  CyberLink::HTTPServerList httpServerList;
  EventListenerList eventListenerList;

  std::string eventSubURI;

  Disposer *deviceDisposer;
  long expiredDeviceMonitoringInterval;

  bool nmprMode;
  RenewSubscriber *renewSubscriber;

 public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const int DEFAULT_EVENTSUB_PORT;
  static const int DEFAULT_EVENTSUB_WORKER_COUNT;
  static const int DEFAULT_SSDP_PORT;
  static const char *DEFAULT_EVENTSUB_URI;
  static const int DEFAULT_EXPIRED_DEVICE_MONITORING_INTERVAL;

private:

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  SSDPNotifySocketList *getSSDPNotifySocketList() {
    return &ssdpNotifySocketList;
  }
  
  SSDPSearchResponseSocketList *getSSDPSearchResponseSocketList() {
    return &ssdpSearchResponseSocketList;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  ControlPoint(int ssdpPort = DEFAULT_SSDP_PORT, int httpPort = DEFAULT_EVENTSUB_PORT);
  virtual ~ControlPoint();

  ////////////////////////////////////////////////
  // Port (SSDP)
  ////////////////////////////////////////////////

 public:
  int getSSDPPort() {
    return ssdpPort;
  }

  void setSSDPPort(int port) {
    ssdpPort = port;
  }

  ////////////////////////////////////////////////
  // HTTP (EventSub)
  ////////////////////////////////////////////////

 public:
  int getHTTPPort() {
    return httpPort;
  }

  void setHTTPPort(int port) {
    httpPort = port;
  }
  
  size_t getHTTPWorkerCount() {
    return httpWorkerCount;
  }
  
  void setHTTPWorkerCount(size_t count) {
    httpWorkerCount = count;
  }
  
  ////////////////////////////////////////////////
  // NMPR
  ////////////////////////////////////////////////

 public:
  void setNMPRMode(bool flag) {
    nmprMode = flag;
  }

  bool isNMPRMode() {
    return nmprMode;
  }

  ////////////////////////////////////////////////
  // Device List
  ////////////////////////////////////////////////

private:

  bool addDevice(cyber_shared_ptr<uXML::Node> rootNode);
  bool addDevice(SSDPPacket *ssdpPacket);

private:
  
  void initDeviceList();

 public:
  DeviceList *getDeviceList() {
    return &deviceList;
  }

  cyber_shared_ptr<Device> getDevice(cyber_shared_ptr<uXML::Node> rootNode);
  cyber_shared_ptr<Device> getDevice(const std::string &name);

  bool hasDevice(const std::string &name) {
    return (getDevice(name)) ? true : false;
  }

private:

  bool removeDevice(cyber_shared_ptr<uXML::Node> rootNode);
  bool removeDevice(SSDPPacket *packet);

  ////////////////////////////////////////////////
  // Expired Device
  ////////////////////////////////////////////////

 public:
  void setExpiredDeviceMonitoringInterval(long interval) {
    expiredDeviceMonitoringInterval = interval;
  }

  long getExpiredDeviceMonitoringInterval() {
    return expiredDeviceMonitoringInterval;
  }
  
  void setDeviceDisposer(Disposer *disposer) {
    if (deviceDisposer)
      delete deviceDisposer;
    deviceDisposer = disposer;
  }
  
  Disposer *getDeviceDisposer() {
    return deviceDisposer;
  }

  void removeExpiredDevices();

  void clean();

  ////////////////////////////////////////////////
  // Notify
  ////////////////////////////////////////////////

 public:
  void addNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.add(listener);
  }    

  void removeNotifyListener(NotifyListener *listener) {
    deviceNotifyListenerList.remove(listener);
  }    

  bool performNotifyListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // SearchResponse
  ////////////////////////////////////////////////

 public:
  void addSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.add(listener);
  }    

  void removeSearchResponseListener(SearchResponseListener *listener) {
    deviceSearchResponseListenerList.remove(listener);
  }    

  bool performSearchResponseListener(SSDPPacket *ssdpPacket);

  ////////////////////////////////////////////////
  // DeviceChangeListener
  // Thanks for Oliver Newell (2004/10/16)
  ////////////////////////////////////////////////

 public:
  void addDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.add(listener);
  }    

  void removeDeviceChangeListener(DeviceChangeListener *listener) {
    deviceChangeListenerList.remove(listener);
  }    

  bool performAddDeviceListener(Device *dev);
  bool performRemoveDeviceListener(Device *dev);

  ////////////////////////////////////////////////
  // SSDPPacket
  ////////////////////////////////////////////////
  
 public:
  void notifyReceived(SSDPPacket *packet);
  void searchResponseReceived(SSDPPacket *packet);

  ////////////////////////////////////////////////
  // M-SEARCH
  ////////////////////////////////////////////////

 public:
  int getSearchMx() {
    return searchMx;
  }

  void setSearchMx(int mx) 
  {
    searchMx = mx;
  }

  bool search(const std::string &target, int mx);

  bool search(const std::string &target) {
    return search(target, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool search() {
    return search(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

  ////////////////////////////////////////////////
  // EventSub HTTPServer
  ////////////////////////////////////////////////

private:

  CyberLink::HTTPServerList *getHTTPServerList() {
    return &httpServerList;
  }

  CyberLink::HTTP::StatusCode httpRequestRecieved(CyberLink::HTTPRequest *httpReq);

  ////////////////////////////////////////////////
  // Event Listener 
  ////////////////////////////////////////////////

 public:
  void addEventListener(EventListener *listener) {
    eventListenerList.add(listener);
  }    

  void removeEventListener(EventListener *listener) {
    eventListenerList.remove(listener);
  }    

  bool performEventListener(const std::string &uuid, long seq, const std::string &name, const std::string &value);

  ////////////////////////////////////////////////
  // Subscription 
  ////////////////////////////////////////////////

public:  
  
  const char *getEventSubURI() {
    return eventSubURI.c_str();
  }

  void setEventSubURI(const std::string &url) {
    eventSubURI = url;
  }

private:

  const char *getEventSubCallbackURL(const std::string &host, std::string &buf) {
    return CyberLink::GetHostURL(host, getHTTPPort(), getEventSubURI(), buf);
  }

 public:
  bool subscribe(Service *service, long timeout);

  bool subscribe(Service *service) {
    return subscribe(service, Subscription::INFINITE_VALUE);
  }

  bool subscribe(Service *service, const std::string &uuid, long timeout);

  bool subscribe(Service *service, const std::string &uuid) {
    return subscribe(service, uuid, Subscription::INFINITE_VALUE);
  }

  bool isSubscribed(Service *service);
  
  bool unsubscribe(Service *service);
  void unsubscribe(Device *device);
  void unsubscribe();

  ////////////////////////////////////////////////
  // getSubscriberService  
  ////////////////////////////////////////////////

 public:
  Service *getSubscriberService(const std::string &uuid);
  
  ////////////////////////////////////////////////
  // getSubscriberService  
  ////////////////////////////////////////////////

 public:
  void renewSubscriberService(Device *dev, long timeout);
  void renewSubscriberService(long timeout);
  void renewSubscriberService();
  
  ////////////////////////////////////////////////
  // Subscriber
  ////////////////////////////////////////////////
  
 public:
  void setRenewSubscriber(RenewSubscriber *sub) {
    if (renewSubscriber)
      delete renewSubscriber;
    renewSubscriber = sub;
  }
  
  RenewSubscriber *getRenewSubscriber() {
    return renewSubscriber;  
  }

  ////////////////////////////////////////////////
  // run  
  ////////////////////////////////////////////////

 public:
  
  bool start(const std::string &target, int mx);

  bool start(const std::string &target) {
    return start(target, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool start() {
    return start(ST::ROOT_DEVICE, SSDP::DEFAULT_MSEARCH_MX);
  }

  bool stop();

  ////////////////////////////////////////////////
  // lock
  ////////////////////////////////////////////////

 public:
  void lock() {
    mutex.lock();
  }

  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // print
  ////////////////////////////////////////////////

 public:
  void print();
};

}

#endif

