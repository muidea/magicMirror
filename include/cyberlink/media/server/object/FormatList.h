/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: FormatList
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FORMATLIST_H_
#define _CLINK_MEDIA_FORMATLIST_H_

#include <util/Vector.h>
#include <io/File.h>

namespace CyberLink {

class Format;

class FormatList : public Vector<Format>
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	FormatList() 
	{
	}

	~FormatList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	Format *getFormat(int n)
	{
		return (Format *)Vector::get(n);
	}

	Format *getFormat(const char *type);

	Format *getFormat(File *file);

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


