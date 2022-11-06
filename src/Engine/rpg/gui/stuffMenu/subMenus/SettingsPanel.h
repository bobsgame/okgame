//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;



class SettingsPanel : public SubPanel
{
public:

	static Logger log;

	//   shared_ptr<Label> autoZoomLabel;
	//   shared_ptr<ToggleButton>const autoZoomToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> playerPhysicsLabel;
	//   shared_ptr<ToggleButton>const playerPhysicsToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> cameraPhysicsLabel;
	//   shared_ptr<ToggleButton>const cameraPhysicsToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> playerWalkSpeedLabel;
	//   shared_ptr<Scrollbar>const playerWalkSpeedScrollbar = make_shared<Scrollbar>(Scrollbar::Orientation::HORIZONTAL);
	//   shared_ptr<Label>const playerWalkSpeedValueLabel = make_shared<Label>("Default");
	//
	//
	//   shared_ptr<DialogLayout> gameSettingsDialogLayout;
	//
	//
	//   shared_ptr<Label> whiteStatusBarToggleButtonLabel;
	//   shared_ptr<ToggleButton>const whiteThemeToggleButton = make_shared<ToggleButton>("");
	//
	//   //	Label grayscaleToggleButtonLabel;
	//   //	final ToggleButton grayscaleToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> statusBarGlossLabel;
	//   shared_ptr<Scrollbar>const statusBarGlossScrollbar = make_shared<Scrollbar>(Scrollbar::Orientation::HORIZONTAL);
	//   shared_ptr<Label>const statusBarGlossValueLabel = make_shared<Label>("Default");
	//
	//   shared_ptr<DialogLayout> guiSettingsDialogLayout;
	//
	//
	//   shared_ptr<Label> hq2xToggleButtonLabel;
	//   shared_ptr<ToggleButton>const hq2xToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> fboToggleButtonLabel;
	//   shared_ptr<ToggleButton>const fboToggleButton = make_shared<ToggleButton>("");
	//
	//   shared_ptr<Label> shadersToggleButtonLabel;
	//   shared_ptr<ToggleButton>const shadersToggleButton = make_shared<ToggleButton>("");
	//
	//
	//   //	Label gammaScrollbarLabel;
	//   //	final public Scrollbar gammaScrollbar = make_shared<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label gammaScrollbarValueLabel = make_shared<Label>("Default");
	//   //
	//   //
	//   //	Label contrastScrollbarLabel;
	//   //	final public Scrollbar contrastScrollbar = make_shared<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label contrastScrollbarValueLabel = make_shared<Label>("Default");
	//   //
	//   //
	//   //	Label brightnessScrollbarLabel;
	//   //	final public Scrollbar brightnessScrollbar = make_shared<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label brightnessScrollbarValueLabel = make_shared<Label>("Default");
	//   //
	//   //
	//   //	Label saturationScrollbarLabel;
	//   //	final public Scrollbar saturationScrollbar = make_shared<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label saturationScrollbarValueLabel = make_shared<Label>("Default");
	//
	//
	//   shared_ptr<DialogLayout> graphicsSettingsDialogLayout;

	SettingsPanel();

	void initGameSettingsSubPanel();

	void initGUISettingsSubPanel();

	void initGraphicsSettingsSubPanel();

	virtual void layout() override;

	virtual void setVisible(bool b) override;
};

