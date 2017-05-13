/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <util/Thread.h>

#include <stdio.h>

using namespace CyberLink;

#define UHTTP_THREAD_DETACHED 1

////////////////////////////////////////////////
// Thread Func
////////////////////////////////////////////////

#if defined(WIN32)
static DWORD WINAPI Win32ThreadProc(LPVOID lpParam) {
	Thread *thread = (Thread *)lpParam;
	thread->invokeRun();
	return 0;
}
#else
static void *PosixThreadProc(void *param) {
	Thread *thread = (Thread *)param;
	thread->invokeRun();
	return 0;
}
#endif

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

Thread::Thread()
	: runningSemaphore(1)
#if defined (WIN32)
	, hThread(NULL)
#endif
{
	setRunnableFlag(false);
	setObject(NULL);
}

bool Thread::start() {
	this->mutex.lock();

#if defined(WIN32)
	hThread = CreateThread(NULL, 0, Win32ThreadProc, (LPVOID)this, 0, &threadID);
	if (hThread == NULL) {
		this->mutex.unlock();
		return false;
	}
#else
	pthread_attr_t thread_attr;
	if (pthread_attr_init(&thread_attr) != 0) {
		this->mutex.unlock();
		return false;
	}
#if defined(UHTTP_THREAD_DETACHED)
	if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
		pthread_attr_destroy(&thread_attr);
		this->mutex.unlock();
		return false;
	}
#endif
	if (pthread_create(&thread, &thread_attr, PosixThreadProc, this) != 0) {
		pthread_attr_destroy(&thread_attr);
		this->mutex.unlock();
		return false;
	}
	pthread_attr_destroy(&thread_attr);
#endif

	setRunnableFlag(true);

	while (!this->runningSemaphore.wait(1)) {
		// 等待线程运行
	}

	this->mutex.unlock();

	return true;
}

Thread::~Thread() {
	stop();
}

bool Thread::stop() {
	this->runningSemaphore.reset();

	this->mutex.lock();

	setRunnableFlag(false);
#if defined(WIN32)
	if (hThread != NULL) {
		WaitForSingleObject(hThread, INFINITE);

		CloseHandle(hThread);
		hThread = NULL;
	}
#else
	if (pthread_cancel(thread) == 0) {
#if defined(UHTTP_THREAD_DETACHED)
		pthread_detach(thread);
#else
		pthread_join(thread, NULL);
#endif
}
#endif

	this->mutex.unlock();

	return true;
}

void Thread::setRunnableFlag(bool flag) {
	runnableFlag = flag;
}

bool Thread::isRunnable() {
#if !defined(WIN32)
	pthread_testcancel();
#endif
	return runnableFlag;
}

