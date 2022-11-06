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

	//   shared_ptr<EditField> emailEditField;
	//
	//   shared_ptr<EditField> passwordEditField;
	//   shared_ptr<EditField> confirmPasswordEditField;
	//
	//
	//   shared_ptr<Button> okButton;
	//   shared_ptr<Button> cancelButton;
	//
	//   string nameString = "";
	//
	//
	//   shared_ptr<DialogLayout> panel;
	//   shared_ptr<DialogLayout> emailDialogLayout;
	//   shared_ptr<DialogLayout> passwordDialogLayout;
	//   shared_ptr<DialogLayout> socialDialogLayout;
	//
	//   shared_ptr<Label> errorLabel;
	//   shared_ptr<Label> statusLabel;
	//
	//
	//   shared_ptr<Label> emailLabel;
	//   shared_ptr<Label> passwordLabel;
	//   shared_ptr<Label> confirmPasswordLabel;
	//
	//
	CreateNewAccountMenuPanel();
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper : public EditField::Callback
	//   {
	//   private:
	//      shared_ptr<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper(shared_ptr<CreateNewAccount> outerInstance);
	//
	//      virtual void callback(int key) override;
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper2 : public EditField::Callback
	//   {
	//   private:
	//      shared_ptr<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper2(shared_ptr<CreateNewAccount> outerInstance);
	//
	//      void callback(int key);
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper3 : public EditField::Callback
	//   {
	//   private:
	//      shared_ptr<CreateNewAccount> outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper3(shared_ptr<CreateNewAccount> outerInstance);
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


	shared_ptr<CreateNewAccountMenuPanel> createNewAccountMenuPanel = nullptr;
	//GUI* createNewAccountGUI = nullptr;


	CreateNewAccountState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

