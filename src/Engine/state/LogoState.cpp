#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LogoState::log = Logger("LogoState");


LogoState::LogoState()
{ //=========================================================================================================================

	//loginScreen = new LoginMenuPanel((Engine*)this);
	//
	//   loginScreenGUI = new GUI(loginScreen, GLUtils::TWLrenderer);
	//   loginScreenGUI->applyTheme(GLUtils::TWLthemeManager);


	logo = GLUtils::getTextureFromPNGExePath("data/theme/bobcorp.png");
	gradient = GLUtils::getTextureFromPNGExePath("data/theme/psychedelicgradient.png");
}

void LogoState::update()
{ //=========================================================================================================================
	//loginScreen->update();


	totalTicksPassed += (int)engineTicksPassed();


	if(totalTicksPassed >= ticksToShow)
	{
		
		Main::getMain()->stateManager->popState();
	}



}

void LogoState::render()
{ //=========================================================================================================================


	{
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		//loginScreen->renderBefore();
		//loginScreenGUI->update();
		//loginScreen->render();
	}
	//SlickCallable.enterSafeBlock();


	float w = (float)GLUtils::getRealWindowWidth();
	float h = (float)GLUtils::getRealWindowHeight();

	GLUtils::drawFilledRect(255, 255, 255, 0, w, 0, h, 1.0f);

	//BobTexture* t = onlineTexture;
//
//	if (loginMenu == nullptr)return;
//
//	//if (t != nullptr)
//	{
//		//loginMenu->setGraphic(t, getWidth() / 8 * 4, 100);
//	}
//
//	if (statusLabel != nullptr && errorLabel != nullptr)
//	{
//		errorLabel->screenY = screenY + (float)(h / 8 * 5);
//		statusLabel->screenY = screenY + (float)((h / 8 * 5) + 24);
//	}
//
//	loginMenu->render(screenY + h / 8 * 3);





//
//	BobTexture* t = Main::glowTileBackgroundMenuPanel->bgScrollTexture;
//
//	BobTexture* over = Main::glowTileBackgroundMenuPanel->glowTileFramesTexture->get(frame);
//
//	float screenWidth = (float)GLUtils::getViewportWidth();
//	float screenHeight = (float)GLUtils::getViewportHeight();
//
//
//	float scale = 2.0f;
//
//	float x0 = screenWidth / 2 - (t->getImageWidth() * scale) / 2;
//	float x1 = x0 + (t->getImageWidth() * scale);
//
//	float y0 = screenHeight / 2 - (t->getImageHeight() * scale) / 2;
//	float y1 = y0 + (t->getImageHeight() * scale);
//
//
//	GLUtils::drawTexture(t, x0, x1, y0, y1, 1.0f, GLUtils::FILTER_NEAREST);
//	GLUtils::drawTexture(over, x0, x1, y0, y1, 1.0f, GLUtils::FILTER_NEAREST);

	float timesToCycle = ticksToShow/1800.0f;



	float iw = logo->getImageWidth();
	float ih = logo->getImageHeight();

	//fullscreen
	float sx0 = 0;
	float sx1 = w;
	float sy0 = 0;
	float sy1 = h;

	//for fitting to screen
	if(iw<w && ih<h)
	{
		sx0 = (w - iw) / 2;
		sx1 = sx0+iw;
		sy0 = (h - ih) / 2;
		sy1 = sy0 + ih;
	}

	//half screen
	//scale by width
	sx0 = w / 8 * 3;
	sx1 = w / 8 * 5;
	float drawwidth = sx1 - sx0;
	float wratio = drawwidth / iw;
	float scaledheight = wratio * ih;

	sy0 = (h - scaledheight) / 8*3;
	sy1 = sy0 + scaledheight;

	//if doesnt fit scale by height
	if(scaledheight>h)
	{
		sy0 = h / 8 * 3;
		sy1 = h / 8 * 5;
		float drawheight = sy1 - sy0;
		float hratio = drawheight / ih;
		float scaledwidth = hratio * iw;

		sx0 = (w - scaledwidth) / 8*3;
		sx1 = sx0 + scaledwidth;
	}




	{
		float tx0 = (float)totalTicksPassed/ ((float)ticksToShow/timesToCycle);
		while (tx0 > 1.0f)tx0 -= 1.0f;
		float tx1 = 1.0f;
		
		float ty0 = 0;
		float ty1 = 1;

		float tdrawn = tx1 - tx0;

		float screenwidth = (sx1 - sx0);

		float drawnwidth = tdrawn * screenwidth;

		GLUtils::drawTexture(gradient, tx0, tx1, ty0, ty1, sx0, sx0+drawnwidth, sy0, sy1, 1.0f, GLUtils::FILTER_LINEAR);

		float tremainderstart = 0.0f;
		float tremainderwidth = (screenwidth - drawnwidth) / screenwidth;
		
		
		GLUtils::drawTexture(gradient, tremainderstart, tremainderwidth, ty0, ty1, sx0 + drawnwidth, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_LINEAR);
	}



	{


		float tw = logo->getTextureWidth();
		float th = logo->getTextureHeight();

		float tx0 = 0;
		float tx1 = iw/tw;
		float ty0 = 0;
		float ty1 = ih/th;

		//fix clipping
		tx1 -= tx1*0.02f;
		ty1 -= ty1*0.02f;



		GLUtils::drawTexture(logo, tx0, tx1, ty0, ty1, sx0-1, sx1+1, sy0-1, sy1+1, 1.0f, GLUtils::FILTER_LINEAR);
	}


}

void LogoState::cleanup()
{ //=========================================================================================================================
  //loginScreenGUI->destroy();
}

