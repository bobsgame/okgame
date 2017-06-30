//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class DialogueData : public AssetData
{
private:
	typedef AssetData super;

	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------


	/*
	
	   //TODO: not used yet
	
	   public boolean forAction = false;
	
	   public boolean forCutscene = false;
	
	   public boolean notTalkingAnyMoreToday = false;
	
	   public boolean generic = false;
	
	
	
	   public boolean annoyed = false;
	   public boolean angry = false;
	   public boolean jealous = false;
	   public boolean furious = false;
	
	
	
	   public boolean sad = false;
	   public boolean beaten = false;
	   public boolean suicidal = false;
	   public boolean crying = false;
	
	   public boolean happy = false;
	
	
	   public boolean defensive = false;
	   public boolean scared = false;
	
	
	   //public boolean cocky = false;
	   //public boolean horny = false;
	   //public boolean desperate = false;
	   //public boolean proud = false;
	
	   public boolean bored = false;
	
	*/


private:
	
	string caption = "";
	
	string comment = "";
	
	string text = "";


public:
	DialogueData();


	DialogueData(int id, const string& name, const string& caption, const string& comment, const string& text);


	string& initFromString(string& t);

	//static DialogueData* fromBase64ZippedJSON(const string& b64);
	//static DialogueData* fromJSON(const string& json);


	string getTYPEIDString();


	string& getCaption();
	string& getComment();
	string& getText();


	void setCaption(const string& s);
	void setComment(const string& s);
	void setText(const string& s);
};

