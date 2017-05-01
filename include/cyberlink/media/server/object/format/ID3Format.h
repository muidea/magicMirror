/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : ID3Format.h
*
*	Revision:
*
*	06/09/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ID3FORMAT_H_
#define _CLINK_MEDIA_ID3FORMAT_H_

#include <io/File.h>
#include <io/InputStream.h>
#include <media/server/object/format/AudioFormat.h>
#include <media/server/object/format/ID3FrameList.h>
#include <string>

namespace CyberLink {

class ID3Format : public AudioFormat
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *HEADER_ID;
	static const int HEADER_SIZE;
	static const int EXT_HEADER_SIZE;
	static const int FRAME_HEADER_SIZE;
	static const int FRAME_ID_SIZE;
	
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

private:

	ID3FrameList frameList;
	unsigned char *header;
	unsigned char *extHeader;
	unsigned char *frameHeader;

	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////
	
public:

	ID3Format();
	ID3Format(File *file);

	~ID3Format();

	////////////////////////////////////////////////
	// loadHeader
	////////////////////////////////////////////////

private:

	bool loadHeader(InputStream *inputStream);
	bool loadHeader(File *file);

	////////////////////////////////////////////////
	// Header
	////////////////////////////////////////////////
	
private:

	int getHeaderSize();

	int getFlag()
	{
		return (header[5] & 0xFF);		
	}
	
	bool isUnsynchronisation()
	{
		return (getFlag() & 0x80) == 1 ? true : false;
	}

	bool hasExtendedHeader()
	{
		return (getFlag() & 0x40) == 1 ? true : false;
	}

	bool isExperimental()
	{
		return (getFlag() & 0x20) == 1 ? true : false;
	}

	bool hasFooter()
	{
		return (getFlag() & 0x10) == 1 ? true : false;
	}

	////////////////////////////////////////////////
	// Extended Header
	////////////////////////////////////////////////

private:

	int getExtHeaderSize();

	////////////////////////////////////////////////
	// Header
	////////////////////////////////////////////////
	
private:

	const char *getFrameID(unsigned char *frameHeader, std::string &buf);
	int getFrameSize(unsigned char *frameHeader);
	int getFrameFlag(unsigned char *frameHeader);

public:

	unsigned char *getFrameData(const char *name)
	{
		return frameList.getFrameData(name);
	}

	const char *getFrameData(const char *name, std::string &buf)
	{
		return frameList.getFrameData(name, buf);
	}
	
	const char *getFrameStringData(const char *name, std::string &buf)
	{
		return frameList.getFrameStringData(name, buf);
	}

	////////////////////////////////////////////////
	// Abstract Methods
	////////////////////////////////////////////////

public:

	bool equals(File *file);

	FormatObject *createObject(File *file)
	{
		return new ID3Format(file);
	}
	
	const char *getMimeType()
	{
		return "audio/mpeg";
	}

	int getAttributeList(uXML::AttributeList &attrList);
	
	const char *getTitle(std::string &buf);
	
	const char *getCreator(std::string &buf);

	////////////////////////////////////////////////
	// print
	////////////////////////////////////////////////
	
	void print();

};

}

#endif


