/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _UHTTP_LOG_H_
#define _UHTTP_LOG_H_

#include <util/Logger.h>
#include <util/LoggerFileTarget.h>
#include <util/LoggerStdTarget.h>

namespace CyberLink {
int Log(
Logger *logger, 
int logType, 
#if defined(DEBUG)
const char *fileName, 
int lineNo, const 
char *functionName, 
#endif
const char *format, ...);

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
