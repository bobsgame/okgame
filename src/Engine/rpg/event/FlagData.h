//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class FlagData : public AssetData
{
private:
	typedef AssetData super;


public:
	FlagData();


	FlagData(int id, const string& name);


	//static sp<FlagData> fromBase64ZippedJSON(const string& b64);
	//static sp<FlagData> fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();
};

