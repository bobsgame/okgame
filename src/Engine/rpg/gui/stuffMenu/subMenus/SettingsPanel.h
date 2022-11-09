//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class SettingsPanel : public SubPanel
{
public:

	static Logger log;

	//   sp<Label> autoZoomLabel;
	//   sp<ToggleButton>const autoZoomToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> playerPhysicsLabel;
	//   sp<ToggleButton>const playerPhysicsToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> cameraPhysicsLabel;
	//   sp<ToggleButton>const cameraPhysicsToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> playerWalkSpeedLabel;
	//   sp<Scrollbar>const playerWalkSpeedScrollbar = ms<Scrollbar>(Scrollbar::Orientation::HORIZONTAL);
	//   sp<Label>const playerWalkSpeedValueLabel = ms<Label>("Default");
	//
	//
	//   sp<DialogLayout> gameSettingsDialogLayout;
	//
	//
	//   sp<Label> whiteStatusBarToggleButtonLabel;
	//   sp<ToggleButton>const whiteThemeToggleButton = ms<ToggleButton>("");
	//
	//   //	Label grayscaleToggleButtonLabel;
	//   //	final ToggleButton grayscaleToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> statusBarGlossLabel;
	//   sp<Scrollbar>const statusBarGlossScrollbar = ms<Scrollbar>(Scrollbar::Orientation::HORIZONTAL);
	//   sp<Label>const statusBarGlossValueLabel = ms<Label>("Default");
	//
	//   sp<DialogLayout> guiSettingsDialogLayout;
	//
	//
	//   sp<Label> hq2xToggleButtonLabel;
	//   sp<ToggleButton>const hq2xToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> fboToggleButtonLabel;
	//   sp<ToggleButton>const fboToggleButton = ms<ToggleButton>("");
	//
	//   sp<Label> shadersToggleButtonLabel;
	//   sp<ToggleButton>const shadersToggleButton = ms<ToggleButton>("");
	//
	//
	//   //	Label gammaScrollbarLabel;
	//   //	final public Scrollbar gammaScrollbar = ms<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label gammaScrollbarValueLabel = ms<Label>("Default");
	//   //
	//   //
	//   //	Label contrastScrollbarLabel;
	//   //	final public Scrollbar contrastScrollbar = ms<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label contrastScrollbarValueLabel = ms<Label>("Default");
	//   //
	//   //
	//   //	Label brightnessScrollbarLabel;
	//   //	final public Scrollbar brightnessScrollbar = ms<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label brightnessScrollbarValueLabel = ms<Label>("Default");
	//   //
	//   //
	//   //	Label saturationScrollbarLabel;
	//   //	final public Scrollbar saturationScrollbar = ms<Scrollbar>(Orientation.HORIZONTAL);
	//   //	final Label saturationScrollbarValueLabel = ms<Label>("Default");
	//
	//
	//   sp<DialogLayout> graphicsSettingsDialogLayout;

	SettingsPanel();

	void initGameSettingsSubPanel();

	void initGUISettingsSubPanel();

	void initGraphicsSettingsSubPanel();

	virtual void layout() override;

	virtual void setVisible(bool b) override;
};

