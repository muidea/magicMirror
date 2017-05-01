/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : FileItemNode.java
*
*	Revision:
*
*	02/12/04
*		- first revision.
*
******************************************************************/

#include <media/server/ContentDirectory.h>
#include <media/server/object/Format.h>
#include <media/server/object/item/file/FileItemNode.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
FileItemNode::FileItemNode()
{
	setFile(NULL);
}

////////////////////////////////////////////////
// Abstract methods
////////////////////////////////////////////////

const char *FileItemNode::getContent(std::string &buf)
{
	buf = "";
	if (itemFile == NULL)
		itemFile->load(buf);
	return buf.c_str();
}

InputStream *FileItemNode::getContentInputStream()
{
	if (itemFile == NULL)
		return NULL;
	return new FileInputStream(itemFile, File::O_BINARY);
}

const char *FileItemNode::getMimeType()
{
	ContentDirectory *cdir = getContentDirectory();
	File *itemFile = getFile();
	Format *itemFormat = cdir->getFormat(itemFile);
	if (itemFormat == NULL) {
		return "*/*";
	}
	return itemFormat->getMimeType();
}



