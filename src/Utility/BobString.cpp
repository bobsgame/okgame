#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






//=========================================================================================================================
bool String::startsWith(const string& doesThisStart, const string& withThis)
{//=========================================================================================================================

	if (doesThisStart.rfind(withThis, 0) == 0)
		return true;
	else return false;
}


//=========================================================================================================================
bool String::startsWith(const string& withThis)
{//=========================================================================================================================

	if (this->rfind(withThis, 0) == 0)
		return true;
	else return false;
}


int String::indexOf(string s)
{
	return (int)this->find(s);

}

String String::substring(int pos)
{
	String s;
	s.assign(this->substr(pos));
	return s;
}
