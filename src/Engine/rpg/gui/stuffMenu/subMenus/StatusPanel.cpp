#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger StatusPanel::log = Logger("StatusPanel");

StatusPanel::StatusPanel()
{ //=========================================================================================================================

	SubPanel();

	//
	//   shared_ptr<Label> statusPanelLabel = make_shared<Label>("Status");
	//   statusPanelLabel->setCanAcceptKeyboardFocus(false);
	//   statusPanelLabel->setTheme("bigLabel");
	//
	//
	//   //final BGClientEngine game = (BGClientEngine) g;
	//
	//
	//   string moneyToolTip = "";
	//   //				"Support \"bob\" ( That's me! ) by adding OKCoin$ to your account to buy more nD minigames and other stuff! (Coming Soon!)\n" +
	//   //				"\n"+
	//   //				"The games you buy can be played by your friends, even if they don't own them!\n" +
	//   //				"Plus, they're really cheap, and you can use them for bonuses in various places in the game.\n" +
	//   //				"\n"+
	//   //				"Have no money? ( That's OK, me too! ) Don't worry, you don't have to buy anything!!\n" +
	//   //				"You can compete in minigame bets and earn money through various tasks.\n"+
	//   //				"\n"+
	//   //				"Hate \"bob?\" and REFUSE to give him a SINGLE RED BOBCOIN?! ( That's OK, me too! )\n"+
	//   //				"The best revenge is to keep playing and tell everyone how terrible the game is so they come and play too!\n"+
	//   //				"All that grinding will swamp my servers and cost me tons of money, leaving me destitute and homeless- just like I always wanted!\n" +
	//   //				"It's win-win all around!"
	//   //				;
	//
	//   moneyDescriptionLabel = make_shared<Label>("OKCoin$: ");
	//   moneyDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   moneyDescriptionLabel->setTheme("descriptionLabel");
	//   moneyLabel = make_shared<Label>(" ");
	//   moneyLabel->setCanAcceptKeyboardFocus(false);
	//   moneyLabel->setTheme("valueLabel");
	//
	//   addMoneyButton = make_shared<Button>("Support \"bob!\" - Add OKCoin$");
	//   addMoneyButton->setCanAcceptKeyboardFocus(false);
	//   addMoneyButton->setTheme("smallButton");
	//   //addMoneyButton.setTooltipContent(moneyToolTip);
	//   addMoneyButton->addCallback([&] ()
	//      {
	//         doAddMoneyButton();
	//      }
	//   );
	//
	//
	//   addMoneyButtonQuestionMark = make_shared<Label>("?!");
	//   addMoneyButtonQuestionMark->setCanAcceptKeyboardFocus(false);
	//   addMoneyButtonQuestionMark->setTheme("bigLabel");
	//   addMoneyButtonQuestionMark->setTooltipContent(moneyToolTip);
	//   //--------
	//
	//
	//   string accountToolTip = string("Support \"bob\" with a OKPass for a one-time price of $12 a year.\n") + "\n" + "   - Avatar Vanity shared_ptr<Plate> (Make everyone else jealous- the spice of life!)\n" + "   - More shared_ptr<Friends> - (Make my servers explode!)\n" + "   - Forum shared_ptr<Membership> - (Come and spew hatred where I could read it and ruin my day!)\n" + "   - Bug shared_ptr<Reports> - (See how much crap I have to fix! Pay to do work for me!)\n" + "   - Beta shared_ptr<Minigames> - (Play em' before they work!)\n" + "   - Make A Custom Avatar - Coming Soon!\n" + "   - Design And Script Your House - Coming Soon!\n" + "   - Whatever else I come up with!\n" + "\n" + "Plus, I'll think you're really cool, and my intense psychic energy will \n" + "resonate in the collective subconscious, improving your life telepathically!**\n" + "\n" + "\n" + "*Features will be rolled out shortly!\n" + "**Results may vary.";
	//   //"   - Bonus OKCoin$ Added To Your Account (Why the heck not!)\n" +
	//   accountTypeDescriptionLabel = make_shared<Label>("Account Type: ");
	//   accountTypeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   accountTypeDescriptionLabel->setTheme("descriptionLabel");
	//   accountTypeLabel = make_shared<Label>(" ");
	//   accountTypeLabel->setCanAcceptKeyboardFocus(false);
	//   accountTypeLabel->setTheme("valueLabel");
	//
	//   goPremiumButton = make_shared<Button>("Support \"bob!\" - Buy A OKPass");
	//   goPremiumButton->setCanAcceptKeyboardFocus(false);
	//   goPremiumButton->setTheme("smallButton");
	//   //goPremiumButton.setTooltipContent(accountToolTip);
	//   goPremiumButton->addCallback([&] ()
	//      {
	//         doGoPremiumButton();
	//      }
	//   );
	//
	//   goPremiumButtonQuestionMark = make_shared<Label>("?!");
	//   goPremiumButtonQuestionMark->setCanAcceptKeyboardFocus(false);
	//   goPremiumButtonQuestionMark->setTheme("bigLabel");
	//   goPremiumButtonQuestionMark->setTooltipContent(accountToolTip);
	//   //---------
	//
	//
	//   //public String characterName = "";
	//
	//   characterNameDescriptionLabel = make_shared<Label>("Character Name: ");
	//   characterNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   characterNameDescriptionLabel->setTheme("descriptionLabel");
	//   characterNameLabel = make_shared<Label>(" ");
	//   characterNameLabel->setCanAcceptKeyboardFocus(false);
	//   characterNameLabel->setTheme("valueLabel");
	//
	//
	//   editCharacterButton = make_shared<Button>("Edit Character");
	//   editCharacterButton->setCanAcceptKeyboardFocus(false);
	//   editCharacterButton->setTheme("smallButton");
	//   editCharacterButton->addCallback([&] ()
	//      {
	//         doEditCharacterButton();
	//      }
	//   );
	//
	//
	//   //public String emailAddress = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete emailAddressDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete emailAddressLabel;
	//   emailAddressDescriptionLabel = make_shared<Label>("Email Address: ");
	//   emailAddressDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   emailAddressDescriptionLabel->setTheme("descriptionLabel");
	//   emailAddressLabel = make_shared<Label>(" ");
	//   emailAddressLabel->setCanAcceptKeyboardFocus(false);
	//   emailAddressLabel->setTheme("valueLabel");
	//
	//
	//   //public long accountCreatedTime = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete accountCreatedTimeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete accountCreatedTimeLabel;
	//   accountCreatedTimeDescriptionLabel = make_shared<Label>("Account Created Time: ");
	//   accountCreatedTimeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   accountCreatedTimeDescriptionLabel->setTheme("descriptionLabel");
	//   accountCreatedTimeLabel = make_shared<Label>(" ");
	//   accountCreatedTimeLabel->setCanAcceptKeyboardFocus(false);
	//   accountCreatedTimeLabel->setTheme("valueLabel");
	//
	//
	//   //public long lastLoginTime = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastLoginTimeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastLoginTimeLabel;
	//   lastLoginTimeDescriptionLabel = make_shared<Label>("Last Login Time: ");
	//   lastLoginTimeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lastLoginTimeDescriptionLabel->setTheme("descriptionLabel");
	//   lastLoginTimeLabel = make_shared<Label>(" ");
	//   lastLoginTimeLabel->setCanAcceptKeyboardFocus(false);
	//   lastLoginTimeLabel->setTheme("valueLabel");
	//
	//
	//   //public int timesLoggedIn = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timesLoggedInDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timesLoggedInLabel;
	//   timesLoggedInDescriptionLabel = make_shared<Label>("Times Logged In: ");
	//   timesLoggedInDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   timesLoggedInDescriptionLabel->setTheme("descriptionLabel");
	//   timesLoggedInLabel = make_shared<Label>(" ");
	//   timesLoggedInLabel->setCanAcceptKeyboardFocus(false);
	//   timesLoggedInLabel->setTheme("valueLabel");
	//
	//
	//   //public String lastIP = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastIPDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastIPLabel;
	//   lastIPDescriptionLabel = make_shared<Label>("Last IP Address: ");
	//   lastIPDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lastIPDescriptionLabel->setTheme("descriptionLabel");
	//   lastIPLabel = make_shared<Label>(" ");
	//   lastIPLabel->setCanAcceptKeyboardFocus(false);
	//   lastIPLabel->setTheme("valueLabel");
	//
	//
	//   accountPanelLabel = make_shared<Label>("Account Stuff");
	//   accountPanelLabel->setCanAcceptKeyboardFocus(false);
	//   accountPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //account box
	//   //---------------------------------------------------------
	//
	//   accountDialogLayout = make_shared<DialogLayout>();
	//   accountDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   accountDialogLayout->setHorizontalGroup(accountDialogLayout->createParallelGroup(accountDialogLayout->createSequentialGroup().addGap().addWidget(accountPanelLabel).addGap(), accountDialogLayout->createSequentialGroup(accountDialogLayout->createParallelGroup(emailAddressDescriptionLabel, accountCreatedTimeDescriptionLabel, lastLoginTimeDescriptionLabel, timesLoggedInDescriptionLabel, lastIPDescriptionLabel), accountDialogLayout->createParallelGroup(emailAddressLabel, accountCreatedTimeLabel, lastLoginTimeLabel, timesLoggedInLabel, lastIPLabel))));
	//
	//   accountDialogLayout->setVerticalGroup(accountDialogLayout->createSequentialGroup(accountDialogLayout->createParallelGroup().addWidgets(accountPanelLabel), accountDialogLayout->createParallelGroup().addWidgets(emailAddressDescriptionLabel, emailAddressLabel), accountDialogLayout->createParallelGroup().addWidgets(accountCreatedTimeDescriptionLabel, accountCreatedTimeLabel), accountDialogLayout->createParallelGroup().addWidgets(lastLoginTimeDescriptionLabel, lastLoginTimeLabel), accountDialogLayout->createParallelGroup().addWidgets(timesLoggedInDescriptionLabel, timesLoggedInLabel), accountDialogLayout->createParallelGroup().addWidgets(lastIPDescriptionLabel, lastIPLabel)));
	//
	//
	//   //		//public String realName = "";
	//   //		realNameDescriptionLabel = null;
	//   //		realNameLabel = null;
	//   //		realNameDescriptionLabel = make_shared<Label>("Real Name: ");
	//   //		realNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		realNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		realNameLabel = make_shared<Label>(" ");
	//   //		realNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		realNameLabel.setTheme("valueLabel");
	//
	//
	//   //public long birthdayTime = 0;
	//   //		birthdayTimeDescriptionLabel = null;
	//   //		birthdayTimeLabel = null;
	//   //		birthdayTimeDescriptionLabel = make_shared<Label>("Birthday Time: ");
	//   //		birthdayTimeDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		birthdayTimeDescriptionLabel.setTheme("descriptionLabel");
	//   //		birthdayTimeLabel = make_shared<Label>(" ");
	//   //		birthdayTimeLabel.setCanAcceptKeyboardFocus(false);
	//   //		birthdayTimeLabel.setTheme("valueLabel");
	//
	//
	//   //public String postalCode = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete postalCodeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete postalCodeLabel;
	//   postalCodeDescriptionLabel = make_shared<Label>("Postal/Zip Code: ");
	//   postalCodeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   postalCodeDescriptionLabel->setTheme("descriptionLabel");
	//   postalCodeLabel = make_shared<Label>(" ");
	//   postalCodeLabel->setCanAcceptKeyboardFocus(false);
	//   postalCodeLabel->setTheme("valueLabel");
	//
	//   //public String countryName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete countryNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete countryNameLabel;
	//   countryNameDescriptionLabel = make_shared<Label>("Country Name: ");
	//   countryNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   countryNameDescriptionLabel->setTheme("descriptionLabel");
	//   countryNameLabel = make_shared<Label>(" ");
	//   countryNameLabel->setCanAcceptKeyboardFocus(false);
	//   countryNameLabel->setTheme("valueLabel");
	//
	//   //public String isoCountryCode = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete isoCountryCodeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete isoCountryCodeLabel;
	//   isoCountryCodeDescriptionLabel = make_shared<Label>("Country Code: ");
	//   isoCountryCodeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   isoCountryCodeDescriptionLabel->setTheme("descriptionLabel");
	//   isoCountryCodeLabel = make_shared<Label>(" ");
	//   isoCountryCodeLabel->setCanAcceptKeyboardFocus(false);
	//   isoCountryCodeLabel->setTheme("valueLabel");
	//
	//   //public String placeName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete placeNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete placeNameLabel;
	//   placeNameDescriptionLabel = make_shared<Label>("Place Name: ");
	//   placeNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   placeNameDescriptionLabel->setTheme("descriptionLabel");
	//   placeNameLabel = make_shared<Label>(" ");
	//   placeNameLabel->setCanAcceptKeyboardFocus(false);
	//   placeNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String stateName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete stateNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete stateNameLabel;
	//   stateNameDescriptionLabel = make_shared<Label>("State Name: ");
	//   stateNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   stateNameDescriptionLabel->setTheme("descriptionLabel");
	//   stateNameLabel = make_shared<Label>(" ");
	//   stateNameLabel->setCanAcceptKeyboardFocus(false);
	//   stateNameLabel->setTheme("valueLabel");
	//
	//
	//   //public float lat = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete latDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete latLabel;
	//   latDescriptionLabel = make_shared<Label>("Latitude: ");
	//   latDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   latDescriptionLabel->setTheme("descriptionLabel");
	//   latLabel = make_shared<Label>(" ");
	//   latLabel->setCanAcceptKeyboardFocus(false);
	//   latLabel->setTheme("valueLabel");
	//
	//   //public float lon = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lonDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lonLabel;
	//   lonDescriptionLabel = make_shared<Label>("Longitude: ");
	//   lonDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lonDescriptionLabel->setTheme("descriptionLabel");
	//   lonLabel = make_shared<Label>(" ");
	//   lonLabel->setCanAcceptKeyboardFocus(false);
	//   lonLabel->setTheme("valueLabel");
	//
	//   //public int timeZone = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timeZoneDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timeZoneLabel;
	//   timeZoneDescriptionLabel = make_shared<Label>("Time Zone: ");
	//   timeZoneDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   timeZoneDescriptionLabel->setTheme("descriptionLabel");
	//   timeZoneLabel = make_shared<Label>(" ");
	//   timeZoneLabel->setCanAcceptKeyboardFocus(false);
	//   timeZoneLabel->setTheme("valueLabel");
	//
	//
	//   locationPanelLabel = make_shared<Label>("Location Stuff");
	//   locationPanelLabel->setCanAcceptKeyboardFocus(false);
	//   locationPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //location box
	//   //---------------------------------------------------------
	//
	//   locationDialogLayout = make_shared<DialogLayout>();
	//   locationDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   locationDialogLayout->setHorizontalGroup(locationDialogLayout->createParallelGroup(locationDialogLayout->createSequentialGroup().addGap().addWidget(locationPanelLabel).addGap(), locationDialogLayout->createSequentialGroup(locationDialogLayout->createParallelGroup(postalCodeDescriptionLabel, countryNameDescriptionLabel, isoCountryCodeDescriptionLabel, placeNameDescriptionLabel, stateNameDescriptionLabel, latDescriptionLabel, lonDescriptionLabel, timeZoneDescriptionLabel), locationDialogLayout->createParallelGroup(postalCodeLabel, countryNameLabel, isoCountryCodeLabel, placeNameLabel, stateNameLabel, latLabel, lonLabel, timeZoneLabel))));
	//
	//   locationDialogLayout->setVerticalGroup(locationDialogLayout->createSequentialGroup(locationDialogLayout->createParallelGroup().addWidgets(locationPanelLabel), locationDialogLayout->createParallelGroup().addWidgets(postalCodeDescriptionLabel, postalCodeLabel), locationDialogLayout->createParallelGroup().addWidgets(countryNameDescriptionLabel, countryNameLabel), locationDialogLayout->createParallelGroup().addWidgets(isoCountryCodeDescriptionLabel, isoCountryCodeLabel), locationDialogLayout->createParallelGroup().addWidgets(placeNameDescriptionLabel, placeNameLabel), locationDialogLayout->createParallelGroup().addWidgets(stateNameDescriptionLabel, stateNameLabel), locationDialogLayout->createParallelGroup().addWidgets(latDescriptionLabel, latLabel), locationDialogLayout->createParallelGroup().addWidgets(lonDescriptionLabel, lonLabel), locationDialogLayout->createParallelGroup().addWidgets(timeZoneDescriptionLabel, timeZoneLabel)));
	//
	//
	//   //public String facebookEmail = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookEmailDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookEmailLabel;
	//   facebookEmailDescriptionLabel = make_shared<Label>("Facebook Email: ");
	//   facebookEmailDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookEmailDescriptionLabel->setTheme("descriptionLabel");
	//   facebookEmailLabel = make_shared<Label>(" ");
	//   facebookEmailLabel->setCanAcceptKeyboardFocus(false);
	//   facebookEmailLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookBirthday = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookBirthdayDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookBirthdayLabel;
	//   facebookBirthdayDescriptionLabel = make_shared<Label>("Facebook Birthday: ");
	//   facebookBirthdayDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookBirthdayDescriptionLabel->setTheme("descriptionLabel");
	//   facebookBirthdayLabel = make_shared<Label>(" ");
	//   facebookBirthdayLabel->setCanAcceptKeyboardFocus(false);
	//   facebookBirthdayLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookFirstName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookFirstNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookFirstNameLabel;
	//   facebookFirstNameDescriptionLabel = make_shared<Label>("Facebook First Name: ");
	//   facebookFirstNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookFirstNameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookFirstNameLabel = make_shared<Label>(" ");
	//   facebookFirstNameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookFirstNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookLastName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLastNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLastNameLabel;
	//   facebookLastNameDescriptionLabel = make_shared<Label>("Facebook Last Name: ");
	//   facebookLastNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLastNameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookLastNameLabel = make_shared<Label>(" ");
	//   facebookLastNameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLastNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookGender = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookGenderDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookGenderLabel;
	//   facebookGenderDescriptionLabel = make_shared<Label>("Facebook Gender: ");
	//   facebookGenderDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookGenderDescriptionLabel->setTheme("descriptionLabel");
	//   facebookGenderLabel = make_shared<Label>(" ");
	//   facebookGenderLabel->setCanAcceptKeyboardFocus(false);
	//   facebookGenderLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookLocale = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLocaleDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLocaleLabel;
	//   facebookLocaleDescriptionLabel = make_shared<Label>("Facebook Locale: ");
	//   facebookLocaleDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLocaleDescriptionLabel->setTheme("descriptionLabel");
	//   facebookLocaleLabel = make_shared<Label>(" ");
	//   facebookLocaleLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLocaleLabel->setTheme("valueLabel");
	//
	//
	//   //public Float facebookTimeZone = 0.0f;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookTimeZoneDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookTimeZoneLabel;
	//   facebookTimeZoneDescriptionLabel = make_shared<Label>("Facebook Time Zone: ");
	//   facebookTimeZoneDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookTimeZoneDescriptionLabel->setTheme("descriptionLabel");
	//   facebookTimeZoneLabel = make_shared<Label>(" ");
	//   facebookTimeZoneLabel->setCanAcceptKeyboardFocus(false);
	//   facebookTimeZoneLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookUsername = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookUsernameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookUsernameLabel;
	//   facebookUsernameDescriptionLabel = make_shared<Label>("Facebook Username: ");
	//   facebookUsernameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookUsernameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookUsernameLabel = make_shared<Label>(" ");
	//   facebookUsernameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookUsernameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookWebsite = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookWebsiteDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookWebsiteLabel;
	//   facebookWebsiteDescriptionLabel = make_shared<Label>("Facebook Website: ");
	//   facebookWebsiteDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookWebsiteDescriptionLabel->setTheme("descriptionLabel");
	//   facebookWebsiteLabel = make_shared<Label>(" ");
	//   facebookWebsiteLabel->setCanAcceptKeyboardFocus(false);
	//   facebookWebsiteLabel->setTheme("valueLabel");
	//
	//
	//   facebookPanelLabel = make_shared<Label>("Facebook Stuff");
	//   facebookPanelLabel->setCanAcceptKeyboardFocus(false);
	//   facebookPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //facebook box
	//   //---------------------------------------------------------
	//
	//   facebookDialogLayout = make_shared<DialogLayout>();
	//   facebookDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   facebookDialogLayout->setHorizontalGroup(facebookDialogLayout->createParallelGroup(facebookDialogLayout->createSequentialGroup().addGap().addWidget(facebookPanelLabel).addGap(), facebookDialogLayout->createSequentialGroup(facebookDialogLayout->createParallelGroup(facebookEmailDescriptionLabel, facebookBirthdayDescriptionLabel, facebookFirstNameDescriptionLabel, facebookLastNameDescriptionLabel, facebookGenderDescriptionLabel, facebookLocaleDescriptionLabel, facebookTimeZoneDescriptionLabel, facebookUsernameDescriptionLabel, facebookWebsiteDescriptionLabel), facebookDialogLayout->createParallelGroup(facebookEmailLabel, facebookBirthdayLabel, facebookFirstNameLabel, facebookLastNameLabel, facebookGenderLabel, facebookLocaleLabel, facebookTimeZoneLabel, facebookUsernameLabel, facebookWebsiteLabel))));
	//
	//   facebookDialogLayout->setVerticalGroup(facebookDialogLayout->createSequentialGroup(facebookDialogLayout->createParallelGroup().addWidgets(facebookPanelLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookEmailDescriptionLabel, facebookEmailLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookBirthdayDescriptionLabel, facebookBirthdayLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookFirstNameDescriptionLabel, facebookFirstNameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookLastNameDescriptionLabel, facebookLastNameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookGenderDescriptionLabel, facebookGenderLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookLocaleDescriptionLabel, facebookLocaleLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookTimeZoneDescriptionLabel, facebookTimeZoneLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookUsernameDescriptionLabel, facebookUsernameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookWebsiteDescriptionLabel, facebookWebsiteLabel)));
	//
	//
	//   //		playerGooglePlusNameDescriptionLabel = make_shared<Label>("Google+ Name: ");
	//   //		playerGooglePlusNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerGooglePlusNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		playerGooglePlusNameLabel = make_shared<Label>("bobsgame");
	//   //		playerGooglePlusNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerGooglePlusNameLabel.setTheme("valueLabel");
	//   //
	//   //		playerTwitterNameDescriptionLabel = make_shared<Label>("Twitter Name: ");
	//   //		playerTwitterNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerTwitterNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		playerTwitterNameLabel = make_shared<Label>("bobsgame");
	//   //		playerTwitterNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerTwitterNameLabel.setTheme("valueLabel");
	//   //
	//   //
	//   //		totalTimePlayedDescriptionLabel = make_shared<Label>("Total Time Played: ");
	//   //		totalTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		totalTimePlayedLabel = make_shared<Label>("20000:00");
	//   //		totalTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		sessionTimePlayedDescriptionLabel = make_shared<Label>("Time Played This Session: ");
	//   //		sessionTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		sessionTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		sessionTimePlayedLabel = make_shared<Label>("0:00");
	//   //		sessionTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		sessionTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		averageTimePlayedDescriptionLabel = make_shared<Label>("Average Session Time: ");
	//   //		averageTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		averageTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		averageTimePlayedLabel = make_shared<Label>("0:02");
	//   //		averageTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		averageTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		gamesPurchasedDescriptionLabel = make_shared<Label>("Games Purchased: ");
	//   //		gamesPurchasedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesPurchasedDescriptionLabel.setTheme("descriptionLabel");
	//   //		gamesPurchasedLabel = make_shared<Label>("15");
	//   //		gamesPurchasedLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesPurchasedLabel.setTheme("valueLabel");
	//   //
	//   //		gamesSoldDescriptionLabel = make_shared<Label>("Games Sold: ");
	//   //		gamesSoldDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesSoldDescriptionLabel.setTheme("descriptionLabel");
	//   //		gamesSoldLabel = make_shared<Label>("0");
	//   //		gamesSoldLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesSoldLabel.setTheme("valueLabel");
	//   //
	//   //		friendsInGameDescriptionLabel = make_shared<Label>("Friends In Game: ");
	//   //		friendsInGameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		friendsInGameDescriptionLabel.setTheme("descriptionLabel");
	//   //		friendsInGameLabel = make_shared<Label>("1");
	//   //		friendsInGameLabel.setCanAcceptKeyboardFocus(false);
	//   //		friendsInGameLabel.setTheme("valueLabel");
	//   //
	//   //		totalGamesPlayedDescriptionLabel = make_shared<Label>("Total Games Played: ");
	//   //		totalGamesPlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalGamesPlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		totalGamesPlayedLabel = make_shared<Label>("0");
	//   //		totalGamesPlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalGamesPlayedLabel.setTheme("valueLabel");
	//   //
	//   //		timesChallengedDescriptionLabel = make_shared<Label>("Times Challenged By Others: ");
	//   //		timesChallengedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengedDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesChallengedLabel = make_shared<Label>("0");
	//   //		timesChallengedLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengedLabel.setTheme("valueLabel");
	//   //
	//   //		timesChallengerDescriptionLabel = make_shared<Label>("Times Challenged Others: ");
	//   //		timesChallengerDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengerDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesChallengerLabel = make_shared<Label>("0");
	//   //		timesChallengerLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengerLabel.setTheme("valueLabel");
	//   //
	//   //		timesWonDescriptionLabel = make_shared<Label>("Times You Won: ");
	//   //		timesWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesWonDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesWonLabel = make_shared<Label>("99999");
	//   //		timesWonLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesWonLabel.setTheme("valueLabel");
	//   //
	//   //		timesLostDescriptionLabel = make_shared<Label>("Times You Lost: ");
	//   //		timesLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesLostDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesLostLabel = make_shared<Label>("0");
	//   //		timesLostLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesLostLabel.setTheme("valueLabel");
	//   //
	//   //		betsWonDescriptionLabel = make_shared<Label>("Bets Won: ");
	//   //		betsWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsWonDescriptionLabel.setTheme("descriptionLabel");
	//   //		betsWonLabel = make_shared<Label>("99999");
	//   //		betsWonLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsWonLabel.setTheme("valueLabel");
	//   //
	//   //		betsLostDescriptionLabel = make_shared<Label>("Bets Lost: ");
	//   //		betsLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsLostDescriptionLabel.setTheme("descriptionLabel");
	//   //		betsLostLabel = make_shared<Label>("0");
	//   //		betsLostLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsLostLabel.setTheme("valueLabel");
	//   //
	//   //		pointsEarnedDescriptionLabel = make_shared<Label>("Total Points Earned: ");
	//   //		pointsEarnedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		pointsEarnedDescriptionLabel.setTheme("descriptionLabel");
	//   //		pointsEarnedLabel = make_shared<Label>("99999999");
	//   //		pointsEarnedLabel.setCanAcceptKeyboardFocus(false);
	//   //		pointsEarnedLabel.setTheme("valueLabel");
	//   //
	//   //		globalRankingDescriptionLabel = make_shared<Label>("Global Ranking: ");
	//   //		globalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		globalRankingDescriptionLabel.setTheme("descriptionLabel");
	//   //		globalRankingLabel = make_shared<Label>("1st Place");
	//   //		globalRankingLabel.setCanAcceptKeyboardFocus(false);
	//   //		globalRankingLabel.setTheme("valueLabel");
	//   //
	//   //		regionalRankingDescriptionLabel = make_shared<Label>("Regional Ranking: ");
	//   //		regionalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		regionalRankingDescriptionLabel.setTheme("descriptionLabel");
	//   //		regionalRankingLabel = make_shared<Label>("1st Place");
	//   //		regionalRankingLabel.setCanAcceptKeyboardFocus(false);
	//   //		regionalRankingLabel.setTheme("valueLabel");
	//   //
	//   //		stepsWalkedDescriptionLabel = make_shared<Label>("Total Steps Walked: ");
	//   //		stepsWalkedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		stepsWalkedDescriptionLabel.setTheme("descriptionLabel");
	//   //		stepsWalkedLabel = make_shared<Label>("2452757542");
	//   //		stepsWalkedLabel.setCanAcceptKeyboardFocus(false);
	//   //		stepsWalkedLabel.setTheme("valueLabel");
	//   //
	//   //		buttonsPushedDescriptionLabel = make_shared<Label>("Total Buttons Pushed: ");
	//   //		buttonsPushedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		buttonsPushedDescriptionLabel.setTheme("descriptionLabel");
	//   //		buttonsPushedLabel = make_shared<Label>("32652357");
	//   //		buttonsPushedLabel.setCanAcceptKeyboardFocus(false);
	//   //		buttonsPushedLabel.setTheme("valueLabel");
	//
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(insideLayout->createSequentialGroup(insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(insideLayout->createSequentialGroup().addGap().addWidget(statusPanelLabel).addGap(), insideLayout->createSequentialGroup(insideLayout->createSequentialGroup(insideLayout->createParallelGroup(characterNameDescriptionLabel, accountTypeDescriptionLabel), insideLayout->createParallelGroup(insideLayout->createSequentialGroup(characterNameLabel), insideLayout->createSequentialGroup(accountTypeLabel)), insideLayout->createParallelGroup(insideLayout->createSequentialGroup(editCharacterButton).addGap(), insideLayout->createSequentialGroup(goPremiumButton, goPremiumButtonQuestionMark).addGap()))), insideLayout->createSequentialGroup(accountDialogLayout), insideLayout->createSequentialGroup(locationDialogLayout), insideLayout->createSequentialGroup(facebookDialogLayout)), insideLayout->createSequentialGroup().addGap())));
	//   //,moneyDescriptionLabel
	//   //realNameDescriptionLabel,
	//   //birthdayTimeDescriptionLabel,
	//   //
	//   //																		playerFacebookNameDescriptionLabel,
	//   //																		playerGooglePlusNameDescriptionLabel,
	//   //																		playerTwitterNameDescriptionLabel,
	//   //																		totalTimePlayedDescriptionLabel,
	//   //																		sessionTimePlayedDescriptionLabel,
	//   //																		averageTimePlayedDescriptionLabel,
	//   //																		stepsWalkedDescriptionLabel,
	//   //																		buttonsPushedDescriptionLabel,
	//   //																		globalRankingDescriptionLabel,
	//   //																		regionalRankingDescriptionLabel,
	//   //																		pointsEarnedDescriptionLabel,
	//   //																		gamesPurchasedDescriptionLabel,
	//   //																		gamesSoldDescriptionLabel,
	//   //																		friendsInGameDescriptionLabel,
	//   //																		totalGamesPlayedDescriptionLabel,
	//   //																		timesChallengedDescriptionLabel,
	//   //																		timesChallengerDescriptionLabel,
	//   //																		timesWonDescriptionLabel,
	//   //																		timesLostDescriptionLabel,
	//   //																		betsWonDescriptionLabel,
	//   //																		betsLostDescriptionLabel
	//   //,insideLayout.createSequentialGroup(moneyLabel)
	//   //realNameLabel,
	//   //birthdayTimeLabel,
	//   //
	//   //																		playerFacebookNameLabel,
	//   //																		playerGooglePlusNameLabel,
	//   //																		playerTwitterNameLabel,
	//   //																		totalTimePlayedLabel,
	//   //																		sessionTimePlayedLabel,
	//   //																		averageTimePlayedLabel,
	//   //																		stepsWalkedLabel,
	//   //																		buttonsPushedLabel,
	//   //																		globalRankingLabel,
	//   //																		regionalRankingLabel,
	//   //																		pointsEarnedLabel,
	//   //																		gamesPurchasedLabel,
	//   //																		gamesSoldLabel,
	//   //																		friendsInGameLabel,
	//   //																		totalGamesPlayedLabel,
	//   //																		timesChallengedLabel,
	//   //																		timesChallengerLabel,
	//   //																		timesWonLabel,
	//   //																		timesLostLabel,
	//   //																		betsWonLabel,
	//   //																		betsLostLabel
	//   //insideLayout.createSequentialGroup(addMoneyButton,addMoneyButtonQuestionMark).addGap(),
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(insideLayout->createParallelGroup(insideLayout->createSequentialGroup(), insideLayout->createSequentialGroup(insideLayout->createSequentialGroup(statusPanelLabel), insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(characterNameDescriptionLabel, characterNameLabel, editCharacterButton), insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(accountTypeDescriptionLabel, accountTypeLabel, goPremiumButton, goPremiumButtonQuestionMark), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(accountDialogLayout), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(locationDialogLayout), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(facebookDialogLayout)))));
	//   //insideLayout.createParallelGroup(editCharacterButton)
	//   //,
	//   //insideLayout.createSequentialGroup().addGap()
	//   //insideLayout.createParallelGroup(moneyDescriptionLabel,moneyLabel,addMoneyButton,addMoneyButtonQuestionMark),
	//   //insideLayout.createParallelGroup(realNameDescriptionLabel,            realNameLabel                ),
	//   //insideLayout.createParallelGroup(birthdayTimeDescriptionLabel,        birthdayTimeLabel            ),
	//   //								insideLayout.createParallelGroup(playerFacebookNameDescriptionLabel,		playerFacebookNameLabel),
	//   //								insideLayout.createParallelGroup(playerGooglePlusNameDescriptionLabel,		playerGooglePlusNameLabel),
	//   //								insideLayout.createParallelGroup(playerTwitterNameDescriptionLabel,		playerTwitterNameLabel),
	//   //								insideLayout.createParallelGroup(totalTimePlayedDescriptionLabel,		totalTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(sessionTimePlayedDescriptionLabel,		sessionTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(averageTimePlayedDescriptionLabel,		averageTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(stepsWalkedDescriptionLabel,			stepsWalkedLabel),
	//   //								insideLayout.createParallelGroup(buttonsPushedDescriptionLabel,			buttonsPushedLabel),
	//   //								insideLayout.createParallelGroup(globalRankingDescriptionLabel,			globalRankingLabel),
	//   //								insideLayout.createParallelGroup(regionalRankingDescriptionLabel,		regionalRankingLabel),
	//   //								insideLayout.createParallelGroup(pointsEarnedDescriptionLabel,			pointsEarnedLabel),
	//   //								insideLayout.createParallelGroup(gamesPurchasedDescriptionLabel,		gamesPurchasedLabel),
	//   //								insideLayout.createParallelGroup(gamesSoldDescriptionLabel,				gamesSoldLabel),
	//   //								insideLayout.createParallelGroup(friendsInGameDescriptionLabel,			friendsInGameLabel),
	//   //								insideLayout.createParallelGroup(totalGamesPlayedDescriptionLabel,		totalGamesPlayedLabel),
	//   //								insideLayout.createParallelGroup(timesChallengedDescriptionLabel,		timesChallengedLabel),
	//   //								insideLayout.createParallelGroup(timesChallengerDescriptionLabel,		timesChallengerLabel),
	//   //								insideLayout.createParallelGroup(timesWonDescriptionLabel,				timesWonLabel),
	//   //								insideLayout.createParallelGroup(timesLostDescriptionLabel,				timesLostLabel),
	//   //								insideLayout.createParallelGroup(betsWonDescriptionLabel,				betsWonLabel),
	//   //								insideLayout.createParallelGroup(betsLostDescriptionLabel,				betsLostLabel)
}

void StatusPanel::doGoPremiumButton()
{ //=========================================================================================================================
	//
	//   if (Main::isApplet == true)
	//   {
	//      //open with javascript
	//
	//      URL* url = nullptr;
	//      try
	//      {
	//         url = new URL("http://www.bobsgame.com/buyOKPass.php?u=" + getGameSave()->userID);
	//      }
	//      catch (MalformedURLException e)
	//      {
	//         e->printStackTrace();
	//      }
	//
	//      Main::mainObject->getAppletContext().showDocument(url, "_blank");
	//   }
	//   else
	//   {
	//      try
	//      {
	//         //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
	//         string url = "http://www.bobsgame.com/buyOKPass.php?u=" + getGameSave()->userID;
	//
	//         java::awt::Desktop::getDesktop().browse(java::net::URI::create(url));
	//      }
	//      catch (java::io::IOException e)
	//      {
	//         log->error("Could not open browser: " + e->getMessage());
	//      }
	//   }
}

void StatusPanel::doAddMoneyButton()
{ //=========================================================================================================================

	//
	//   if (Main::isApplet == true)
	//   {
	//      //open with javascript
	//
	//      URL* url = nullptr;
	//      try
	//      {
	//         url = new URL("http://www.bobsgame.com/buyOKCoins.php?u=" + getGameSave()->userID);
	//      }
	//      catch (MalformedURLException e)
	//      {
	//         e->printStackTrace();
	//      }
	//
	//      Main::mainObject->getAppletContext().showDocument(url, "_blank");
	//   }
	//   else
	//   {
	//      try
	//      {
	//         //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
	//         string url = "http://www.bobsgame.com/buyOKCoins.php?u=" + getGameSave()->userID;
	//
	//         java::awt::Desktop::getDesktop().browse(java::net::URI::create(url));
	//      }
	//      catch (java::io::IOException e)
	//      {
	//         log->error("Could not open browser: " + e->getMessage());
	//      }
	//   }
}

void StatusPanel::doEditCharacterButton()
{ //=========================================================================================================================
	getStuffMenu()->setActivated(false);

	getPlayerEditMenu()->setActivated(true);
}

void StatusPanel::init()
{ //=========================================================================================================================
	SubPanel::init();
	//getGUI().setTooltipDelay(1);
}

void StatusPanel::layout()
{ //=========================================================================================================================

	//
	//   //Login panel is centered
	//
	//   //panel.adjustSize();
	//   //panel.setPosition(
	//   //insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - panel.getWidth()) / 2,
	//   //insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - panel.getHeight()) / 2);
	//
	//   if (facebookDialogLayout->isVisible() == true)
	//   {
	//      facebookDialogLayout->adjustSize();
	//   }
	//   else
	//   {
	//      facebookDialogLayout->setSize(0, 0);
	//   }

	SubPanel::layout();
}

void StatusPanel::setVisible(bool b)
{ //=========================================================================================================================
	SubPanel::setVisible(b);

	//
	//   if (b == true)
	//   {
	//      //String birthdayString = "?";
	//      //if(getGameSave()->birthdayTime>0)birthdayString = make_shared<SimpleDateFormat>("yyyy-MM-dd").format(make_shared<Date>(getGameSave()->birthdayTime));
	//
	//      string accountCreatedTimeString = "?";
	//      if (getGameSave()->accountCreatedTime > 0)
	//      {
	//         accountCreatedTimeString = (make_shared<SimpleDateFormat>("yyyy-MM-dd-HH:mm"))->format(make_shared<Date>(getGameSave()->accountCreatedTime));
	//      }
	//
	//      string lastLoginTimeString = "?";
	//      if (getGameSave()->lastLoginTime > 0)
	//      {
	//         lastLoginTimeString = (make_shared<SimpleDateFormat>("yyyy-MM-dd-HH:mm"))->format(make_shared<Date>(getGameSave()->lastLoginTime));
	//      }
	//
	//      string accountTypeString = ClientEngine()->getAccountTypeString(getGameSave()->accountType);
	//
	//
	//      string moneyString = string::format("%1$,.2f", getGameSave()->money);
	//
	//
	//      //update labels
	//      moneyLabel->setText("" + moneyString);
	//      accountTypeLabel->setText("" + accountTypeString);
	//
	//      characterNameLabel->setText("" + getGameSave()->characterName);
	//      emailAddressLabel->setText("" + getGameSave()->emailAddress);
	//
	//      accountCreatedTimeLabel->setText("" + accountCreatedTimeString);
	//      lastLoginTimeLabel->setText("" + lastLoginTimeString);
	//      timesLoggedInLabel->setText("" + getGameSave()->timesLoggedIn);
	//      lastIPLabel->setText("" + getGameSave()->lastIP);
	//      //realNameLabel.setText(""+getGameSave()->realName);
	//      //birthdayTimeLabel.setText(""+birthdayString);
	//      postalCodeLabel->setText("" + getGameSave()->postalCode);
	//      countryNameLabel->setText("" + getGameSave()->countryName);
	//      isoCountryCodeLabel->setText("" + getGameSave()->isoCountryCode);
	//      placeNameLabel->setText("" + getGameSave()->placeName);
	//      stateNameLabel->setText("" + getGameSave()->stateName);
	//      latLabel->setText("" + getGameSave()->lat);
	//      lonLabel->setText("" + getGameSave()->lon);
	//      timeZoneLabel->setText("" + to_string(Main::mainObject->timeZoneGMTOffset));
	//
	//      postalCodeLabel->setText("" + getGameSave()->postalCode);
	//      stateNameLabel->setText("" + getGameSave()->stateName);
	//      countryNameLabel->setText("" + getGameSave()->countryName);
	//
	//
	//      if (getGameSave()->facebookID.length() > 0)
	//      {
	//         facebookDialogLayout->setVisible(true);
	//
	//         facebookEmailLabel->setText("" + getGameSave()->facebookEmail);
	//         facebookBirthdayLabel->setText("" + getGameSave()->facebookBirthday);
	//         facebookFirstNameLabel->setText("" + getGameSave()->facebookFirstName);
	//         facebookLastNameLabel->setText("" + getGameSave()->facebookLastName);
	//         facebookGenderLabel->setText("" + getGameSave()->facebookGender);
	//         facebookLocaleLabel->setText("" + getGameSave()->facebookLocale);
	//         facebookTimeZoneLabel->setText("" + getGameSave()->facebookTimeZone);
	//         facebookUsernameLabel->setText("" + getGameSave()->facebookUsername);
	//         facebookWebsiteLabel->setText("" + getGameSave()->facebookWebsite);
	//      }
	//      else
	//      {
	//         facebookDialogLayout->setVisible(false);
	//      }
}

