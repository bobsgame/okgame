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
	//   shared_ptr<Label> label = make_shared<Label>("Messages");
	//   label->setCanAcceptKeyboardFocus(false);
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(label));
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(label));
}

