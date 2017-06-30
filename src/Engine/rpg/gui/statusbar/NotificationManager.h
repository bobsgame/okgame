//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "notification/Notification.h"


class NotificationManager : public EnginePart
{
public:

	static Logger log;


	ArrayList<Notification*>* notificationList = new ArrayList<Notification*>();

	static BobTexture* loadingBarTexture;
	static BobTexture* loadingBarBackgroundTexture;


	NotificationManager(BGClientEngine* g);


	void init();


	void update();


	void render(int layer);


	void add(Notification* n);


	void remove(Notification* n);
};

