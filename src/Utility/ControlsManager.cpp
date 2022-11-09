
#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#include "ControlsManager.h"

#include <complex>

Logger ControlsManager::log = Logger("ControlsManager");

int ControlsManager::DEADZONE = 8000;

//HashMap<int,sp<SDL_GameController>> *ControlsManager::controllersByJoystickNum = ms<HashMap><int,sp<SDL_GameController>>();
HashMap<SDL_JoystickID,sp<SDL_GameController>> ControlsManager::controllersByJoystickID;

float ControlsManager::MAXZOOM = 3.0f;
float ControlsManager::MINZOOM = 1.0f;
float ControlsManager::ZOOMINCREMENT = 0.25f;

int ControlsManager::numControllers = 0;
string ControlsManager::controllerNames = "";

vector<sp<GameController>> ControlsManager::gameControllers;

ControlsManager::ControlsManager()
{

}


//			case SDLK_w:
//				//case SDLK_UP: {KEY_UP_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_KEYBOARD;} break;
//			case SDLK_s:
//				//case SDLK_DOWN: {KEY_DOWN_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_KEYBOARD;} break;
//			case SDLK_a:
//				// case SDLK_LEFT: {KEY_LEFT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_KEYBOARD;} break;
//			case SDLK_d:
//				//case SDLK_RIGHT: {KEY_RIGHT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_KEYBOARD;} break;

//
//				//case SDLK_f: {if(fpsmeter==0)fpsmeter=1;else fpsmeter=0;}break;
//				//debug
//
//				//map layer on/off
//			case SDLK_1:
//				{
//					if (GLUtils::GLOBAL_bg_layer_enabled[1] == 1)GLUtils::GLOBAL_bg_layer_enabled[1] = 0; else GLUtils::GLOBAL_bg_layer_enabled[1] = 1;
//				}
//				break;
//			case SDLK_2:
//				{
//					if (GLUtils::GLOBAL_bg_layer_enabled[2] == 1)GLUtils::GLOBAL_bg_layer_enabled[2] = 0; else GLUtils::GLOBAL_bg_layer_enabled[2] = 1;
//				}
//				break;
//			case SDLK_3:
//				{
//					if (GLUtils::GLOBAL_bg_layer_enabled[3] == 1)GLUtils::GLOBAL_bg_layer_enabled[3] = 0; else GLUtils::GLOBAL_bg_layer_enabled[3] = 1;
//				}
//				break;
//			case SDLK_0:
//				{
//					if (GLUtils::GLOBAL_bg_layer_enabled[0] == 1)GLUtils::GLOBAL_bg_layer_enabled[0] = 0; else GLUtils::GLOBAL_bg_layer_enabled[0] = 1;
//				}
//				break;
//			case SDLK_4:
//				{
//					if (GLUtils::GLOBAL_sprite_layer_enabled == 1)GLUtils::GLOBAL_sprite_layer_enabled = 0; else GLUtils::GLOBAL_sprite_layer_enabled = 1;
//				}
//				break;
//
//			case SDLK_f:
//				{
//					if (GLUtils::GLOBAL_FRAMEBUFFER_FILTER_TYPE == GL_LINEAR)GLUtils::GLOBAL_FRAMEBUFFER_FILTER_TYPE = GL_NEAREST; else GLUtils::GLOBAL_FRAMEBUFFER_FILTER_TYPE = GL_LINEAR;
//				}
//				break;
//
//			case SDLK_BACKQUOTE:
//				{
//					if (error_console_on == 1)error_console_on = 0; else error_console_on = 1;
//				}
//				break;
//
//				//case SDLK_5: {CLOCK_hour--;CLOCK_moving=true;CLOCK_update_clock();}break;
//				//case SDLK_6: {CLOCK_hour++;CLOCK_moving=true;CLOCK_update_clock();}break;
//				//case SDLK_7: {CLOCK_minute--;CLOCK_moving=true;CLOCK_update_clock();}break;
//				//case SDLK_8: {CLOCK_minute++;CLOCK_moving=true;CLOCK_update_clock();}break;
//
//				//TODO: brightness controls
//			case SDLK_MINUS:
//				{
//					if (GLUtils::ZOOMlock == 0)
//					{
//						if (GLUtils::ZOOMto > MINZOOM)GLUtils::ZOOMto -= ZOOMINCREMENT;
//						if (GLUtils::ZOOMto < MINZOOM)GLUtils::ZOOMto = MINZOOM;
//					}
//					//HARDWARE_brightness--;
//					//HARDWARE_create_brightened_palette((void*)GAME_original_SPRITE_PALETTE,(int*)GAME_temp_SPRITE_PALETTE,HARDWARE_brightness);
//					//HARDWARE_load_sprite_palette(1,0,(int*)GAME_temp_SPRITE_PALETTE);
//					//HARDWARE_refresh_sprite_textures();
//					break;
//				}
//			case SDLK_EQUALS:
//				{
//					if (GLUtils::ZOOMlock == 0)
//					{
//						if (GLUtils::ZOOMto < MAXZOOM)GLUtils::ZOOMto += ZOOMINCREMENT;
//						if (GLUtils::ZOOMto > MAXZOOM)GLUtils::ZOOMto = MAXZOOM;
//					}
//					//HARDWARE_brightness++;
//					//HARDWARE_create_brightened_palette((void*)GAME_original_SPRITE_PALETTE,(int*)GAME_temp_SPRITE_PALETTE,HARDWARE_brightness);
//					//HARDWARE_load_sprite_palette(1,0,(int*)GAME_temp_SPRITE_PALETTE);
//					//HARDWARE_refresh_sprite_textures();
//					break;
//				}
//			case SDLK_ESCAPE:
//				{
//					Main::quit = true;
//				}
//				break;
//			default: break;
//			}
//		}
//




//=========================================================================================================================
void ControlsManager::initControllers()
{ //=========================================================================================================================

	log->debug("Init controllers");


	Uint64 start=0, now=0;
	start = SDL_GetPerformanceCounter();




	//   try
	//   {
	//      Controllers::create();
	//   }
	//   catch (exception& e)
	//   {
	//      e.printStackTrace();
	//   }
	//
	//   numControllers = Controllers::getControllerCount();
	//   log->info(to_string(numControllers) + " Controllers Found");
	//
	//   for (int n = 0; n < numControllers; n++)
	//   {
	//      sp<Controller> controller = Controllers::getController(n);
	//      log->info(controller->getName());
	//
	//      if (controllerNames.length() > 0)
	//      {
	//         controllerNames = controllerNames.concat("," + controller->getName());
	//      }
	//      else
	//      {
	//         controllerNames = controllerNames.concat(controller->getName());
	//      }
	//
	//
	//      for (int i = 0; i < controller->getButtonCount(); i++)
	//      {
	//      }
	//      for (int i = 0; i < controller->getAxisCount(); i++)
	//      {
	//         //controller.setDeadZone(i, -1.0f);
	//      }
	//   }



	string s = Main::getPath();
	SDL_GameControllerAddMappingsFromFile(string(s+"data/gamecontrollerdb.txt").c_str());
	//-----------------------------
	//set up controllers
	//-----------------------------
	for (int i = 0; i<SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			sp<SDL_GameController >controller = SDL_GameControllerOpen(i);
			//controllersByJoystickNum->put(i, controller);

			log->info("Found Controller " + to_string(i) + ": " + string(SDL_GameControllerName(controller)));
			sp<SDL_Joystick >joy = SDL_GameControllerGetJoystick(controller);

			log->info("Found Joystick on Controller: " + string(SDL_JoystickName(joy)));

			SDL_JoystickID id = SDL_JoystickInstanceID(joy);
			controllersByJoystickID.put(id, controller);


			sp<GameController> g = ms<GameController>();
			g->id = id;

			gameControllers.add(g);

			sp<SDL_Haptic >haptic = nullptr;
			haptic = SDL_HapticOpenFromJoystick(joy);
			if (haptic != NULL)
			{
				log->info("Found Haptic on Controller: " + string(SDL_JoystickName(joy)));
				g->haptic = haptic;

				SDL_HapticRumbleInit(haptic);


//				// See if it can do sine waves
//				if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE) == 0)
//				{
//					SDL_HapticClose(haptic); // No sine effect
//					haptic = nullptr;
//				}
			}


			
			

			char* mapping = SDL_GameControllerMapping(controller);
			log->info("Controller " + to_string(i) + " is mapped as " + string(mapping));

		}
		else
		{
			log->error("Found a controller device but it is not compatible.");
		}

	}
	SDL_JoystickEventState(SDL_ENABLE);

	//log->debug("Controllers Loaded.");

	now = SDL_GetPerformanceCounter();
	log->debug("Init controllers took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");


	//string path = string(SDL_GetPrefPath("OK Corporation", "bob's game")) + "controls.cfg";

}


//==========================================================================================================================
void ControlsManager::cleanup()
{//==========================================================================================================================

	log->info("Cleaning up controllers");

	for(int i=0;i<gameControllers.size();i++)
	{
		if(gameControllers.get(i)->haptic!=nullptr)
		{
			SDL_HapticClose(gameControllers.get(i)->haptic);
		}
	}

	if (controllersByJoystickID.size()>0)
	{
		sp<vector<sp<SDL_GameController>>>controllers = controllersByJoystickID.getAllValues();

		for (int i = 0; i < controllers->size(); i++)
		{
			sp<SDL_GameController >controller = controllers->get(i);
			SDL_GameControllerClose(controller);
		}
		delete controllers;
	}
	//controllersByJoystickNum->clear();
	controllersByJoystickID.clear();

}

//=========================================================================================================================
void ControlsManager::resetPressedButtons()
{//=========================================================================================================================


	//------------------------------------
	//reset key pressed
	//------------------------------------
	KEY_UP_PRESSED = false;
	KEY_DOWN_PRESSED = false;
	KEY_LEFT_PRESSED = false;
	KEY_RIGHT_PRESSED = false;
	KEY_SPACE_PRESSED = false; //was A
	KEY_TAB_PRESSED = false; //was START
	KEY_RETURN_PRESSED = false; //was SELECT
	KEY_A_PRESSED = false;
	KEY_B_PRESSED = false;
	KEY_C_PRESSED = false;
	KEY_D_PRESSED = false;
	KEY_E_PRESSED = false;
	KEY_F_PRESSED = false;
	KEY_G_PRESSED = false;
	KEY_H_PRESSED = false;
	KEY_I_PRESSED = false;
	KEY_J_PRESSED = false;
	KEY_K_PRESSED = false;
	KEY_L_PRESSED = false;
	KEY_M_PRESSED = false;
	KEY_N_PRESSED = false;
	KEY_O_PRESSED = false;
	KEY_P_PRESSED = false;
	KEY_Q_PRESSED = false;
	KEY_R_PRESSED = false;
	KEY_S_PRESSED = false;
	KEY_T_PRESSED = false;
	KEY_U_PRESSED = false;
	KEY_V_PRESSED = false;
	KEY_W_PRESSED = false;
	KEY_X_PRESSED = false;
	KEY_Y_PRESSED = false;
	KEY_Z_PRESSED = false;
	KEY_COMMA_PRESSED = false;
	KEY_PERIOD_PRESSED = false;
	KEY_FRONTSLASH_PRESSED = false;
	KEY_SEMICOLON_PRESSED = false;
	KEY_QUOTE_PRESSED = false;
	KEY_BACKSLASH_PRESSED = false;

	KEY_LBRACKET_PRESSED = false; //was L
	KEY_RBRACKET_PRESSED = false; //was R
	KEY_RALT_PRESSED = false;
	KEY_LALT_PRESSED = false;
	KEY_LSHIFT_PRESSED = false; //was B
	KEY_RSHIFT_PRESSED = false; //quickzoom
	KEY_LCTRL_PRESSED = false;
	KEY_RCTRL_PRESSED = false; //quickzoom
	KEY_BACKSPACE_PRESSED = false; //reset zoom
	KEY_ESC_PRESSED = false;
	KEY_F1_PRESSED = false;
	KEY_F2_PRESSED = false;
	KEY_F3_PRESSED = false;
	KEY_F4_PRESSED = false;
	KEY_F5_PRESSED = false;
	KEY_F6_PRESSED = false;
	KEY_F7_PRESSED = false;
	KEY_F8_PRESSED = false;
	KEY_F9_PRESSED = false;
	KEY_F10_PRESSED = false;
	KEY_F11_PRESSED = false;
	KEY_F12_PRESSED = false;
	KEY_PRINTSCREEN_PRESSED = false;
	KEY_PAUSE_PRESSED = false;
	KEY_TILDE_PRESSED = false;
	KEY_1_PRESSED = false;
	KEY_2_PRESSED = false;
	KEY_3_PRESSED = false;
	KEY_4_PRESSED = false;
	KEY_5_PRESSED = false;
	KEY_6_PRESSED = false;
	KEY_7_PRESSED = false;
	KEY_8_PRESSED = false;
	KEY_9_PRESSED = false;
	KEY_0_PRESSED = false;
	KEY_MINUS_PRESSED = false; //zoom in
	KEY_PLUS_PRESSED = false; //zoom out
	KEY_NUM0_PRESSED = false;
	KEY_NUM1_PRESSED = false;
	KEY_NUM2_PRESSED = false;
	KEY_NUM3_PRESSED = false;
	KEY_NUM4_PRESSED = false;
	KEY_NUM5_PRESSED = false;
	KEY_NUM6_PRESSED = false;
	KEY_NUM7_PRESSED = false;
	KEY_NUM8_PRESSED = false;
	KEY_NUM9_PRESSED = false;

	MOUSE_LEFTBUTTON_PRESSED = false;

	//------------------------------------
	//reset controller pressed
	//------------------------------------

	for (int i = 0; i < gameControllers.size(); i++)
	{
		sp<GameController>g = gameControllers.get(i);
		g->resetPressedButtons();
	}


	//------------------------------------
	//reset game button pressed
	//------------------------------------

	BGCLIENT_UP_PRESSED = false;
	BGCLIENT_DOWN_PRESSED = false;
	BGCLIENT_LEFT_PRESSED = false;
	BGCLIENT_RIGHT_PRESSED = false;
	BGCLIENT_ACTION_PRESSED = false;
	BGCLIENT_CANCELRUN_PRESSED = false;
	//BGCLIENT_START_PRESSED = false;
	//BGCLIENT_SELECT_PRESSED = false;
	BGCLIENT_OPENND_PRESSED = false;
	BGCLIENT_ZOOMOUT_PRESSED = false;
	BGCLIENT_ZOOMIN_PRESSED = false;
	BGCLIENT_ZOOMRESET_PRESSED = false;
	BGCLIENT_OPENMENU_PRESSED = false;
	BGCLIENT_QUICKZOOMOUT_PRESSED = false;
	BGCLIENT_QUICKZOOMIN_PRESSED = false;


	MINIGAME_UP_PRESSED = false;
	MINIGAME_DOWN_PRESSED = false;
	MINIGAME_LEFT_PRESSED = false;
	MINIGAME_RIGHT_PRESSED = false;
	MINIGAME_ANALOGUP_PRESSED = false;
	MINIGAME_ANALOGDOWN_PRESSED = false;
	MINIGAME_ANALOGLEFT_PRESSED = false;
	MINIGAME_ANALOGRIGHT_PRESSED = false;
	//MINIGAME_ACTION_PRESSED = false;//TODO: can be customized to either a or b
	//MINIGAME_RUN_PRESSED = false;//TODO: can be customized to either a or b
	//MINIGAME_START_PRESSED = false;
	//MINIGAME_SELECT_PRESSED = false;
	MINIGAME_L_PRESSED = false;
	MINIGAME_R_PRESSED = false;
	MINIGAME_Y_PRESSED = false;
	MINIGAME_X_PRESSED = false;
	MINIGAME_A_PRESSED = false;
	MINIGAME_B_PRESSED = false;
}

//=========================================================================================================================
void ControlsManager::unsetHeldButtons()
{//=========================================================================================================================
	

	KEY_UP_HELD = false;
	KEY_DOWN_HELD = false;
	KEY_LEFT_HELD = false;
	KEY_RIGHT_HELD = false;
	KEY_SPACE_HELD = false; //was A
	KEY_TAB_HELD = false; //was START
	KEY_RETURN_HELD = false; //was SELECT
	KEY_A_HELD = false;
	KEY_B_HELD = false;
	KEY_C_HELD = false;
	KEY_D_HELD = false;
	KEY_E_HELD = false;
	KEY_F_HELD = false;
	KEY_G_HELD = false;
	KEY_H_HELD = false;
	KEY_I_HELD = false;
	KEY_J_HELD = false;
	KEY_K_HELD = false;
	KEY_L_HELD = false;
	KEY_M_HELD = false;
	KEY_N_HELD = false;
	KEY_O_HELD = false;
	KEY_P_HELD = false;
	KEY_Q_HELD = false;
	KEY_R_HELD = false;
	KEY_S_HELD = false;
	KEY_T_HELD = false;
	KEY_U_HELD = false;
	KEY_V_HELD = false;
	KEY_W_HELD = false;
	KEY_X_HELD = false;
	KEY_Y_HELD = false;
	KEY_Z_HELD = false;
	KEY_COMMA_HELD = false;
	KEY_PERIOD_HELD = false;
	KEY_FRONTSLASH_HELD = false;
	KEY_SEMICOLON_HELD = false;
	KEY_QUOTE_HELD = false;
	KEY_BACKSLASH_HELD = false;

	KEY_LBRACKET_HELD = false; //was L
	KEY_RBRACKET_HELD = false; //was R
	KEY_RALT_HELD = false;
	KEY_LALT_HELD = false;
	KEY_LSHIFT_HELD = false; //was B
	KEY_RSHIFT_HELD = false; //quickzoom
	KEY_LCTRL_HELD = false;
	KEY_RCTRL_HELD = false; //quickzoom
	KEY_BACKSPACE_HELD = false; //reset zoom
	KEY_ESC_HELD = false;
	KEY_F1_HELD = false;
	KEY_F2_HELD = false;
	KEY_F3_HELD = false;
	KEY_F4_HELD = false;
	KEY_F5_HELD = false;
	KEY_F6_HELD = false;
	KEY_F7_HELD = false;
	KEY_F8_HELD = false;
	KEY_F9_HELD = false;
	KEY_F10_HELD = false;
	KEY_F11_HELD = false;
	KEY_F12_HELD = false;
	KEY_PRINTSCREEN_HELD = false;
	KEY_PAUSE_HELD = false;
	KEY_TILDE_HELD = false;
	KEY_1_HELD = false;
	KEY_2_HELD = false;
	KEY_3_HELD = false;
	KEY_4_HELD = false;
	KEY_5_HELD = false;
	KEY_6_HELD = false;
	KEY_7_HELD = false;
	KEY_8_HELD = false;
	KEY_9_HELD = false;
	KEY_0_HELD = false;
	KEY_MINUS_HELD = false; //zoom in
	KEY_PLUS_HELD = false; //zoom out
	KEY_NUM0_HELD = false;
	KEY_NUM1_HELD = false;
	KEY_NUM2_HELD = false;
	KEY_NUM3_HELD = false;
	KEY_NUM4_HELD = false;
	KEY_NUM5_HELD = false;
	KEY_NUM6_HELD = false;
	KEY_NUM7_HELD = false;
	KEY_NUM8_HELD = false;
	KEY_NUM9_HELD = false;



	BGCLIENT_UP_HELD = false;
	BGCLIENT_DOWN_HELD = false;
	BGCLIENT_LEFT_HELD = false;
	BGCLIENT_RIGHT_HELD = false;
	BGCLIENT_ACTION_HELD = false;
	BGCLIENT_CANCELRUN_HELD = false;
	//BGCLIENT_START_HELD = false;
	//BGCLIENT_SELECT_HELD = false;
	BGCLIENT_OPENND_HELD = false;
	BGCLIENT_ZOOMOUT_HELD = false;
	BGCLIENT_ZOOMIN_HELD = false;
	BGCLIENT_ZOOMRESET_HELD = false;
	BGCLIENT_OPENMENU_HELD = false;
	BGCLIENT_QUICKZOOMOUT_HELD = false;
	BGCLIENT_QUICKZOOMIN_HELD = false;



	MINIGAME_UP_HELD = false;
	MINIGAME_DOWN_HELD = false;
	MINIGAME_LEFT_HELD = false;
	MINIGAME_RIGHT_HELD = false;
	MINIGAME_ANALOGUP_HELD = false;
	MINIGAME_ANALOGDOWN_HELD = false;
	MINIGAME_ANALOGLEFT_HELD = false;
	MINIGAME_ANALOGRIGHT_HELD = false;
	//MINIGAME_ACTION_HELD  = false;
	//MINIGAME_RUN_HELD  = false;
	//MINIGAME_START_HELD  = false;
	//MINIGAME_SELECT_HELD  = false;
	MINIGAME_L_HELD = false;
	MINIGAME_R_HELD = false;
	MINIGAME_Y_HELD = false;
	MINIGAME_X_HELD = false;
	MINIGAME_A_HELD = false;
	MINIGAME_B_HELD = false;


	BGCLIENT_UP_HELD = false;
	BGCLIENT_DOWN_HELD = false;
	BGCLIENT_LEFT_HELD = false;
	BGCLIENT_RIGHT_HELD = false;
	BGCLIENT_ACTION_HELD = false;
	BGCLIENT_CANCELRUN_HELD = false;
	//BGCLIENT_START_HELD = false;
	//BGCLIENT_SELECT_HELD = false;
	BGCLIENT_OPENND_HELD = false;
	BGCLIENT_ZOOMOUT_HELD = false;
	BGCLIENT_ZOOMIN_HELD = false;
	BGCLIENT_ZOOMRESET_HELD = false;
	BGCLIENT_OPENMENU_HELD = false;
	BGCLIENT_QUICKZOOMOUT_HELD = false;
	BGCLIENT_QUICKZOOMIN_HELD = false;


	MINIGAME_UP_HELD = false;
	MINIGAME_DOWN_HELD = false;
	MINIGAME_LEFT_HELD = false;
	MINIGAME_RIGHT_HELD = false;
	MINIGAME_ANALOGUP_HELD = false;
	MINIGAME_ANALOGDOWN_HELD = false;
	MINIGAME_ANALOGLEFT_HELD = false;
	MINIGAME_ANALOGRIGHT_HELD = false;
	MINIGAME_ACTION_HELD = false;
	MINIGAME_RUN_HELD = false;
	MINIGAME_START_HELD = false;
	MINIGAME_SELECT_HELD = false;
	MINIGAME_L_HELD = false;
	MINIGAME_R_HELD = false;
	MINIGAME_X_HELD = false;
	MINIGAME_Y_HELD = false;
	MINIGAME_A_HELD = false;
	MINIGAME_B_HELD = false;

}

//=========================================================================================================================
void ControlsManager::setButtonStates()
{//=========================================================================================================================

	//------------------------------------
	//see if button was held last frame
	//if it wasnt, pressed = 1
	//------------------------------------

	//------------------------------------
	//store held
	//------------------------------------

	bool LAST_KEY_UP_HELD = KEY_UP_HELD;
	bool LAST_KEY_DOWN_HELD = KEY_DOWN_HELD;
	bool LAST_KEY_LEFT_HELD = KEY_LEFT_HELD;
	bool LAST_KEY_RIGHT_HELD = KEY_RIGHT_HELD;
	bool LAST_KEY_SPACE_HELD = KEY_SPACE_HELD; //was A
	bool LAST_KEY_TAB_HELD = KEY_TAB_HELD; //was START
	bool LAST_KEY_RETURN_HELD = KEY_RETURN_HELD; //was SELECT
	bool LAST_KEY_A_HELD = KEY_A_HELD;
	bool LAST_KEY_B_HELD = KEY_B_HELD;
	bool LAST_KEY_C_HELD = KEY_C_HELD;
	bool LAST_KEY_D_HELD = KEY_D_HELD;
	bool LAST_KEY_E_HELD = KEY_E_HELD;
	bool LAST_KEY_F_HELD = KEY_F_HELD;
	bool LAST_KEY_G_HELD = KEY_G_HELD;
	bool LAST_KEY_H_HELD = KEY_H_HELD;
	bool LAST_KEY_I_HELD = KEY_I_HELD;
	bool LAST_KEY_J_HELD = KEY_J_HELD;
	bool LAST_KEY_K_HELD = KEY_K_HELD;
	bool LAST_KEY_L_HELD = KEY_L_HELD;
	bool LAST_KEY_M_HELD = KEY_M_HELD;
	bool LAST_KEY_N_HELD = KEY_N_HELD;
	bool LAST_KEY_O_HELD = KEY_O_HELD;
	bool LAST_KEY_P_HELD = KEY_P_HELD;
	bool LAST_KEY_Q_HELD = KEY_Q_HELD;
	bool LAST_KEY_R_HELD = KEY_R_HELD;
	bool LAST_KEY_S_HELD = KEY_S_HELD;
	bool LAST_KEY_T_HELD = KEY_T_HELD;
	bool LAST_KEY_U_HELD = KEY_U_HELD;
	bool LAST_KEY_V_HELD = KEY_V_HELD;
	bool LAST_KEY_W_HELD = KEY_W_HELD;
	bool LAST_KEY_X_HELD = KEY_X_HELD;
	bool LAST_KEY_Y_HELD = KEY_Y_HELD;
	bool LAST_KEY_Z_HELD = KEY_Z_HELD;
	bool LAST_KEY_COMMA_HELD = KEY_COMMA_HELD;
	bool LAST_KEY_PERIOD_HELD = KEY_PERIOD_HELD;
	bool LAST_KEY_FRONTSLASH_HELD = KEY_FRONTSLASH_HELD;
	bool LAST_KEY_SEMICOLON_HELD = KEY_SEMICOLON_HELD;
	bool LAST_KEY_QUOTE_HELD = KEY_QUOTE_HELD;
	bool LAST_KEY_BACKSLASH_HELD = KEY_BACKSLASH_HELD;

	bool LAST_KEY_LBRACKET_HELD = KEY_LBRACKET_HELD; //was L
	bool LAST_KEY_RBRACKET_HELD = KEY_RBRACKET_HELD; //was R
	bool LAST_KEY_RALT_HELD = KEY_RALT_HELD;
	bool LAST_KEY_LALT_HELD = KEY_LALT_HELD;
	bool LAST_KEY_LSHIFT_HELD = KEY_LSHIFT_HELD; //was B
	bool LAST_KEY_RSHIFT_HELD = KEY_RSHIFT_HELD; //quickzoom
	bool LAST_KEY_LCTRL_HELD = KEY_LCTRL_HELD;
	bool LAST_KEY_RCTRL_HELD = KEY_RCTRL_HELD; //quickzoom
	bool LAST_KEY_BACKSPACE_HELD = KEY_BACKSPACE_HELD; //reset zoom
	bool LAST_KEY_ESC_HELD = KEY_ESC_HELD;
	bool LAST_KEY_F1_HELD = KEY_F1_HELD;
	bool LAST_KEY_F2_HELD = KEY_F2_HELD;
	bool LAST_KEY_F3_HELD = KEY_F3_HELD;
	bool LAST_KEY_F4_HELD = KEY_F4_HELD;
	bool LAST_KEY_F5_HELD = KEY_F5_HELD;
	bool LAST_KEY_F6_HELD = KEY_F6_HELD;
	bool LAST_KEY_F7_HELD = KEY_F7_HELD;
	bool LAST_KEY_F8_HELD = KEY_F8_HELD;
	bool LAST_KEY_F9_HELD = KEY_F9_HELD;
	bool LAST_KEY_F10_HELD = KEY_F10_HELD;
	bool LAST_KEY_F11_HELD = KEY_F11_HELD;
	bool LAST_KEY_F12_HELD = KEY_F12_HELD;
	bool LAST_KEY_PRINTSCREEN_HELD = KEY_PRINTSCREEN_HELD;
	bool LAST_KEY_PAUSE_HELD = KEY_PAUSE_HELD;
	bool LAST_KEY_TILDE_HELD = KEY_TILDE_HELD;
	bool LAST_KEY_1_HELD = KEY_1_HELD;
	bool LAST_KEY_2_HELD = KEY_2_HELD;
	bool LAST_KEY_3_HELD = KEY_3_HELD;
	bool LAST_KEY_4_HELD = KEY_4_HELD;
	bool LAST_KEY_5_HELD = KEY_5_HELD;
	bool LAST_KEY_6_HELD = KEY_6_HELD;
	bool LAST_KEY_7_HELD = KEY_7_HELD;
	bool LAST_KEY_8_HELD = KEY_8_HELD;
	bool LAST_KEY_9_HELD = KEY_9_HELD;
	bool LAST_KEY_0_HELD = KEY_0_HELD;
	bool LAST_KEY_MINUS_HELD = KEY_MINUS_HELD; //zoom in
	bool LAST_KEY_PLUS_HELD = KEY_PLUS_HELD; //zoom out
	bool LAST_KEY_NUM0_HELD = KEY_NUM0_HELD;
	bool LAST_KEY_NUM1_HELD = KEY_NUM1_HELD;
	bool LAST_KEY_NUM2_HELD = KEY_NUM2_HELD;
	bool LAST_KEY_NUM3_HELD = KEY_NUM3_HELD;
	bool LAST_KEY_NUM4_HELD = KEY_NUM4_HELD;
	bool LAST_KEY_NUM5_HELD = KEY_NUM5_HELD;
	bool LAST_KEY_NUM6_HELD = KEY_NUM6_HELD;
	bool LAST_KEY_NUM7_HELD = KEY_NUM7_HELD;
	bool LAST_KEY_NUM8_HELD = KEY_NUM8_HELD;
	bool LAST_KEY_NUM9_HELD = KEY_NUM9_HELD;


	for (int i = 0; i < gameControllers.size(); i++)
	{
		sp<GameController>g = gameControllers.get(i);
		g->setButtonStates();
	}



	bool LAST_BGCLIENT_UP_HELD = BGCLIENT_UP_HELD;
	bool LAST_BGCLIENT_DOWN_HELD = BGCLIENT_DOWN_HELD;
	bool LAST_BGCLIENT_LEFT_HELD = BGCLIENT_LEFT_HELD;
	bool LAST_BGCLIENT_RIGHT_HELD = BGCLIENT_RIGHT_HELD;
	bool LAST_BGCLIENT_ACTION_HELD = BGCLIENT_ACTION_HELD;
	bool LAST_BGCLIENT_CANCELRUN_HELD = BGCLIENT_CANCELRUN_HELD;
	//bool LAST_BGCLIENT_START_HELD = BGCLIENT_START_HELD;
	//bool LAST_BGCLIENT_SELECT_HELD = BGCLIENT_SELECT_HELD;
	bool LAST_BGCLIENT_OPENND_HELD = BGCLIENT_OPENND_HELD;
	bool LAST_BGCLIENT_ZOOMOUT_HELD = BGCLIENT_ZOOMOUT_HELD;
	bool LAST_BGCLIENT_ZOOMIN_HELD = BGCLIENT_ZOOMIN_HELD;
	bool LAST_BGCLIENT_ZOOMRESET_HELD = BGCLIENT_ZOOMRESET_HELD;
	bool LAST_BGCLIENT_OPENMENU_HELD = BGCLIENT_OPENMENU_HELD;
	bool LAST_BGCLIENT_QUICKZOOMOUT_HELD = BGCLIENT_QUICKZOOMOUT_HELD;
	bool LAST_BGCLIENT_QUICKZOOMIN_HELD = BGCLIENT_QUICKZOOMIN_HELD;



	bool LAST_MINIGAME_UP_HELD = MINIGAME_UP_HELD ;
	bool LAST_MINIGAME_DOWN_HELD = MINIGAME_DOWN_HELD ;
	bool LAST_MINIGAME_LEFT_HELD = MINIGAME_LEFT_HELD ;
	bool LAST_MINIGAME_RIGHT_HELD = MINIGAME_RIGHT_HELD ;
	bool LAST_MINIGAME_ANALOGUP_HELD = MINIGAME_ANALOGUP_HELD ;
	bool LAST_MINIGAME_ANALOGDOWN_HELD = MINIGAME_ANALOGDOWN_HELD ;
	bool LAST_MINIGAME_ANALOGLEFT_HELD = MINIGAME_ANALOGLEFT_HELD ;
	bool LAST_MINIGAME_ANALOGRIGHT_HELD = MINIGAME_ANALOGRIGHT_HELD ;
	//bool LAST_MINIGAME_ACTION_HELD = MINIGAME_ACTION_HELD ;
	//bool LAST_MINIGAME_RUN_HELD = MINIGAME_RUN_HELD ;
	//bool LAST_MINIGAME_START_HELD = MINIGAME_START_HELD ;
	//bool LAST_MINIGAME_SELECT_HELD = MINIGAME_SELECT_HELD ;
	bool LAST_MINIGAME_L_HELD = MINIGAME_L_HELD ;
	bool LAST_MINIGAME_R_HELD = MINIGAME_R_HELD ;
	bool LAST_MINIGAME_Y_HELD = MINIGAME_Y_HELD ;
	bool LAST_MINIGAME_X_HELD = MINIGAME_X_HELD ;
	bool LAST_MINIGAME_A_HELD = MINIGAME_A_HELD ;
	bool LAST_MINIGAME_B_HELD = MINIGAME_B_HELD ;

	//------------------------------------
	//reset held
	//------------------------------------

	//only reset held for game buttons, hardware buttons get set by SDL events

	BGCLIENT_UP_HELD = false;
	BGCLIENT_DOWN_HELD = false;
	BGCLIENT_LEFT_HELD = false;
	BGCLIENT_RIGHT_HELD = false;
	BGCLIENT_ACTION_HELD = false;
	BGCLIENT_CANCELRUN_HELD = false;
	//BGCLIENT_START_HELD = false;
	//BGCLIENT_SELECT_HELD = false;
	BGCLIENT_OPENND_HELD = false;
	BGCLIENT_ZOOMOUT_HELD = false;
	BGCLIENT_ZOOMIN_HELD = false;
	BGCLIENT_ZOOMRESET_HELD = false;
	BGCLIENT_OPENMENU_HELD = false;
	BGCLIENT_QUICKZOOMOUT_HELD = false;
	BGCLIENT_QUICKZOOMIN_HELD = false;


	MINIGAME_UP_HELD = false;
	MINIGAME_DOWN_HELD = false;
	MINIGAME_LEFT_HELD = false;
	MINIGAME_RIGHT_HELD = false;	
	MINIGAME_ANALOGUP_HELD = false;
	MINIGAME_ANALOGDOWN_HELD = false;
	MINIGAME_ANALOGLEFT_HELD = false;
	MINIGAME_ANALOGRIGHT_HELD = false;
	MINIGAME_ACTION_HELD = false;
	MINIGAME_RUN_HELD = false;
	MINIGAME_START_HELD = false;
	MINIGAME_SELECT_HELD = false;
	MINIGAME_L_HELD = false;
	MINIGAME_R_HELD = false;
	MINIGAME_X_HELD = false;
	MINIGAME_Y_HELD = false;
	MINIGAME_A_HELD = false;
	MINIGAME_B_HELD = false;
	/*
	
	SDL_JoystickClose
SDL_JoystickCurrentPowerLevel
SDL_JoystickEventState
SDL_JoystickFromInstanceID
SDL_JoystickGetAttached
SDL_JoystickGetAxis
SDL_JoystickGetBall
SDL_JoystickGetButton
SDL_JoystickGetDeviceGUID
SDL_JoystickGetGUID
SDL_JoystickGetGUIDFromString
SDL_JoystickGetGUIDString
SDL_JoystickGetHat
SDL_JoystickInstanceID
SDL_JoystickIsHaptic
SDL_JoystickName
SDL_JoystickNameForIndex
SDL_JoystickNumAxes
SDL_JoystickNumBalls
SDL_JoystickNumButtons
SDL_JoystickNumHats
SDL_JoystickOpen
SDL_JoystickUpdate

SDL_GameControllerAddMapping
SDL_GameControllerAddMappingsFromFile
SDL_GameControllerAddMappingsFromRW
SDL_GameControllerClose
SDL_GameControllerEventState
SDL_GameControllerFromInstanceID
SDL_GameControllerGetAttached
SDL_GameControllerGetAxis
SDL_GameControllerGetAxisFromString
SDL_GameControllerGetBindForAxis
SDL_GameControllerGetBindForButton
SDL_GameControllerGetButton
SDL_GameControllerGetButtonFromString
SDL_GameControllerGetJoystick
SDL_GameControllerGetStringForAxis
SDL_GameControllerGetStringForButton
SDL_GameControllerMapping
SDL_GameControllerMappingForGUID
SDL_GameControllerName
SDL_GameControllerNameForIndex
SDL_GameControllerOpen
SDL_GameControllerUpdate

SDL_ControllerAxisEvent
SDL_ControllerButtonEvent
SDL_ControllerDeviceEvent

SDL_JoyAxisEvent
SDL_JoyBallEvent
SDL_JoyButtonEvent
SDL_JoyDeviceEvent
SDL_JoyHatEvent
	*/
//
//
//		if (controllersByJoystickNum->size()>0)
//		{
//			//these get updated by events automatically
//			//SDL_GameControllerUpdate();
//			//SDL_JoystickUpdate();
//	
//	
//			//analog
//			int xval = 0;
//			int yval = 0;
//	
//			xval = SDL_JoystickGetAxis(stick, 0);//x axis, returns -32767 to 32767
//			yval = SDL_JoystickGetAxis(stick, 1);//y axis
//	
//			if (xval < 0 - DEADZONE || xval > DEADZONE)
//			{
//				 if(xval>0)BGCLIENT_RIGHT_HELD=true;
//				 if(xval<0)BGCLIENT_LEFT_HELD=true;
//			}
//	
//			if (yval < 0 - DEADZONE || yval > DEADZONE)
//			{
//				 if(yval>0)BGCLIENT_DOWN_HELD=true;
//				 if(yval<0)BGCLIENT_UP_HELD=true;
//			}
//	
//	
//			//dpad
//			int dpad = SDL_JoystickGetHat(stick, 0);
//	
//			//      switch (dpad)
//			//      {
//			//         // case SDL_HAT_RIGHTUP:{BGCLIENT_UP_HELD=1;BGCLIENT_RIGHT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_RIGHTDOWN:{BGCLIENT_DOWN_HELD=1;BGCLIENT_RIGHT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_LEFTUP:{BGCLIENT_UP_HELD=1;BGCLIENT_LEFT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_LEFTDOWN:{BGCLIENT_DOWN_HELD=1;BGCLIENT_LEFT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//
//			//         // case SDL_HAT_UP:{BGCLIENT_UP_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_RIGHT:{BGCLIENT_RIGHT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_DOWN:{BGCLIENT_DOWN_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//         // case SDL_HAT_LEFT:{BGCLIENT_LEFT_HELD=1;YUU_WALKING_SPEED=YUU_WALKING_SPEED_JOYSTICK;}break;
//			//
//			//         /*
//			//         case SDL_HAT_CENTERED:
//			//         {
//			//         BGCLIENT_UP_HELD=0;
//			//         BGCLIENT_DOWN_HELD=0;
//			//         BGCLIENT_LEFT_HELD=0;
//			//         BGCLIENT_RIGHT_HELD=0;
//			//         }break;
//			//         */
//			//
//			//      default: break;
//			//      }
//	
//	
//			//buttons
//			if (SDL_JoystickGetButton(stick, 1) == 1)BGCLIENT_A_HELD = 1;
//			if (SDL_JoystickGetButton(stick, 0) == 1)BGCLIENT_B_HELD = 1;
//	
//			if (SDL_JoystickGetButton(stick, 2) == 1)BGCLIENT_Y_HELD = 1;
//			if (SDL_JoystickGetButton(stick, 3) == 1)BGCLIENT_X_HELD = 1;
//	
//			if (SDL_JoystickGetButton(stick, 4) == 1)BGCLIENT_L_HELD = 1;
//			if (SDL_JoystickGetButton(stick, 5) == 1)BGCLIENT_R_HELD = 1;
//	
//			if (SDL_JoystickGetButton(stick, 6) == 1)BGCLIENT_SELECT_HELD = 1;
//			if (SDL_JoystickGetButton(stick, 7) == 1)BGCLIENT_START_HELD = 1;
//		}
//

//bool Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_DPAD_UP);
//bool Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_DPAD_DOWN);
//bool Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_DPAD_LEFT);
//bool Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_DPAD_RIGHT);
//bool Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_START);
//bool Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_BACK);
//bool LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_LEFTSHOULDER);
//bool RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_RIGHTSHOULDER);
//bool AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_A);
//bool BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_B);
//bool XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_X);
//bool YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BGCLIENT_Y);
//
//int16 StickX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);
//int16 StickY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);

//sp<SDL_Joystick >JoystickHandle = SDL_GameControllerGetJoystick(ControllerHandles[ControllerIndex]);
//RumbleHandles[ControllerIndex] = SDL_HapticOpenFromJoystick(JoystickHandle);
//
//if (SDL_HapticRumbleInit(RumbleHandles[ControllerIndex]) != 0)
//{
//	SDL_HapticClose(RumbleHandles[ControllerIndex]);
//	RumbleHandles[ControllerIndex] = 0;
//}
//
//if (BButton)
//{
//	if (RumbleHandle[ControllerIndex])
//	{
//		SDL_HapticRumblePlay(RumbleHandle[ControllerIndex], 0.5f, 2000);
//	}
//}
//
//if (RumbleHandles[ControllerIndex])
//SDL_HapticClose(RumbleHandles[ControllerIndex]);
//

	//------------------------------------
	//set key held
	//------------------------------------
	//if(Mouse.isButtonDown(0))MOUSEBGCLIENT_0_HELD=true;else MOUSEBGCLIENT_0_HELD=false;




//
//ArrayList<sp<SDL_GameController>> *c = controllersByJoystickID.getAllValues();
//
//for (int i = 0; i < c->size(); i++)
//{
//	sp<SDL_GameController> controller = c->get(i);
//
//
//	//doesn't work
//	{
//		int value = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
//		//log->debug("Controller " + to_string(i) + " Axis X Value: "+to_string(value));
//		if (value >= 20000) { CONTROLLER1_ANALOGLEFT_HELD = true; log->debug("left held"); }
//		else if (value <= -20000) { CONTROLLER1_ANALOGRIGHT_HELD = true; log->debug("right held"); }
//		else if (value <= 20000 && value >= -20000) { CONTROLLER1_ANALOGLEFT_HELD = false; CONTROLLER1_ANALOGRIGHT_HELD = false; }
//
//		value = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
//		if (value >= 20000) { CONTROLLER1_ANALOGUP_HELD = true; log->debug("up held"); }
//		else if (value <= -20000) { CONTROLLER1_ANALOGDOWN_HELD = true; log->debug("down held"); }
//		else if (value <= 20000 && value >= -20000) { CONTROLLER1_ANALOGUP_HELD = false; CONTROLLER1_ANALOGDOWN_HELD = false; }
//	}
//
//
//
//	char* mappingChar = SDL_GameControllerMapping(controller);
//	string mapping = string(mappingChar);
//	SDL_free(mappingChar);
//
//	sp<SDL_Joystick >joy = SDL_GameControllerGetJoystick(controller);
//
//	int axes = SDL_JoystickNumAxes(joy);
//
//	for (int a = 0; a<axes; a++)
//	{
//
//		//find axis value for lefttrigger and righttrigger in mapping string
//		string axisString = "a" + to_string(a);
//
//		//78696e70757401000000000000000000,HORIPAD,platform:Windows,x:b2,a:b0,b:b1,y:b3,back:b6,guide:b10,start:b7,dpleft:h0.8,dpdown:h0.4,dpright:h0.2,dpup:h0.1,leftshoulder:b4,lefttrigger:a2,rightshoulder:b5,righttrigger:a5,leftstick:b8,rightstick:b9,leftx:a0,lefty:a1,rightx:a3,righty:a4,
//
//
//		bool leftX = false;
//		bool leftY = false;
//
//		if (mapping.find("leftx:" + axisString + ",") != string::npos)leftX = true;
//		else if (mapping.find("lefty:" + axisString + ",") != string::npos)leftY = true;
//
//		if (leftX)
//		{
//			int value = SDL_JoystickGetAxis(joy, a);
//			//log->debug(to_string(value));
//			if (value >= 20000) { CONTROLLER1_ANALOGLEFT_HELD = true; log->debug("left held"); }
//			else if (value <= -20000) { CONTROLLER1_ANALOGRIGHT_HELD = true; log->debug("right held"); }
//			else if (value <= 20000 && value >= -20000) { CONTROLLER1_ANALOGLEFT_HELD = false; CONTROLLER1_ANALOGRIGHT_HELD = false; }
//		}
//		if (leftY)
//		{
//			int value = SDL_JoystickGetAxis(joy, a);
//			if (value >= 20000) { CONTROLLER1_ANALOGUP_HELD = true; log->debug("up held"); }
//			else if (value <= -20000) { CONTROLLER1_ANALOGDOWN_HELD = true; log->debug("down held"); }
//			else if (value <= 20000 && value >= -20000) { CONTROLLER1_ANALOGUP_HELD = false; CONTROLLER1_ANALOGDOWN_HELD = false; }
//		}
//
//	}
//}



	//While there are events to handle
	while (events.size()>0)
	{
		SDL_Event event = events.get(0);
		events.removeAt(0);

		if (event.type == SDL_CONTROLLERDEVICEADDED) 
		{
			int joystickDeviceIndex = event.cdevice.which;
			if (SDL_IsGameController(joystickDeviceIndex))
			{

				sp<SDL_GameController >controller = SDL_GameControllerOpen(joystickDeviceIndex);
				sp<SDL_Joystick >joy = SDL_GameControllerGetJoystick(controller);
				SDL_JoystickID joystickID = SDL_JoystickInstanceID(joy);

				if (controllersByJoystickID.containsValue(controller) == false)
				{
					//controllersByJoystickNum->put(i,controller);
					log->debug("New Controller Connected: " + to_string(joystickDeviceIndex) + ": " + string(SDL_GameControllerName(controller)));
				}
				else
				{
					log->debug("Existing Controller Reconnected: " + to_string(joystickDeviceIndex) + ": " + string(SDL_GameControllerName(controller)));
				}

				controllersByJoystickID.removeAllValues(controller);
				controllersByJoystickID.put(joystickID, controller);
				log->debug("Found Joystick on Controller: " + string(SDL_JoystickName(joy)));

				for (int n = 0; n < gameControllers.size(); n++)
				{
					sp<GameController>g = gameControllers.get(n);
					if (g->id == joystickID)
					{
						gameControllers.removeAt(n);
						n = 0;
					}
				}



				sp<GameController> g = ms<GameController>();
				g->id = joystickID;
				gameControllers.add(g);

				sp<SDL_Haptic >haptic = nullptr;
				haptic = SDL_HapticOpenFromJoystick(joy);
				if (haptic != NULL)
				{
					log->info("Found Haptic on Controller: " + string(SDL_JoystickName(joy)));
					g->haptic = haptic;

					SDL_HapticRumbleInit(haptic);


					//				// See if it can do sine waves
					//				if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE) == 0)
					//				{
					//					SDL_HapticClose(haptic); // No sine effect
					//					haptic = nullptr;
					//				}
				}

				char* mapping = SDL_GameControllerMapping(controller);
				log->debug("Controller " + to_string(joystickDeviceIndex) + " is mapped as " + string(mapping));

			}

		}
		
			 if (event.type == SDL_CONTROLLERDEVICEREMOVED)
			 {
				 SDL_JoystickID joystickID = event.cdevice.which;
				 sp<SDL_GameController >controller = controllersByJoystickID.get(joystickID);

				//controllersByJoystickNum->removeAllValues(controller);
				controllersByJoystickID.removeAllValues(controller);


				for (int i = 0; i < gameControllers.size(); i++)
				{
					sp<GameController>g = gameControllers.get(i);
					if (g->id == joystickID)
					{
						if(g->haptic!=nullptr)SDL_HapticClose(g->haptic);
						gameControllers.removeAt(i);
						i = 0;
					}
				}			

				SDL_GameControllerClose(controller);

				log->debug("Controller Removed: " + string(SDL_GameControllerName(controller)));


			 }
			 
			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				int joystickID = event.cbutton.which;

				if (controllersByJoystickID.containsKey(joystickID))
				{
					sp<SDL_GameController >controller = controllersByJoystickID.get(joystickID);
					SDL_GameControllerButton b = (SDL_GameControllerButton)event.cbutton.button;
					int value = event.cbutton.state;


					string s = string("Controller Button Down Event: " + string(SDL_GameControllerName(controller)));
					if (b == SDL_CONTROLLER_BUTTON_A)s += (" Button: SDL_CONTROLLER_BUTTON_A");
					if (b == SDL_CONTROLLER_BUTTON_B)s += (" Button: SDL_CONTROLLER_BUTTON_B");
					if (b == SDL_CONTROLLER_BUTTON_X)s += (" Button: SDL_CONTROLLER_BUTTON_X");
					if (b == SDL_CONTROLLER_BUTTON_Y)s += (" Button: SDL_CONTROLLER_BUTTON_Y");
					if (b == SDL_CONTROLLER_BUTTON_BACK)s += (" Button: SDL_CONTROLLER_BUTTON_BACK");
					if (b == SDL_CONTROLLER_BUTTON_GUIDE)s += (" Button: SDL_CONTROLLER_BUTTON_GUIDE");
					if (b == SDL_CONTROLLER_BUTTON_START)s += (" Button: SDL_CONTROLLER_BUTTON_START");
					if (b == SDL_CONTROLLER_BUTTON_LEFTSTICK)s += (" Button: SDL_CONTROLLER_BUTTON_LEFTSTICK");
					if (b == SDL_CONTROLLER_BUTTON_RIGHTSTICK)s += (" Button: SDL_CONTROLLER_BUTTON_RIGHTSTICK");
					if (b == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)s += (" Button: SDL_CONTROLLER_BUTTON_LEFTSHOULDER");
					if (b == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)s += (" Button: SDL_CONTROLLER_BUTTON_RIGHTSHOULDER");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_UP)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_UP");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_DOWN)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_DOWN");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_LEFT)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_LEFT");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_RIGHT");
					s += (" Value:" + to_string(value));
#ifdef _DEBUG
					log->debug(s);
#endif
		
					for (int i = 0; i < gameControllers.size(); i++)
					{
						sp<GameController>g = gameControllers.get(i);
						if(g->id == joystickID)
						{
							if (b == SDL_CONTROLLER_BUTTON_A)g->A_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_B)g->B_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_X)g->X_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_Y)g->Y_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_BACK)g->SELECT_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_GUIDE)g->START_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_START)g->START_HELD = true;
							//if (b == SDL_CONTROLLER_BUTTON_LEFTSTICK)log->debug("SDL_CONTROLLER_BUTTON_LEFTSTICK");
							//if (b == SDL_CONTROLLER_BUTTON_RIGHTSTICK)log->debug("SDL_CONTROLLER_BUTTON_RIGHTSTICK");
							if (b == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)g->L_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)g->R_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_UP)g->UP_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_DOWN)g->DOWN_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_LEFT)g->LEFT_HELD = true;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)g->RIGHT_HELD = true;
						}
					}

				}
				
			}
			
			if (event.type == SDL_CONTROLLERBUTTONUP) 
			{

				int id = event.cbutton.which;

				if (controllersByJoystickID.containsKey(id))
				{
					sp<SDL_GameController >controller = controllersByJoystickID.get(id);
					SDL_GameControllerButton b = (SDL_GameControllerButton)event.cbutton.button;
					int value = event.cbutton.state;

					string s = string("Controller Button Up Event: " + string(SDL_GameControllerName(controller)));
					if (b == SDL_CONTROLLER_BUTTON_A)s += (" Button: SDL_CONTROLLER_BUTTON_A");
					if (b == SDL_CONTROLLER_BUTTON_B)s += (" Button: SDL_CONTROLLER_BUTTON_B");
					if (b == SDL_CONTROLLER_BUTTON_X)s += (" Button: SDL_CONTROLLER_BUTTON_X");
					if (b == SDL_CONTROLLER_BUTTON_Y)s += (" Button: SDL_CONTROLLER_BUTTON_Y");
					if (b == SDL_CONTROLLER_BUTTON_BACK)s += (" Button: SDL_CONTROLLER_BUTTON_BACK");
					if (b == SDL_CONTROLLER_BUTTON_GUIDE)s += (" Button: SDL_CONTROLLER_BUTTON_GUIDE");
					if (b == SDL_CONTROLLER_BUTTON_START)s += (" Button: SDL_CONTROLLER_BUTTON_START");
					if (b == SDL_CONTROLLER_BUTTON_LEFTSTICK)s += (" Button: SDL_CONTROLLER_BUTTON_LEFTSTICK");
					if (b == SDL_CONTROLLER_BUTTON_RIGHTSTICK)s += (" Button: SDL_CONTROLLER_BUTTON_RIGHTSTICK");
					if (b == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)s += (" Button: SDL_CONTROLLER_BUTTON_LEFTSHOULDER");
					if (b == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)s += (" Button: SDL_CONTROLLER_BUTTON_RIGHTSHOULDER");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_UP)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_UP");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_DOWN)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_DOWN");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_LEFT)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_LEFT");
					if (b == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)s += (" Button: SDL_CONTROLLER_BUTTON_DPAD_RIGHT");
					s += (" Value:" + to_string(value));
#ifdef _DEBUG
					log->debug(s);
#endif
					for (int i = 0; i < gameControllers.size(); i++)
					{
						sp<GameController>g = gameControllers.get(i);
						if (g->id == id)
						{
							if (b == SDL_CONTROLLER_BUTTON_A)g->A_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_B)g->B_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_X)g->X_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_Y)g->Y_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_BACK)g->SELECT_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_GUIDE)g->START_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_START)g->START_HELD = false;
							//if (b == SDL_CONTROLLER_BUTTON_LEFTSTICK)log->debug("SDL_CONTROLLER_BUTTON_LEFTSTICK");
							//if (b == SDL_CONTROLLER_BUTTON_RIGHTSTICK)log->debug("SDL_CONTROLLER_BUTTON_RIGHTSTICK");
							if (b == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)g->L_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)g->R_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_UP)g->UP_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_DOWN)g->DOWN_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_LEFT)g->LEFT_HELD = false;
							if (b == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)g->RIGHT_HELD = false;
						}
					}
				}
				
			}
			
			if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				int id = event.caxis.which;


				//Unfortunately, this is easier to idenfity because it says "lefttrigger" and is correct, but it ONLY fires an axis down event and not an axis-up event.
				//Oh, it does register an axis up event, it's just value 0 and not -
				if (controllersByJoystickID.containsKey(id))
				{
					sp<SDL_GameController >controller = controllersByJoystickID.get(id);
					SDL_GameControllerAxis axis = (SDL_GameControllerAxis)event.caxis.axis;
					int value = event.caxis.value;

					if (value<0-DEADZONE || value > DEADZONE || value == 0)
					{

#ifdef _DEBUG
						//SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(controller, axis);
						string s = string("Controller Axis Event: " + string(SDL_GameControllerName(controller)));
						if (axis == SDL_CONTROLLER_AXIS_LEFTX)s += (" Axis: SDL_CONTROLLER_AXIS_LEFTX");
						if (axis == SDL_CONTROLLER_AXIS_LEFTY)s += (" Axis: SDL_CONTROLLER_AXIS_LEFTY");
						if (axis == SDL_CONTROLLER_AXIS_RIGHTX)s += (" Axis: SDL_CONTROLLER_AXIS_RIGHTX");
						if (axis == SDL_CONTROLLER_AXIS_RIGHTY)s += (" Axis: SDL_CONTROLLER_AXIS_RIGHTY");
						if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)s += (" Axis: SDL_CONTROLLER_AXIS_TRIGGERLEFT");
						if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)s += (" Axis: SDL_CONTROLLER_AXIS_TRIGGERRIGHT");
						s += " Value:" + to_string(value);

						log->debug(s);
						//log->debug("SDL_GameControllerGetStringForAxis:" + string(SDL_GameControllerGetStringForAxis(axis)));
						//SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(controller, axis);
						//if (bind.bindType == SDL_CONTROLLER_BINDTYPE_AXIS)log->debug("Axis #:"+to_string(bind.value.axis));
#endif

						int dz = 32000;

						for (int i = 0; i < gameControllers.size(); i++)
						{
							sp<GameController>g = gameControllers.get(i);
							if (g->id == id)
							{
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value >= dz)g->L_HELD = true;
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value < 100)g->L_HELD = false;
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value >= dz)g->R_HELD = true;
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value < 100)g->R_HELD = false;
#ifdef _DEBUG
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value>= dz)log->debug("Controller Axis Event: Left trigger held " + to_string(value));
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value < 100)log->debug("Controller Axis Event: Left trigger released " + to_string(value));
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value>= dz)log->debug("Controller Axis Event: Right trigger held " + to_string(value));
								if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value < 100)log->debug("Controller Axis Event: Right trigger released " + to_string(value));
#endif
							}
						}



						if (Main::globalSettings->useAnalogSticks)
						{
							//none of this works, have to check axis manually:
							for (int i = 0; i < gameControllers.size(); i++)
							{
								sp<GameController>g = gameControllers.get(i);
								if (g->id == id)
								{
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value < -dz)g->ANALOGLEFT_HELD = true;
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value > dz)g->ANALOGRIGHT_HELD = true;
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value < -dz)g->ANALOGUP_HELD = true;
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value > dz)g->ANALOGDOWN_HELD = true;
	#ifdef _DEBUG
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value < -dz)log->debug("Controller Axis Event: Left held " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value > dz)log->debug("Controller Axis Event: Right held " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value < -dz)log->debug("Controller Axis Event: Up held " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value > dz)log->debug("Controller Axis Event: Down held " + to_string(value));

									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value > -dz && g->ANALOGLEFT_HELD)log->debug("Controller Axis Event: Left unpressed " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value < dz && g->ANALOGRIGHT_HELD)log->debug("Controller Axis Event: Right unpressed " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value > -dz && g->ANALOGUP_HELD)log->debug("Controller Axis Event: Up unpressed " + to_string(value));
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value < dz && g->ANALOGDOWN_HELD)log->debug("Controller Axis Event: Down unpressed " + to_string(value));
	#endif
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value > -dz)g->ANALOGLEFT_HELD = false;
									if (axis == SDL_CONTROLLER_AXIS_LEFTX&&value < dz)g->ANALOGRIGHT_HELD = false;
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value > -dz)g->ANALOGUP_HELD = false;
									if (axis == SDL_CONTROLLER_AXIS_LEFTY&&value < dz)g->ANALOGDOWN_HELD = false;
								}
							}
						}
					}

				}
				

			 }
			
			 if (event.type == SDL_JOYAXISMOTION)
			 {
				 SDL_JoystickID id = event.jaxis.which;
				// sp<SDL_Joystick >joy = SDL_JoystickFromInstanceID(id);
				 

				if (controllersByJoystickID.containsKey(id))
				{
					sp<SDL_GameController >controller = controllersByJoystickID.get(id);
					int axis = event.jaxis.axis;
					int value = event.jaxis.value;
					
					

					if (value < 0 - DEADZONE || value > DEADZONE)
					{
#ifdef _DEBUG
						//SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(controller, axis);
						string s = string("Joystick Axis Event: " + string(SDL_GameControllerName(controller)));
						s += string(" Axis: "+to_string(axis));
						s += " Value:" + to_string(value);
						log->debug(s);
#endif

						//this is wrong, SDL_CONTROLLER_AXIS_TRIGGERLEFT does not correspond to joystick axis
						//if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value >= 32768)CONTROLLER1_L_HELD = true;
						//if (axis == SDL_CONTROLLER_AXIS_RIGHTX&&value<=-30000)CONTROLLER1_L_HELD = false;
						//if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT&&value<=-30000)CONTROLLER1_L_HELD = false;
						//if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value >= 32768)CONTROLLER1_R_HELD = true;
						//if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT&&value<=-30000)CONTROLLER1_R_HELD = false;

						//sp<SDL_Joystick >joy = SDL_GameControllerGetJoystick(controller);
						//get GUID mapping for axis number
						//buffer in which to write the ASCII string
						//int cbGUID = 4096; //the size of pszGUID
						//SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joy), pszGUID, cbGUID);
						//log->debug("GUIDString: " + string(pszGUID));

						char* mappingChar = SDL_GameControllerMapping(controller);
						string mapping = string(mappingChar);
						//log->debug("Mapping String: "+mapping);
						SDL_free(mappingChar);

						//find axis value for lefttrigger and righttrigger in mapping string

						string axisString = "a" + to_string(axis);

						//78696e70757401000000000000000000,HORIPAD,platform:Windows,x:b2,a:b0,b:b1,y:b3,back:b6,guide:b10,start:b7,dpleft:h0.8,dpdown:h0.4,dpright:h0.2,dpup:h0.1,leftshoulder:b4,lefttrigger:a2,rightshoulder:b5,righttrigger:a5,leftstick:b8,rightstick:b9,leftx:a0,lefty:a1,rightx:a3,righty:a4,

						bool leftTrigger = false;
						bool rightTrigger = false;
						bool leftX = false;
						bool leftY = false;
						//search for lefttrigger:___,

						if (mapping.find("lefttrigger:" + axisString + ",") != string::npos)leftTrigger = true;
						else if (mapping.find("righttrigger:" + axisString + ",") != string::npos)rightTrigger = true;
						else if (mapping.find("leftx:" + axisString + ",") != string::npos)leftX = true;
						else if (mapping.find("lefty:" + axisString + ",") != string::npos)leftY = true;

						int dz = 32000;

						for (int i = 0; i < gameControllers.size(); i++)
						{
							sp<GameController>g = gameControllers.get(i);
							if (g->id == id)
							{
								//						if (leftTrigger&&value >= 32768)g->L_HELD = true;
								//						if (leftTrigger&&value <= -32767)g->L_HELD = false;
								//						if (rightTrigger&&value >= 32768)g->R_HELD = true;
								//						if (rightTrigger&&value <= -32767)g->R_HELD = false;

#ifdef _DEBUG
								if (leftTrigger&&value >= dz)log->debug("Joystick Axis Event: Left trigger held " + to_string(value));
								if (leftTrigger&&value <= -dz)log->debug("Joystick Axis Event: Left trigger released " + to_string(value));
								if (rightTrigger&&value >= dz)log->debug("Joystick Axis Event: Right trigger held " + to_string(value));
								if (rightTrigger&&value <= -dz)log->debug("Joystick Axis Event: Right trigger released " + to_string(value));
#endif
							}
						}

						

						if (Main::globalSettings->useAnalogSticks)
						{
							for (int i = 0; i < gameControllers.size(); i++)
							{
								sp<GameController>g = gameControllers.get(i);
								if (g->id == id)
								{
									//none of this works, have to check axis manually:

//									if (leftX&&value < -dz)g->ANALOGLEFT_HELD = true;
//									if (leftX&&value > dz)g->ANALOGRIGHT_HELD = true;
//									if (leftY&&value < -dz)g->ANALOGUP_HELD = true;
//									if (leftY&&value > dz)g->ANALOGDOWN_HELD = true;
//
//#ifdef _DEBUG
//									if (leftX&&value < -dz)log->debug("Joystick Axis Event: Left held " + to_string(value));
//									if (leftX&&value > dz)log->debug("Joystick Axis Event: Right held " + to_string(value));
//									if (leftY&&value < -dz)log->debug("Joystick Axis Event: Up held " + to_string(value));
//									if (leftY&&value > dz)log->debug("Joystick Axis Event: Down held " + to_string(value));
//
//									if (leftX&&value > -dz && g->ANALOGLEFT_HELD)log->debug("Joystick Axis Event: Left unpressed " + to_string(value));
//									if (leftX&&value < dz && g->ANALOGRIGHT_HELD)log->debug("Joystick Axis Event: Right unpressed " + to_string(value));
//									if (leftY&&value > -dz && g->ANALOGUP_HELD)log->debug("Joystick Axis Event: Up unpressed " + to_string(value));
//									if (leftY&&value < dz && g->ANALOGDOWN_HELD)log->debug("Joystick Axis Event: Down unpressed " + to_string(value));
//#endif
//									if (leftX&&value > -dz)g->ANALOGLEFT_HELD = false;
//									if (leftX&&value < dz)g->ANALOGRIGHT_HELD = false;
//									if (leftY&&value > -dz)g->ANALOGUP_HELD = false;
//									if (leftY&&value < dz)g->ANALOGDOWN_HELD = false;
								}
							}
						}

					}
				}
				 

			 }
			
			if (event.type == SDL_TEXTINPUT) 
			{
				text += event.text.text;
			}
			
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
			{
				text.pop_back();
			}

			switch (event.key.keysym.sym)
			{
				case SDLK_UP:KEY_UP_HELD = true;break;
				case SDLK_DOWN:KEY_DOWN_HELD = true;break;
				case SDLK_LEFT:KEY_LEFT_HELD = true;break;
				case SDLK_RIGHT:KEY_RIGHT_HELD = true;break;
				case SDLK_SPACE:KEY_SPACE_HELD = true; break;
				case SDLK_LEFTBRACKET:KEY_LBRACKET_HELD = true;break;
				case SDLK_RIGHTBRACKET:KEY_RBRACKET_HELD = true;break;
				case SDLK_a:KEY_A_HELD = true; break;
				case SDLK_b:KEY_B_HELD = true; break;
				case SDLK_c:KEY_C_HELD = true; break;
				case SDLK_d:KEY_D_HELD = true; break;
				case SDLK_e:KEY_E_HELD = true; break;
				case SDLK_f:KEY_F_HELD = true; break;
				case SDLK_g:KEY_G_HELD = true; break;
				case SDLK_h:KEY_H_HELD = true; break;
				case SDLK_i:KEY_I_HELD = true; break;
				case SDLK_j:KEY_J_HELD = true; break;
				case SDLK_k:KEY_K_HELD = true; break;
				case SDLK_l:KEY_L_HELD = true; break;
				case SDLK_m:KEY_M_HELD = true; break;
				case SDLK_n:KEY_N_HELD = true; break;
				case SDLK_o:KEY_O_HELD = true; break;
				case SDLK_p:KEY_P_HELD = true; break;
				case SDLK_q:KEY_Q_HELD = true; break;
				case SDLK_r:KEY_R_HELD = true; break;
				case SDLK_s:KEY_S_HELD = true; break;
				case SDLK_t:KEY_T_HELD = true; break;
				case SDLK_u:KEY_U_HELD = true; break;
				case SDLK_v:KEY_V_HELD = true; break;
				case SDLK_w:KEY_W_HELD = true; break;
				case SDLK_x:KEY_X_HELD = true; break;
				case SDLK_y:KEY_Y_HELD = true; break;
				case SDLK_z:KEY_Z_HELD = true; break;
				case SDLK_COMMA:KEY_COMMA_HELD = true; break;
				case SDLK_PERIOD:KEY_PERIOD_HELD = true; break;
				case SDLK_SLASH:KEY_FRONTSLASH_HELD = true; break;
				case SDLK_SEMICOLON:KEY_SEMICOLON_HELD = true; break;
				case SDLK_QUOTE:KEY_QUOTE_HELD = true; break;
				case SDLK_BACKSLASH:KEY_BACKSLASH_HELD = true; break;

				case SDLK_LSHIFT:KEY_LSHIFT_HELD = true; break;
				case SDLK_RSHIFT:KEY_RSHIFT_HELD = true; break;
				case SDLK_LCTRL:KEY_LCTRL_HELD = true; break;
				case SDLK_RCTRL:KEY_RCTRL_HELD = true; break;
				case SDLK_RALT:KEY_RALT_HELD = true; break;
				case SDLK_LALT:KEY_LALT_HELD = true; break;
				case SDLK_BACKSPACE:KEY_BACKSPACE_HELD = true; break;
				case SDLK_TAB:KEY_TAB_HELD = true; break;
				case SDLK_RETURN:KEY_RETURN_HELD = true; break;
				case SDLK_ESCAPE:KEY_ESC_HELD = true; break;
				case SDLK_F1:KEY_F1_HELD = true;break;
				case SDLK_F2:KEY_F2_HELD = true;break;
				case SDLK_F3:KEY_F3_HELD = true;break;
				case SDLK_F4:KEY_F4_HELD = true;break;
				case SDLK_F5:KEY_F5_HELD = true;break;
				case SDLK_F6:KEY_F6_HELD = true;break;
				case SDLK_F7:KEY_F7_HELD = true;break;
				case SDLK_F8:KEY_F8_HELD = true;break;
				case SDLK_F9:KEY_F9_HELD = true;break;
				case SDLK_F10:KEY_F10_HELD = true;break;
				case SDLK_F11:KEY_F11_HELD = true;break;
				case SDLK_F12:KEY_F12_HELD = true;break;
				case SDLK_SYSREQ:KEY_PRINTSCREEN_HELD = true;break;
				case SDLK_PAUSE:KEY_PAUSE_HELD = true; break;
				case SDLK_BACKQUOTE:KEY_TILDE_HELD = true;break;
				case SDLK_1:KEY_1_HELD = true;break;
				case SDLK_2:KEY_2_HELD = true;break;
				case SDLK_3:KEY_3_HELD = true;break;
				case SDLK_4:KEY_4_HELD = true;break;
				case SDLK_5:KEY_5_HELD = true;break;
				case SDLK_6:KEY_6_HELD = true;break;
				case SDLK_7:KEY_7_HELD = true;break;
				case SDLK_8:KEY_8_HELD = true;break;
				case SDLK_9:KEY_9_HELD = true;break;
				case SDLK_0:KEY_0_HELD = true;break;
				case SDLK_PLUS:KEY_PLUS_HELD = true; break;
				case SDLK_MINUS:KEY_MINUS_HELD = true; break;
				case SDLK_KP_0:KEY_NUM0_HELD = true; break;
				case SDLK_KP_1:KEY_NUM1_HELD = true; break;
				case SDLK_KP_2:KEY_NUM2_HELD = true;break;
				case SDLK_KP_3:KEY_NUM3_HELD = true;break;
				case SDLK_KP_4:KEY_NUM4_HELD = true; break;
				case SDLK_KP_5:KEY_NUM5_HELD = true;break;
				case SDLK_KP_6:KEY_NUM6_HELD = true;break;
				case SDLK_KP_7:KEY_NUM7_HELD = true;break;
				case SDLK_KP_8:KEY_NUM8_HELD = true;break;
				case SDLK_KP_9:KEY_NUM9_HELD = true;break;
			default: break;
			}
		}
		
		if (event.type == SDL_KEYUP)
		{
			//int key = event.key.keysym.sym & ~SDLK_SCANCODE_MASK;

			switch (event.key.keysym.sym)
			{
				case SDLK_UP:KEY_UP_HELD = false; break;
				case SDLK_DOWN:KEY_DOWN_HELD = false; break;
				case SDLK_LEFT:KEY_LEFT_HELD = false; break;
				case SDLK_RIGHT:KEY_RIGHT_HELD = false; break;
				case SDLK_SPACE:KEY_SPACE_HELD = false; break;
				case SDLK_LEFTBRACKET:KEY_LBRACKET_HELD = false; break;
				case SDLK_RIGHTBRACKET:KEY_RBRACKET_HELD = false; break;
				case SDLK_a:KEY_A_HELD = false; break;
				case SDLK_b:KEY_B_HELD = false; break;
				case SDLK_c:KEY_C_HELD = false; break;
				case SDLK_d:KEY_D_HELD = false; break;
				case SDLK_e:KEY_E_HELD = false; break;
				case SDLK_f:KEY_F_HELD = false; break;
				case SDLK_g:KEY_G_HELD = false; break;
				case SDLK_h:KEY_H_HELD = false; break;
				case SDLK_i:KEY_I_HELD = false; break;
				case SDLK_j:KEY_J_HELD = false; break;
				case SDLK_k:KEY_K_HELD = false; break;
				case SDLK_l:KEY_L_HELD = false; break;
				case SDLK_m:KEY_M_HELD = false; break;
				case SDLK_n:KEY_N_HELD = false; break;
				case SDLK_o:KEY_O_HELD = false; break;
				case SDLK_p:KEY_P_HELD = false; break;
				case SDLK_q:KEY_Q_HELD = false; break;
				case SDLK_r:KEY_R_HELD = false; break;
				case SDLK_s:KEY_S_HELD = false; break;
				case SDLK_t:KEY_T_HELD = false; break;
				case SDLK_u:KEY_U_HELD = false; break;
				case SDLK_v:KEY_V_HELD = false; break;
				case SDLK_w:KEY_W_HELD = false; break;
				case SDLK_x:KEY_X_HELD = false; break;
				case SDLK_y:KEY_Y_HELD = false; break;
				case SDLK_z:KEY_Z_HELD = false; break;
				case SDLK_COMMA:KEY_COMMA_HELD = false; break;
				case SDLK_PERIOD:KEY_PERIOD_HELD = false; break;
				case SDLK_SLASH:KEY_FRONTSLASH_HELD = false; break;
				case SDLK_SEMICOLON:KEY_SEMICOLON_HELD = false; break;
				case SDLK_QUOTE:KEY_QUOTE_HELD = false; break;
				case SDLK_BACKSLASH:KEY_BACKSLASH_HELD = false; break;
				case SDLK_LSHIFT:KEY_LSHIFT_HELD = false; break;
				case SDLK_RSHIFT:KEY_RSHIFT_HELD = false; break;
				case SDLK_LCTRL:KEY_LCTRL_HELD = false; break;
				case SDLK_RCTRL:KEY_RCTRL_HELD = false; break;
				case SDLK_RALT:KEY_RALT_HELD = false; break;
				case SDLK_LALT:KEY_LALT_HELD = false; break;
				case SDLK_BACKSPACE:KEY_BACKSPACE_HELD = false; break;
				case SDLK_TAB:KEY_TAB_HELD = false; break;
				case SDLK_RETURN:KEY_RETURN_HELD = false; break;
				case SDLK_ESCAPE:KEY_ESC_HELD = false; break;
				case SDLK_F1:KEY_F1_HELD = false; break;
				case SDLK_F2:KEY_F2_HELD = false; break;
				case SDLK_F3:KEY_F3_HELD = false; break;
				case SDLK_F4:KEY_F4_HELD = false; break;
				case SDLK_F5:KEY_F5_HELD = false; break;
				case SDLK_F6:KEY_F6_HELD = false; break;
				case SDLK_F7:KEY_F7_HELD = false; break;
				case SDLK_F8:KEY_F8_HELD = false; break;
				case SDLK_F9:KEY_F9_HELD = false; break;
				case SDLK_F10:KEY_F10_HELD = false; break;
				case SDLK_F11:KEY_F11_HELD = false; break;
				case SDLK_F12:KEY_F12_HELD = false; break;
				case SDLK_SYSREQ:KEY_PRINTSCREEN_HELD = false; break;
				case SDLK_PAUSE:KEY_PAUSE_HELD = false; break;
				case SDLK_BACKQUOTE:KEY_TILDE_HELD = false; break;
				case SDLK_1:KEY_1_HELD = false; break;
				case SDLK_2:KEY_2_HELD = false; break;
				case SDLK_3:KEY_3_HELD = false; break;
				case SDLK_4:KEY_4_HELD = false; break;
				case SDLK_5:KEY_5_HELD = false; break;
				case SDLK_6:KEY_6_HELD = false; break;
				case SDLK_7:KEY_7_HELD = false; break;
				case SDLK_8:KEY_8_HELD = false; break;
				case SDLK_9:KEY_9_HELD = false; break;
				case SDLK_0:KEY_0_HELD = false; break;
				case SDLK_PLUS:KEY_PLUS_HELD = false; break;
				case SDLK_MINUS:KEY_MINUS_HELD = false; break;
				case SDLK_KP_0:KEY_NUM0_HELD = false; break;
				case SDLK_KP_1:KEY_NUM1_HELD = false; break;
				case SDLK_KP_2:KEY_NUM2_HELD = false; break;
				case SDLK_KP_3:KEY_NUM3_HELD = false; break;
				case SDLK_KP_4:KEY_NUM4_HELD = false; break;
				case SDLK_KP_5:KEY_NUM5_HELD = false; break;
				case SDLK_KP_6:KEY_NUM6_HELD = false; break;
				case SDLK_KP_7:KEY_NUM7_HELD = false; break;
				case SDLK_KP_8:KEY_NUM8_HELD = false; break;
				case SDLK_KP_9:KEY_NUM9_HELD = false; break;
			default: break;
			}
		}
		
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				MOUSE_LEFTBUTTON_PRESSED = true;
				MOUSE_X = event.button.x;
				MOUSE_Y = event.button.y;
			}
		}
		
		if (event.type == SDL_MOUSEMOTION)
		{

			MOUSE_X = event.motion.x;
			MOUSE_Y = event.motion.y;
			
		}
		
		{

#ifdef _DEBUG
			if (event.type == SDL_FIRSTEVENT)							log->debug("SDL_FIRSTEVENT");
			if (event.type == SDL_QUIT)								log->debug("SDL_QUIT");
			if (event.type == SDL_APP_TERMINATING		)			log->debug("SDL_APP_TERMINATING");
			if (event.type == SDL_APP_LOWMEMORY			)		log->debug("SDL_APP_LOWMEMORY");
			if (event.type == SDL_APP_WILLENTERBACKGROUND)			log->debug("SDL_APP_WILLENTERBACKGROUND");
			if (event.type == SDL_APP_DIDENTERBACKGROUND)			log->debug("SDL_APP_DIDENTERBACKGROUND");
			if (event.type == SDL_APP_WILLENTERFOREGROUND)			log->debug("SDL_APP_WILLENTERFOREGROUND");
			if (event.type == SDL_APP_DIDENTERFOREGROUND)			log->debug("SDL_APP_DIDENTERFOREGROUND");
			if (event.type == SDL_WINDOWEVENT			)			log->debug("SDL_WINDOWEVENT");
			if (event.type == SDL_SYSWMEVENT			)			log->debug("SDL_SYSWMEVENT");
			//if (event.type == SDL_KEYDOWN				)			log->debug("SDL_KEYDOWN");
			//if (event.type == SDL_KEYUP					)		log->debug("SDL_KEYUP");
			//if (event.type == SDL_TEXTEDITING			)			log->debug("SDL_TEXTEDITING");
			//if (event.type == SDL_TEXTINPUT				)		log->debug("SDL_TEXTINPUT");
			if (event.type == SDL_KEYMAPCHANGED			)		log->debug("SDL_KEYMAPCHANGED");
			//if (event.type == SDL_MOUSEMOTION			)			log->debug("SDL_MOUSEMOTION");
			//if (event.type == SDL_MOUSEBUTTONDOWN		)			log->debug("SDL_MOUSEBUTTONDOWN");
			//if (event.type == SDL_MOUSEBUTTONUP			)		log->debug("SDL_MOUSEBUTTONUP");
			//if (event.type == SDL_MOUSEWHEEL			)			log->debug("SDL_MOUSEWHEEL");
			//if (event.type == SDL_JOYAXISMOTION			)		log->debug("SDL_JOYAXISMOTION");
			if (event.type == SDL_JOYBALLMOTION			)		log->debug("SDL_JOYBALLMOTION");
			if (event.type == SDL_JOYHATMOTION			)		log->debug("SDL_JOYHATMOTION");
			//if (event.type == SDL_JOYBUTTONDOWN			)		log->debug("SDL_JOYBUTTONDOWN");
			//if (event.type == SDL_JOYBUTTONUP			)			log->debug("SDL_JOYBUTTONUP");
			if (event.type == SDL_JOYDEVICEADDED		)			log->debug("SDL_JOYDEVICEADDED");
			if (event.type == SDL_JOYDEVICEREMOVED		)		log->debug("SDL_JOYDEVICEREMOVED");
			//if (event.type == SDL_CONTROLLERAXISMOTION	)		log->debug("SDL_CONTROLLERAXISMOTION");
			//if (event.type == SDL_CONTROLLERBUTTONDOWN	)		log->debug("SDL_CONTROLLERBUTTONDOWN");
			//if (event.type == SDL_CONTROLLERBUTTONUP	)			log->debug("SDL_CONTROLLERBUTTONUP");
			if (event.type == SDL_CONTROLLERDEVICEADDED	)		log->debug("SDL_CONTROLLERDEVICEADDED");
			if (event.type == SDL_CONTROLLERDEVICEREMOVED)			log->debug("SDL_CONTROLLERDEVICEREMOVED");
			if (event.type == SDL_CONTROLLERDEVICEREMAPPED)		log->debug("SDL_CONTROLLERDEVICEREMAPPED");
			if (event.type == SDL_FINGERDOWN			)			log->debug("SDL_FINGERDOWN");
			if (event.type == SDL_FINGERUP				)		log->debug("SDL_FINGERUP");
			if (event.type == SDL_FINGERMOTION			)		log->debug("SDL_FINGERMOTION");
			if (event.type == SDL_DOLLARGESTURE			)		log->debug("SDL_DOLLARGESTURE");
			if (event.type == SDL_DOLLARRECORD			)		log->debug("SDL_DOLLARRECORD");
			if (event.type == SDL_MULTIGESTURE			)		log->debug("SDL_MULTIGESTURE");
			if (event.type == SDL_CLIPBOARDUPDATE		)			log->debug("SDL_CLIPBOARDUPDATE");
			if (event.type == SDL_DROPFILE				)		log->debug("SDL_DROPFILE");
			//if (event.type == SDL_DROPTEXT				)		log->debug("SDL_DROPTEXT");
			//if (event.type == SDL_DROPBEGIN				)		log->debug("SDL_DROPBEGIN");
			//if (event.type == SDL_DROPCOMPLETE			)		log->debug("SDL_DROPCOMPLETE");
			//if (event.type == SDL_AUDIODEVICEADDED		)		log->debug("SDL_AUDIODEVICEADDED");
			//if (event.type == SDL_AUDIODEVICEREMOVED	)			log->debug("SDL_AUDIODEVICEREMOVED");
			if (event.type == SDL_RENDER_TARGETS_RESET	)		log->debug("SDL_RENDER_TARGETS_RESET");
			if (event.type == SDL_RENDER_DEVICE_RESET	)			log->debug("SDL_RENDER_DEVICE_RESET");
			if (event.type == SDL_USEREVENT				)		log->debug("SDL_USEREVENT");
			if (event.type == SDL_LASTEVENT				)		log->debug("SDL_LASTEVENT");
#endif
		}

	}





	//------------------------------------
	//set keys and controllers pressed states based on LAST_HELD
	//------------------------------------


	if(KEY_UP_HELD			&&LAST_KEY_UP_HELD			==false)KEY_UP_PRESSED=true;
	if(KEY_DOWN_HELD		&&LAST_KEY_DOWN_HELD		==false)KEY_DOWN_PRESSED=true;
	if(KEY_LEFT_HELD		&&LAST_KEY_LEFT_HELD		==false)KEY_LEFT_PRESSED=true;
	if(KEY_RIGHT_HELD		&&LAST_KEY_RIGHT_HELD		==false)KEY_RIGHT_PRESSED	=true;
	if(KEY_SPACE_HELD		&&LAST_KEY_SPACE_HELD		==false)KEY_SPACE_PRESSED	=true;
	if(KEY_TAB_HELD			&&LAST_KEY_TAB_HELD			==false)KEY_TAB_PRESSED	=true;
	if(KEY_RETURN_HELD		&&LAST_KEY_RETURN_HELD		==false)KEY_RETURN_PRESSED=true;
	if(KEY_A_HELD			&&LAST_KEY_A_HELD			==false)KEY_A_PRESSED	=true;
	if(KEY_B_HELD			&&LAST_KEY_B_HELD			==false)KEY_B_PRESSED	=true;
	if(KEY_C_HELD			&&LAST_KEY_C_HELD			==false)KEY_C_PRESSED	=true;
	if(KEY_D_HELD			&&LAST_KEY_D_HELD			==false)KEY_D_PRESSED	=true;
	if(KEY_E_HELD			&&LAST_KEY_E_HELD			==false)KEY_E_PRESSED	=true;
	if(KEY_F_HELD			&&LAST_KEY_F_HELD			==false)KEY_F_PRESSED	=true;
	if(KEY_G_HELD			&&LAST_KEY_G_HELD			==false)KEY_G_PRESSED	=true;
	if(KEY_H_HELD			&&LAST_KEY_H_HELD			==false)KEY_H_PRESSED	=true;
	if(KEY_I_HELD			&&LAST_KEY_I_HELD			==false)KEY_I_PRESSED	=true;
	if(KEY_J_HELD			&&LAST_KEY_J_HELD			==false)KEY_J_PRESSED	=true;
	if(KEY_K_HELD			&&LAST_KEY_K_HELD			==false)KEY_K_PRESSED	=true;
	if(KEY_L_HELD			&&LAST_KEY_L_HELD			==false)KEY_L_PRESSED	=true;
	if(KEY_M_HELD			&&LAST_KEY_M_HELD			==false)KEY_M_PRESSED	=true;
	if(KEY_N_HELD			&&LAST_KEY_N_HELD			==false)KEY_N_PRESSED	=true;
	if(KEY_O_HELD			&&LAST_KEY_O_HELD			==false)KEY_O_PRESSED	=true;
	if(KEY_P_HELD			&&LAST_KEY_P_HELD			==false)KEY_P_PRESSED	=true;
	if(KEY_Q_HELD			&&LAST_KEY_Q_HELD			==false)KEY_Q_PRESSED	=true;
	if(KEY_R_HELD			&&LAST_KEY_R_HELD			==false)KEY_R_PRESSED	=true;
	if(KEY_S_HELD			&&LAST_KEY_S_HELD			==false)KEY_S_PRESSED	=true;
	if(KEY_T_HELD			&&LAST_KEY_T_HELD			==false)KEY_T_PRESSED	=true;
	if(KEY_U_HELD			&&LAST_KEY_U_HELD			==false)KEY_U_PRESSED	=true;
	if(KEY_V_HELD			&&LAST_KEY_V_HELD			==false)KEY_V_PRESSED	=true;
	if(KEY_W_HELD			&&LAST_KEY_W_HELD			==false)KEY_W_PRESSED	=true;
	if(KEY_X_HELD			&&LAST_KEY_X_HELD			==false)KEY_X_PRESSED	=true;
	if(KEY_Y_HELD			&&LAST_KEY_Y_HELD			==false)KEY_Y_PRESSED	=true;
	if(KEY_Z_HELD			&&LAST_KEY_Z_HELD			==false)KEY_Z_PRESSED	=true;

	if(KEY_COMMA_HELD		&&LAST_KEY_COMMA_HELD		==false)KEY_COMMA_PRESSED	=true;
	if(KEY_PERIOD_HELD		&&LAST_KEY_PERIOD_HELD		==false)KEY_PERIOD_PRESSED	=true;
	if(KEY_FRONTSLASH_HELD	&&LAST_KEY_FRONTSLASH_HELD	==false)KEY_FRONTSLASH_PRESSED	=true;
	if(KEY_SEMICOLON_HELD	&&LAST_KEY_SEMICOLON_HELD	==false)KEY_SEMICOLON_PRESSED	=true;
	if(KEY_QUOTE_HELD		&&LAST_KEY_QUOTE_HELD		==false)KEY_QUOTE_PRESSED	=true;
	if(KEY_BACKSLASH_HELD	&&LAST_KEY_BACKSLASH_HELD	==false)KEY_BACKSLASH_PRESSED	=true;

	if(KEY_LBRACKET_HELD	&&LAST_KEY_LBRACKET_HELD	==false)KEY_LBRACKET_PRESSED=true;
	if(KEY_RBRACKET_HELD	&&LAST_KEY_RBRACKET_HELD	==false)KEY_RBRACKET_PRESSED=true;
	if(KEY_RALT_HELD		&&LAST_KEY_RALT_HELD		==false)KEY_RALT_PRESSED=true;
	if(KEY_LALT_HELD		&&LAST_KEY_LALT_HELD		==false)KEY_LALT_PRESSED=true;
	if(KEY_LSHIFT_HELD		&&LAST_KEY_LSHIFT_HELD		==false)KEY_LSHIFT_PRESSED=true;
	if(KEY_RSHIFT_HELD		&&LAST_KEY_RSHIFT_HELD		==false)KEY_RSHIFT_PRESSED=true;
	if(KEY_LCTRL_HELD		&&LAST_KEY_LCTRL_HELD		==false)KEY_LCTRL_PRESSED	=true;
	if(KEY_RCTRL_HELD		&&LAST_KEY_RCTRL_HELD		==false)KEY_RCTRL_PRESSED	=true;
	if(KEY_BACKSPACE_HELD	&&LAST_KEY_BACKSPACE_HELD	==false)KEY_BACKSPACE_PRESSED	=true;
	if(KEY_ESC_HELD			&&LAST_KEY_ESC_HELD			==false)KEY_ESC_PRESSED	=true;
	if(KEY_F1_HELD			&&LAST_KEY_F1_HELD			==false)KEY_F1_PRESSED=true;
	if(KEY_F2_HELD			&&LAST_KEY_F2_HELD			==false)KEY_F2_PRESSED=true;
	if(KEY_F3_HELD			&&LAST_KEY_F3_HELD			==false)KEY_F3_PRESSED=true;
	if(KEY_F4_HELD			&&LAST_KEY_F4_HELD			==false)KEY_F4_PRESSED=true;
	if(KEY_F5_HELD			&&LAST_KEY_F5_HELD			==false)KEY_F5_PRESSED=true;
	if(KEY_F6_HELD			&&LAST_KEY_F6_HELD			==false)KEY_F6_PRESSED=true;
	if(KEY_F7_HELD			&&LAST_KEY_F7_HELD			==false)KEY_F7_PRESSED=true;
	if(KEY_F8_HELD			&&LAST_KEY_F8_HELD			==false)KEY_F8_PRESSED=true;
	if(KEY_F9_HELD			&&LAST_KEY_F9_HELD			==false)KEY_F9_PRESSED=true;
	if(KEY_F10_HELD			&&LAST_KEY_F10_HELD			==false)KEY_F10_PRESSED	=true;
	if(KEY_F11_HELD			&&LAST_KEY_F11_HELD			==false)KEY_F11_PRESSED	=true;
	if(KEY_F12_HELD			&&LAST_KEY_F12_HELD			==false)KEY_F12_PRESSED	=true;
	if(KEY_PRINTSCREEN_HELD	&&LAST_KEY_PRINTSCREEN_HELD	==false)KEY_PRINTSCREEN_PRESSED	=true;
	if(KEY_PAUSE_HELD		&&LAST_KEY_PAUSE_HELD		==false)KEY_PAUSE_PRESSED	=true;
	if(KEY_TILDE_HELD		&&LAST_KEY_TILDE_HELD		==false)KEY_TILDE_PRESSED	=true;
	if(KEY_1_HELD			&&LAST_KEY_1_HELD			==false)KEY_1_PRESSED	=true;
	if(KEY_2_HELD			&&LAST_KEY_2_HELD			==false)KEY_2_PRESSED	=true;
	if(KEY_3_HELD			&&LAST_KEY_3_HELD			==false)KEY_3_PRESSED	=true;
	if(KEY_4_HELD			&&LAST_KEY_4_HELD			==false)KEY_4_PRESSED	=true;
	if(KEY_5_HELD			&&LAST_KEY_5_HELD			==false)KEY_5_PRESSED	=true;
	if(KEY_6_HELD			&&LAST_KEY_6_HELD			==false)KEY_6_PRESSED	=true;
	if(KEY_7_HELD			&&LAST_KEY_7_HELD			==false)KEY_7_PRESSED	=true;
	if(KEY_8_HELD			&&LAST_KEY_8_HELD			==false)KEY_8_PRESSED	=true;
	if(KEY_9_HELD			&&LAST_KEY_9_HELD			==false)KEY_9_PRESSED	=true;
	if(KEY_0_HELD			&&LAST_KEY_0_HELD			==false)KEY_0_PRESSED	=true;
	if(KEY_MINUS_HELD		&&LAST_KEY_MINUS_HELD		==false)KEY_MINUS_PRESSED	=true;
	if(KEY_PLUS_HELD		&&LAST_KEY_PLUS_HELD		==false)KEY_PLUS_PRESSED=true;
	if(KEY_NUM0_HELD		&&LAST_KEY_NUM0_HELD		==false)KEY_NUM0_PRESSED=true;
	if(KEY_NUM1_HELD		&&LAST_KEY_NUM1_HELD		==false)KEY_NUM1_PRESSED=true;
	if(KEY_NUM2_HELD		&&LAST_KEY_NUM2_HELD		==false)KEY_NUM2_PRESSED=true;
	if(KEY_NUM3_HELD		&&LAST_KEY_NUM3_HELD		==false)KEY_NUM3_PRESSED=true;
	if(KEY_NUM4_HELD		&&LAST_KEY_NUM4_HELD		==false)KEY_NUM4_PRESSED=true;
	if(KEY_NUM5_HELD		&&LAST_KEY_NUM5_HELD		==false)KEY_NUM5_PRESSED=true;
	if(KEY_NUM6_HELD		&&LAST_KEY_NUM6_HELD		==false)KEY_NUM6_PRESSED=true;
	if(KEY_NUM7_HELD		&&LAST_KEY_NUM7_HELD		==false)KEY_NUM7_PRESSED=true;
	if(KEY_NUM8_HELD		&&LAST_KEY_NUM8_HELD		==false)KEY_NUM8_PRESSED=true;
	if(KEY_NUM9_HELD		&&LAST_KEY_NUM9_HELD		==false)KEY_NUM9_PRESSED=true;


	//------------------------------------
	//set controller pressed
	//------------------------------------

	for (int i = 0; i < gameControllers.size(); i++)
	{
		sp<GameController>g = gameControllers.get(i);
		g->setPressedButtons();
	}

	//------------------------------------
	//map keys and joysticks to game button
	//------------------------------------

	//bgclient

	if (KEY_UP_HELD == true)BGCLIENT_UP_HELD = true;
	if (KEY_DOWN_HELD == true)BGCLIENT_DOWN_HELD = true;
	if (KEY_LEFT_HELD == true)BGCLIENT_LEFT_HELD = true;
	if (KEY_RIGHT_HELD == true)BGCLIENT_RIGHT_HELD = true;
	if (KEY_SPACE_HELD == true)BGCLIENT_ACTION_HELD = true;
	if (KEY_LSHIFT_HELD == true)BGCLIENT_CANCELRUN_HELD = true;
	//if (KEY_ESC_HELD == true)BGCLIENT_START_HELD = true;
	//if (KEY_RETURN_HELD == true)BGCLIENT_SELECT_HELD = true;
	if (KEY_RETURN_HELD == true)BGCLIENT_OPENND_HELD = true;
	if (KEY_MINUS_HELD == true)BGCLIENT_ZOOMOUT_HELD = true;
	if (KEY_PLUS_HELD == true)BGCLIENT_ZOOMIN_HELD = true;
	if (KEY_BACKSPACE_HELD == true)BGCLIENT_ZOOMRESET_HELD = true;
	if (KEY_ESC_HELD == true)BGCLIENT_OPENMENU_HELD = true;
	if (KEY_RCTRL_HELD == true)BGCLIENT_QUICKZOOMOUT_HELD = true;
	if (KEY_RSHIFT_HELD == true)BGCLIENT_QUICKZOOMIN_HELD = true;

	for (int i = 0; i < gameControllers.size(); i++)
	{
		sp<GameController>g = gameControllers.get(i);
		if (g->UP_HELD == true)BGCLIENT_UP_HELD = true;
		if (g->DOWN_HELD == true)BGCLIENT_DOWN_HELD = true;
		if (g->LEFT_HELD == true)BGCLIENT_LEFT_HELD = true;
		if (g->RIGHT_HELD == true)BGCLIENT_RIGHT_HELD = true;
		if (g->ANALOGUP_HELD == true)BGCLIENT_UP_HELD = true;
		if (g->ANALOGDOWN_HELD == true)BGCLIENT_DOWN_HELD = true;
		if (g->ANALOGLEFT_HELD == true)BGCLIENT_LEFT_HELD = true;
		if (g->ANALOGRIGHT_HELD == true)BGCLIENT_RIGHT_HELD = true;
		if (g->B_HELD == true)BGCLIENT_ACTION_HELD = true;
		if (g->A_HELD == true)BGCLIENT_CANCELRUN_HELD = true;
		//if (g->START_HELD == true)BGCLIENT_START_HELD = true;
		//if (g->SELECT_HELD == true)BGCLIENT_SELECT_HELD = true;
		if (g->SELECT_HELD == true)BGCLIENT_OPENND_HELD = true;
		if (g->L_HELD == true)BGCLIENT_ZOOMOUT_HELD = true;
		if (g->R_HELD == true)BGCLIENT_ZOOMIN_HELD = true;
		if (g->Y_HELD == true)BGCLIENT_ZOOMRESET_HELD = true;
		if (g->START_HELD == true)BGCLIENT_OPENMENU_HELD = true;
		if (g->L2_HELD == true)BGCLIENT_QUICKZOOMOUT_HELD = true;
		if (g->R2_HELD == true)BGCLIENT_QUICKZOOMIN_HELD = true;
	}


	//generic minigame

	if (KEY_UP_HELD == true)MINIGAME_UP_HELD = true;
	if (KEY_DOWN_HELD == true)MINIGAME_DOWN_HELD = true;
	if (KEY_LEFT_HELD == true)MINIGAME_LEFT_HELD = true;
	if (KEY_RIGHT_HELD == true)MINIGAME_RIGHT_HELD = true;
	if (KEY_SPACE_HELD == true)MINIGAME_ACTION_HELD = true;
	if (KEY_LSHIFT_HELD == true)MINIGAME_RUN_HELD = true;
	if (KEY_RETURN_HELD == true)MINIGAME_START_HELD = true;
	if (KEY_ESC_HELD == true)MINIGAME_SELECT_HELD = true;
	if (KEY_LCTRL_HELD == true)MINIGAME_L_HELD = true;
	if (KEY_LALT_HELD == true)MINIGAME_R_HELD = true;

	for (int i = 0; i < gameControllers.size(); i++)
	{
		sp<GameController>g = gameControllers.get(i);
		if (g->UP_HELD == true)MINIGAME_UP_HELD = true;
		if (g->DOWN_HELD == true)MINIGAME_DOWN_HELD = true;
		if (g->LEFT_HELD == true)MINIGAME_LEFT_HELD = true;
		if (g->RIGHT_HELD == true)MINIGAME_RIGHT_HELD = true;
		if (g->ANALOGUP_HELD == true)MINIGAME_ANALOGUP_HELD = true;
		if (g->ANALOGDOWN_HELD == true)MINIGAME_ANALOGDOWN_HELD = true;
		if (g->ANALOGLEFT_HELD == true)MINIGAME_ANALOGLEFT_HELD = true;
		if (g->ANALOGRIGHT_HELD == true)MINIGAME_ANALOGRIGHT_HELD = true;
		if (g->B_HELD == true)MINIGAME_ACTION_HELD = true;//TODO: can be customized to either a or b
		if (g->B_HELD == true)MINIGAME_B_HELD = true;
		if (g->A_HELD == true)MINIGAME_RUN_HELD = true;//TODO: can be customized to either a or b
		if (g->A_HELD == true)MINIGAME_A_HELD = true;
		if (g->START_HELD == true)MINIGAME_START_HELD = true;
		if (g->SELECT_HELD == true)MINIGAME_SELECT_HELD = true;
		if (g->L_HELD == true)MINIGAME_L_HELD = true;
		if (g->R_HELD == true)MINIGAME_R_HELD = true;
		if (g->Y_HELD == true)MINIGAME_Y_HELD = true;
		if (g->X_HELD == true)MINIGAME_X_HELD = true;
	}



	//------------------------------------
	//set whether game button was just pressed
	//------------------------------------

	if (BGCLIENT_UP_HELD == true			&& LAST_BGCLIENT_UP_HELD == false)BGCLIENT_UP_PRESSED = true;
	if (BGCLIENT_DOWN_HELD == true			&& LAST_BGCLIENT_DOWN_HELD == false)BGCLIENT_DOWN_PRESSED = true;
	if (BGCLIENT_LEFT_HELD == true			&& LAST_BGCLIENT_LEFT_HELD == false)BGCLIENT_LEFT_PRESSED = true;
	if (BGCLIENT_RIGHT_HELD == true			&& LAST_BGCLIENT_RIGHT_HELD == false)BGCLIENT_RIGHT_PRESSED = true;
	if (BGCLIENT_ACTION_HELD == true		&& LAST_BGCLIENT_ACTION_HELD == false)BGCLIENT_ACTION_PRESSED = true;
	if (BGCLIENT_CANCELRUN_HELD == true		&& LAST_BGCLIENT_CANCELRUN_HELD == false)BGCLIENT_CANCELRUN_PRESSED = true;
	//if (BGCLIENT_START_HELD == true		&& LAST_BGCLIENT_START_HELD == false)BGCLIENT_START_PRESSED = true;
	//if (BGCLIENT_SELECT_HELD == true		&& LAST_BGCLIENT_SELECT_HELD == false)BGCLIENT_SELECT_PRESSED = true;
	if (BGCLIENT_OPENND_HELD == true		&& LAST_BGCLIENT_OPENND_HELD == false)BGCLIENT_OPENND_PRESSED = true;
	if (BGCLIENT_ZOOMOUT_HELD == true		&& LAST_BGCLIENT_ZOOMOUT_HELD == false)BGCLIENT_ZOOMOUT_PRESSED = true;
	if (BGCLIENT_ZOOMIN_HELD == true		&& LAST_BGCLIENT_ZOOMIN_HELD == false)BGCLIENT_ZOOMIN_PRESSED = true;
	if (BGCLIENT_ZOOMRESET_HELD == true		&& LAST_BGCLIENT_ZOOMRESET_HELD == false)BGCLIENT_ZOOMRESET_PRESSED = true;
	if (BGCLIENT_OPENMENU_HELD == true		&& LAST_BGCLIENT_OPENMENU_HELD == false)BGCLIENT_OPENMENU_PRESSED = true;
	if (BGCLIENT_QUICKZOOMOUT_HELD == true	&& LAST_BGCLIENT_QUICKZOOMOUT_HELD == false)BGCLIENT_QUICKZOOMOUT_PRESSED = true;
	if (BGCLIENT_QUICKZOOMIN_HELD == true	&& LAST_BGCLIENT_QUICKZOOMIN_HELD == false)BGCLIENT_QUICKZOOMIN_PRESSED = true;


	if (MINIGAME_UP_HELD						&&LAST_MINIGAME_UP_HELD == false)			 MINIGAME_UP_PRESSED = true;
	if (MINIGAME_DOWN_HELD						&&LAST_MINIGAME_DOWN_HELD == false)		MINIGAME_DOWN_PRESSED = true;
	if (MINIGAME_LEFT_HELD						&&LAST_MINIGAME_LEFT_HELD == false)		MINIGAME_LEFT_PRESSED = true;
	if (MINIGAME_RIGHT_HELD						&&LAST_MINIGAME_RIGHT_HELD == false)		 MINIGAME_RIGHT_PRESSED = true;
	if (MINIGAME_ANALOGUP_HELD						&&LAST_MINIGAME_ANALOGUP_HELD == false)			 MINIGAME_ANALOGUP_PRESSED = true;
	if (MINIGAME_ANALOGDOWN_HELD						&&LAST_MINIGAME_ANALOGDOWN_HELD == false)		MINIGAME_ANALOGDOWN_PRESSED = true;
	if (MINIGAME_ANALOGLEFT_HELD						&&LAST_MINIGAME_ANALOGLEFT_HELD == false)		MINIGAME_ANALOGLEFT_PRESSED = true;
	if (MINIGAME_ANALOGRIGHT_HELD						&&LAST_MINIGAME_ANALOGRIGHT_HELD == false)		 MINIGAME_ANALOGRIGHT_PRESSED = true;

	//if (MINIGAME_ACTION_HELD					&&LAST_MINIGAME_ACTION_HELD == false)			 MINIGAME_ACTION_PRESSED = true;//TODO: can be customized to either a or b
	//if (MINIGAME_RUN_HELD					&&LAST_MINIGAME_RUN_HELD == false)			 MINIGAME_RUN_PRESSED = true;//TODO: can be customized to either a or b
	//if (MINIGAME_START_HELD						&&LAST_MINIGAME_START_HELD == false) MINIGAME_START_PRESSED = true;
	//if (MINIGAME_SELECT_HELD					&&LAST_MINIGAME_SELECT_HELD == false)		 MINIGAME_SELECT_PRESSED = true;

	if (MINIGAME_L_HELD							&&LAST_MINIGAME_L_HELD == false)	 MINIGAME_L_PRESSED = true;
	if (MINIGAME_R_HELD							&&LAST_MINIGAME_R_HELD == false)	 MINIGAME_R_PRESSED = true;
	if (MINIGAME_Y_HELD							&&LAST_MINIGAME_Y_HELD == false)	 MINIGAME_Y_PRESSED = true;
	if (MINIGAME_X_HELD							&&LAST_MINIGAME_X_HELD == false)	 MINIGAME_X_PRESSED = true;
	if (MINIGAME_A_HELD							&&LAST_MINIGAME_A_HELD == false)	 MINIGAME_A_PRESSED = true;
	if (MINIGAME_B_HELD							&&LAST_MINIGAME_B_HELD == false)	 MINIGAME_B_PRESSED = true;
		

}


//=========================================================================================================================
void ControlsManager::doHaptic(sp<GameController>g, int length, int magnitude, int attackLength, int fadeLength, int wavePeriod)
{//=========================================================================================================================

	log->debug("doHaptic");
	if (g->haptic == nullptr)return;

	SDL_HapticRumblePlay(g->haptic, (float)magnitude/32767.0f, length);

	log->debug("Played haptic");

//	if(g->hapticID!=-1)
//	{
//		SDL_HapticDestroyEffect(g->haptic, g->hapticID);
//		g->hapticID = -1;
//	}
//
//	SDL_HapticEffect effect;
//	int effect_id;
//
//	// Create the effect
//	SDL_memset(&effect, 0, sizeof(SDL_HapticEffect)); // 0 is safe default
//	effect.type = SDL_HAPTIC_SINE;
//	effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
//	effect.periodic.direction.dir[0] = 18000; // Force comes from south
//	effect.periodic.period = wavePeriod; // 1000 ms
//	effect.periodic.magnitude = magnitude; // 20000/32767 strength
//	effect.periodic.length = length; // 5 seconds long
//	effect.periodic.attack_length = attackLength; // Takes 1 second to get max strength
//	effect.periodic.fade_length = fadeLength; // Takes 1 second to fade away
//
//										// Upload the effect
//	effect_id = SDL_HapticNewEffect(g->haptic, &effect);
//
//	g->hapticID = effect_id;
//
//	SDL_HapticRunEffect(g->haptic, effect_id, 1);
//
//	//SDL_HapticDestroyEffect(haptic, effect_id);


}



//void ControlsManager::update()
//{
//	resetPressedButtons();
//	setButtonStates();
//}
int ControlsManager::getMouseX()
{
	return MOUSE_X;
}

int ControlsManager::getMouseY()
{
	return MOUSE_Y;
}

