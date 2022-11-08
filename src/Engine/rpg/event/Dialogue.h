//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class ServerObject;
class DialogueData;


class Dialogue : public ServerObject, public std::enable_shared_from_this<Dialogue>
{
public:

	static Logger log;


private:
	bool doneValue_S = false;
	long long timeSet = -1;

	shared_ptr<DialogueData> data = nullptr;


public:
	Dialogue(shared_ptr<Engine> g, int id);


	Dialogue(shared_ptr<Engine> g, shared_ptr<DialogueData> data);


	//The following method was originally marked 'synchronized':
	void setData_S(shared_ptr<DialogueData> data);


	shared_ptr<DialogueData> getData();

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

