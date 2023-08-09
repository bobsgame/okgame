//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



#include "../buttons/StatusBarButton.h"

class Notification : public StatusBarButton, public std::enable_shared_from_this<Notification>
{
public:

	static Logger log;

	sp<Caption> caption = nullptr;

	string notificationString;

	bool fadeIn = false;
	bool fadeOut = false;

	float progress = 0;
	float lastProgress = 0;
	int progressBarFrame = 0;
	bool hasProgressBar = true;
	int progressTicks = 0;
	int lastProgressTicks = 0;

	float alpha = 0.0f;

	float scrollX = 0;
	bool scrolling = false;

	Notification(sp<BGClientEngine> g, const string& s);

	virtual void update() override;

	virtual void render(int layer) override;

	sp<Notification> fadeOutAndDelete();
};

