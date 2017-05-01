/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2004
*
*	File : FileDirectory.h
*
*	Revision:
*
*	04/14/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FILE_DIRECTORY_H_
#define _CLINK_MEDIA_FILE_DIRECTORY_H_

#include <string>
#include <io/File.h>
#include <media/server/Directory.h>
#include <media/server/object/item/file/FileItemNode.h>
#include <media/server/object/item/file/FileItemNodeList.h>

namespace CyberLink {

class FileDirectory : public Directory
{
	std::string path;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	FileDirectory(const char *name, const char *path);
	
	////////////////////////////////////////////////
	// Path
	////////////////////////////////////////////////

public:

	void setPath(const char *value)
	{
		path = value;		
	}
	
	const char *getPath()
	{
		return path.c_str();
	}

	////////////////////////////////////////////////
	// create/updateItemNode
	////////////////////////////////////////////////

private:

	bool updateItemNode(FileItemNode *itemNode, File *file);
	FileItemNode *createCompareItemNode(File *file);
	
	////////////////////////////////////////////////
	// FileList
	////////////////////////////////////////////////

private:

	int getDirectoryItemNodeList(File *dirFile, FileItemNodeList &itemNodeList);
	int getCurrentDirectoryItemNodeList(FileItemNodeList &fileNodeList);

	////////////////////////////////////////////////
	// updateItemNodeList
	////////////////////////////////////////////////

private:

	FileItemNode *getItemNode(File *file);

	void addItemNode(FileItemNode *itemNode)
	{
		addContentNode(itemNode);
	}
	
	bool updateItemNodeList(FileItemNode *newItemNode);
	void updateItemNodeList();

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////
	
public:

	void update();
};

}

#endif


