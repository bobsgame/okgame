//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
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
	//   shared_ptr<Button> editCharacterButton = nullptr;
	//
	//
	//   shared_ptr<Label> moneyDescriptionLabel = nullptr;
	//   shared_ptr<Label> moneyLabel = nullptr;
	//   shared_ptr<Button> addMoneyButton = nullptr;
	//   shared_ptr<Label> addMoneyButtonQuestionMark = nullptr;
	//
	//   shared_ptr<Label> accountTypeDescriptionLabel = nullptr;
	//   shared_ptr<Label> accountTypeLabel = nullptr;
	//   shared_ptr<Button> goPremiumButton = nullptr;
	//   shared_ptr<Label> goPremiumButtonQuestionMark = nullptr;
	//
	//
	//   //public String characterName = "";
	//   shared_ptr<Label> characterNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> characterNameLabel = nullptr;
	//
	//
	//   shared_ptr<DialogLayout> accountDialogLayout;
	//   shared_ptr<Label> accountPanelLabel;
	//
	//
	//   //public String emailAddress = "";
	//   shared_ptr<Label> emailAddressDescriptionLabel = nullptr;
	//   shared_ptr<Label> emailAddressLabel = nullptr;
	//
	//
	//   //public long accountCreatedTime = 0;
	//   shared_ptr<Label> accountCreatedTimeDescriptionLabel = nullptr;
	//   shared_ptr<Label> accountCreatedTimeLabel = nullptr;
	//
	//
	//   //public long lastLoginTime = 0;
	//   shared_ptr<Label> lastLoginTimeDescriptionLabel = nullptr;
	//   shared_ptr<Label> lastLoginTimeLabel = nullptr;
	//
	//
	//   //public int timesLoggedIn = 0;
	//   shared_ptr<Label> timesLoggedInDescriptionLabel = nullptr;
	//   shared_ptr<Label> timesLoggedInLabel = nullptr;
	//
	//
	//   //public String lastIP = "";
	//   shared_ptr<Label> lastIPDescriptionLabel = nullptr;
	//   shared_ptr<Label> lastIPLabel = nullptr;
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
	//   shared_ptr<DialogLayout> facebookDialogLayout;
	//   shared_ptr<Label> facebookPanelLabel;
	//
	//   //public String facebookEmail = "";
	//   shared_ptr<Label> facebookEmailDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookEmailLabel = nullptr;
	//
	//
	//   //public String facebookBirthday = "";
	//   shared_ptr<Label> facebookBirthdayDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookBirthdayLabel = nullptr;
	//
	//
	//   //public String facebookFirstName = "";
	//   shared_ptr<Label> facebookFirstNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookFirstNameLabel = nullptr;
	//
	//
	//   //public String facebookLastName = "";
	//   shared_ptr<Label> facebookLastNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookLastNameLabel = nullptr;
	//
	//
	//   //public String facebookGender = "";
	//   shared_ptr<Label> facebookGenderDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookGenderLabel = nullptr;
	//
	//
	//   //public String facebookLocale = "";
	//   shared_ptr<Label> facebookLocaleDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookLocaleLabel = nullptr;
	//
	//
	//   //public Float facebookTimeZone = 0.0f;
	//   shared_ptr<Label> facebookTimeZoneDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookTimeZoneLabel = nullptr;
	//
	//
	//   //public String facebookUsername = "";
	//   shared_ptr<Label> facebookUsernameDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookUsernameLabel = nullptr;
	//
	//
	//   //public String facebookWebsite = "";
	//   shared_ptr<Label> facebookWebsiteDescriptionLabel = nullptr;
	//   shared_ptr<Label> facebookWebsiteLabel = nullptr;
	//
	//
	//   shared_ptr<DialogLayout> locationDialogLayout;
	//   shared_ptr<Label> locationPanelLabel;
	//
	//   //public String postalCode = "";
	//   shared_ptr<Label> postalCodeDescriptionLabel = nullptr;
	//   shared_ptr<Label> postalCodeLabel = nullptr;
	//
	//   //public String countryName = "";
	//   shared_ptr<Label> countryNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> countryNameLabel = nullptr;
	//
	//   //public String isoCountryCode = "";
	//   shared_ptr<Label> isoCountryCodeDescriptionLabel = nullptr;
	//   shared_ptr<Label> isoCountryCodeLabel = nullptr;
	//
	//   //public String placeName = "";
	//   shared_ptr<Label> placeNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> placeNameLabel = nullptr;
	//
	//
	//   //public String stateName = "";
	//   shared_ptr<Label> stateNameDescriptionLabel = nullptr;
	//   shared_ptr<Label> stateNameLabel = nullptr;
	//
	//
	//   //public float lat = 0;
	//   shared_ptr<Label> latDescriptionLabel = nullptr;
	//   shared_ptr<Label> latLabel = nullptr;
	//
	//   //public float lon = 0;
	//   shared_ptr<Label> lonDescriptionLabel = nullptr;
	//   shared_ptr<Label> lonLabel = nullptr;
	//
	//   //public int timeZone = 0;
	//   shared_ptr<Label> timeZoneDescriptionLabel = nullptr;
	//   shared_ptr<Label> timeZoneLabel = nullptr;
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

