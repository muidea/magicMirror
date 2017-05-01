/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : iTunesItemNode.java
*
*	Revision:
*
*	03/14/06
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ITUNESITEMNODE_H_
#define _CLINK_MEDIA_ITUNESITEMNODE_H_

#include <io/File.h>
#include <io/FileInputStream.h>
#include <media/server/object/item/ItemNode.h>

namespace CyberLink {

class iTunesItemNode : public ItemNode
{
	File *itemFile;

	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	iTunesItemNode();

	////////////////////////////////////////////////
	// File/TimeStamp
	////////////////////////////////////////////////
	
public:

	void setFile(File *file)
	{
		itemFile = file;
	}
	
	File *getFile()
	{
		return itemFile;
	}

	long getFileTimeStamp()
	{
		return itemFile->lastModified();
	}
	
	bool equals(File *file)
	{
		if (itemFile == NULL)
			return false;
		return itemFile->equals(file);
	}

	////////////////////////////////////////////////
	// Abstract methods
	////////////////////////////////////////////////

public:

	const char *getContent(std::string &buf);
	
	long getContentLength()
	{
		return itemFile->length();
	}

	InputStream *getContentInputStream();

	const char *getMimeType();
};

}

#endif


