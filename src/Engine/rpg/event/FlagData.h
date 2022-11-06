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


	//static shared_ptr<FlagData> fromBase64ZippedJSON(const string& b64);
	//static shared_ptr<FlagData> fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();
};

