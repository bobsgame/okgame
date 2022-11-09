//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;





#include "notification/Notification.h"


class NotificationManager : public EnginePart
{
public:

	static Logger log;


	vector<sp<Notification>> notificationList;// = ms<ArrayList><sp<Notification>>();

	static sp<OKTexture> loadingBarTexture;
	static sp<OKTexture> loadingBarBackgroundTexture;


	NotificationManager(sp<BGClientEngine> g);


	void init();


	void update();


	void render(int layer);


	void add(sp<Notification> n);


	void remove(sp<Notification> n);
};

