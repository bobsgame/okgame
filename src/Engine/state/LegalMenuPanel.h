//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class LegalMenuPanel : public MenuPanel
{
public:
	static Logger log;


	//   DialogLayout* legalPanel;
	//
	//   Button* noButton;
	//   Button* okButton;


	LegalMenuPanel();

	bool _clickedOK = false;
	bool _clickedCancel = false;

	//The following method was originally marked 'synchronized':
	bool getClickedOK_S();
	//The following method was originally marked 'synchronized':
	bool getClickedCancel_S();

	//The following method was originally marked 'synchronized':
	void setClickedOK_S(bool b);
	//The following method was originally marked 'synchronized':
	void setClickedCancel_S(bool b);


	virtual void update() override;


	virtual void onScrolledUp() override;


protected:
	virtual void layout() override;


public:
	void setButtonsVisible(bool b);


	virtual void scrollDown() override;


	void doDisagree();


	void doAgree();


	virtual void renderBefore() override;


	virtual void render() override;
};

