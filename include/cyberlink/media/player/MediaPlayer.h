/******************************************************************
*
*	MediaPlayer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MediaPlayer.h
*
*	04/20/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MEDIAPLAYER_H_
#define _CLINK_MEDIA_MEDIAPLAYER_H_

#include <media/server/MediaServer.h>
#include <media/server/action/BrowseAction.h>
#include <xml/Node.h>
#include <ControlPoint.h>

namespace CyberLink {

class MediaPlayer : public ControlPoint
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *DEVICE_TYPE;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:
	
	MediaPlayer();
	~MediaPlayer();
	
	////////////////////////////////////////////////
	// start/stop (Overided)
	////////////////////////////////////////////////
	
public:

	bool start();
	bool stop();
	
	////////////////////////////////////////////////
	// Browse
	////////////////////////////////////////////////

public:

	cyber_shared_ptr<uXML::Node> browse(
		Device *dev,
		const char *objectID,
		const char *browseFlag,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria);

	cyber_shared_ptr<uXML::Node> browseMetaData(
		Device *dev,
		const char *objectID,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria)
	{
		return browse(dev, objectID, BrowseAction::BROWSE_METADATA, filter, startIndex, requestedCount, sortCaiteria);
	}

	cyber_shared_ptr<uXML::Node> browseDirectChildren(
		Device *dev,
		const char *objectID,
		const char *filter,
		int startIndex,
		int requestedCount,
		const char *sortCaiteria)
	{
		return browse(dev, objectID, BrowseAction::BROWSE_DIRECT_CHILDREN, filter, startIndex, requestedCount, sortCaiteria);
	}

	////////////////////////////////////////////////
	// Content
	////////////////////////////////////////////////

public:

	ContentNode *getContentDirectory(Device *dev);

private:

	int getContentDirectory(ContentNode *parentNode, Device *dev, const char *objectID);

};

}

#endif


