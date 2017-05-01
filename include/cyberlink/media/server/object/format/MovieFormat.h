/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MovieFormat.h
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MOVIEFORMAT_H_
#define _CLINK_MEDIA_MOVIEFORMAT_H_

#include <media/server/object/format/DefaultFormat.h>

namespace CyberLink {

class MovieFormat : public DefaultFormat
{
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	MovieFormat()
	{	
		setFile(NULL);
	}
	
	MovieFormat(File *file)
	{
		setFile(file);
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////
	
public:

	virtual bool equals(File *file) = 0;
	virtual FormatObject *createObject(File *file) = 0;
	virtual const char *getMimeType() = 0;
	
	const char *getMediaClass()
	{
		return "object.item.videoItem.movie";
	}
	
	virtual int getAttributeList(uXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}

	const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif
