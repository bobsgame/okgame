//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Utility/AssetData.h"
class Logger;




class GameStringData : public AssetData
{
private:
	typedef AssetData super;



private:
	
	string text = "";


public:
	GameStringData();

	GameStringData(int id, const string& name, const string& text);

	//static GameStringData* fromBase64ZippedJSON(const string& b64);

	//static GameStringData* fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();

	string& getText();

	void setText(const string& s);
};

