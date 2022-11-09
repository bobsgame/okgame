//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;






class CreateNewAccountMenuPanel : public MenuPanel
{
	//EditField nameEditField;
public:

	static Logger log;

	//   sp<EditField> emailEditField;
	//
	//   sp<EditField> passwordEditField;
	//   sp<EditField> confirmPasswordEditField;
	//
	//
	//   sp<Button> okButton;
	//   sp<Button> cancelButton;
	//
	//   string nameString = "";
	//
	//
	//   sp<DialogLayout> panel;
	//   sp<DialogLayout> emailDialogLayout;
	//   sp<DialogLayout> passwordDialogLayout;
	//   sp<DialogLayout> socialDialogLayout;
	//
	//   sp<Label> errorLabel;
	//   sp<Label> statusLabel;
	//
	//
	//   sp<Label> emailLabel;
	//   sp<Label> passwordLabel;
	//   sp<Label> confirmPasswordLabel;
	//
	//
	CreateNewAccountMenuPanel();
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper : public EditField::Callback
	//   {
	//   private:
	//      sp<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper(sp<CreateNewAccount> outerInstance);
	//
	//      virtual void callback(int key) override;
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper2 : public EditField::Callback
	//   {
	//   private:
	//      sp<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper2(sp<CreateNewAccount> outerInstance);
	//
	//      void callback(int key);
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper3 : public EditField::Callback
	//   {
	//   private:
	//      sp<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper3(sp<CreateNewAccount> outerInstance);
	//
	//      void callback(int key);
	//   };

public:
	void init();

	void setButtonsVisible(bool b);

	virtual void onScrolledUp() override;

	void doCancel();

	void doCreateAccount();

protected:
	virtual void layout() override;

public:
	virtual void update() override;

	virtual void setActivated(bool b) override;

	virtual void renderBefore() override;

	virtual void render() override;
};





class CreateNewAccountState : public Engine
{
public:

	static Logger log;


	sp<CreateNewAccountMenuPanel> createNewAccountMenuPanel = nullptr;
	//GUI* createNewAccountGUI = nullptr;


	CreateNewAccountState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

