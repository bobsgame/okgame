#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



//Logger AssetData::log = Logger("AssetData");

AssetData::AssetData()
{ //===============================================================================================
}

AssetData::AssetData(int id, const string& name)
{ //===============================================================================================
	this->id = id;
	this->name = name;
}

string& AssetData::getName()
{
	return name;
}

int AssetData::getID()
{
	return id;
}

void AssetData::setName(const string& s)
{
	name = s;
}

void AssetData::setID(int s)
{
	id = s;
}

//
////===============================================================================================
//public String toString()
//{//===============================================================================================
//
//	String s = "";
//
//	while (name.contains("`"))
//	{
//		String front = name.substring(0, name.indexOf("`"));
//		String back = name.substring(name.indexOf("`") + 1);
//		name = front + back;
//	}
//
//
//
//	s += "name:`" + name + "`,";
//	s += "id:`" + id + "`,";
//
//
//	return s;
//}



string& AssetData::initFromString(string& t)
{

	t = t.substr(t.find("name:`") + 1);
	t = t.substr(t.find("`") + 1);
	name = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("id:`") + 1);
	t = t.substr(t.find("`") + 1);
	id = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	return t;
}
