//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Utility/AssetData.h"
class Logger;




class SkillData : public AssetData
{

private:
	typedef AssetData super;


public:
	SkillData();


	SkillData(int id, const string& name);


	//static SkillData* fromBase64ZippedJSON(const string& b64);
	//static SkillData* fromJSON(const string& json);


	string& initFromString(string& t);

	string getTYPEIDString();
};

