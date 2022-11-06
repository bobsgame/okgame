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


	ArrayList<shared_ptr<Notification>>* notificationList = make_shared<ArrayList><shared_ptr<Notification>>();

	static shared_ptr<BobTexture> loadingBarTexture;
	static shared_ptr<BobTexture> loadingBarBackgroundTexture;


	NotificationManager(shared_ptr<BGClientEngine> g);


	void init();


	void update();


	void render(int layer);


	void add(shared_ptr<Notification> n);


	void remove(shared_ptr<Notification> n);
};

