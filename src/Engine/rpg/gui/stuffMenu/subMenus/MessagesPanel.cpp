#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger MessagesPanel::log = Logger("MessagesPanel");


MessagesPanel::MessagesPanel()
{ //=========================================================================================================================

	SubPanel();

	//
	//   sp<Label> label = ms<Label>("Messages");
	//   label->setCanAcceptKeyboardFocus(false);
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(label));
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(label));
}

