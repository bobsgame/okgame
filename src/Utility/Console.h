//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
#include <mutex>
class Logger;




class ConsoleText;
class OKColor;
class CaptionManager;



//================
//defines
//================


//================
//variables
//================

extern bool error_console_on;



extern DEBUG_overlay_STRUCT* DEBUG_overlays[128];



//================
//prototypes
//================

void ERROR_init_error_console();

void DEBUG_delete_overlay(DEBUG_overlay_STRUCT* overlay);
DEBUG_overlay_STRUCT* DEBUG_make_overlay(string text, float x, float y);
void DEBUG_update_overlay(DEBUG_overlay_STRUCT* overlay, string text, float, float);
void DEBUG_draw_overlays();

void DEBUG_draw_text(float screenX0, float screenY0, string text, sp<OKColor> color);

//void gl_check_errors(int val);
void error_console(string error_string);
void ERROR_set_error(string error_string);
void ERROR_draw_error_console();


class Console
{
public:
	static Logger log;

	static sp<CaptionManager> captionManager;

	sp<vector<sp<ConsoleText>>> consoleTextList = nullptr;
	mutex _consoleTextList_Mutex;

	static bool showConsole;

	bool justifyRight = false;

	int fontSize = 12;

	Console();
	void update();

	void pruneChats(int max);

	sp<ConsoleText> error(const string& s, int ticks = -1, int x = -1, int y = -1, sp<OKColor> c = nullptr);
	sp<ConsoleText> debug(const string& s, int ticks = -1, int x = -1, int y = -1, sp<OKColor> c = nullptr);

	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	sp<ConsoleText> add(const string& s, int ticks = -1, int x = -1, int y = -1, sp<OKColor> c = nullptr, bool isDebug = false);
	sp<ConsoleText> add(const string& s, int ticks, sp<OKColor> c);
	sp<ConsoleText> add(const string& s, sp<OKColor> c);



	void render();
};

