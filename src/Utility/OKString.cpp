#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






//=========================================================================================================================
bool OKString::startsWith(const string& doesThisStart, const string& withThis)
{//=========================================================================================================================

	if (doesThisStart.rfind(withThis, 0) == 0)
		return true;
	else return false;
}


//=========================================================================================================================
bool OKString::startsWith(const string& withThis)
{//=========================================================================================================================

	if (this->rfind(withThis, 0) == 0)
		return true;
	else return false;
}


int OKString::indexOf(string s)
{
	return (int)this->find(s);

}

string OKString::substring(int pos)
{
	string s;
	s.assign(this->substr(pos));
	return s;
}
