//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;



class PlayerEditMenu : public MenuPanel
{
public:
	static Logger log;

	//   shared_ptr<DialogLayout> editPanel;
	//   shared_ptr<DialogLayout> animPanel;
	//
	//   shared_ptr<Label> playerEditPanelLabel;
	//
	//   shared_ptr<Label> errorLabel;
	//   shared_ptr<Label> statusLabel;
	//
	//
	//   shared_ptr<Label> nameLabel;
	//   shared_ptr<EditField> nameEditField;
	//
	//   shared_ptr<Label> zipCodeLabel;
	//   shared_ptr<EditField> zipCodeEditField;
	//
	//
	//   shared_ptr<Label> addSocialAccountsLabel;
	//   shared_ptr<Label> facebookAccountLabel;
	//   shared_ptr<Button> addFacebookAccountButton;
	//
	//   shared_ptr<Label> googlePlusAccountLabel;
	//   //Button addGooglePlusAccountButton;
	//
	//   shared_ptr<Label> genderLabel;
	//   ArrayList<shared_ptr<Label>> genderButtonLabels;
	//   shared_ptr<SimpleIntegerModel> genderOptionModel;
	//   ArrayList<shared_ptr<ToggleButton>> genderButtons;
	//
	//   shared_ptr<Label> countryLabel;
	//   SimpleChangableListModel<string>* countryStrings;
	//   ComboBox<string>* countryComboBox;
	//
	//   shared_ptr<Label> archetypeLabel;
	//   SimpleChangableListModel<string>* archetypeStrings;
	//   ComboBox<string>* archetypeComboBox;
	//
	//   shared_ptr<Label> hairColorLabel;
	//   SimpleChangableListModel<string>* hairColorStrings;
	//   ComboBox<string>* hairColorComboBox;
	//
	//   shared_ptr<Label> skinColorLabel;
	//   SimpleChangableListModel<string>* skinColorStrings;
	//   ComboBox<string>* skinColorComboBox;
	//
	//   shared_ptr<Label> eyeColorLabel;
	//   SimpleChangableListModel<string>* eyeColorStrings;
	//   ComboBox<string>* eyeColorComboBox;
	//
	//   shared_ptr<Label> shirtColorLabel;
	//   SimpleChangableListModel<string>* shirtColorStrings;
	//   ComboBox<string>* shirtColorComboBox;
	//
	//   shared_ptr<Label> pantsColorLabel;
	//   SimpleChangableListModel<string>* pantsColorStrings;
	//   ComboBox<string>* pantsColorComboBox;
	//
	//   shared_ptr<Label> shoeColorLabel;
	//   SimpleChangableListModel<string>* shoeColorStrings;
	//   ComboBox<string>* shoeColorComboBox;
	//
	//   shared_ptr<Button> randomButton;
	//   shared_ptr<Button> okButton;

	string nameString = "";

	int genderIndex = 0;

	int archetypeIndex = 0;
	int hairColorIndex = 0;
	int skinColorIndex = 0;
	int eyeColorIndex = 0;
	int shirtColorIndex = 0;
	int pantsColorIndex = 0;
	int shoeColorIndex = 0;

	shared_ptr<Caption> playerNameCaption = nullptr;

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
		shared_ptr<PlayerEditMenu> outerInstance = nullptr;

	public:
		CallbackAnonymousInnerClassHelper(shared_ptr<PlayerEditMenu> outerInstance);

		virtual void callback(int key);//;
	};

private:
	class CallbackAnonymousInnerClassHelper2// : public EditField::Callback
	{
	private:
		shared_ptr<PlayerEditMenu> outerInstance = nullptr;

	public:
		CallbackAnonymousInnerClassHelper2(shared_ptr<PlayerEditMenu> outerInstance);

		virtual void callback(int key);//;
	};

public:
	void init();

	void setButtonsVisible(bool b);

public:
	class AddressInfo
	{
	private:
		shared_ptr<PlayerEditMenu> outerInstance = nullptr;

	public:
		AddressInfo(shared_ptr<PlayerEditMenu> outerInstance);

		string postalCode = "";
		string stateName = "";
		string placeName = "";

		float lat = 0.0f;
		float lon = 0.0f;
		float timeZone = 0.0f;
	};

public:
	shared_ptr<AddressInfo> queryYahooGeocodingAPI(const string& address);

	shared_ptr<AddressInfo> queryGoogleGeocodingAPI(const string& address);

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

