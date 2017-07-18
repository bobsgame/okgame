//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class KeyboardMenuPanel : public MenuPanel
{
public:
	static Logger log;


	//DialogLayout* keyboardPanel = nullptr;


	//Button* okButton = nullptr;


	KeyboardMenuPanel();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		KeyboardMenuPanel* outerInstance = nullptr;

	public:
		WidgetAnonymousInnerClassHelper(KeyboardMenuPanel* outerInstance);

		void layout();
	};

public:
	bool _clickedOK = false;

	//The following method was originally marked 'synchronized':
	bool getClickedOK_S();

	//The following method was originally marked 'synchronized':
	void setClickedOK_S(bool b);


	virtual void update() override;


	virtual void onScrolledUp() override;


	virtual void scrollDown() override;


protected:
	virtual void layout() override;


public:
	void setButtonsVisible(bool b);


	void doOK();


	virtual void renderBefore() override;


	virtual void render() override;
};

