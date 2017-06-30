//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class ServerObject;
class DialogueData;


class Dialogue : public ServerObject
{
public:

	static Logger log;


private:
	bool doneValue_S = false;
	long long timeSet = -1;

	DialogueData* data = nullptr;


public:
	Dialogue(Engine* g, int id);


	Dialogue(Engine* g, DialogueData* data);


	//The following method was originally marked 'synchronized':
	void setData_S(DialogueData* data);


	DialogueData* getData();

	int getID();
	string& getName();
	string& caption();
	string& getComment();
	string& text();

	string getTYPEIDString();

	void setID(int id);
	void setName(const string& name);
	void setCaption(const string& caption);
	void setComment(const string& comment);
	void setText(const string& text);


	//The following method was originally marked 'synchronized':
	void setDialogueDoneValue_S(bool b); //sendServerDialogueDoneValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	void initDialogueDoneValueFromGameSave_S(bool b, long long timeSet);


	//The following method was originally marked 'synchronized':
	bool getDialogueDoneValue_S();


	long long getTimeSet();
};

