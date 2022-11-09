//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class PlayerEditMenu : public MenuPanel
{
public:
	static Logger log;

	//   sp<DialogLayout> editPanel;
	//   sp<DialogLayout> animPanel;
	//
	//   sp<Label> playerEditPanelLabel;
	//
	//   sp<Label> errorLabel;
	//   sp<Label> statusLabel;
	//
	//
	//   sp<Label> nameLabel;
	//   sp<EditField> nameEditField;
	//
	//   sp<Label> zipCodeLabel;
	//   sp<EditField> zipCodeEditField;
	//
	//
	//   sp<Label> addSocialAccountsLabel;
	//   sp<Label> facebookAccountLabel;
	//   sp<Button> addFacebookAccountButton;
	//
	//   sp<Label> googlePlusAccountLabel;
	//   //Button addGooglePlusAccountButton;
	//
	//   sp<Label> genderLabel;
	//   ArrayList<sp<Label>> genderButtonLabels;
	//   sp<SimpleIntegerModel> genderOptionModel;
	//   ArrayList<sp<ToggleButton>> genderButtons;
	//
	//   sp<Label> countryLabel;
	//   SimpleChangableListModel<string>* countryStrings;
	//   ComboBox<string>* countryComboBox;
	//
	//   sp<Label> archetypeLabel;
	//   SimpleChangableListModel<string>* archetypeStrings;
	//   ComboBox<string>* archetypeComboBox;
	//
	//   sp<Label> hairColorLabel;
	//   SimpleChangableListModel<string>* hairColorStrings;
	//   ComboBox<string>* hairColorComboBox;
	//
	//   sp<Label> skinColorLabel;
	//   SimpleChangableListModel<string>* skinColorStrings;
	//   ComboBox<string>* skinColorComboBox;
	//
	//   sp<Label> eyeColorLabel;
	//   SimpleChangableListModel<string>* eyeColorStrings;
	//   ComboBox<string>* eyeColorComboBox;
	//
	//   sp<Label> shirtColorLabel;
	//   SimpleChangableListModel<string>* shirtColorStrings;
	//   ComboBox<string>* shirtColorComboBox;
	//
	//   sp<Label> pantsColorLabel;
	//   SimpleChangableListModel<string>* pantsColorStrings;
	//   ComboBox<string>* pantsColorComboBox;
	//
	//   sp<Label> shoeColorLabel;
	//   SimpleChangableListModel<string>* shoeColorStrings;
	//   ComboBox<string>* shoeColorComboBox;
	//
	//   sp<Button> randomButton;
	//   sp<Button> okButton;

	string nameString = "";

	int genderIndex = 0;

	int archetypeIndex = 0;
	int hairColorIndex = 0;
	int skinColorIndex = 0;
	int eyeColorIndex = 0;
	int shirtColorIndex = 0;
	int pantsColorIndex = 0;
	int shoeColorIndex = 0;

	sp<Caption> playerNameCaption = nullptr;

	bool initRandom = false;

	long long lastTime = 0;
	int frame = 0;

	int direction = 0;
	int loopCount = 0;

	PlayerEditMenu();

private:
	class CallbackAnonymousInnerClassHelper// : public EditField::Callback
	{
	private:
		sp<PlayerEditMenu> outerInstance = nullptr;

	public:
		CallbackAnonymousInnerClassHelper(sp<PlayerEditMenu> outerInstance);

		virtual void callback(int key);//;
	};

private:
	class CallbackAnonymousInnerClassHelper2// : public EditField::Callback
	{
	private:
		sp<PlayerEditMenu> outerInstance = nullptr;

	public:
		CallbackAnonymousInnerClassHelper2(sp<PlayerEditMenu> outerInstance);

		virtual void callback(int key);//;
	};

public:
	void init();

	void setButtonsVisible(bool b);

public:
	class AddressInfo
	{
	private:
		sp<PlayerEditMenu> outerInstance = nullptr;

	public:
		AddressInfo(sp<PlayerEditMenu> outerInstance);

		string postalCode = "";
		string stateName = "";
		string placeName = "";

		float lat = 0.0f;
		float lon = 0.0f;
		float timeZone = 0.0f;
	};

public:
	sp<AddressInfo> queryYahooGeocodingAPI(const string& address);

	sp<AddressInfo> queryGoogleGeocodingAPI(const string& address);

	void doOKButton();

	void linkFacebookAccount();

	void redrawPlayer();

	void setRandomOptions();

protected:
	virtual void layout();

public:
	virtual void setActivated(bool b);

	virtual void update();

	virtual void render();
};

