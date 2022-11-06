#include "stdafx.h"


#include "GameTestMenu.h"

using namespace Gwen;
using namespace Gwen::Controls;

#include "Room.h"




//GWEN_CONTROL_CONSTRUCTOR(GameTestMenuControl)
GameTestMenuControl::GameTestMenuControl(Gwen::Controls::Base* pParent, const Gwen::String& pName, shared_ptr<OKGame >b) : Gwen::Controls::Base(pParent, pName)
{//=========================================================================================================================

	this->bobsGame = b;

	SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	//SetDeleteOnClose(false);
	Dock(Pos::Fill);

	/*
	None
	Left
	Right
	Top
	Bottom
	CenterV
	CenterH
	Fill
	Center
	*/
	//int w = GLUtils::getViewportWidth();
	//int h = GLUtils::getViewportHeight();


	Controls::Label *label = make_shared<Controls>::Label(this);
	label->SetText("You can test and vote on new game types and sequences in this sandbox.");
	label->Dock(Pos::Top);
	label->SetHeight(20);
	
	shared_ptr<Base> checkBase = make_shared<Base>(this);
	checkBase->Dock(Pos::Top);
	checkBase->SetHeight(20);
	{
		Controls::Label *checkLabel = make_shared<Controls>::Label(checkBase);
		checkLabel->SetText("Hide already voted:");
		checkLabel->Dock(Pos::Left);
		checkLabel->SetHeight(20);
		checkLabel->SetWidth(200);

		hideVotedGames = make_shared<CheckBox>(checkLabel, "Hide already voted");
		hideVotedGames->SetChecked(true);
		hideVotedGames->onCheckChanged.Add(this, &GameTestMenuControl::onChangeHideVotedGames);
		hideVotedGames->Dock(Pos::Left);
		hideVotedGames->SetWidth(20);
		hideVotedGames->SetHeight(20);
	}

	mainWindowSplitter = make_shared<Gwen>::Controls::HorizontalSplitter(this);
	mainWindowSplitter->GetSplitter()->onDragged.Add(this, &GameTestMenuControl::doResize);
	mainWindowSplitter->Dock(Pos::Top);

	leftBase = make_shared<Gwen>::Controls::Base(mainWindowSplitter);
	mainWindowSplitter->SetPanel(0, leftBase);
	{

		leftBaseTabControl = make_shared<Controls>::TabControl(leftBase);
		leftBaseTabControl->Dock(Pos::Fill);

		gameTypesTab = leftBaseTabControl->AddPage(L"Single Game Types");
		gameTypesPage = gameTypesTab->GetPage();
		gameTypesPage->Dock(Pos::Fill);


		gameTypesWindow = make_shared<Gwen>::Controls::Base(gameTypesPage);
		gameTypesWindow->SetToolTip("");
		gameTypesWindow->Dock(Pos::Top);
		{

			gameTypesListBoxBase = make_shared<Gwen>::Controls::Base(gameTypesWindow);
			gameTypesListBoxBase->Dock(Pos::Left);
			{
				gameTypesListBox = make_shared<Gwen>::Controls::ListBox(gameTypesListBoxBase);
				gameTypesListBox->Dock(Pos::Fill);
				gameTypesListBox->SetAllowMultiSelect(false);

				populateGameTypesListBox();
			}

		}

		gameSequencesTab = leftBaseTabControl->AddPage(L"Game Sequences");
		gameSequencesPage = gameSequencesTab->GetPage();
		gameSequencesPage->Dock(Pos::Fill);

		gameSequencesWindow = make_shared<Gwen>::Controls::Base(gameSequencesPage);
		gameSequencesWindow->SetToolTip("");
		gameSequencesWindow->Dock(Pos::Top);
		{

			gameSequencesListBoxBase = make_shared<Gwen>::Controls::Base(gameSequencesWindow);
			gameSequencesListBoxBase->Dock(Pos::Left);
			{
				gameSequencesListBox = make_shared<Gwen>::Controls::ListBox(gameSequencesListBoxBase);
				gameSequencesListBox->Dock(Pos::Fill);
				gameSequencesListBox->SetAllowMultiSelect(false);

				populateGameSequencesListBox();

			}

		}
	}

	previewBase = make_shared<Base>(mainWindowSplitter);
	mainWindowSplitter->SetPanel(1, previewBase);
	//previewBase->SetSize(w * 2 / 5, h - 20);
	//previewBase->Dock(Pos::Fill);
	{

		applyButtonsBase = make_shared<Base>(previewBase);
		applyButtonsBase->Dock(Pos::Top);
		applyButtonsBase->SetSize(previewBase->Width(), 20);
		{

			shared_ptr<Base> topBase = make_shared<Base>(applyButtonsBase);
			topBase->Dock(Pos::Top);
			topBase->SetHeight(20);

			selectedGameLabel = make_shared<Controls>::Label(topBase, "label");
			selectedGameLabel->SetText("Current Game Type: None");
			selectedGameLabel->Dock(Pos::Left);
			selectedGameLabel->SetWidth(300);
			selectedGameLabel->SetHeight(25);

			shared_ptr<Base> bottomBase = make_shared<Base>(applyButtonsBase);
			bottomBase->Dock(Pos::Top);
			bottomBase->SetHeight(20);

			previewButton = make_shared<Button>(bottomBase);
			previewButton->SetText(L"Reset");
			previewButton->Dock(Pos::Left | Pos::Center);
			previewButton->SetWidth(100);
			previewButton->onPress.Add(this, &GameTestMenuControl::onPreviewButton);

			difficultyCombo = make_shared<ComboBox>(bottomBase,"difficultyCombo");
			GameType g;
			for(int i=0;i<g.difficultyTypes.size();i++)difficultyCombo->AddItem(Gwen::Utility::StringToUnicode(g.difficultyTypes.get(i)->name));
			difficultyCombo->Dock(Pos::Left);
			difficultyCombo->SetHeight(25);
			difficultyCombo->onSelection.Add(this, &GameTestMenuControl::onChangeDifficulty);
			
			upVoteButton = make_shared<Button>(bottomBase);
			upVoteButton->SetText(L"Up Vote");
			upVoteButton->Dock(Pos::Left | Pos::Center);
			upVoteButton->SetWidth(100);
			upVoteButton->onPress.Add(this, &GameTestMenuControl::onUpVoteButton);

			downVoteButton = make_shared<Button>(bottomBase);
			downVoteButton->SetText(L"Down Vote");
			downVoteButton->Dock(Pos::Left | Pos::Center);
			downVoteButton->SetWidth(100);
			downVoteButton->onPress.Add(this, &GameTestMenuControl::onDownVoteButton);


			exitButton = make_shared<Button>(bottomBase);
			exitButton->SetText(L"Exit To Title Screen");
			//exitButton->SetToolTip("Leave (Ask to save changes).");
			exitButton->Dock(Pos::Right | Pos::Center);
			exitButton->SetWidth(150);
			exitButton->onPress.Add(this, &GameTestMenuControl::onExitButton);


			//load, save, preview, exit



			//on load
			//edit
			//copy to new
			//create new game
			//cancel


		}


		darkRectangle = make_shared<GameTestPreviewRectangle>(previewBase, "", bobsGame);
		darkRectangle->SetColor(Color(0, 0, 0, 255));
		darkRectangle->Dock(Pos::Top);
		darkRectangle->SetSize(previewBase->Width(), previewBase->Height() - 20);
	}

	GetParent()->SizeToChildren();
	SizeToChildren();

	doResize();

}



void GameTestMenuControl::checkResize()
{//=========================================================================================================================
	if (lastW != GLUtils::getViewportWidth() || lastH != GLUtils::getViewportHeight())
	{

		doResize();

		lastW = GLUtils::getViewportWidth();
		lastH = GLUtils::getViewportHeight();

	}
}
void GameTestMenuControl::doResize()
{//=========================================================================================================================

	SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	GetParent()->SizeToChildren();

	int w = GLUtils::getViewportWidth();
	int h = GLUtils::getViewportHeight();
	{

		mainWindowSplitter->SetSize(w, h - 20);
		{
			int sw = mainWindowSplitter->GetSplitter()->X();
			if (500 > sw)sw = 500;
			leftBase->SetSize(sw, mainWindowSplitter->Height());
			{
				gameTypesWindow->SetSize(leftBase->Width(), leftBase->Height());
				{
					gameTypesListBoxBase->SetSize(gameTypesWindow->Width() - 100, gameTypesWindow->Height());
					{
						gameTypesListBox->SetSize(gameTypesListBoxBase->Width() - 30, gameTypesListBoxBase->Height() - 60);
					}
				}
				gameSequencesWindow->SetSize(leftBase->Width(), leftBase->Height());
				{
					gameSequencesListBoxBase->SetSize(gameSequencesWindow->Width() - 100, gameSequencesWindow->Height());
					{
						gameSequencesListBox->SetSize(gameSequencesListBoxBase->Width() - 30, gameSequencesListBoxBase->Height() - 60);
					}
				}
			}

			previewBase->SetSize(w * 2 / 5, h - 20);
			{
				applyButtonsBase->SetSize(previewBase->Width(), 40);
				darkRectangle->SetSize(previewBase->Width(), previewBase->Height() - 40);
			}
		}
	}

	SizeToChildren(true, true);

}

#include <fstream>
#include <iostream>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;


//shared_ptr<GameSequence> GameTestMenuControl::getGameSequenceByName(string name)
//{//=========================================================================================================================
//
//	shared_ptr<GameSequence >bt = nullptr;
//	for (int i = 0; i<bobsGame->loadedGameSequences.size(); i++)
//	{
//		shared_ptr<GameSequence >b = bobsGame->loadedGameSequences.get(i);
//		if (b->name == name)
//		{
//			bt = b;
//		}
//	}
//	return bt;
//
//}

void GameTestMenuControl::populateGameTypesListBox()
{//=========================================================================================================================

	gameTypesListBox->Clear();
	GetCanvas()->DoThink();

	ArrayList<pair<shared_ptr<GameType>, pair<string, shared_ptr<OKColor>>>> gamesStringColor = bobsGame->getSortedGameTypes();
	for (int i = 0; i < gamesStringColor.size(); i++)
	{
		pair<shared_ptr<GameType>, pair<string, shared_ptr<OKColor>>> gameTypeStringColorPairPair = gamesStringColor.get(i);
		shared_ptr<GameType >g = gameTypeStringColorPairPair.first;
		pair<string, shared_ptr<OKColor>> stringColorPair = gameTypeStringColorPairPair.second;
		string name = stringColorPair.first;
		shared_ptr<OKColor >color = stringColorPair.second;

		//if (g->builtInType)
//		{
//			if (hideVotedGames->IsChecked())continue;
//		}
		if (g->downloaded == false)
		{
			if (hideVotedGames->IsChecked())continue;
		}
		if (g->yourVote!="none" && hideVotedGames->IsChecked())continue;

		if (g->yourVote == "up")name = "(Upvoted) " + name;
		if (g->yourVote == "down")name = "(Downvoted) " + name;

		Layout::TableRow *row = gameTypesListBox->AddItem(name, g->uuid);
		row->onRowSelected.Add(this, &GameTestMenuControl::onGameTypesListSelect);
		if (g->yourVote!="none")row->SetTextColor(Gwen::Color(128, 128, 128));
		else row->SetTextColor(Gwen::Color(color->ri(), color->gi(), color->bi()));

	}

}

void GameTestMenuControl::populateGameSequencesListBox()
{//=========================================================================================================================

	gameSequencesListBox->Clear();
	GetCanvas()->DoThink();

	ArrayList<pair<shared_ptr<GameSequence>, pair<string, shared_ptr<OKColor>>>> gamesStringColor = bobsGame->getSortedGameSequences();
	for (int i = 0; i < gamesStringColor.size(); i++)
	{
		pair<shared_ptr<GameSequence>, pair<string, shared_ptr<OKColor>>> gameSequenceStringColorPairPair = gamesStringColor.get(i);
		shared_ptr<GameSequence >g = gameSequenceStringColorPairPair.first;
		pair<string, shared_ptr<OKColor>> stringColorPair = gameSequenceStringColorPairPair.second;
		string name = stringColorPair.first;
		shared_ptr<OKColor >color = stringColorPair.second;

//		if (g->builtInType)
//		{
//			if (hideVotedGames->IsChecked())continue;
//		}
		if (g->downloaded == false)
		{
			if (hideVotedGames->IsChecked())continue;
		}
		if (g->yourVote!="none" && hideVotedGames->IsChecked())continue;

		if (g->yourVote == "up")name = "(Upvoted) " + name;
		if (g->yourVote == "down")name = "(Downvoted) " + name;

		Layout::TableRow *row = gameSequencesListBox->AddItem(name, g->uuid);
		row->onRowSelected.Add(this, &GameTestMenuControl::onGameSequencesListSelect);
		if (g->yourVote!="none")row->SetTextColor(Gwen::Color(128, 128, 128));
		else row->SetTextColor(Gwen::Color(color->ri(), color->gi(), color->bi()));

	}
}

void GameTestMenuControl::onGameTypesListSelect(shared_ptr<Base> control)
{//=========================================================================================================================

	Layout::TableRow* row = (Layout::TableRow*)control;
	string uuid = row->GetName().c_str();

	shared_ptr<GameType >s = bobsGame->getGameTypeByUUID(uuid);

	if (s == nullptr)
	{
		OKGame::log->error("Could not find game type with uuid:" + uuid);
		return;
	}

	currentGameSequence = make_shared<GameSequence>();
	currentGameSequence->gameTypes.add(s);

	selectedGameLabel->SetText(Utility::StringToUnicode("Current Game Type:"+s->name));
	initPreviewGame();
}

void GameTestMenuControl::onGameSequencesListSelect(shared_ptr<Base> control)
{//=========================================================================================================================

	Layout::TableRow* row = (Layout::TableRow*)control;
	string uuid = row->GetName().c_str();

	shared_ptr<GameSequence >s = bobsGame->getGameSequenceByUUID(uuid);

	if (s == nullptr)
	{
		OKGame::log->error("Could not find game sequence with uuid:" + uuid);
		return;
	}

	currentGameSequence = s;
	selectedGameLabel->SetText(Utility::StringToUnicode("Current Game Sequence:" + s->name));

	initPreviewGame();

}


void GameTestMenuControl::onExitButton(shared_ptr<Base> control)
{//=========================================================================================================================
	exit = true;
}

//=========================================================================================================================
void GameTestMenuControl::vote(bool upDown)
{//=========================================================================================================================

	string uuid = "";

	string vote = "up";
	if (upDown == false)vote = "down";

	if (currentGameSequence->gameTypes.size() == 1)
	{
		uuid = currentGameSequence->gameTypes.get(0)->uuid;
		bobsGame->getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::OK_Game_GameTypesAndSequences_Vote_Request + "GameType:" + uuid + ":" +vote+":"+ OKNet::endline);
	}
	else
	{
		uuid = currentGameSequence->uuid;
		bobsGame->getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::OK_Game_GameTypesAndSequences_Vote_Request + "GameSequence:" + uuid + ":" + vote + ":" + OKNet::endline);
	}


	string response = "";
	int tries = 0;
	while (tries<10)
	{
		tries++;
		Main::delay(500);
		response = bobsGame->getServerConnection()->getAndResetOKGameGameTypesAndSequencesVoteResponse_S();
		if (response != "")
		{
			break;
		}
	}

	if (response == "")response = "Did not get a response from the server. Try again later.";
	else
	{
		if (currentGameSequence->gameTypes.size() == 1)
		{
			if(upDown)currentGameSequence->gameTypes.get(0)->yourVote = "up";
			else currentGameSequence->gameTypes.get(0)->yourVote = "down";
		}
		else
		{
			if (upDown)currentGameSequence->yourVote = "up";
			else currentGameSequence->yourVote = "down";
		}
	}
	
	shared_ptr<WindowControl >result = make_shared<WindowControl>(GetCanvas());
	result->SetTitle("Result");
	result->SetSize(300, 60);
	result->MakeModal(true);
	result->SetPos(GLUtils::getViewportWidth() / 2 - 150, GLUtils::getViewportHeight() / 2 - 30);
	result->SetDeleteOnClose(true);

	shared_ptr<Label> label = make_shared<Label>(result);
	label->SetText(response);
	label->Dock(Pos::Fill);

	populateGameTypesListBox();
	populateGameSequencesListBox();

}

void GameTestMenuControl::onUpVoteButton(shared_ptr<Base> control)
{//=========================================================================================================================

	vote(true);

}

void GameTestMenuControl::onDownVoteButton(shared_ptr<Base> control)
{//=========================================================================================================================

	vote(false);

}


//=========================================================================================================================
void GameTestMenuControl::onPreviewButton(shared_ptr<Base> control)
{//=========================================================================================================================
 //we basically already have the settings in memory so we can just create a new game instance and set the currentGameType to these ones
 //but we need to make a game sequence that is only this game

	initPreviewGame();
}
//=========================================================================================================================
void GameTestMenuControl::onChangeDifficulty(shared_ptr<Base> control)
{//=========================================================================================================================
	initPreviewGame();
}
//=========================================================================================================================
void GameTestMenuControl::onChangeHideVotedGames(shared_ptr<Base> control)
{//=========================================================================================================================
	

	populateGameTypesListBox();
	populateGameSequencesListBox();

}

//=========================================================================================================================
void GameTestMenuControl::initPreviewGame()
{//=========================================================================================================================


 //need to render game board into fbo
	bobsGame->initPlayer();

	if (currentGameSequence == nullptr)
	{
		currentGameSequence = make_shared<GameSequence>();
	}
	if(currentGameSequence->gameTypes.size()==0)
	{
		

		shared_ptr<GameType >g = make_shared<GameType>();
		shared_ptr<BlockType> bt(make_shared<BlockType>());
		bt->name = "Gray Square";
		bt->colors.add(OKColor::gray);
		bt->useInNormalPieces = true;
		bt->useAsPlayingFieldFiller = true;
		bt->useAsGarbage = true;
		shared_ptr<PieceType> pt(make_shared<PieceType>());
		pt->name = "Single Block Piece";
		pt->useAsNormalPiece = true;
		pt->useAsPlayingFieldFillerPiece = true;
		pt->useAsGarbagePiece = true;
		g->blockTypes.add(bt);
		g->pieceTypes.add(pt);

		currentGameSequence->gameTypes.add(g);
	}

	
	bobsGame->getPlayer1Game()->currentGameType = (currentGameSequence->gameTypes.get(0));
	bobsGame->getPlayer1Game()->currentGameSequence = currentGameSequence;
	bobsGame->getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyCombo->GetSelectedItem()->GetText().c_str();
	bobsGame->currentRoom->endlessMode = true;
	


}


//=========================================================================================================================
void GameTestPreviewRectangle::Render(Skin::Base* skin)
{//=========================================================================================================================


	m_Color = Gwen::Color(0, 0, 0, 255);
	skin->GetRender()->SetDrawColor(m_Color);
	skin->GetRender()->DrawFilledRect(GetRenderBounds());

	if (bobsGame->gameTestMenu->windowOpen)return;
	m_Color = Gwen::Color(255, 255, 255, 255);
	skin->GetRender()->SetDrawColor(m_Color);
	//glPushMatrix();
	//glLoadIdentity();
	//bobsGame->setOKGameFBOSize();
	//bobsGame->renderGameIntoFBO(bobsGame->getPlayer1Game());
	//float x0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->X()).x;
	//float x1 = x0 + customGameEditor->darkRectangle->Width();
	//float y0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->Y()).y;
	//float y1 = y0 + customGameEditor->darkRectangle->Height();

	//GLUtils::bindFBO(0);
	//GLUtils::drawIntoFBOAttachment(GLUtils::preColorFilterFBO); //draw to nD FBO screen texture
	//GLUtils::setPreColorFilterViewport();
	//bobsGame->drawOKGameFBO(x0, x1, y0, y1);
	//bobsGame->drawOKGameFBO(0,Width(),0,Height());
	//glPopMatrix();
	//customGameEditor->renderRotationPreview(skin);

	//glPushMatrix();
	//glLoadIdentity();
	//GLUtils::setPreColorFilterViewport();
	Gwen::Texture *t = make_shared<Gwen>::Texture();
	t->data = (shared_ptr<GLuint>)&GLUtils::bobsGame_mainGameFBO_Texture_Attachment0;
	skin->GetRender()->DrawTexturedRect(t, Gwen::Rect(0, Height(), Width(), 0 - Height()));
	delete t;
	//glPopMatrix();
}


//=========================================================================================================================
void OKGame::gameTestMenuUpdate()
{//=========================================================================================================================

 //	if (gameTestMenuMenu == nullptr)
 //	{
 //		gameTestMenuMenu = make_shared<Menu>(this);
 //
 //		gameTestMenuMenu->add("Back To Game", "Back To Game", OKColor::white);
 //		gameTestMenuMenu->add("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%", "Music Volume", OKColor::white);
 //		gameTestMenuMenu->add("Quit Game And Return To Title Screen", "Quit Game And Return To Title Screen", OKColor::white);
 //
 //		gameTestMenuMenu->cursorPosition = gameTestMenuMenuCursorPosition;
 //	}

	if (gameTestMenu == nullptr)
	{
		gameTestMenu = make_shared<GameTestMenuControl>(Main::gwenCanvas, "GameTestMenuControl", this);

		gameTestMenu->initPreviewGame();

		gameTestMenu->doResize();
	}



	bool leaveMenu = false;

	if (gameTestMenu != nullptr)
	{

		gameTestMenu->checkResize();

		if (gameTestMenu->windowOpen == false)
		{
			getPlayer1Game()->update(0, 1, gameTestMenu->darkRectangle->Width(), gameTestMenu->darkRectangle->Height());
		}

		if (gameTestMenu->exit == true)
		{

			//remove unsaved game sequences
			//			for (int i = 0; i<loadedGameSequences.size(); i++)
			//			{
			//				if (loadedGameSequences.get(i)->loadedFilename == "")
			//				{
			//					loadedGameSequences.removeAt(i);
			//					i--;
			//				}
			//			}

			leaveMenu = true;
			delete gameTestMenu;
			gameTestMenu = nullptr;
		}
	}




	//	if (getControlsManager()->miniGame_UP_Pressed())
	//	{
	//		gameTestMenuMenu->up();
	//	}
	//
	//	if (getControlsManager()->miniGame_DOWN_Pressed())
	//	{
	//		gameTestMenuMenu->down();
	//	}
	//

	//
	//	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	//	{
	//
	//		if (gameTestMenuMenu->isSelectedID("Quit Game And Return To Title Screen"))
	//		{
	//			leaveMenu = true;
	//			titleMenuShowing = true;
	//			initPlayer();
	//		}
	//
	//	}
	//
	//	if (getControlsManager()->miniGame_CANCEL_Pressed())
	//	{
	//		leaveMenu = true;
	//	}

	if (leaveMenu)
	{
		initPlayer();

		gameTestMenuShowing = false;

		startScreenMenuShowing = true;

	}
}

//=========================================================================================================================
void OKGame::gameTestMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);
	//
	//	shared_ptr<OKTexture> t = keyboardTexture;
	//
	//	if (gameTestMenuMenu == nullptr)return;
	//
	//	if (t != nullptr)
	//	{
	//		gameTestMenuMenu->setGraphic(t, getWidth() / 8 * 6, getHeight() / 10);
	//	}
	//
	//	gameTestMenuMenu->render();

	Main::gwenCanvas->RenderCanvas();

	if (gameTestMenu != nullptr)
	{


		//need to be able to force an FBO size
		//i should give each gamelogic its own captionmanager and render the captions in the fbo with the game 
		//so that the internals of the game doesn't need to know where it is on screen at all

		if (gameTestMenu->windowOpen == false)
		{
			setOKGameFBOSize();
			renderGameIntoFBO(getPlayer1Game(), true);
			//		float x0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->X()).x;
			//		float x1 = x0 + customGameEditor->darkRectangle->Width();
			//		float y0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->Y()).y;
			//		float y1 = y0 + customGameEditor->darkRectangle->Height();
			//
			GLUtils::bindFBO(GLUtils::preColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			GLUtils::setPreColorFilterViewport();
			//		drawOKGameFBO(x0, x1, y0, y1);



		}
	}

}


