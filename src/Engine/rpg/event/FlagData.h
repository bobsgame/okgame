//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class FlagData : public AssetData
{
private:
	typedef AssetData super;


public:
	FlagData();


	FlagData(int id, const string& name);


	//static FlagData* fromBase64ZippedJSON(const string& b64);
	//static FlagData* fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();
};

