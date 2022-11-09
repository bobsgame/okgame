#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Wallet::log = Logger("Wallet");


Wallet::Wallet(sp<BGClientEngine> g)
{ //=========================================================================================================================
	this->e = g;
}

void Wallet::init()
{ //=========================================================================================================================
}

void Wallet::update()
{ //=========================================================================================================================


	//TODO: use BigDecimal or that blog post on matthias blog about money types

	string moneyString = "";


	if (lastMoney != money)
	{
		lastMoney = money;

		
		moneyString = "" + to_string(money);
		if (moneyString.find('.') != -1)
		{
			if (moneyString.find('.') < (moneyString.length() - 1) - 2)
			{
				moneyString = moneyString.substr(0, moneyString.find('.') + 2);
			}
			else
			{
				if (moneyString.find('.') > (moneyString.length() - 1) - 2)
				{
					if (moneyString.find('.') == (moneyString.length() - 1) - 0)
					{
						moneyString = moneyString + "00";
					}
					else if (moneyString.find('.') == (moneyString.length() - 1) - 1)
					{
						moneyString = moneyString + "0";
					}
				}
			}
		}
		else
		{
			moneyString = moneyString + ".0f0";
		}

		moneyString = " $" + moneyString + " ";


		// getStatusBar()->moneyCaption::updateCaption(moneyString);
	}
}

