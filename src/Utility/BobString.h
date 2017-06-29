//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class String : public std::string
{
public:
	static bool startsWith(const string& doesThisStart, const string& withThis);
	bool startsWith(const string& withThis);

//	string s = "";
//	String(string s)
//	{
//		this->assign(s);
//	}
//	void setString(string s)
//	{
//		this->s = s;
//	}
//	string& getString()
//	{
//		return s;
//	}

	int indexOf(string s);
	String substring(int pos);

};

