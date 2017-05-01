/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _CLINKCC_LOG_H_
#define _CLINKCC_LOG_H_

#include <util/Log.h>

namespace CyberLink {
  
#if defined(DEBUG)
#define LogTrace(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::TRACE,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogInfo(format, ...)      CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::INFO,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogWarn(format, ...)      CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::WARN,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogError(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::ERR,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogFatal(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::FATAL,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogDebug(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::DBG,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#else
#define LogTrace(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::TRACE,   format, ##__VA_ARGS__)
#define LogInfo(format, ...)      CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::INFO,    format, ##__VA_ARGS__)
#define LogWarn(format, ...)      CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::WARN,    format, ##__VA_ARGS__)
#define LogError(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::ERR,     format, ##__VA_ARGS__)
#define LogFatal(format, ...)     CyberLink::Log(CyberLink::Logger::GetSharedInstance(), CyberLink::LoggerTarget::FATAL,   format, ##__VA_ARGS__)
#define LogDebug(format, ...)
#endif

}

#endif
