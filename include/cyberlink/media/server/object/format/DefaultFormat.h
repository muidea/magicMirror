/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : DefaultPlugIn.h
*
*	Revision:
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DEFAULTFORMT_H_
#define _CLINK_MEDIA_DEFAULTFORMT_H_

#include <io/File.h>
#include <media/server/object/Format.h>
#include <media/server/object/FormatObject.h>

namespace CyberLink {

class DefaultFormat : public Format, public FormatObject
{
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

private:

	File *file;
		
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	DefaultFormat()
	{
		setFile(NULL);
	}

	DefaultFormat(File *file)
	{
		setFile(file);
	}
	
	////////////////////////////////////////////////
	// File
	////////////////////////////////////////////////

public:

	void setFile(File *f)
	{
		file = f;
	}

	File *getFile()
	{
		return file;
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////

public:

	virtual bool equals(File *file)
	{
		return true;
	}
	
	virtual FormatObject *createObject(File *file)
	{
		return new DefaultFormat(file);
	}
	
	virtual const char *getMimeType()
	{
		return "*/*";
	}

	virtual const char *getMediaClass()
	{
		return "object.item";
	}
	
	virtual int getAttributeList(uXML::AttributeList &attrList)
	{
		attrList.clear();
		return attrList.size();
	}
	
	virtual const char *getTitle(std::string &buf);
	
	virtual const char *getCreator(std::string &buf)
	{
		buf = "";
		return buf.c_str();
	}
};

}

#endif


