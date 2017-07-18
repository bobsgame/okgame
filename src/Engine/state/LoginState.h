//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class LoginMenuPanel;


class LoginState : public Engine
{
public:

	static Logger log;


	//GUI* loginScreenGUI = nullptr;
	LoginMenuPanel* loginMenuPanel = nullptr;


	LoginState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};





class Main;

class LoginMenuPanel : public MenuPanel
{
public:
	static Logger log;


	BobMenu *loginMenu = nullptr;
	int loginMenuCursorPosition = 0;
	bool textStarted = false;
	string userNameOrEmailText = "";
	string userNameText = "";
	string emailText = "";
	string passwordText = "";
	string passwordStarsText = "";
	string confirmPasswordText = "";
	string confirmPasswordStarsText = "";
	bool stayLoggedIn = true;

	Caption* errorLabel = nullptr;
	Caption* statusLabel = nullptr;

	int lastMX = 0;
	int lastMY = 0;

	//   DialogLayout* loginPanel;
	//   EditField* emailEditField;
	//   EditField* passwordEditField;
	//   Button* loginWithFacebookButton;
	//   Button* loginButton;
	//   Button* createNewAccountButton;
	//   Button* forgotPasswordButton;
	//
	//   Label* errorLabel;
	//   Label* statusLabel;
	//
	//
	//   Label* emailLabel;
	//   Label* passwordLabel;
	//
	bool loggedIn = false;
	//bool leaveMenu = false;
	bool createNewAccount = false;
	//
	//
	//   Label* sendStatsQuestionMark;
	//
	//   Label* stayLoggedInToggleButtonLabel;
	//   ToggleButton*const stayLoggedInToggleButton = new ToggleButton("");
	//
	//   Label* sendStatsToggleButtonLabel;
	//   ToggleButton*const sendStatsToggleButton = new ToggleButton("");
	//
	//
	LoginMenuPanel(Engine* e);
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper : public EditField::Callback
	//   {
	//   private:
	//      LoginScreen* outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper(LoginScreen* outerInstance);
	//
	//      void callback(int key);
	//   };


public:
	virtual void update() override;


	virtual void onScrolledUp() override;


protected:
	virtual void layout() override;


public:
	void setButtonsVisible(bool b);


	void doLoginWithFacebook();


	//void doCreateNewAccount();


	void doForgotPassword();


	void doLogin();


	//TODO: write these to a cookie and an applet ini if the user wants to remain logged in.

	//if we are running as an application, we should use the Preferences API or write a file to the cache dir


	//if we are running as an applet
	//browser cookies are only accessible through JSObject

	//we can use the JNLP PersistenceService

	//or use CookieManager to send an URL request and set and read cookies sent from the server (this only stays in memory in application, in applet it uses browser CookieStore)
	//it might be possible to read the browser cookies using this, i'm not sure.

	//it also may write browser cookies as an applet, because it uses the browser cookieStore, using this:
	//URLConnection conn = url.openConnection();
	//conn.setRequestProperty("cookie", cookie_val);


	//or get the cookies from the browser with JSObject
	//or pass the session in through params to the applet using JS or PHP
	//...or sign the applet and use the same as the application

	//applet login should set a browser cookie, can do this through JSObject or maybe through CookieManager? check this.


	void checkForSessionTokenAndLogInIfExists();


	void showStatsDialogue();


	virtual void renderBefore() override;


	virtual void render() override;
};
