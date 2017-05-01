/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: DirectoryList.h
*
*	Revision;
*
*	03/23/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DIRECTORYLIST_H_
#define _CLINK_MEDIA_DIRECTORYLIST_H_

#include <util/Vector.h>
#include <media/server/Directory.h>

namespace CyberLink {

class DirectoryList : public Vector<Directory>
{
	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	DirectoryList() 
	{
	}
	
	~DirectoryList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	// getDirectory
	////////////////////////////////////////////////
	
public:

	Directory *getDirectory(int n)
	{
		return (Directory *)Vector::get(n);
	}

	Directory *getDirectory(const char *name);

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

public:

	void update();
	
};

}

#endif


