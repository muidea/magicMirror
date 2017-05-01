/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: ConnectionInfoList.h
*
*	Revision:
*
*	06/19/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_CONNECTIONINFOLIST_H_
#define _CLINK_MEDIA_CONNECTIONINFOLIST_H_

#include <util/Vector.h>
#include <media/server/ConnectionInfo.h>

namespace CyberLink {

class ConnectionInfoList : public Vector<ConnectionInfo>
{
	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	ConnectionInfoList() 
	{
	}
	
	~ConnectionInfoList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	// getConnectionInfo
	////////////////////////////////////////////////
	
public:

	ConnectionInfo *getConnectionInfo(int n)
	{
		return (ConnectionInfo *)Vector::get(n);
	}

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();

};

}

#endif


