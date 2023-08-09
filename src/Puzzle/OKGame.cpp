#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



Logger OKGame::log = Logger("OKGame");
//sp<OKGame> OKGame::b = nullptr;

sp<OKTexture> OKGame::upperLeft = nullptr;
sp<OKTexture> OKGame::top = nullptr;
sp<OKTexture> OKGame::upperRight = nullptr;
sp<OKTexture> OKGame::left = nullptr;
sp<OKTexture> OKGame::right = nullptr;
sp<OKTexture> OKGame::lowerLeft = nullptr;
sp<OKTexture> OKGame::bottom = nullptr;
sp<OKTexture> OKGame::lowerRight = nullptr;

bool OKGame::_gotIncomingGamesFromServer = false;
mutex OKGame::_gotIncomingGamesFromServer_Mutex;
queue<sp<GameType>>OKGame::_incomingGameTypes;
mutex OKGame::_incomingGameTypes_Mutex;
queue<sp<GameSequence>>OKGame::_incomingGameSequences;
mutex OKGame::_incomingGameSequences_Mutex;
sp<vector<sp<GameType>>> OKGame::loadedGameTypes;
sp<vector<sp<GameSequence>>> OKGame::loadedGameSequences;
sp<vector<sp<Sprite>>> OKGame::loadedSprites;


sp<vector<sp<OKGameUserStatsForSpecificGameAndDifficulty>>> OKGame::userStatsPerGameAndDifficulty;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topPlayersByTotalTimePlayed;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topPlayersByTotalBlocksCleared;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topPlayersByPlaneswalkerPoints;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topPlayersByEloScore;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topGamesByTimeLasted;
sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>> OKGame::topGamesByBlocksCleared;


sp<vector<string>> OKGame::activityStream;



#include "Stats/GameStats.h"

//=========================================================================================================================
OKGame::OKGame()
{//=========================================================================================================================

#ifdef _DEBUG
	log.debug("OKGame()");
#endif

	//constructors are called from the base class up, so State->Engine->GameEngine->OKGame

}
//=========================================================================================================================
OKGame::OKGame(ND* nD)
{//=========================================================================================================================

#ifdef _DEBUG
	log.debug("OKGame()");
#endif

	this->nD = nD;

}

//=========================================================================================================================
OKGame::~OKGame()
{//=========================================================================================================================
#ifdef _DEBUG
	log.debug("~OKGame()");
#endif

	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);

		if (p->gameLogic != nullptr)
		{
			p->gameLogic->deleteAllCaptions();
		}

		//delete p->gameLogic;
		p->gameLogic = nullptr;

		//delete p;
		p = nullptr;

	}

	players->clear();

}




//=========================================================================================================================
void OKGame::init()
{//=========================================================================================================================

	super::init();

#ifdef _DEBUG
	log.debug("OKGame::init()");
#endif

	//the reason why i have an init function is because i can control the order of the subclass/superclass calling
	//in the regular constructor, it calls the base class first, so it will always be called State->Engine->GameEngine->OKGame
	//but by using the init function I can call them specifically in any order that I want

  //oh it is also so that i can call init code from multiple constructors, oops

	
	initAssets();


	

	log.debug("Init Player");
	initPlayer();



	//music = ms<Music>(this, "data/music/slick_v10.ogg");
	music = getAudioManager()->playMusic("slick_v10");
	music->setVolume((((float)Main::globalSettings->musicVolume) / 100.0f));

	//	games.put(randomSeed,ME);
	//	player2 = ms<Game>(this);
	//	player2.controlledByNetwork = true;
	//	games->push_back(player2);

}

//=========================================================================================================================
void OKGame::initPlayer()
{//=========================================================================================================================
	for (int i = 0; i<players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);

		if (p->gameLogic != nullptr)
		{
			p->gameLogic->deleteAllCaptions();
		}

		//delete p->gameLogic;
		p->gameLogic = nullptr;

		//delete p;
		p = nullptr;

		//for simulator connection
		//if(friend==null&&connection!=null)OKGame::setConnection(connection);

		//		nD.setGame(bobsgame);
		//		this.nD = null;
		//
		//		if(isNetworkGame())
		//		{
		//			if(connection!=null)setConnection(null);
		//			if(friend!=null)
		//			{
		//				friend.setGameToForwardPacketsTo(null);
		//				friend = null;
		//			}
		//		}

	}
	players->clear();

	sp<PuzzlePlayer>p = ms<PuzzlePlayer>(ms<GameLogic>(this, -1));
	
	p->useKeyboard = true;
	//if (getControlsManager()->gameControllers->size() > 0)p->gameController = getControlsManager()->gameControllers->at(0);
	players->push_back(p);

	if (currentRoom == nullptr)currentRoom = ms<Room>();

	//randomSeed = p->game->randomSeed;
	//originalSettings = p->game->getCurrentGameType();
}

//=========================================================================================================================
bool OKGame::isMultiplayer()
{//=========================================================================================================================
	if (networkMultiplayer)return true;
	if (localMultiplayer)return true;
	if (players->size() > 1)return true;
	return false;
}



//=========================================================================================================================
bool OKGame::isNetworkGame()
{//=========================================================================================================================
	for (int i = 0; i < players->size(); i++)
	{
		if (players->at(i)->isNetworkPlayer())return true;
	}
	if (networkMultiplayer)return true;
	return false;
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

//=========================================================================================================================
void OKGame::initAssets()
{//=========================================================================================================================

	log.debug("OKGame::initAssets");

	Uint64 start=0, now=0, totalStart, totalNow;
	start = SDL_GetPerformanceCounter();
	totalStart = SDL_GetPerformanceCounter();

	log.debug("Loading icons");
	keyboardTexture = GLUtils::getTextureFromPNGExePath("data/theme/keyboard.png");
	controllerTexture = GLUtils::getTextureFromPNGExePath("data/theme/controller.png");
	controllerIconTexture = GLUtils::getTextureFromPNGExePath("data/theme/controllerIcon.png");
	keyboardIconTexture = GLUtils::getTextureFromPNGExePath("data/theme/keyboardIcon.png");
	onlineTexture = GLUtils::getTextureFromPNGExePath("data/theme/online.png");
	networkIconTexture = GLUtils::getTextureFromPNGExePath("data/theme/networkIcon.png");
	gearsTexture = GLUtils::getTextureFromPNGExePath("data/theme/gears.png");
	chartTexture = GLUtils::getTextureFromPNGExePath("data/theme/chart.png");

	log.debug("Loading frame");
	upperLeft = GLUtils::getTextureFromPNGExePath("data/frame/frame1-ul.png");
	top = GLUtils::getTextureFromPNGExePath("data/frame/frame1-u.png");
	upperRight = GLUtils::getTextureFromPNGExePath("data/frame/frame1-ur.png");
	left = GLUtils::getTextureFromPNGExePath("data/frame/frame1-l.png");
	right = GLUtils::getTextureFromPNGExePath("data/frame/frame1-r.png");
	lowerLeft = GLUtils::getTextureFromPNGExePath("data/frame/frame1-dl.png");
	bottom = GLUtils::getTextureFromPNGExePath("data/frame/frame1-d.png");
	lowerRight = GLUtils::getTextureFromPNGExePath("data/frame/frame1-dr.png");

	now = SDL_GetPerformanceCounter();
	log.debug("Loading graphics took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();

	log.debug("Loading sprites");



	//done: load sprite text files regardless of names
	//load all txt files from sprites folder
	string spriteFolderString = Main::getPath() + "data/sprite/";
	Path spriteFolderPath(spriteFolderString);
	File spriteFolderPathDir(spriteFolderPath);
	if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
	vector<string>files;
	spriteFolderPathDir.list(files);
	vector<string>::iterator it = files.begin();
	for (; it != files.end(); ++it)
	{
		//cout << *it << endl;
		string name = *it;
		if (name.find(".txt") != string::npos)
		{
			string nameWithoutExtension = name.substr(0, name.find(".txt"));
			loadedSprites->push_back(spriteManager->preloadSpriteFromDataFile(nameWithoutExtension));
		}
	}

	now = SDL_GetPerformanceCounter();
	log.debug("Loading sprites took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();



	//spriteManager.preloadSpriteFromFile("bobsGameLogoSmall");


	log.debug("Loading GameTypes and GameSequences");

	loadGameTypesFromXML();
	loadGameSequencesFromXML();

	updateVersion0ToVersion1();

	now = SDL_GetPerformanceCounter();
	log.debug("Loading GameTypes and GameSequences took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();


	totalNow = SDL_GetPerformanceCounter();
	log.debug("OKGame::initAssets took " + to_string((double)((totalNow - totalStart) * 1000) / SDL_GetPerformanceFrequency()) + "ms");



}


//=========================================================================================================================
sp<Sprite> OKGame::getSpriteFromName(const string& name)
{//=========================================================================================================================

	return spriteManager->getSpriteByName(name);

}

//=========================================================================================================================
sp<GameLogic> OKGame::getPlayer1Game()
{//=========================================================================================================================
	return players->at(0)->gameLogic;
}
//=========================================================================================================================
sp<PuzzlePlayer> OKGame::getPlayer1()
{//=========================================================================================================================
	return players->at(0);
}
//=========================================================================================================================
void OKGame::setOKGameFBOSize()
{//=========================================================================================================================
	//let's size the game FBO to the board size, which means sizing the bloom FBO and others

	//calculate the needed board size
	//if FBOs are not that size, resize the FBOs, that also means rendering the game into that size

	//draw each game to an FBO, then draw it to the main screen

	//make this into a function so that i can apply it to the custom game preview

	//ok, so when i calculate the playing field size, let's do that here instead of inside the game itself, and then set the internal size within the game
	//then we can do things like if(preview) use this size, if(singleplayer) fullscreen, if multiplayer do this size

	float w = getPlayer1Game()->playingFieldX1 - getPlayer1Game()->playingFieldX0;
	float h = getPlayer1Game()->playingFieldY1 - getPlayer1Game()->playingFieldY0;

	if (GLUtils::bobsGameFBO_Width != w || GLUtils::bobsGameFBO_Height != h)
	{
		GLUtils::resizeOKGameFBO(w, h);
	}
}

//=========================================================================================================================
void OKGame::renderGameIntoFBO(sp<GameLogic> g, bool useColorFilter)
{//=========================================================================================================================

	GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
	GLUtils::drawIntoFBOAttachment(0); //draw to mainGameFBO texture
	GLUtils::setOKGameMainFBOFilterViewport();

	//clear the main game FBO since we used it to draw the previous game
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	g->renderBackground();//draw the background into the main fbo

	//render the playing field blocks to a FBO
	//draw the FBO to the screen with blur shader and 50% alpha
	//draw the FBO to the screen
	if (GLUtils::useShaders)
	{
		GLUtils::drawIntoFBOAttachment(1); // draw to bloom mask texture
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);
	}

	g->renderBlocks(); //draw blocks into bloom mask texture

	if (GLUtils::useShaders)
	{

		GLUtils::bindFBO(GLUtils::bobsGame_bloomFBO);
		//GLUtils::drawIntoFBOAttachment(0);
		GLUtils::setBloomViewport();

		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(false);

		GLUtils::drawIntoFBOAttachment(1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);//clear both ping pong textures

		GLUtils::drawIntoFBOAttachment(0); //draw to bloom FBO texture 0
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);


		GLUtils::useShader(GLUtils::bloomMaskShader);

		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);//has the blocks in it
		GLUtils::setShaderVar1i(GLUtils::bloomMaskShader, (char*)"u_texture0", 0);
		float threshold = 0.1f;
		GLUtils::setShaderVar2f(GLUtils::bloomMaskShader, (char*)"treshold", threshold, 1.0f / (1.0f - threshold));

		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);//draw the blocks into ping pong 0

		GLUtils::useShader(0);


		int blurPasses = g->currentGameType->bloomTimes;
		for (int n = 0; n < blurPasses; n++)//blur the blocks
		{
			// horizontal
			GLUtils::drawIntoFBOAttachment(1);
			{
				GLUtils::useShader(GLUtils::gaussianShader);
				{
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"size", GLUtils::bobsGameFBO_Width*GLUtils::BLOOM_FBO_SCALE, GLUtils::bobsGameFBO_Height* GLUtils::BLOOM_FBO_SCALE);
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"dir", 1.0f, 0.0f);
					GLUtils::drawTexture(GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);
				}
				GLUtils::useShader(0);
			}

			// vertical
			GLUtils::drawIntoFBOAttachment(0);
			{
				GLUtils::useShader(GLUtils::gaussianShader);
				{
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"size", GLUtils::bobsGameFBO_Width*GLUtils::BLOOM_FBO_SCALE, GLUtils::bobsGameFBO_Height* GLUtils::BLOOM_FBO_SCALE);
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"dir", 0.0f, 1.0f);
					GLUtils::drawTexture(GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils::DEFAULT_BLOOM_FBO_FILTER);

				}
				GLUtils::useShader(0);
			}
		}


		GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
		GLUtils::drawIntoFBOAttachment(0); //draw to mainFBO texture 0, has the playing field
		GLUtils::setOKGameMainFBOFilterViewport();

		glEnable(GL_BLEND);
		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0);//has blurred blocks in it

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);//has original blocks in it

		float bloomIntensity = g->currentGameType->bloomIntensity;

//		float w = g->playingFieldX1 - g->playingFieldX0;
//		float h = g->playingFieldY1 - g->playingFieldY0;
//		log.debug(to_string(w));
//		log.debug(to_string(h));
//		log.debug(to_string(GLUtils::bobsGameFBO_Width));
//		log.debug(to_string(GLUtils::bobsGameFBO_Height));

		GLUtils::useShader(GLUtils::bloomShader);//draw the blurred and original blocks with bloom on top of shaders and playing field
		{
			GLUtils::setShaderVar1f(GLUtils::bloomShader, (char*)"OriginalIntensity", 0.8f);
			GLUtils::setShaderVar1f(GLUtils::bloomShader, (char*)"BloomIntensity", bloomIntensity);
			GLUtils::setShaderVar1i(GLUtils::bloomShader, (char*)"u_texture0", 0);//original blocks
			GLUtils::setShaderVar1i(GLUtils::bloomShader, (char*)"u_texture1", 1);//blurred blocks
			GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);
		}
		GLUtils::useShader(0);

		//disable texture2D on texture unit 1
		glActiveTexture(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);

		//switch back to texture unit 0
		glActiveTexture(GL_TEXTURE0);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);

		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	g->renderForeground();
	
	if(players->size()==1 && Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer)
	{
		g->renderHighScoreMeters();
	}

	if (useColorFilter)
	{
		captionManager->render(RenderOrder::ABOVE);
		captionManager->render(RenderOrder::ABOVE_TOP);
		captionManager->render(RenderOrder::OVER_TEXT);
		captionManager->render(RenderOrder::OVER_GUI);
//		for (int i = 0; i < players->size(); i++)
//		{
//			sp<PuzzlePlayer>p = players->at(i);
//			sp<GameLogic>g = p->gameLogic;
//			g->getCaptionManager()->render(RenderOrder::ABOVE);
//			g->getCaptionManager()->render(RenderOrder::ABOVE_TOP);
//			g->getCaptionManager()->render(RenderOrder::OVER_TEXT);
//			g->getCaptionManager()->render(RenderOrder::OVER_GUI);
//		}

		//let's now draw the main fbo into the mask fbo with the color shader, then back to the main fbo
		GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
		GLUtils::drawIntoFBOAttachment(1);
		GLUtils::setOKGameMainFBOFilterViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLUtils::drawIntoFBOAttachment(0);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (GLUtils::useShaders)
		{
			GLUtils::useShader(GLUtils::colorShader);


			//ignore global settings and use default so custom games dont use user settings and are more accurate
			GlobalSettings gs;
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", gs.hue);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", gs.saturation);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", gs.brightness);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", gs.contrast);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", gs.gamma);
			GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
		}
		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (GLUtils::useShaders)
		{
			GLUtils::useShader(0);
		}

		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}

//=========================================================================================================================
void OKGame::drawOKGameFBO(float x0, float x1, float y0, float y1)
{//=========================================================================================================================

	GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);

	GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

//int clearToggle = 0;
//
//#ifdef _DEBUG
//if (Main::getMain()->controlsManager->key_NUM1_Pressed())
//{
//	clearToggle++;
//	if (clearToggle > 4)clearToggle = 0;
//	log.debug("ClearToggle: " + to_string(clearToggle));
//}
//
//if (clearToggle == 0)
//{
//
//}
//if (clearToggle == 1)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//if (clearToggle == 2)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//if (clearToggle == 3)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//if (clearToggle == 4)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//#endif
//=========================================================================================================================
void OKGame::render()
{//=========================================================================================================================


	GLUtils::bindFBO(GLUtils::preColorFilterFBO);
	GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
	GLUtils::setPreColorFilterViewport();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
	glClear(GL_COLOR_BUFFER_BIT);

	if (renderMenus() == true)
	{

		//render game captions
//		{
//			//super::render();
//			captionManager->render(RenderOrder::ABOVE);
//			captionManager->render(RenderOrder::ABOVE_TOP);
//			captionManager->render(RenderOrder::OVER_TEXT);
			captionManager->render(RenderOrder::OVER_GUI);
//			for (int i = 0; i < players->size(); i++)
//			{
//				sp<PuzzlePlayer>p = players->at(i);
//				sp<GameLogic>g = p->gameLogic;
//				g->getCaptionManager()->render(RenderOrder::OVER_GUI);
//			}
//		}



		//--------------------------
		// draw MAIN FBO texture into SCREEN BUFFER
		//--------------------------
		GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
		GLUtils::setRealWindowViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);

		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	else
	{

		if (GLUtils::useShaders)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glEnable(GL_DEPTH_TEST);

			bgShaderFBOTextureToggle = !bgShaderFBOTextureToggle;

			GLUtils::bindFBO(GLUtils::bobsGame_bgShaderFBO);
			if (bgShaderFBOTextureToggle)
			{
				GLUtils::drawIntoFBOAttachment(0);
			}
			else
			{
				GLUtils::drawIntoFBOAttachment(1);
			}

			GLUtils::setShaderViewport();
			float tempDrawScale = GLUtils::globalDrawScale;
			GLUtils::globalDrawScale = 1.0f;

			glActiveTexture(GL_TEXTURE1);
			glEnable(GL_TEXTURE_2D);

			if (bgShaderFBOTextureToggle)
			{
				glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bgShaderFBO_Texture_Attachment1);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bgShaderFBO_Texture_Attachment0);
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);

			//clear the shader bg
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
			glClear(GL_COLOR_BUFFER_BIT);


			long long startTime = timeRenderBegan;
			long long currentTime = System::currentHighResTimer();
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			float time = (float)(ticksPassed / 2000.0f);

			int shaderInt = GLUtils::bgShaders->at(shaderCount)->value();

			GLUtils::useShader(shaderInt);
			GLUtils::setShaderVar2f(shaderInt, (char*)"resolution", (float)GLUtils::getViewportWidth()*GLUtils::SHADER_FBO_SCALE, (float)GLUtils::getViewportHeight()*GLUtils::SHADER_FBO_SCALE);
			GLUtils::setShaderVar2f(shaderInt, (char*)"mouse", 0.5f, 0.5f);
			GLUtils::setShaderVar1f(shaderInt, (char*)"time", time);
			GLUtils::setShaderVar1i(shaderInt, (char*)"tex0", 0);
			GLUtils::setShaderVar1i(shaderInt, (char*)"backbuffer", 1);
			GLUtils::setShaderVar1i(shaderInt, (char*)"bb", 1);
			//GLUtils.setShaderVar1i(GLUtils.fractalShader, "tex1"), 1);

			GLUtils::drawFilledRect(255, 255, 255, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f);

			GLUtils::useShader(0);

			glDisable(GL_DEPTH_TEST);

			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			GLUtils::bindFBO(GLUtils::postColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			GLUtils::setPostColorFilterViewport();
			GLUtils::globalDrawScale = tempDrawScale;

			//clear the preColor FBO
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (bgShaderFBOTextureToggle)
			{
				GLUtils::drawTexture(GLUtils::bobsGame_bgShaderFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f, GLUtils::DEFAULT_SHADER_FBO_FILTER);
			}
			else
			{
				GLUtils::drawTexture(GLUtils::bobsGame_bgShaderFBO_Texture_Attachment1, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f, GLUtils::DEFAULT_SHADER_FBO_FILTER);
			}

			//draw transparent black to darken background
			GLUtils::drawFilledRect(0, 0, 0, 0, (float)getWidth(), 0, (float)getHeight(), 0.3f);
		}

		setOKGameFBOSize();

		for (int i = 0; i < players->size(); i++)
		{

			sp<PuzzlePlayer>p = players->at(i);
			sp<GameLogic>g = p->gameLogic;

			//render into mainGameFBO
			renderGameIntoFBO(g, false);

			//draw the mainGameFBO to the preColorFilterFBO in the correct place with correct size
			GLUtils::bindFBO(GLUtils::postColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0);
			GLUtils::setPostColorFilterViewport();

			if (GLUtils::useShaders)
			{
				GLUtils::useShader(GLUtils::colorShader);

				GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", Main::globalSettings->hue * p->hue);
				GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", Main::globalSettings->saturation);
				GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", Main::globalSettings->brightness);
				GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", Main::globalSettings->contrast);
				GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", Main::globalSettings->gamma);
				GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
			}

			drawOKGameFBO(g->playingFieldX0, g->playingFieldX1, g->playingFieldY0, g->playingFieldY1);

			if (GLUtils::useShaders)
			{
				GLUtils::useShader(0);
			}
		}


		//--------------------------
		//set main FBO
		//--------------------------

//		GLUtils::bindFBO(GLUtils::postColorFilterFBO); //set the framebuffer object to the MAIN FBO
//		GLUtils::drawIntoFBOAttachment(0); //set which framebuffer object to draw into (whatever buffer is set with glBindFramebuffer)
//
//		//--------------------------
//		//set main viewport
//		//--------------------------
//		GLUtils::setPostColorFilterViewport();
//
//		//--------------------------
//		// draw ND FBO texture into MAIN FBO
//		//--------------------------
//
//		if (GLUtils::useShaders)
//		{
//			GLUtils::useShader(GLUtils::colorShader);
//
//			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", Main::globalSettings->hue * p->hue);
//			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", Main::globalSettings->saturation);
//			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", Main::globalSettings->brightness);
//			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", Main::globalSettings->contrast);
//			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", Main::globalSettings->gamma);
//			GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
//		}
//
//		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//		GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)(GLUtils::getViewportWidth()), 0, (float)(GLUtils::getViewportHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
//		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//		if (GLUtils::useShaders)
//		{
//			GLUtils::useShader(0);
//		}

		//render game captions
		{
			//super::render();
			captionManager->render(RenderOrder::ABOVE);
			captionManager->render(RenderOrder::ABOVE_TOP);
			captionManager->render(RenderOrder::OVER_TEXT);
			captionManager->render(RenderOrder::OVER_GUI);
//			for (int i = 0; i < players->size(); i++)
//			{
//				sp<PuzzlePlayer>p = players->at(i);
//				sp<GameLogic>g = p->gameLogic;
//				g->getCaptionManager()->render(RenderOrder::ABOVE);
//				g->getCaptionManager()->render(RenderOrder::ABOVE_TOP);
//				g->getCaptionManager()->render(RenderOrder::OVER_TEXT);
//				g->getCaptionManager()->render(RenderOrder::OVER_GUI);
//			}
		}

		for (int i = 0; i < players->size(); i++)
		{
			sp<PuzzlePlayer>p = players->at(i);

			if (p->gameLogic->pauseMiniMenuShowing)playerPauseMiniMenuRender(p, p->gameLogic->playingFieldX0, p->gameLogic->playingFieldX1, p->gameLogic->playingFieldY0, p->gameLogic->playingFieldY1);;
		}

		if (pauseMenuShowing == true)
		{
			pauseMenuRender();
		}

		if(voteMenu!=nullptr)
		{
			voteMenu->render(GLUtils::getViewportHeight()/2 + 100);
		}

		if(statsUploadMenu!=nullptr)
		{
			statsUploadMenu->render(GLUtils::getViewportHeight()/2 + 100,0,getHeight(),false);
		}

		//--------------------------
		// draw MAIN FBO texture into SCREEN BUFFER
		//--------------------------
		GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
		GLUtils::setRealWindowViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //this fixes the small shadow problems, and also makes the doorknob glow brighter.
		GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

}

//=========================================================================================================================
void OKGame::debugKeys()
{//=========================================================================================================================


	if (getControlsManager()->key_F1_Pressed())
	{
		shaderCount++;
		if (shaderCount >= GLUtils::bgShaderCount)shaderCount = 0;
		log.info("Shader: " + to_string(shaderCount));
		Main::console->add("Shader: " + to_string(shaderCount), 10000);

		getPlayer1Game()->updateCaptions();
	}

#ifdef _DEBUG
	if (getControlsManager()->key_F2_Pressed())
	{
		getPlayer1Game()->changeGame();
		getPlayer1Game()->updateCaptions();
	}

	if (getControlsManager()->key_1_Pressed() == true)
	{
		Main::globalSettings->hue -= 0.1f;
		Main::console->debug("Hue: " + to_string(Main::globalSettings->hue), 1000);
	}

	if (getControlsManager()->key_2_Pressed() == true)
	{
		Main::globalSettings->hue += 0.1f;
		Main::console->debug("Hue: " + to_string(Main::globalSettings->hue), 1000);
	}

	if (getControlsManager()->key_3_Pressed() == true)
	{
		Main::globalSettings->contrast -= 0.1f;
		Main::console->debug("Contrast: " + to_string(Main::globalSettings->contrast), 1000);
	}

	if (getControlsManager()->key_4_Pressed() == true)
	{
		Main::globalSettings->contrast += 0.1f;
		Main::console->debug("Contrast: " + to_string(Main::globalSettings->contrast), 1000);
	}

	if (getControlsManager()->key_5_Pressed() == true)
	{
		Main::globalSettings->
			brightness -= 0.1f;
		Main::console->debug("Brightness: " + to_string(Main::globalSettings->brightness), 1000);
	}

	if (getControlsManager()->key_6_Pressed() == true)
	{
		Main::globalSettings->brightness += 0.1f;
		Main::console->debug("Brightness: " + to_string(Main::globalSettings->brightness), 1000);
	}

	if (getControlsManager()->key_7_Pressed() == true)
	{
		Main::globalSettings->saturation -= 0.1f;
		Main::console->debug("Saturation: " + to_string(Main::globalSettings->saturation), 1000);
	}

	if (getControlsManager()->key_8_Pressed() == true)
	{
		Main::globalSettings->saturation += 0.1f;
		Main::console->debug("Saturation: " + to_string(Main::globalSettings->saturation), 1000);
	}

	if (getControlsManager()->key_9_Pressed() == true)
	{
		Main::globalSettings->gamma -= 0.1f;
		Main::console->debug("Gamma: " + to_string(Main::globalSettings->gamma), 1000);
	}

	if (getControlsManager()->key_0_Pressed() == true)
	{
		Main::globalSettings->gamma += 0.1f;
		Main::console->debug("Gamma: " + to_string(Main::globalSettings->gamma), 1000);
	}

	if (getControlsManager()->key_BACKSPACE_Pressed() == true)
	{
		Main::globalSettings->hue = 1.5f;
		Main::globalSettings->saturation = 1.2f;
		Main::globalSettings->brightness = 1.0f;
		Main::globalSettings->contrast = 1.2f;
		Main::globalSettings->gamma = 1.0f;
		Main::console->debug("Hue: " + to_string(Main::globalSettings->hue) + " | Saturation: " + to_string(Main::globalSettings->saturation) + " | Brightness: " + to_string(Main::globalSettings->brightness) + " | Contrast: " + to_string(Main::globalSettings->contrast) + " | Gamma: " + to_string(Main::globalSettings->gamma), 1000);
	}

#endif

}



//=========================================================================================================================
void OKGame::update()
{//=========================================================================================================================


	if(networkMultiplayerLobbyMenuShowing || networkMultiplayerPlayerJoinMenuShowing)
	{
		if (music->isPlaying() == true)
		{
			music->pause();
		}

	}
	else
	{
		if (music->isPlaying() == false)
		{
			music->unpause();
		}
	}


	debugKeys();

	//super::update();
	{
		captionManager->update();
		audioManager->update();
		spriteManager->update();

		updateChatConsole();
	}

	


	getGameTypesAndSequencesFromServer();


	if (updateMenus() == true)
	{
		return;
	}


	if(pauseMenuShowing==true)
	{
		pauseMenuUpdate();

		return;
	}


	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);

		sp<GameLogic>g = p->gameLogic;

		//actual game update
		g->update(i,(int)players->size());



		//				if (g->lose || g->win)
		//				{
		//					if (currentTime - winOrLoseTime > 5000)
		//					{
		//						if (getControlsManager().BUTTON_SPACE_PRESSED)
		//						{
		//							newGame();
		//						}
		//					}
		//				}
		//				else
		//				{
		//					winOrLoseTime = currentTime;
		//				}

	}

	bool gameOver = false;

	if (players->size() == 1 && players->at(0)->gameLogic->complete)
	{
		gameOver = true;
	}

	bool allPlayersDead = true;
	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);
		if (p->gameLogic->died == false)
		{
			allPlayersDead = false;
		}
	}
	if (allPlayersDead)
	{
		gameOver = true;
	}

	if (currentRoom->multiplayer_GameEndsWhenOnePlayerRemains && players->size()>1)
	{
		int alivePlayers = 0;
		for (int i = 0; i < players->size(); i++)
		{
			sp<PuzzlePlayer>p = players->at(i);
			if (p->gameLogic->died == false)
			{
				alivePlayers++;
			}
		}

		if (alivePlayers == 1)
		{
			for (int i = 0; i < players->size(); i++)
			{
				sp<PuzzlePlayer>p = players->at(i);
				if (p->gameLogic->died == false)
				{
					p->gameLogic->won = true;
				}
			}
			gameOver = true;
		}
	}

	if (currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel && players->size()>1)
	{

		bool someoneWon = false;
		for (int i = 0; i < players->size(); i++)
		{
			sp<PuzzlePlayer>p = players->at(i);
			if (p->gameLogic->complete == true)
			{
				someoneWon = true;
			}
		}

		if (someoneWon)
		{
			for (int i = 0; i < players->size(); i++)
			{
				sp<PuzzlePlayer>p = players->at(i);
				if (p->gameLogic->complete == false)
				{
					p->gameLogic->lost = true;
				}
			}
			gameOver = true;
		}
	}

	if(gameOver)
	{

		sendGameStatsToServer();

		//if single game, check youVoted=="none"
		//if sequence, check
		//if connected to server, make menu to vote up or down
		//has to be single player game because its tied to account

		if (sentStats && gotStatsResponse && statsUploadMenu == nullptr)
		{
			doVoting();
		}
		

		if(sentStats && gotStatsResponse && statsUploadMenu == nullptr && sentVote)
		{

			//if connected to server and authorized
			//if game sequence only has one game type
			//ask to rate game

			if (pressEnterToRestartCaption == nullptr)
			{
				string text = "Press Enter or Start to restart";

				if (isNetworkGame() || players->size() > 1)
				{
					text = "Press Enter or Start to return to lobby";
				}

				pressEnterToRestartCaption = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, getHeight() - 300, -1, text, 32, true, OKColor::white);
				pressEnterToRestartCaption->flashing = true;
				pressEnterToRestartCaption->flashingTicksPerFlash = 2000;
			}

			if (getControlsManager()->miniGame_START_Pressed())
			{
				sentStats = false;
				gotStatsResponse = false;
				sentVote = false;
				

				if (players->size() == 1)
				{
					sp<GameSequence>gs = getPlayer1Game()->currentGameSequence;
					initPlayer();
					getPlayer1Game()->currentGameSequence = gs;
				}
				else
				{
					initPlayer();

					if (isNetworkGame())
					{
						networkMultiplayerLobbyMenuShowing = true;
					}
					else
					{
						localMultiplayerPlayerJoinMenuShowing = true;
					}
				}

				if (pressEnterToRestartCaption != nullptr)
				{
					pressEnterToRestartCaption->setToBeDeletedImmediately();
					pressEnterToRestartCaption = nullptr;
				}
			}
		}
	}
}

#include <chrono>

//=========================================================================================================================
void OKGame::sendGameStatsToServer()
{//=========================================================================================================================


	if (
		getServerConnection()->getConnectedToServer_S() == false || 
		getServerConnection()->getAuthorizedOnServer_S() == false
		)
	{
		sentStats = true;
		gotStatsResponse = true;
		
		if(statsUploadMenu !=nullptr)
		{
			//delete statsUploadMenu;
			statsUploadMenu = nullptr;
		}

		return;
	}

	long long currentTime = System::currentHighResTimer();

	if (sentStats==false)
	{

		if (statsUploadMenu == nullptr)
		{
			statsUploadMenu = ms<OKMenu>(this, "Results");
			statsUploadMenu->outline = true;
			statsUploadMenu->defaultMenuColor = OKColor::white;
			statsUploadMenu->setFontSize(24);
			statsUploadMenu->add("Uploading stats to server...", "Status");
		}

		//do stats
		//user stats
		//tell server all game information
		//even include local multiplayer why not
		//include it in "games played" and "time played"

		for (int i = 0; i < players->size(); i++)
		{
			sp<PuzzlePlayer>p = players->at(i);
			if (p->isNetworkPlayer() == false)
			{

				sp<GameLogic>g = p->gameLogic;

				OKGameGameStats s;
				s.userName = g->getEngine()->getUserName_S();
				s.userID = g->getEngine()->getUserID_S();

				if (g->currentGameSequence->gameTypes->size() == 1)
				{
					s.isGameTypeOrSequence = "GameType";
					s.gameTypeName = g->currentGameSequence->gameTypes->at(0)->name;
					s.gameTypeUUID = g->currentGameSequence->gameTypes->at(0)->uuid;
				}
				else
				{
					s.isGameTypeOrSequence = "GameSequence";
					s.gameSequenceName = g->currentGameSequence->name;
					s.gameSequenceUUID = g->currentGameSequence->uuid;
				}
				s.difficultyName = g->currentGameSequence->currentDifficultyName;

				s.gameTypeEndedOnName = g->currentGameType->name;
				s.gameTypeEndedOnUUID = g->currentGameType->uuid;

				s.won = (int)g->won;
				s.lost = (int)g->lost;
				s.died = (int)g->died;
				s.complete = (int)g->complete;
				s.isLocalMultiplayer = (int)localMultiplayer;
				s.isNetworkMultiplayer = (int)networkMultiplayer;
				s.numPlayers = (int)players->size();
				s.level = g->currentLevel;
				s.timeLasted = g->totalTicksPassed;
				s.timeStarted = g->timeStarted;
				if (g->timeEnded == 0)
				{
					chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
					g->timeEnded = (long long)ms.count();
				}
				s.timeEnded = g->timeEnded;
				s.blocksMade = g->blocksMadeTotal;
				s.piecesMade = g->piecesMadeTotal;
				s.blocksCleared = g->blocksClearedTotal;
				s.piecesPlaced = g->piecesPlacedTotal;
				s.combosMade = g->totalCombosMade;
				s.biggestCombo = g->biggestComboChain;

				s.allFrameStatesZipped = "temp";// FrameState::getFrameStatesAsBase64GZippedXML(g->framesArray);

				for (int n = 0; n < players->size(); n++)
				{
					sp<PuzzlePlayer>pp = players->at(n);
					long long playerUserID = -1;
					if (pp->isNetworkPlayer() && pp->peerConnection != nullptr)
						playerUserID = pp->peerConnection->peerUserID;
					else playerUserID = g->getEngine()->getUserID_S();

					string playerUserName = "Local Player";
					if (pp->isNetworkPlayer() && pp->peerConnection != nullptr)
						playerUserName = pp->peerConnection->getUserName();

					if (players->size() == 1)playerUserName = g->getEngine()->getUserName_S();

					string statusString = "";
					if (pp->gameLogic->won)statusString = "won";
					if (pp->gameLogic->died)statusString = "died";
					if (pp->gameLogic->lost)statusString = "lost";
					s.playerIDsCSV += to_string(playerUserID) + ":" + "`" + playerUserName + "`" + ":" + statusString + ",";//id:`userName`:lost,id:`userName`:won,:
				}

				s.room = currentRoom;

				string statsString = s.encode();
				getServerConnection()->sendOKGameGameStats_S(statsString);

			}
		}

		sentStats = true;
		firstCheckedStatsResponseTime = currentTime;

	}
	
	if(sentStats)
	{
		
		//waiting for response from server
		if (gotStatsResponse == false)
		{


			long long startTime = lastCheckedStatsResponseTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (ticksPassed > 100)
			{


				lastCheckedStatsResponseTime = currentTime;


				if (getServerConnection()->getAndResetGotOKGameGameStatsResponse_S())
				{
					gotStatsResponse = true;
					sp<vector<string>>statsResponse = getServerConnection()->getAndResetOKGameGameStatsResponse_S();
					for (int i = 0; i<statsResponse->size(); i++)
					{
						statsUploadMenu->clear();
						statsUploadMenu->add(statsResponse->at(i));
						statsUploadMenu->add(" ");
						statsUploadMenu->add("Press Action", "", OKColor::green);
					}
				}
				else
				{
					if ((int)(System::getTicksBetweenTimes(firstCheckedStatsResponseTime, currentTime)) > 4000)
					{
						gotStatsResponse = true;
						statsUploadMenu->clear();
						statsUploadMenu->getMenuItemByID("Status")->setText("Timed out waiting for results from server.");
						statsUploadMenu->add(" ");
						statsUploadMenu->add("Press Action", "", OKColor::green);
					}
				}
			}


		}
		else
		{
			if (getControlsManager()->miniGame_ACTION_Pressed())
			{
				if (statsUploadMenu != nullptr)
				{
					//delete statsUploadMenu;
					statsUploadMenu = nullptr;
				}
			}

		}

			
		
	}

}

//=========================================================================================================================
void OKGame::doVoting()
{//=========================================================================================================================



	if (
		players->size() > 1 ||
		sentVote ||
		getServerConnection()->getConnectedToServer_S() == false ||
		getServerConnection()->getAuthorizedOnServer_S() == false
		)
	{
		sentVote = true;
		if (voteMenu != nullptr)
		{
			//delete voteMenu;
			voteMenu = nullptr;
		}
		return;
	}


	if (sentVote == false)
	{
		string type = "game sequence";
		sp<GameSequence>gs = getPlayer1Game()->currentGameSequence;
		string name = gs->name;
		if (gs->gameTypes->size() == 1)
		{
			type = "game type";
			sp<GameType>g = gs->gameTypes->at(0);
			name = g->name;
			if (g->downloaded == false || g->yourVote != "none")
			{
				sentVote = true;
				return;
			}
		}
		else
		{
			if (gs->downloaded == false || gs->yourVote != "none")
			{
				sentVote = true;
				return;
			}
		}

		if (voteMenu == nullptr)
		{
			voteMenu = ms<OKMenu>(this, "Vote");
			voteMenu->outline = true;
			voteMenu->setFontSize(32);
			voteMenu->addInfo("Please vote on this "+type+" ("+name+")", "", OKColor::green)->outline = true;
			voteMenu->add("Up", "", OKColor::white);
			voteMenu->add("Down", "", OKColor::white);
		}

		if (voteMenu != nullptr)
		{
			if (getControlsManager()->miniGame_UP_Pressed())
			{
				voteMenu->up();
			}

			if (getControlsManager()->miniGame_DOWN_Pressed())
			{
				voteMenu->down();
			}

			bool leaveMenu = false;

			bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
			bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
			int mx = getControlsManager()->getMouseX();
			int my = getControlsManager()->getMouseY();
			if (confirm || clicked)
			{
				string vote = "none";

				if (voteMenu->isSelectedID("Up", clicked, mx, my))
				{
					vote = "up";
				}
				if (voteMenu->isSelectedID("Down", clicked, mx, my))
				{
					vote = "down";
				}

				if (vote != "none")
				{
					sentVote = true;

					if (getPlayer1Game()->currentGameSequence->gameTypes->size() == 1)
					{
						string uuid = getPlayer1Game()->currentGameSequence->gameTypes->at(0)->uuid;
						getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::OK_Game_GameTypesAndSequences_Vote_Request + "GameType:" + uuid + ":" + vote + ":" + OKNet::endline);
					}
					else
					{
						string uuid = getPlayer1Game()->currentGameSequence->uuid;
						getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::OK_Game_GameTypesAndSequences_Vote_Request + "GameSequence:" + uuid + ":" + vote + ":" + OKNet::endline);
					}

					if (getPlayer1Game()->currentGameSequence->gameTypes->size() == 1)
					{
						if (vote=="up")getPlayer1Game()->currentGameSequence->gameTypes->at(0)->yourVote = "up";
						else getPlayer1Game()->currentGameSequence->gameTypes->at(0)->yourVote = "down";
					}
					else
					{
						if (vote=="down")getPlayer1Game()->currentGameSequence->yourVote = "up";
						else getPlayer1Game()->currentGameSequence->yourVote = "down";
					}

				}

				leaveMenu = true;
			}

			if (leaveMenu)
			{
				if (voteMenu != nullptr)
				{
					//delete voteMenu;
					voteMenu = nullptr;
				}
			}
		}
	}



}

//=========================================================================================================================
void OKGame::tryToCloseGame()
{//=========================================================================================================================
//
//	if (isNetworkGame())
//	{
//
//		long long startTime = lastTimeTriedToCloseGame;
//		long long currentTime = System::currentHighResTimer();
//		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
//		if (ticksPassed < 5000)
//		{
//			//send "quit" message
//			//TODO: add "lose" to records
//
//			sendForfeit();
//
//		}
//		else
//		{
//			//warn that network game will be forfeit
//			//if try to close again within 5 seconds, close.
//
//			lastTimeTriedToCloseGame = currentTime;
//
//			getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN,0,5000,"Network game is in progress! Match will be forfeit. Try again within 5 seconds to confirm.",oswald_16,Color::red);
//		}
//	}
//	else
//	{
//		//nD.setActivated(false);
//	}
}


//=========================================================================================================================
void OKGame::changeBG()
{//=========================================================================================================================

	//shaderCount++;
	//if(shaderCount>=LWJGLUtils.bgShaderCount)shaderCount=0;

	shaderCount = Math::randLessThan(GLUtils::bgShaderCount);
	//log.debug("Shader: " + to_string(shaderCount));
	//CaptionManager().newManagedCaption(0,0,1000,""+shaderCount,OKFont.font_normal_16_outlined_smooth,OKColor.white,OKColor.black,2.0f);

}


//
////=========================================================================================================================
//sp<OKGame> OKGame::getThis()
//{//=========================================================================================================================
//
//	return b;
//
//}
//


void OKGame::updateControls()
{
	resetPressedButtons();
	setButtonStates();

}

void OKGame::resetPressedButtons()
{//=========================================================================================================================

	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);
		p->resetPressedButtons();
	}

	getActiveControlsManager()->resetPressedButtons();
}

void OKGame::setButtonStates()
{//=========================================================================================================================
	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);
		p->setButtonStates();
	}

	getActiveControlsManager()->setButtonStates();


	//puzzlegame

//	if (players->size() == 1)
//	{
//
//		//use MINIGAME controls
//
//		sp<PuzzlePlayer>p = players->at(0);
//
//		if (getControlsManager()->MINIGAME_UP_HELD == true)p->UP_HELD = true;
//		if (getControlsManager()->MINIGAME_DOWN_HELD == true)p->DOWN_HELD = true;
//		if (getControlsManager()->MINIGAME_LEFT_HELD == true)p->LEFT_HELD = true;
//		if (getControlsManager()->MINIGAME_RIGHT_HELD == true)p->RIGHT_HELD = true;
//
//		if (p->allowAnalogControls)
//		{
//			if (getControlsManager()->MINIGAME_ANALOGUP_HELD == true)p->UP_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGDOWN_HELD == true)p->DOWN_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGLEFT_HELD == true)p->LEFT_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGRIGHT_HELD == true)p->RIGHT_HELD = true;
//		}
//		if (getControlsManager()->MINIGAME_RUN_HELD == true)p->ROTATECCW_HELD = true;
//		if (getControlsManager()->MINIGAME_ACTION_HELD == true)p->ROTATECW_HELD = true;
//		if (getControlsManager()->MINIGAME_L_HELD == true)p->HOLDRAISE_HELD = true;
//
//		if (getControlsManager()->miniGame_PAUSE_Pressed() == true)p->PAUSE_PRESSED = true;//doesn't really matter for single player
//		if (getControlsManager()->miniGame_CONFIRM_Pressed() == true)p->CONFIRM_PRESSED = true;//doesn't really matter for single player
//		if (getControlsManager()->miniGame_CANCEL_Pressed() == true)p->CANCEL_PRESSED = true;//doesn't really matter for single player
//
//		if (p->slamWithR)
//		{
//			if (getControlsManager()->MINIGAME_R_HELD == true)p->SLAM_HELD = true;
//		}
//		else
//		{
//			if (getControlsManager()->MINIGAME_R_HELD == true)p->HOLDRAISE_HELD = true;
//		}
//
//		if (p->slamWithY)
//		{
//			if (getControlsManager()->MINIGAME_Y_HELD == true)p->SLAM_HELD = true;
//		}
//
//		if (p->slamWithUp)
//		{
//			if (getControlsManager()->MINIGAME_UP_HELD == true)p->SLAM_HELD = true;
//		}
//		p->setPressedButtons();
//
//	}
//	else
//	if (players->size() > 1)
//	{
	sp<PuzzlePlayer>p = nullptr;// = players->at(0);

		for (int i = 0; i < players->size();i++)
		{
			p = players->at(i);

			if (p->useKeyboard)
			{
				if (getControlsManager()->KEY_UP_HELD == true)p->UP_HELD = true;
				if (getControlsManager()->KEY_DOWN_HELD == true)p->DOWN_HELD = true;
				if (getControlsManager()->KEY_LEFT_HELD == true)p->LEFT_HELD = true;
				if (getControlsManager()->KEY_RIGHT_HELD == true)p->RIGHT_HELD = true;
				if (getControlsManager()->KEY_SPACE_HELD == true)p->ROTATECW_HELD = true;
				if (getControlsManager()->KEY_LSHIFT_HELD == true)p->ROTATECCW_HELD = true;
				if (getControlsManager()->KEY_LCTRL_HELD == true)p->HOLDRAISE_HELD = true;

				//if (getControlsManager()->KEY_RETURN_HELD == true)p->START_HELD = true;

				if (getControlsManager()->KEY_ESC_HELD == true)p->PAUSE_HELD = true;

				if (getControlsManager()->KEY_RETURN_HELD == true)p->CONFIRM_HELD = true;
				if (getControlsManager()->KEY_SPACE_HELD == true)p->CONFIRM_HELD = true;

				//if (getControlsManager()->KEY_ESC_HELD == true)p->CANCEL_HELD = true;
				if (getControlsManager()->KEY_LSHIFT_HELD == true)p->CANCEL_HELD = true;

				if (p->slamWithUp)
				{
					if (getControlsManager()->KEY_UP_HELD == true)p->SLAM_HELD = true;
				}

				if (p->slamWithR)
				{
					if (getControlsManager()->KEY_LALT_HELD == true)p->SLAM_HELD = true;
				}
				else
				{
					if (getControlsManager()->KEY_LALT_HELD == true)p->HOLDRAISE_HELD = true;
				}
			}

			if (p->gameController!=nullptr)
			{
				sp<GameController>g = p->gameController;

				if (g->UP_HELD == true)p->UP_HELD = true;
				if (g->DOWN_HELD == true)p->DOWN_HELD = true;
				if (g->LEFT_HELD == true)p->LEFT_HELD = true;
				if (g->RIGHT_HELD == true)p->RIGHT_HELD = true;

				if (p->allowAnalogControls)
				{
					if (g->ANALOGUP_HELD == true)p->UP_HELD = true;
					if (g->ANALOGDOWN_HELD == true)p->DOWN_HELD = true;
					if (g->ANALOGLEFT_HELD == true)p->LEFT_HELD = true;
					if (g->ANALOGRIGHT_HELD == true)p->RIGHT_HELD = true;
				}

				if (g->B_HELD == true)p->ROTATECW_HELD = true;
				if (g->A_HELD == true)p->ROTATECCW_HELD = true;
				if (g->L_HELD == true)p->HOLDRAISE_HELD = true;

				if (g->START_HELD == true)p->PAUSE_HELD = true;
				//if (g->START_HELD == true)p->START_HELD = true;
				//if (g->START_HELD == true)p->CONFIRM_HELD = true;
				if (g->A_HELD == true)p->CONFIRM_HELD = true;
				if (g->B_HELD == true)p->CANCEL_HELD = true;

				if (p->slamWithR)
				{
					if (g->R_HELD == true)p->SLAM_HELD = true;
				}
				else
				{
					if (g->R_HELD == true)p->HOLDRAISE_HELD = true;
				}

				if (p->slamWithY)
				{
					if (g->Y_HELD == true)p->SLAM_HELD = true;
				}

				if (p->slamWithUp)
				{
					if (g->UP_HELD == true)p->SLAM_HELD = true;
				}
			}

			p->setPressedButtons();

		}
	}
//}

//=========================================================================================================================
void OKGame::shakeSmall()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(300,10,10,60);

}

//=========================================================================================================================
void OKGame::shakeHard()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(600,20,20,60);
}

//void OKGameStadium::shakeSmall()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.1f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(300, 2, 2, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}
//
//void OKGameStadium::shakeHard()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.5f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(1000, 5, 5, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}


//=========================================================================================================================
void OKGame::loadGameTypesFromXML()
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameTypes/";
	string builtInDataPathString = Main::getPath() + "data/gameTypes/";
	string downloadedDataPathString = FileUtils::appDataPath + "downloadedGameTypes/";

	Path userDataPath(userDataPathString);
	Path builtInDataPath(builtInDataPathString);
	Path downloadedDataPath(downloadedDataPathString);
	//make sure both directories exist, make them if they don't

	File userDataPathDir(userDataPath);
	File builtInDataPathDir(builtInDataPath);
	File downloadedDataPathDir(downloadedDataPath);

	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();
	if (builtInDataPathDir.exists() == false)builtInDataPathDir.createDirectories();
	if (downloadedDataPathDir.exists() == false)downloadedDataPathDir.createDirectories();

	loadedGameTypes->clear();

	bool found = false;

	//show all files in dir
	for (int i = 0; i<3; i++)
	{
		vector<string>files;
		if (i == 0)builtInDataPathDir.list(files);
		if (i == 1)userDataPathDir.list(files);
		if (i == 2)downloadedDataPathDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			//cout << *it << endl;
			string name = *it;
			if (name.find(".xml") != string::npos)
			{
				if(i==0)found = true;

				string fullPathName;
				if (i == 0)fullPathName = builtInDataPathString + name;
				if (i == 1)fullPathName = userDataPathString + name;
				if (i == 2)fullPathName = downloadedDataPathString + name;

				ifstream t(fullPathName);
				string str;

				t.seekg(0, ios::end);
				str.reserve((size_t)t.tellg());
				t.seekg(0, ios::beg);

				str.assign((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

				stringstream ss;
				ss << str;
				boost::archive::xml_iarchive ia(ss);

				GameType gt;
				try
				{
					ia >> BOOST_SERIALIZATION_NVP(gt);
					sp<GameType>s = ms<GameType>();
					*s = gt;

					//if(i==0)s->builtInType = true;
					if(i==1) {s->creatorUserName = "(You)"; }//s->builtInType = false; 
					if(i==2)s->downloaded = true;

					loadedGameTypes->push_back(s);
				}
				catch(exception)
				{
					log.error("Could not load GameType: " + name);
				}
			}
		}

	}

}

//=========================================================================================================================
void OKGame::loadGameSequencesFromXML()
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameSequences/";
	string builtInDataPathString = Main::getPath() + "data/gameSequences/";
	string downloadedDataPathString = FileUtils::appDataPath + "downloadedGameSequences/";

	Path userDataPath(userDataPathString);
	Path builtInDataPath(builtInDataPathString);
	Path downloadedDataPath(downloadedDataPathString);
	//make sure both directories exist, make them if they don't

	File userDataPathDir(userDataPath);
	File builtInDataPathDir(builtInDataPath);
	File downloadedDataPathDir(downloadedDataPath);

	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();
	if (builtInDataPathDir.exists() == false)builtInDataPathDir.createDirectories();
	if (downloadedDataPathDir.exists() == false)downloadedDataPathDir.createDirectories();

	loadedGameSequences->clear();

	bool found = false;

	//show all files in dir
	for(int i=0;i<3;i++)
	{
		vector<string>files;
		if(i==0)builtInDataPathDir.list(files);
		if(i==1)userDataPathDir.list(files);
		if(i==2)downloadedDataPathDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			//cout << *it << endl;
			string name = *it;
			if (name.find(".xml") != string::npos)
			{
				if(i==0)found = true;

				string fullPathName;
				if (i == 0)fullPathName = builtInDataPathString + name;
				if (i == 1)fullPathName = userDataPathString + name;
				if (i == 2)fullPathName = downloadedDataPathString + name;

				ifstream t(fullPathName);
				string str;

				t.seekg(0, ios::end);
				str.reserve((size_t)t.tellg());
				t.seekg(0, ios::beg);

				str.assign((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

				stringstream ss;
				ss << str;

				boost::archive::xml_iarchive ia(ss);

				GameSequence gs;
				try
				{
					ia >> BOOST_SERIALIZATION_NVP(gs);

					sp<GameSequence>s = ms<GameSequence>();
					*s = gs;

					//if (i == 0)s->builtInType = true;
					if (i == 1) { s->creatorUserName = "(You)"; }//s->builtInType = false; 
					if (i == 2)s->downloaded = true;

					loadedGameSequences->push_back(s);
				}
				catch(exception)
				{
					log.error("Could not load GameSequence: " + name);
				}

			}
		}
	}


	{

		//initialize actual games from game names in game sequences, this should be improved using game IDs so it can download missing games and sequences can be shared


		for(int i=0;i<loadedGameSequences->size();i++)
		{
			sp<GameSequence>g = loadedGameSequences->at(i);

			loadGameSequenceUUIDsToGamesArray(g);
		}

	}

}

//=========================================================================================================================
void OKGame::loadGameSequenceUUIDsToGamesArray(sp<GameSequence>g)
{//=========================================================================================================================

	g->gameTypes->clear();

	for (int n = 0; n<g->importExport_gameUUIDs->size(); n++)
	{
		string uuid = g->importExport_gameUUIDs->at(n);
		sp<GameType>s = getGameTypeByUUID(uuid);

		if (s != nullptr)
		{
			g->gameTypes->push_back(s);
		}
		else
		{
			log.debug("Could not load game UUID: " + uuid);
		}

	}
}
//=========================================================================================================================
sp<GameType> OKGame::getGameTypeByName(string name)
{//=========================================================================================================================

	if (name == "")return nullptr;

	sp<GameType>bt = nullptr;
	for (int i = 0; i<loadedGameTypes->size(); i++)
	{
		sp<GameType>b = loadedGameTypes->at(i);
		if (b->name == name)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
sp<GameType> OKGame::getGameTypeByUUID(string uuid)
{//=========================================================================================================================

	if (uuid == "")return nullptr;

	sp<GameType>bt = nullptr;
	for (int i = 0; i<loadedGameTypes->size(); i++)
	{
		sp<GameType>b = loadedGameTypes->at(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
sp<GameSequence> OKGame::getGameSequenceByName(string name)
{//=========================================================================================================================

	if (name == "")return nullptr;

	sp<GameSequence>bt = nullptr;
	for (int i = 0; i<loadedGameSequences->size(); i++)
	{
		sp<GameSequence>b = loadedGameSequences->at(i);
		if (b->name == name)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
sp<GameSequence> OKGame::getGameSequenceByUUID(string uuid)
{//=========================================================================================================================
	if (uuid == "")return nullptr;

	sp<GameSequence>bt = nullptr;
	for (int i = 0; i<loadedGameSequences->size(); i++)
	{
		sp<GameSequence>b = loadedGameSequences->at(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}

//=========================================================================================================================
void OKGame::saveRoomConfigToFile(sp<Room> currentRoom,string name)
{//=========================================================================================================================
	
	string userDataPathString = FileUtils::appDataPath + "savedRoomConfigs/";
	Poco::Path userDataPath(userDataPathString);
	Poco::File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	//Path filePath();
	Poco::File file(userDataPathString + name);

	{
		
		if(currentRoom->gameSequence->gameTypes->size()==1)
		{
			currentRoom->room_IsGameSequenceOrType = "GameType";
			currentRoom->room_GameTypeName = currentRoom->gameSequence->gameTypes->at(0)->name;
			currentRoom->room_GameTypeUUID = currentRoom->gameSequence->gameTypes->at(0)->uuid;
		}
		else
		{
			currentRoom->room_IsGameSequenceOrType = "GameSequence";

			currentRoom->room_GameSequenceName = currentRoom->gameSequence->name;
			currentRoom->room_GameSequenceUUID = currentRoom->gameSequence->uuid;
		}

		Room r;
		r = *currentRoom;

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(r);

		ofstream outputFile;
		outputFile.open(userDataPathString + name, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}
}
//=========================================================================================================================
sp<vector<string>> OKGame::getRoomConfigsList()
{//=========================================================================================================================
	
	string userDataPathString = FileUtils::appDataPath + "savedRoomConfigs/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();


	sp<vector<string>> roomConfigFileNames;


	vector<string>files;
	userDataPathDir.list(files);

	vector<string>::iterator it = files.begin();
	for (; it != files.end(); ++it)
	{
		//cout << *it << endl;
		string name = *it;
		if (name.find(".roomConfig") != string::npos)
		{
			roomConfigFileNames->push_back(name.substr(0,name.find(".roomConfig")));
		}
	}
	
	return roomConfigFileNames;

}

//=========================================================================================================================
sp<Room> OKGame::loadRoomConfig(string configName)
{//=========================================================================================================================
	
	string userDataPathString = FileUtils::appDataPath + "savedRoomConfigs/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	string fullPathName = userDataPathString + configName + ".roomConfig";


	
	sp<Room>room = ms<Room>();
	try
	{

		ifstream t(fullPathName);
		string str;

		t.seekg(0, ios::end);
		str.reserve((size_t)t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		stringstream ss;
		ss << str;

		boost::archive::xml_iarchive ia(ss);

		Room gs;
		ia >> BOOST_SERIALIZATION_NVP(gs);

		*room = gs;

	}
	catch (exception)
	{
		log.error("Could not load Room: " + configName);
		return nullptr;
	}


	sp<GameSequence>gs = getGameSequenceByUUID(room->room_GameSequenceUUID);
	if(gs == nullptr)
	{
		gs = ms<GameSequence>();
		sp<GameType> gt = getGameTypeByUUID(room->room_GameTypeUUID);
		if (gt != nullptr)
		{
			gs->gameTypes->push_back(gt);
		}
		else
		{
			log.error("Could not load Room: " + configName);
			return nullptr;
		}
	}

	return room;


}


//=========================================================================================================================
void OKGame::saveUnknownGameSequencesAndTypesToXML(sp<GameSequence>gs)
{//=========================================================================================================================

	//save game sequence locally and each game type locally!
	//go through each game sequence and each game type and ignore if the uuid doesn't exist
	if (gs->creatorUserID != -1 && gs->dateCreated != -1 && getGameSequenceByUUID(gs->uuid) == nullptr)
	{
		loadedGameSequences->push_back(gs);
		saveGameSequenceToXML(gs, true);
	}
	for (int i = 0; i < gs->gameTypes->size(); i++)
	{
		sp<GameType>g = gs->gameTypes->at(i);
		if (g->creatorUserID != -1 && g->dateCreated != -1 && getGameTypeByUUID(g->uuid) == nullptr)
		{

			loadedGameTypes->push_back(g);
			saveGameTypeToXML(g, true);
		}
	}
}

//=========================================================================================================================
void OKGame::saveGameSequenceToXML(sp<GameSequence>gs, bool downloaded)
{//=========================================================================================================================

	string userDataPathString = FileUtils::appDataPath + "gameSequences/";
	if(downloaded)userDataPathString = FileUtils::appDataPath + "downloadedGameSequences/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	//if type exists, do we overwrite?
	//let's rename the old file to .000

	//TODO: we should have some kind of server based versioning using username-gamename
	string filename = gs->uuid + ".xml";

	filename = FileUtils::removeIllegalFilenameChars(filename);

	Path filePath(userDataPathString + filename);
	File file(filePath);
	int version = 0;

	if (file.exists())
	{
		while (file.exists())
		{
			file = File(userDataPathString + gs->uuid + "." + to_string(version));
			version++;
		}
		file = File(filePath);
		file.renameTo(userDataPathString + gs->uuid + "." + to_string(version));
	}

	{
		GameSequence g;
		g = *gs;

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(g);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}
}

//=========================================================================================================================
void OKGame::saveGameTypeToXML(sp<GameType>gs, bool downloaded)
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameTypes/";
	if (downloaded)userDataPathString = FileUtils::appDataPath + "downloadedGameTypes/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	//if type exists, do we overwrite?
	//let's rename the old file to .000

	//TODO: we should have some kind of server based versioning using username-gamename
	string filename = gs->uuid + ".xml";

	filename = FileUtils::removeIllegalFilenameChars(filename);

	//Path filePath();
	File file(userDataPathString + filename);
	int version = 0;

	if (file.exists())
	{
		while (file.exists())
		{
			file = File(userDataPathString + gs->uuid + "." + to_string(version));
			version++;
		}
		file = File(userDataPathString + filename);
		file.renameTo(userDataPathString + gs->uuid + "." + to_string(version));
	}

	{

		GameType g;
		g = *gs;
		if (downloaded)g.downloaded = true;

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(g);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}
}

//=========================================================================================================================
void OKGame::getGameTypesAndSequencesFromServer()
{//=========================================================================================================================
	

	if (getServerConnection()->getConnectedToServer_S())
	{
		if (sentActivityStreamRequest == false)
		{
			sentActivityStreamRequest = true;
			getServerConnection()->sendOKGameActivityStreamRequest_S();
		}
	}

	
	if (getServerConnection()->getConnectedToServer_S())
	{
		//if (getServerConnection()->getAuthorizedOnServer_S())
		{
			if (gotGamesFromServer == false)
			{
				if (getServerConnection()->getAuthorizedOnServer_S() || sentServerGamesRequest)gettingGamesFromServerMenuShowing = true;

				long long currentTime = System::currentHighResTimer();
				long long startTime = lastCheckedGamesFromServerTime;
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
				if (ticksPassed > 2000)
				{
					lastCheckedGamesFromServerTime = currentTime;
					if (sentServerGamesRequest == false)
					{
						getServerConnection()->sendOKGameGameTypesAndSequencesDownloadRequest_S();
						sentServerGamesRequest = true;

						wasAuthorizedWhenSent = getServerConnection()->getAuthorizedOnServer_S();
						
					}
					else
					{
						if (getServerConnection()->getAndResetOKGameGameTypesAndSequencesDownloadResponseReceived_S())
						{
							gotGamesFromServer = true;

						}
					}
				}
			}
			else
			{

				long long currentTime = System::currentHighResTimer();
				long long startTime = lastCheckedGotIncomingGamesFromServerTime;
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
				if (ticksPassed > 1000)
				{
					lastCheckedGotIncomingGamesFromServerTime = currentTime;

					//if wasnt authed when got games but now we are authed get games again so votes are correct
					if (wasAuthorizedWhenSent == false && getServerConnection()->getAuthorizedOnServer_S() == true)
					{
						gotGamesFromServer = false;
						sentServerGamesRequest = false;
					}

					if (getAndResetGotIncomingGamesFromServer_S() == true)
					{

						//load threadsafe games into normal loadedGameTypes array in update and save all to xml

						while (incomingGameTypesQueueSize_S() > 0)
						{
							sp<GameType>g = incomingGameTypesQueuePop_S();

							sp<GameType>existing = getGameTypeByUUID(g->uuid);
							if (existing != nullptr)
							{
								if (existing->downloaded == true)
								{
									//loadedGameTypes->remove(existing);
									for (int i = 0; i < loadedGameTypes->size(); i++)
									{
										if (loadedGameTypes->at(i).get() == existing.get())
										{
											loadedGameTypes->erase(loadedGameTypes->begin() + i);
											i--;
										}
									}
								}
							}

							//it won't replace your local version with the server version if you are the creator, 
							//rather it assumes that the local version is the most recent.

							if (existing == nullptr || existing->downloaded == true)//dont replace usermade game with downloaded version
							{
								g->downloaded = true;
								loadedGameTypes->push_back(g);
								saveGameTypeToXML(g, true);
							}
						}

						while (incomingGameSequencesQueueSize_S()>0)
						{
							sp<GameSequence>g = incomingGameSequencesQueuePop_S();

							sp<GameSequence> existing = getGameSequenceByUUID(g->uuid);
							if (existing != nullptr)
							{
								if (existing->downloaded == true)
								{
									//loadedGameSequences->remove(existing);
									for (int i = 0; i < loadedGameSequences->size(); i++)
									{
										if (loadedGameSequences->at(i).get() == existing.get())
										{
											loadedGameSequences->erase(loadedGameSequences->begin() + i);
											i--;
										}
									}
								}
							}
							if (existing == nullptr || existing->downloaded == true)
							{
								g->downloaded = true;
								loadedGameSequences->push_back(g);
								saveGameSequenceToXML(g, true);
							}
						}

						for (int i = 0; i<loadedGameSequences->size(); i++)
						{
							sp<GameSequence>g = loadedGameSequences->at(i);

							loadGameSequenceUUIDsToGamesArray(g);
						}

						setGotIncomingGamesFromServer_S(false);
						gettingGamesFromServerMenuShowing = false;


						if (sentHighScoresAndLeaderboardsRequestWhileLoggedIn == false)
						{
							getServerConnection()->sendOKGameGetHighScoresAndLeaderboardsRequest_S();

							if (getServerConnection()->getAuthorizedOnServer_S())
							{
								sentHighScoresAndLeaderboardsRequestWhileLoggedIn = true;
							}
						}

						if (gettingGamesFromServerMenu != nullptr)
						{

							//delete gettingGamesFromServerMenu;
							gettingGamesFromServerMenu = nullptr;

						}
					}
				}
			}
		}


		if (gotGamesFromServer)
		{
			if (getServerConnection()->getAuthorizedOnServer_S())
			{
				if (sentHighScoresAndLeaderboardsRequestWhileLoggedIn == false)
				{
					sentHighScoresAndLeaderboardsRequestWhileLoggedIn = true;
					getServerConnection()->sendOKGameGetHighScoresAndLeaderboardsRequest_S();
				}
			}
		}
		
	}




}

//=========================================================================================================================
void OKGame::parseIncomingGameTypesAndSequencesFromServer_S(string& s)
{//=========================================================================================================================

	//GameType:MD5:XML:userid:username:name:uuid:datecreated:lastmodified:howmanytimesupdated:upvotes:downvotes:haveyouvoted
	//					GameSequence:MD5

	while(s.length()>0)
	{

		bool gameType = false;
		bool gameSequence = false;

		if(OKString::startsWith(s,"GameType:"))
		{
			gameType = true;
		}
		else
		if (OKString::startsWith(s, "GameSequence:"))
		{
			gameSequence = true;
		}
		else
		{
			log.error("Could not parse Game string from server: " + s);
			return;
		}

		s = s.substr(s.find(":") + 1);
		string md5String = s.substr(0,s.find(":"));
		s = s.substr(s.find(":") + 1);
		string b64zippedXMLString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string userIDString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		s = s.substr(s.find("`") + 1);
		string userNameString = s.substr(0, s.find("`:"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(":") + 1);
		s = s.substr(s.find("`") + 1);
		string gameNameString = s.substr(0, s.find("`:"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(":") + 1);
		string uuidString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string dateCreatedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string lastModifiedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string howManyTimesUpdatedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string upVotesString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string downVotesString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string yourVoteString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);

		long long userID = -1;
		try
		{
			userID = stoll(userIDString);
		}
		catch (exception)
		{
			log.error("userID could not be parsed");
			return;
		}

		long long dateCreated = -1;
		try
		{
			dateCreated = stoll(dateCreatedString);
		}
		catch (exception)
		{
			log.error("dateCreated could not be parsed");
			return;
		}

		long long lastModified = -1;
		try
		{
			lastModified = stoll(lastModifiedString);
		}
		catch (exception)
		{
			log.error("lastModified could not be parsed");
			return;
		}


		long long howManyTimesUpdated = -1;
		try
		{
			howManyTimesUpdated = stoll(howManyTimesUpdatedString);
		}
		catch (exception)
		{
			log.error("howManyTimesUpdated could not be parsed");
			return;
		}


		long long upVotes = -1;
		try
		{
			upVotes = stoll(upVotesString);
		}
		catch (exception)
		{
			log.error("upVotes could not be parsed");
			return;
		}


		long long downVotes = -1;
		try
		{
			downVotes = stoll(downVotesString);
		}
		catch (exception)
		{
			log.error("downVotes could not be parsed");
			return;
		}


		//check xml string with md5
		string compMD5 = FileUtils::getStringMD5(b64zippedXMLString);
		if (md5String == compMD5 == false)
		{
			log.error("GameType MD5 did not match in "+ gameNameString);
			continue;
		}

		//unzip to xml
		string xmlString = FileUtils::unzipBase64StringToString(b64zippedXMLString);

		if (xmlString == "" || xmlString.length() == 0)
		{
			log.error("Could not unzip GameType in "+ gameNameString);
			continue;
		}

		if(gameType)
		{
			//unserialize, add to threadsafe gameTypeArray

			stringstream ss;
			ss << xmlString;

			boost::archive::xml_iarchive ia(ss);
			GameType gs;
			try
			{
				ia >> BOOST_SERIALIZATION_NVP(gs);
				sp<GameType>g = ms<GameType>();
				*g = gs;

				g->creatorUserID = userID;
				g->creatorUserName = userNameString;
				g->dateCreated = dateCreated;
				g->lastModified = lastModified;
				g->howManyTimesUpdated = howManyTimesUpdated;
				g->upVotes = upVotes;
				g->downVotes = downVotes;
				g->yourVote = yourVoteString;

				g->creatorUserName = FileUtils::removeSwearWords(g->creatorUserName);
				g->name = FileUtils::removeSwearWords(g->name);
				g->rules1 = FileUtils::removeSwearWords(g->rules1);
				g->rules2 = FileUtils::removeSwearWords(g->rules2);
				g->rules3 = FileUtils::removeSwearWords(g->rules3);

				incomingGameTypesQueuePush_S(g);
			}
			catch (exception)
			{
				log.error("Could not load GameType from server:"+gameNameString+" "+uuidString);
			}
		}

		if(gameSequence)
		{
			stringstream ss;
			ss << xmlString;

			boost::archive::xml_iarchive ia(ss);
			GameSequence gs;
			try
			{
				ia >> BOOST_SERIALIZATION_NVP(gs);

				sp<GameSequence>g = ms<GameSequence>();
				*g = gs;

				g->creatorUserID = userID;
				g->creatorUserName = userNameString;
				g->dateCreated = dateCreated;
				g->lastModified = lastModified;
				g->howManyTimesUpdated = howManyTimesUpdated;
				g->upVotes = upVotes;
				g->downVotes = downVotes;
				g->yourVote = yourVoteString;

				g->creatorUserName = FileUtils::removeSwearWords(g->creatorUserName);
				g->name = FileUtils::removeSwearWords(g->name);

				incomingGameSequencesQueuePush_S(g);
			}
			catch(exception)
			{
				log.error("Could not load GameSequence from server:" + gameNameString + " " + uuidString);
			}
		}

		//set threadsafe loaded games from server flag
		//load threadsafe games into normal loadedGameTypes array in update and save all to xml

		setGotIncomingGamesFromServer_S(true);

	}

}

//=========================================================================================================================
void OKGame::updateVersion0ToVersion1()
{//=========================================================================================================================

 //after load, if makePieceTypeWhenCleared>0 but UUID==0 get piece types by name and add uuids
 //search and replace using makePieceTypeWhenCleared with UUID everywhere

 //BlockType::makePieceTypeWhenCleared
 //BlockType::ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType
 //BlockType::whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut
 //TurnFromBlockTypeToType::fromType
 //TurnFromBlockTypeToType::toType
 //PieceType::overrideBlockTypes

//search and replace with UUID
//TurnFromBlockTypeToType::fromType
//TurnFromBlockTypeToType::toType
//PieceType::overrideBlockTypes
//GameType::getBlockTypeByName
//GameType::getPieceTypeByName

	//fix for loading version 0 game types before moved to using uuid
	bool resave = false;
	for (int i = 0; i<loadedGameTypes->size(); i++)
	{
		sp<GameType>g = loadedGameTypes->at(i);

		for (int n = 0; n < g->pieceTypes->size(); n++)
		{
			sp<PieceType> p = g->pieceTypes->at(n);
			if (p->uuid == "")
			{
				boost::uuids::random_generator generator;
				p->uuid = to_string(generator());
			}
		}
		for (int n = 0; n < g->blockTypes->size(); n++)
		{
			sp<BlockType> b = g->blockTypes->at(n);
			if (b->uuid == "")
			{
				boost::uuids::random_generator generator;
				b->uuid = to_string(generator());
			}
		}
		for (int n = 0; n<g->pieceTypes->size(); n++)
		{
			sp<PieceType> p = g->pieceTypes->at(n);
			for (int x = 0; x<p->overrideBlockTypes_DEPRECATED->size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				sp<BlockType> b = p->overrideBlockTypes_DEPRECATED->at(x);//wrong block, instantiated by serialize
				sp<BlockType> correctBlock = g->getBlockTypeByName(b->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					p->overrideBlockTypes_UUID->push_back(correctBlock->uuid);
				}
			}
		}
		for (int n = 0; n < g->blockTypes->size(); n++)
		{
			sp<BlockType> b = g->blockTypes->at(n);

			for (int x = 0; x<b->makePieceTypeWhenCleared_DEPRECATED->size(); x++)
			{
				resave = true;
				sp<PieceType> p = b->makePieceTypeWhenCleared_DEPRECATED->at(x);
				sp<PieceType> correctPiece = g->getPieceTypeByName(p->name);
				if (correctPiece != nullptr)
				{
					if (correctPiece->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctPiece->uuid = to_string(generator());
					}
					b->makePieceTypeWhenCleared_UUID->push_back(correctPiece->uuid);
				}
			}
			for (int x = 0; x<b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED->size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				sp<BlockType> bb = b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED->at(x);//wrong block, instantiated by serialize
				sp<BlockType> correctBlock = g->getBlockTypeByName(bb->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID->push_back(correctBlock->uuid);
				}
			}
			for (int x = 0; x < b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut->size(); x++)
			{
				sp<TurnFromBlockTypeToType> t = b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut->at(x);
				if (t->fromType_DEPRECATED != "")
				{
					sp<BlockType> correctBlock = g->getBlockTypeByName(t->fromType_DEPRECATED);
					if (correctBlock != nullptr)
					{
						if (correctBlock->uuid == "")
						{
							boost::uuids::random_generator generator;
							correctBlock->uuid = to_string(generator());
						}
						t->fromType_UUID = correctBlock->uuid;
					}
				}
				if (t->toType_DEPRECATED != "")
				{
					sp<BlockType> correctBlock = g->getBlockTypeByName(t->toType_DEPRECATED);
					if (correctBlock != nullptr)
					{
						if (correctBlock->uuid == "")
						{
							boost::uuids::random_generator generator;
							correctBlock->uuid = to_string(generator());
						}
						t->toType_UUID = correctBlock->uuid;
					}
				}
			}
		}

		for(int n=0;n<g->difficultyTypes->size();n++)
		{
			sp<DifficultyType>d = g->difficultyTypes->at(n);

			for (int x = 0; x < d->pieceTypesToDisallow_DEPRECATED->size(); x++)
			{
				resave = true;
				sp<PieceType> p = d->pieceTypesToDisallow_DEPRECATED->at(x);
				sp<PieceType> correctPiece = g->getPieceTypeByName(p->name);
				if (correctPiece != nullptr)
				{
					if (correctPiece->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctPiece->uuid = to_string(generator());
					}
					d->pieceTypesToDisallow_UUID->push_back(correctPiece->uuid);
				}
			}
			for (int x = 0; x<d->blockTypesToDisallow_DEPRECATED->size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				sp<BlockType> bb = d->blockTypesToDisallow_DEPRECATED->at(x);//wrong block, instantiated by serialize
				sp<BlockType> correctBlock = g->getBlockTypeByName(bb->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					d->blockTypesToDisallow_UUID->push_back(correctBlock->uuid);
				}
			}
		}

	}
	if (resave)
	{
		for (int i = 0; i < loadedGameTypes->size(); i++)
		{
			sp<GameType>g = loadedGameTypes->at(i);
			//if (g->builtInType == false)
				saveGameTypeToXML(g,g->downloaded);
		}
	}
}
