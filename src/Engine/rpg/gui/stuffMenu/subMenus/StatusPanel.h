//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class StatusPanel : public SubPanel
{
public:
	static Logger log;

	/*
	
	   public int userID=-1;
	   public String emailAddress = "";
	   public String passwordHash = "";
	   public int accountVerified = 0;
	   public String verificationHash = "";
	   public long lastPasswordResetTime = 0;
	   public long accountCreatedTime = 0;
	   public long accountVerifiedTime = 0;
	   public long firstLoginTime = 0;
	   public long lastLoginTime = 0;
	   public long lastLoginTime = 0;
	   public int timesLoggedIn = 0;
	   public String firstIP = "";
	   public String lastIP = "";
	   public String realName = "";
	   public long birthdayTime = 0;
	   public String facebookID = "";
	   public String facebookAccessToken = "";
	   public String facebookEmail = "";
	   public String facebookBirthday = "";
	   public String facebookFirstName = "";
	   public String facebookLastName = "";
	   public String facebookGender = "";
	   public String facebookLocale = "";
	   public Float facebookTimeZone = 0.0f;
	   public String facebookUsername = "";
	   public String facebookWebsite = "";
	
	   public String googlePlusID = "";
	   public String postalCode = "";
	   public String countryName = "";
	   public String isoCountryCode = "";
	   public String placeName = "";
	   public String stateName = "";
	   public float lat = 0;
	   public float lon = 0;
	   public int timeZone = 0;
	   public String notes = "";
	   public String warnings = "";
	   public String avatarIcon = "";
	   public String lastKnownRoom = "";
	   public int lastKnownX = 0;
	   public int lastKnownY = 0;
	   public String startingRoom = "";
	   public long timePlayed = 0;
	   public long pixelsWalked = 0;
	   public int money = 0;
	   public int moneyPurchased = 0;
	   public int realWorldTransactions = 0;
	   public int inGameTransactions = 0;
	   public int timesTalkedToNPCs = 0;
	   public int timesTalkedToOtherPlayers = 0;
	   public String characterAppearance = "";
	   public String characterName = "";
	   public String itemsHeld = "";
	   public String itemsTotalCollected = "";
	   public String itemsPurchased = "";
	*/
	//
	//   sp<Button> editCharacterButton = nullptr;
	//
	//
	//   sp<Label> moneyDescriptionLabel = nullptr;
	//   sp<Label> moneyLabel = nullptr;
	//   sp<Button> addMoneyButton = nullptr;
	//   sp<Label> addMoneyButtonQuestionMark = nullptr;
	//
	//   sp<Label> accountTypeDescriptionLabel = nullptr;
	//   sp<Label> accountTypeLabel = nullptr;
	//   sp<Button> goPremiumButton = nullptr;
	//   sp<Label> goPremiumButtonQuestionMark = nullptr;
	//
	//
	//   //public String characterName = "";
	//   sp<Label> characterNameDescriptionLabel = nullptr;
	//   sp<Label> characterNameLabel = nullptr;
	//
	//
	//   sp<DialogLayout> accountDialogLayout;
	//   sp<Label> accountPanelLabel;
	//
	//
	//   //public String emailAddress = "";
	//   sp<Label> emailAddressDescriptionLabel = nullptr;
	//   sp<Label> emailAddressLabel = nullptr;
	//
	//
	//   //public long accountCreatedTime = 0;
	//   sp<Label> accountCreatedTimeDescriptionLabel = nullptr;
	//   sp<Label> accountCreatedTimeLabel = nullptr;
	//
	//
	//   //public long lastLoginTime = 0;
	//   sp<Label> lastLoginTimeDescriptionLabel = nullptr;
	//   sp<Label> lastLoginTimeLabel = nullptr;
	//
	//
	//   //public int timesLoggedIn = 0;
	//   sp<Label> timesLoggedInDescriptionLabel = nullptr;
	//   sp<Label> timesLoggedInLabel = nullptr;
	//
	//
	//   //public String lastIP = "";
	//   sp<Label> lastIPDescriptionLabel = nullptr;
	//   sp<Label> lastIPLabel = nullptr;
	//
	//
	//   //public String realName = "";
	//   //Label realNameDescriptionLabel = null;
	//   //Label realNameLabel = null;
	//
	//
	//   //public long birthdayTime = 0;
	//   //Label birthdayTimeDescriptionLabel = null;
	//   //Label birthdayTimeLabel = null;
	//
	//
	//   sp<DialogLayout> facebookDialogLayout;
	//   sp<Label> facebookPanelLabel;
	//
	//   //public String facebookEmail = "";
	//   sp<Label> facebookEmailDescriptionLabel = nullptr;
	//   sp<Label> facebookEmailLabel = nullptr;
	//
	//
	//   //public String facebookBirthday = "";
	//   sp<Label> facebookBirthdayDescriptionLabel = nullptr;
	//   sp<Label> facebookBirthdayLabel = nullptr;
	//
	//
	//   //public String facebookFirstName = "";
	//   sp<Label> facebookFirstNameDescriptionLabel = nullptr;
	//   sp<Label> facebookFirstNameLabel = nullptr;
	//
	//
	//   //public String facebookLastName = "";
	//   sp<Label> facebookLastNameDescriptionLabel = nullptr;
	//   sp<Label> facebookLastNameLabel = nullptr;
	//
	//
	//   //public String facebookGender = "";
	//   sp<Label> facebookGenderDescriptionLabel = nullptr;
	//   sp<Label> facebookGenderLabel = nullptr;
	//
	//
	//   //public String facebookLocale = "";
	//   sp<Label> facebookLocaleDescriptionLabel = nullptr;
	//   sp<Label> facebookLocaleLabel = nullptr;
	//
	//
	//   //public Float facebookTimeZone = 0.0f;
	//   sp<Label> facebookTimeZoneDescriptionLabel = nullptr;
	//   sp<Label> facebookTimeZoneLabel = nullptr;
	//
	//
	//   //public String facebookUsername = "";
	//   sp<Label> facebookUsernameDescriptionLabel = nullptr;
	//   sp<Label> facebookUsernameLabel = nullptr;
	//
	//
	//   //public String facebookWebsite = "";
	//   sp<Label> facebookWebsiteDescriptionLabel = nullptr;
	//   sp<Label> facebookWebsiteLabel = nullptr;
	//
	//
	//   sp<DialogLayout> locationDialogLayout;
	//   sp<Label> locationPanelLabel;
	//
	//   //public String postalCode = "";
	//   sp<Label> postalCodeDescriptionLabel = nullptr;
	//   sp<Label> postalCodeLabel = nullptr;
	//
	//   //public String countryName = "";
	//   sp<Label> countryNameDescriptionLabel = nullptr;
	//   sp<Label> countryNameLabel = nullptr;
	//
	//   //public String isoCountryCode = "";
	//   sp<Label> isoCountryCodeDescriptionLabel = nullptr;
	//   sp<Label> isoCountryCodeLabel = nullptr;
	//
	//   //public String placeName = "";
	//   sp<Label> placeNameDescriptionLabel = nullptr;
	//   sp<Label> placeNameLabel = nullptr;
	//
	//
	//   //public String stateName = "";
	//   sp<Label> stateNameDescriptionLabel = nullptr;
	//   sp<Label> stateNameLabel = nullptr;
	//
	//
	//   //public float lat = 0;
	//   sp<Label> latDescriptionLabel = nullptr;
	//   sp<Label> latLabel = nullptr;
	//
	//   //public float lon = 0;
	//   sp<Label> lonDescriptionLabel = nullptr;
	//   sp<Label> lonLabel = nullptr;
	//
	//   //public int timeZone = 0;
	//   sp<Label> timeZoneDescriptionLabel = nullptr;
	//   sp<Label> timeZoneLabel = nullptr;
	//
	//
	//   //Label playerFacebookNameDescriptionLabel = null;
	//   //Label playerFacebookNameLabel = null;
	//
	//   //Label playerGooglePlusNameDescriptionLabel = null;
	//   //Label playerGooglePlusNameLabel = null;
	//
	//   //Label playerTwitterNameDescriptionLabel = null;
	//   //Label playerTwitterNameLabel = null;
	//
	//
	//   //Label totalTimePlayedDescriptionLabel = null;
	//   //Label totalTimePlayedLabel = null;
	//
	//   //Label sessionTimePlayedDescriptionLabel = null;
	//   //Label sessionTimePlayedLabel = null;
	//
	//   //Label averageTimePlayedDescriptionLabel = null;
	//   //Label averageTimePlayedLabel = null;
	//
	//   //Label gamesPurchasedDescriptionLabel = null;
	//   //Label gamesPurchasedLabel = null;
	//
	//   //Label gamesSoldDescriptionLabel = null;
	//   //Label gamesSoldLabel = null;
	//
	//   //Label friendsInGameDescriptionLabel = null;
	//   //Label friendsInGameLabel = null;
	//
	//   //Label totalGamesPlayedDescriptionLabel = null;
	//   //Label totalGamesPlayedLabel = null;
	//
	//   //Label timesChallengedDescriptionLabel = null;
	//   //Label timesChallengedLabel = null;
	//
	//   //Label timesChallengerDescriptionLabel = null;
	//   //Label timesChallengerLabel = null;
	//
	//   //Label timesWonDescriptionLabel = null;
	//   //Label timesWonLabel = null;
	//
	//   //Label timesLostDescriptionLabel = null;
	//   //Label timesLostLabel = null;
	//
	//   //Label betsWonDescriptionLabel = null;
	//   //Label betsWonLabel= null;
	//
	//   //Label betsLostDescriptionLabel = null;
	//   //Label betsLostLabel = null;
	//
	//   //Label pointsEarnedDescriptionLabel = null;
	//   //Label pointsEarnedLabel = null;
	//
	//   //Label globalRankingDescriptionLabel = null;
	//   //Label globalRankingLabel = null;
	//
	//   //Label regionalRankingDescriptionLabel = null;
	//   //Label regionalRankingLabel = null;
	//
	//   //Label stepsWalkedDescriptionLabel = null;
	//   //Label stepsWalkedLabel= null;
	//
	//   //Label buttonsPushedDescriptionLabel = null;
	//   //Label buttonsPushedLabel = null;

	StatusPanel();

protected:
	void doGoPremiumButton();

	void doAddMoneyButton();

	void doEditCharacterButton();

public:
	virtual void init() override;

	virtual void layout() override;

	virtual void setVisible(bool b) override;
};

