#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LogsPanel::log = Logger("LogsPanel");


LogsPanel::LogsPanel()
{ //=========================================================================================================================

	SubPanel();


	//TODO: connect to server and get last x logs

	//
	//   shared_ptr<Label> label = make_shared<Label>("Logs");
	//   label->setCanAcceptKeyboardFocus(false);
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(label));
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(label));
}

