
#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



Logger System::log = Logger("System");


//string System::internetProviderString = "";
//string System::browserUserAgentString = "";
//string System::browserAppNameVersionString = "";
//string System::browserReferrerString = "";
//
//string System::getEnvProcessorIdentifier = "";
//string System::getEnvProcessorArchitecture = "";
//string System::getEnvNumberOfProcessors = "";
//
//float System::timeZoneGMTOffset=0.0f;
//
//string System::jreVersion = "";
//string System::jreVendor = "";
//string System::jreHomeDir = "";
//string System::jvmVersion = "";
//string System::jvmName = "";
//string System::javaClassVersion = "";
//string System::javaClassPath = "";
//string System::javaLibraryPath = "";
//string System::javaTempDir = "";
//string System::osName = "";
//string System::osArch = "";
//string System::osVersion = "";
//string System::osUserAccountName = "";
//string System::osHomeDir = "";
//string System::workingDir = "";
//
//int System::displayWidth = -1;
//int System::displayHeight = -1;
//int System::displayBPP = -1;
//int System::displayFreq = -1;
//bool System::shaderCompiled = false;
//bool System::canUseFBO = false;
//bool System::usingVSync = false;
//string System::displayAdapter = "";
//string System::displayDriver = "";
//string System::lwjglVersion = "";
//bool System::lwjglIs64Bit=false;
//string System::lwjglPlatformName = "";
//int System::numCPUs=-1;
//
//int System::numControllersFound=-1;
//string System::controllersNames = "";
//
//string System::glVendor = "";
//string System::glVersion = "";
//string System::glRenderer = "";
//string System::shaderVersion = "";
//string System::glExtensions = "";


ConsoleText* System::totalRendersText = nullptr;
ConsoleText* System::totalUpdatesText = nullptr;
ConsoleText* System::rendersPerSecondText = nullptr;
ConsoleText* System::averageRendersPerSecondText = nullptr;
ConsoleText* System::updatesPerSecondText = nullptr;
ConsoleText* System::rendersSkippedText = nullptr;
ConsoleText* System::updatesSkippedText = nullptr;
ConsoleText* System::averageTicksPerFrameText = nullptr;
ConsoleText* System::averageTicksPerUpdateText = nullptr;
ConsoleText* System::onlineStatusText = nullptr;

ConsoleText* System::upTimeText = nullptr;

ConsoleText* System::ticksText[amtTicksTexts] = {nullptr};


ConsoleText* System::mxThreadCountText = nullptr;

ConsoleText* System::memoryText = nullptr;
ConsoleText* System::texturesLoadedText = nullptr;// = Console::debug("texturesLoadedText");
ConsoleText* System::textureBytesLoadedText = nullptr;// = Console::debug("textureBytesLoadedText");



//
//#include "Poco/Path.h"
//using Poco::Path;

#include "Poco/Environment.h"
using Poco::Environment;


#ifdef __WINDOWS__
#define USE_SIGAR
#endif

#if defined(__WINDOWS__) && defined(USE_SIGAR)
#include "sigar.h"
#endif

#ifdef USE_SIGAR
sigar_t *sigar = nullptr;
#endif


void System::initSystemInfo()
{ //=========================================================================================================================


	log.debug("Init system info");



	Uint64 start=0, now=0, totalStart, totalNow;
	start = SDL_GetPerformanceCounter();
	totalStart = SDL_GetPerformanceCounter();

	//audio
	int numAudioDevices = SDL_GetNumAudioDevices(0);
	GLUtils::e();
	for (int i = 0; i < numAudioDevices; i++)
	{
		log.info("SDL_GetAudioDeviceName" + to_string(i) + ":" + SDL_GetAudioDeviceName(i, 0));
		GLUtils::e();
		//log.info("SDL_GetAudioDeviceStatus" + to_string(i) + ":" + to_string(SDL_GetAudioDeviceStatus(i)));
		//GLUtils::e();
	}
	GLUtils::e();

	int numAudioDrivers = SDL_GetNumAudioDrivers();
	for (int i = 0; i < numAudioDrivers; i++)
	{
		log.info("SDL_GetAudioDriver" + to_string(i) + ":" + SDL_GetAudioDriver(i));
	}
	GLUtils::e();

	log.info("SDL_GetAudioStatus:" + to_string(SDL_GetAudioStatus()));
	GLUtils::e();
	log.info("SDL_GetCurrentAudioDriver:" + string(SDL_GetCurrentAudioDriver()));
	GLUtils::e();


	//os
	log.info("SDL_GetBasePath:" + string(SDL_GetBasePath()));

	log.info("SDL_GetPerformanceCounter:" + to_string(SDL_GetPerformanceCounter()));
	log.info("SDL_GetPerformanceFrequency:" + to_string(SDL_GetPerformanceFrequency()));
	log.info("SDL_GetPlatform:" + string(SDL_GetPlatform()));
	log.info("SDL_GetPrefPath:" + string(SDL_GetPrefPath("Bob Corporation", "bob's game")));
	log.info("SDL_GetRevision:" + string(SDL_GetRevision()));
	log.info("SDL_GetRevisionNumber:" + to_string(SDL_GetRevisionNumber()));
	log.info("SDL_GetSystemRAM:" + to_string(SDL_GetSystemRAM()));


	//log.info("SDL_GetVersion" + string(SDL_GetVersion()));
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	log.info("Compiled against SDL version:" + to_string(compiled.major) + to_string(compiled.minor) + to_string(compiled.patch));
	log.info("Linked against SDL version:" + to_string(linked.major) + to_string(linked.minor) + to_string(linked.patch));


	//window
	//SDL_GetGrabbedWindow();
	log.info("SDL_GetWindowBrightness:" + to_string(SDL_GetWindowBrightness(GLUtils::window)));
	log.info("SDL_GetWindowDisplayIndex:" + to_string(SDL_GetWindowDisplayIndex(GLUtils::window)));
	log.info("SDL_GetWindowFlags:" + to_string(SDL_GetWindowFlags(GLUtils::window)));
	log.info("SDL_GetWindowGrab:" + to_string(SDL_GetWindowGrab(GLUtils::window)));
	log.info("SDL_GetWindowID:" + to_string(SDL_GetWindowID(GLUtils::window)));
	log.info("SDL_GetWindowPixelFormat:" + to_string(SDL_GetWindowPixelFormat(GLUtils::window)));
	log.info("SDL_GetWindowTitle:" + string(SDL_GetWindowTitle(GLUtils::window)));


	//mouse
	log.info("SDL_GetNumTouchDevices:" + to_string(SDL_GetNumTouchDevices()));
	log.info("SDL_GetRelativeMouseMode:" + to_string(SDL_GetRelativeMouseMode()));

	//key
	log.info("SDL_HasScreenKeyboardSupport:" + to_string(SDL_HasScreenKeyboardSupport()));

	//cpu
	log.info("SDL_GetCPUCacheLineSize:" + to_string(SDL_GetCPUCacheLineSize()));
	log.info("SDL_GetCPUCount:" + to_string(SDL_GetCPUCount()));
	log.info("SDL_Has3DNow:" + to_string(SDL_Has3DNow()));
	log.info("SDL_HasAVX:" + to_string(SDL_HasAVX()));
	log.info("SDL_HasAltiVec:" + to_string(SDL_HasAltiVec()));
	log.info("SDL_HasMMX:" + to_string(SDL_HasMMX()));
	log.info("SDL_HasRDTSC:" + to_string(SDL_HasRDTSC()));
	log.info("SDL_HasSSE:" + to_string(SDL_HasSSE()));
	log.info("SDL_HasSSE2:" + to_string(SDL_HasSSE2()));
	log.info("SDL_HasSSE3:" + to_string(SDL_HasSSE3()));
	log.info("SDL_HasSSE41:" + to_string(SDL_HasSSE41()));
	log.info("SDL_HasSSE42:" + to_string(SDL_HasSSE42()));


	//video
	log.info("SDL_GetNumRenderDrivers:" + to_string(SDL_GetNumRenderDrivers()));
	log.info("SDL_GetNumVideoDisplays:" + to_string(SDL_GetNumVideoDisplays()));
	log.info("SDL_GetNumVideoDrivers:" + to_string(SDL_GetNumVideoDrivers()));

	now = SDL_GetPerformanceCounter();
	log.debug("SDL info took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();


	log.info("Poco::libraryVersion:" + to_string(Environment::libraryVersion()));
	log.info("Poco::osName:" + string(Environment::osName()));
	log.info("Poco::osVersion:" + string(Environment::osVersion()));
	log.info("Poco::processorCount:" + to_string(Environment::processorCount()));


#ifdef USE_SIGAR

int status, i;

sigar_cpu_info_list_t cpulist;


sigar_open(&sigar);

status = sigar_cpu_info_list_get(sigar, &cpulist);
if (status != SIGAR_OK) 
{
	printf("sigar_cpu_info_list_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	//exit(1);
}
else
{
	for (i = 0; i < (int)cpulist.number; i++)
	{
		sigar_cpu_info_t cpu = cpulist.data[i];
		log.info("Sigar::CPU " + to_string(i) + " Vendor:" + string(cpu.vendor));
		log.info("Sigar::CPU " + to_string(i) + " Model:" + string(cpu.model));
		log.info("Sigar::CPU " + to_string(i) + " Mhz:" + to_string(cpu.mhz));
		log.info("Sigar::CPU " + to_string(i) + " Cores:" + to_string(cpu.total_cores));
	}
	sigar_cpu_info_list_destroy(sigar, &cpulist);
}

sigar_mem_t mem;
status = sigar_mem_get(sigar, &mem);
if (status != SIGAR_OK) 
{
	printf("sigar_mem_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	//exit(1);
}
else
{
	log.info("Sigar::Ram:" + to_string(mem.ram));
	log.info("Sigar::Total:" + to_string(mem.total / 1024 / 1024));
	log.info("Sigar::Used:" + to_string(mem.used / 1024 / 1024));
	log.info("Sigar::Free:" + to_string(mem.free / 1024 / 1024));
	log.info("Sigar::Actual Used:" + to_string(mem.actual_used / 1024 / 1024));
	log.info("Sigar::Actual Free:" + to_string(mem.actual_free / 1024 / 1024));
	log.info("Sigar::Used %:" + to_string(mem.used_percent));
	log.info("Sigar::Free %:" + to_string(mem.free_percent));
}

sigar_sys_info_t sys;
status = sigar_sys_info_get(sigar, &sys);
if (status != SIGAR_OK) 
{
	printf("sigar_sys_info_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	//exit(1);
}
else
{
	log.info("Sigar::System Name:" + string(sys.name));
	log.info("Sigar::System Version:" + string(sys.version));
	log.info("Sigar::System Arch:" + string(sys.arch));
	log.info("Sigar::System Machine:" + string(sys.machine));
	log.info("Sigar::System Description:" + string(sys.description));
	log.info("Sigar::System Vendor:" + string(sys.vendor));
	log.info("Sigar::System Vendor Version:" + string(sys.vendor_version));
	log.info("Sigar::System Vendor Name:" + string(sys.vendor_name));
	log.info("Sigar::System Vendor Code Name:" + string(sys.vendor_code_name));
}

sigar_proc_mem_t proc;
status = sigar_proc_mem_get(sigar, sigar_pid_get(sigar), &proc);
if (status != SIGAR_OK) 
{
	printf("sigar_proc_mem_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	//exit(1);
}
else
{
	log.info("Sigar::Proc Mem Size:" + to_string(proc.size / 1024 / 1024));
	log.info("Sigar::Proc Mem Resident:" + to_string(proc.resident / 1024 / 1024));
	log.info("Sigar::Proc Mem Share:" + to_string(proc.share / 1024 / 1024));
}

//sigar_proc_stat_t procstat;
//status = sigar_proc_stat_get(sigar, &procstat);
//if (status != SIGAR_OK) 
//{
//	printf("sigar_proc_stat_get error: %d (%s)\n",
//		status, sigar_strerror(sigar, status));
//	//exit(1);
//}
//else
//{
//	log.info("Sigar::Proc Total:" + to_string(procstat.total));
//	log.info("Sigar::Proc Sleeping:" + to_string(procstat.sleeping));
//	log.info("Sigar::Proc Running:" + to_string(procstat.running));
//	log.info("Sigar::Proc Zombie:" + to_string(procstat.zombie));
//	log.info("Sigar::Proc Stopped:" + to_string(procstat.stopped));
//	log.info("Sigar::Proc Idle:" + to_string(procstat.idle));
//	log.info("Sigar::Proc Threads:" + to_string(procstat.threads));
//}

sigar_close(sigar);

now = SDL_GetPerformanceCounter();
log.debug("Sigar info took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
start = SDL_GetPerformanceCounter();


#endif



//clientInfo->timeZoneGMTOffset = timeZoneGMTOffset;


//	char* vendorString = (char*)glGetString(GL_VENDOR);
//	char* versionString = (char*)glGetString(GL_VERSION);
//	char* rendererString = (char*)glGetString(GL_RENDERER);
//	char* shaderVersionString = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
//	char* extensionsString = (char*)glGetString(GL_EXTENSIONS);
//
//	if (vendorString != NULL)glVendor = string(vendorString);
//	if (versionString != NULL)glVersion = string(versionString);
//	if (rendererString != NULL)glRenderer = string(rendererString);
//	if (shaderVersionString != NULL)shaderVersion = string(shaderVersionString);
//	if (extensionsString != NULL)glExtensions = string(extensionsString);

	//logSystemInfo();
	//log.info("Window Width:" + to_string(GLUtils::getRealWindowWidth()));
	//log.info("Window Height:" + to_string(GLUtils::getRealWindowHeight()));


totalNow = SDL_GetPerformanceCounter();
log.debug("Init system info took " + to_string((double)((totalNow - totalStart) * 1000) / SDL_GetPerformanceFrequency()) + "ms");


}

//#include "Poco/DateTime.h"
//using Poco::DateTime;
//#include "Poco/LocalDateTime.h"
//using Poco::LocalDateTime;
//#include "Poco/Timezone.h"
//#include "Poco/Timestamp.h"
//using Poco::Timezone;
//using Poco::Timestamp;
#undef INADDR_ANY       
#undef INADDR_LOOPBACK  
#undef INADDR_BROADCAST 
#undef INADDR_NONE  
#include <Poco/Net/NTPClient.h>
using namespace Poco::Net;

void System::initClockAndTimeZone()
{ //=========================================================================================================================

	log.debug("Init clock");
	
	time_t t = time(0); // get time now 
	struct tm * now = localtime(&t);
	//cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << endl;


//	char buf[80];
//	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
//	// for more information about date/time format
//	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", now);
//	string formattedTime(buf);
//	//log.info(formattedTime);

	log.info("Local time: "+to_string(now->tm_year + 1900)+"-"+to_string((now->tm_mon + 1))+"-"+to_string(now->tm_mday)+" "+ to_string(now->tm_hour)+":"+ to_string(now->tm_min)+":"+ to_string(now->tm_sec));
	
	//time zone




	//general location based on IP, ask server



//	NTPClient client{ IPAddress::Family::IPv4 };
//	int responses = 0;
//		try
//		{
//			
//			responses = client.request("pool.ntp.org");
//			
//		}
//		catch (std::exception& e)
//		{
//			log.error("Error getting NTP time: "+string(e.what()));
//		}
//	
//		if(responses>0)
//		{
//			
//		}



	//
	//	{
	//		DateTime now; // the current date and time in UTC
	//		int year = now.year();
	//		int month = now.month();
	//		int day = now.day();
	//		int dow = now.dayOfWeek();
	//		int doy = now.dayOfYear();
	//		int hour = now.hour();
	//		int hour12 = now.hourAMPM();
	//		int min = now.minute();
	//		int sec = now.second();
	//		int ms = now.millisecond();
	//		int us = now.microsecond();
	//		double jd = now.julianDay();
	//		Poco::Timestamp ts = now.timestamp();
	//		DateTime xmas(2006, 12, 25);                // 2006-12-25 00:00:00
	//		Poco::Timespan timeToXmas = xmas - now;
	//
	//		DateTime dt(1973, 9, 12, 2, 30, 45);      // 1973-09-12 02:30:45
	//		dt.assign(2006, 10, 13, 13, 45, 12, 345); // 2006-10-13 12:45:12.345
	//		bool isAM = dt.isAM(); // false
	//		bool isPM = dt.isPM(); // true
	//		bool isLeap = DateTime::isLeapYear(2006);     // false
	//		int days = DateTime::daysOfMonth(2006, 2); // 28
	//		bool isValid = DateTime::isValid(2006, 02, 29); // false
	//		dt.assign(2006, DateTime::OCTOBER, 22); // 2006-10-22 00:00:00
	//		if (dt.dayOfWeek() == DateTime::SUNDAY)
	//		{
	//			// ...
	//		}
	//	}
	//
	//
	//	{
	//		LocalDateTime now; // the current date and local time
	//		int year = now.year();
	//		int month = now.month();
	//		int day = now.day();
	//		int dow = now.dayOfWeek();
	//		int doy = now.dayOfYear();
	//		int hour = now.hour();
	//		int hour12 = now.hourAMPM();
	//		int min = now.minute();
	//		int sec = now.second();
	//		int ms = now.millisecond();
	//		int us = now.microsecond();
	//		int tzd = now.tzd();
	//		double jd = now.julianDay();
	//		Poco::Timestamp ts = now.timestamp();
	//
	//		LocalDateTime dt1(1973, 9, 12, 2, 30, 45); // 1973-09-12 02:30:45
	//		dt1.assign(2006, 10, 13, 13, 45, 12, 345); // 2006-10-13 12:45:12.345
	//		LocalDateTime dt2(3600, 1973, 9, 12, 2, 30, 45, 0, 0); // UTC + 1 hour
	//		dt2.assign(3600, 2006, 10, 13, 13, 45, 12, 345, 0);
	//		Poco::Timestamp nowTS;
	//		LocalDateTime dt3(3600, nowTS); // construct from Timestamp
	//	}
	//
	//	int utcOffset = Timezone::utcOffset();
	//	int dst = Timezone::dst();
	//	bool isDst = Timezone::isDst(Timestamp());
	//	int tzd = Timezone::tzd();
	//	string name = Timezone::name();
	//	string stdName = Timezone::standardName();
	//	string dstName = Timezone::dstName();







}






long long System::highResolutionTicksPerSecond;
long long System::highResTimer;

long long System::currentHighResTime = 0;


int System::averageRendersPerSecond = 0;
int System::totalSecondsPassed = 0;
int System::averageFPSTestSecondsPassed = 0;
int System::totalRenders = 0;
int System::averageFPSTestTotalRenders = 0;
int System::totalUpdates = 0;

long long System::lastUpdateHighResTime = 0;
long long System::lastRenderHighResTime = 0;

int System::ticksPassedThisRender = 0;
int System::ticksPassedThisUpdate = 0;

int System::updatesThisSecond = 0;
int System::rendersThisSecond = 0;

long long System::totalUpdateTicks = 0;
long long System::totalRenderTicks = 0;

int System::rendersSkipped = 0;
int System::updatesSkipped = 0;

long long System::lastSecondTime = 0;

double System::cpuFreq = 0;

long long System::timerOffset = 0;

//=========================================================================================================================
void System::initTimers()
{ //=========================================================================================================================



	highResolutionTicksPerSecond = SDL_GetPerformanceFrequency();

	cpuFreq = double(highResolutionTicksPerSecond) / 1000.0;

	// Take an initial sampling of the time at startup
	// This stops the value from being ridiculously high if the
	// player's computer has been on for a few days, which would
	// cause precision issues if casted to a float
	timerOffset = SDL_GetPerformanceCounter();

	highResTimer = getPerformanceCounter();
	currentHighResTime = highResTimer;
	lastRenderHighResTime = highResTimer;
	lastUpdateHighResTime = highResTimer;
	lastSecondTime = highResTimer;
	

}


//=========================================================================================================================
void System::updateRenderTimers()
{ //=========================================================================================================================
	rendersThisSecond++;
	totalRenders++;

	if (Main::mainLoopStarted && totalSecondsPassed > 15)
	{
		averageFPSTestTotalRenders++;
	}

	highResTimer = getPerformanceCounter();

	
	//get time passed since game started
	//currentHighResTime = SDL_GetTicks();
	currentHighResTime = highResTimer;

	ticksPassedThisRender = (int)(System::getTicksBetweenTimes(lastRenderHighResTime, currentHighResTime));

	lastRenderHighResTime = currentHighResTime;
	totalRenderTicks += ticksPassedThisRender;

	//if(ticksPassedThisUpdate>17)ticksPassedThisUpdate=17; //TODO: this is frameskip off, basically. game will slow down instead
	if (ticksPassedThisRender > (int)(16 * 1.5))
	{
		rendersSkipped++; //= ticksPassed/16;
	}

}


//=========================================================================================================================
void System::updateUpdateTimers()
{ //=========================================================================================================================

	updatesThisSecond++;
	totalUpdates++;

	//get time passed since last frame
	ticksPassedThisUpdate = (int)(System::getTicksBetweenTimes(lastUpdateHighResTime, currentHighResTime));


	lastUpdateHighResTime = currentHighResTime;
	totalUpdateTicks += ticksPassedThisUpdate;
	

	//if(ticksPassedThisUpdate>17)ticksPassedThisUpdate=17; //TODO: this is frameskip off, basically. game will slow down instead
	if (ticksPassedThisUpdate > (int)(16 * 1.5))
	{
		updatesSkipped++; //= ticksPassed/16;
	}
}



//frame stats
long long System::lastRenderTime = 0;
long long System::lastUpdateTime = 0;

int System::ticksTextCount = 0;

int System::averageTicksPerRenderLastSecond = 0;
int System::averageTicksPerUpdateLastSecond = 0;

//memory stats
int System::mb = 1024 * 1024;
long long System::usedMemory = 0;
long long System::maxUsedMemory = 0;
long long System::totalMemory = 0;
long long System::freeMemory = 0;
long long System::maxMemory = 0;


void System::initStats()
{ //=========================================================================================================================


  //	if (GLUtils::usingVSync)
  //	{
  //		Console::debug("Vsync: on");
  //	}
  //	else
  //	{
  //		Console::debug("Vsync: off");
  //	}


  //initFrameStats();
	{
		upTimeText = Console::debug(" ");

		totalRendersText = Console::debug(" ");
		totalUpdatesText = Console::debug(" ");

		rendersPerSecondText = Console::add(" ");
		updatesPerSecondText = Console::debug(" ");
		averageRendersPerSecondText = Console::add(" ");
		onlineStatusText = Console::add(" ");

		rendersSkippedText = Console::debug(" ");
		updatesSkippedText = Console::debug(" ");

		averageTicksPerFrameText = Console::debug(" ");
		averageTicksPerUpdateText = Console::debug(" ");

#ifdef _DEBUG
		for (int i = 0; i < amtTicksTexts; i++)
			ticksText[i] = Console::debug(" ");
#endif
	}


	//initMemoryStats();
	{
		//memoryText = Console::debug("memoryText");
		texturesLoadedText = Console::debug(" ");
		textureBytesLoadedText = Console::debug(" ");

		//vramText = DebugConsole.add("vramText");

		totalMemory = 0;
		freeMemory = 0;
		maxMemory = 0;
	}



}


//=========================================================================================================================
void System::updateStats()
{ //=========================================================================================================================


	upTimeText->text = "Uptime: " + to_string(totalUpdateTicks / 1000) + "s (" + to_string(totalUpdateTicks) + "ms)";


	totalRendersText->text = "Total Renders: " + to_string(totalRenders);
	totalUpdatesText->text = "Total Updates: " + to_string(totalUpdates);

	rendersSkippedText->text = "Renders Skipped: " + to_string(rendersSkipped);
	updatesSkippedText->text = "Updates Skipped: " + to_string(updatesSkipped);


	if(Main::bobNet->tcpServerConnection.getConnectedToServer_S()==true)
	{
		if (Main::bobNet->tcpServerConnection.serverStats != nullptr)
		{
			int usersOnline = Main::bobNet->tcpServerConnection.serverStats->usersOnline;
			if(usersOnline==1)onlineStatusText->text = "Connected: " + to_string(usersOnline) + " player online";
			else onlineStatusText->text = "Connected: " + to_string(usersOnline) + " players online";
			onlineStatusText->color = BobColor::green;
		}
		else
		{
			onlineStatusText->text = "Connected";
			onlineStatusText->color = BobColor::green;
		}
	}
	else
	{
		onlineStatusText->text = "Offline";
		onlineStatusText->color = ConsoleText::defaultColor;
	}

	//if a second has passed
	int ticksPassedThisSecond = (int)(System::getTicksBetweenTimes(lastSecondTime, currentHighResTime));
	if (ticksPassedThisSecond >= 1000)
	{
		
		if (rendersThisSecond>0)averageTicksPerRenderLastSecond = ticksPassedThisSecond / rendersThisSecond;
		if (updatesThisSecond>0)averageTicksPerUpdateLastSecond = ticksPassedThisSecond / updatesThisSecond;

		if (rendersThisSecond >= 60)
		{
			rendersPerSecondText->color = ConsoleText::defaultColor;
		}
		else
			if (rendersThisSecond >= 30)
			{
				rendersPerSecondText->color = BobColor::yellow;
			}
			else
			{
				rendersPerSecondText->color = BobColor::red;
			}


		if (updatesThisSecond >= 60)
		{
			updatesPerSecondText->color = ConsoleText::defaultColor;
		}
		else
			if (updatesThisSecond >= 30)
			{
				updatesPerSecondText->color = BobColor::yellow;
			}
			else
			{
				updatesPerSecondText->color = BobColor::red;
			}


		rendersPerSecondText->text = "FPS: " + to_string(rendersThisSecond);
		updatesPerSecondText->text = "Updates/sec: " + to_string(updatesThisSecond);
		//averageRendersPerSecondText->text = "Average FPS: " + to_string(averageRendersPerSecond);

		averageTicksPerFrameText->text = "Average Ticks Per Frame (Last Second): " + to_string(averageTicksPerRenderLastSecond);
		averageTicksPerUpdateText->text = "Average Ticks Per Update (Last Second): " + to_string(averageTicksPerUpdateLastSecond);

		lastSecondTime += (long long)(1000 * cpuFreq);
		rendersThisSecond = 0;
		updatesThisSecond = 0;


		totalSecondsPassed++;


		averageRendersPerSecond = totalRenders / totalSecondsPassed;



		if (Main::mainLoopStarted && totalSecondsPassed > 15)
		{
			averageFPSTestSecondsPassed++;
			int averageFPSTestRendersPerSecond = averageFPSTestTotalRenders / averageFPSTestSecondsPassed;

			averageRendersPerSecondText->text = "Average FPS: " + to_string(averageFPSTestRendersPerSecond);

			if (averageFPSTestRendersPerSecond < 50)
			{
				averageFPSTestTotalRenders = 0;
				averageFPSTestSecondsPassed = 0;
				if (GLUtils::SHADER_FBO_SCALE == 1.0f)
				{
					log.debug("Downscaled shaders to try for higher framerate");
					GLUtils::SHADER_FBO_SCALE = 0.5f;
					GLUtils::doResize();
				}
				else
					if (GLUtils::SHADER_FBO_SCALE == 0.5f)
					{
						log.debug("Downscaled shaders again to try for higher framerate");
						GLUtils::SHADER_FBO_SCALE = 0.25f;
						GLUtils::doResize();
					}
				//GLUtils::DEFAULT_SHADER_FBO_FILTER = GLUtils::FILTER_FBO_LINEAR_NO_MIPMAPPING;
			}


			//		else
			//		if(averageFPSTestSecondsPassed>15 && averageFPSTestRendersPerSecond>=50)
			//		{
			//			averageFPSTestTotalRenders = 0;
			//			averageFPSTestSecondsPassed = 0;
			//			if (GLUtils::SHADER_FBO_SCALE == 0.25f)
			//			{
			//				log.debug("Upscaled shaders to try for higher framerate");
			//				GLUtils::SHADER_FBO_SCALE = 0.5f;
			//				GLUtils::doResize();
			//			}
			//			else			
			//			if (GLUtils::SHADER_FBO_SCALE == 0.5f)
			//			{
			//				log.debug("Upscaled shaders to try for higher framerate");
			//				GLUtils::SHADER_FBO_SCALE = 1.0f;
			//				GLUtils::doResize();
			//			}
			//		}

		}
	}


#ifdef _DEBUG
	long long thisRenderTime = currentHighResTime;
	int debugTicksPassed = (int)(System::getTicksBetweenTimes(lastRenderTime, thisRenderTime));
	lastRenderTime = thisRenderTime;

	for (int i = 0; i < amtTicksTexts; i++)
	{
		if (ticksTextCount == i)
		{
			ticksText[i]->text = string("Ticks Passed " + to_string(i) + ": ") + to_string(debugTicksPassed);
			if (debugTicksPassed > 17)
			{
				ticksText[i]->color = BobColor::red;
			}
			else
			{
				ticksText[i]->color = ConsoleText::defaultColor;
			}
		}
	}

	ticksTextCount++;
	if (ticksTextCount >= amtTicksTexts)
	{
		ticksTextCount = 0;
	}
#endif



	//---------------------------------
	//memory
	//---------------------------------
	//if(currentHighResTime>=last100Ticks+100)
	//#ifdef USE_SIGAR
	//	int status;
	//	sigar_proc_mem_t proc;
	//	status = sigar_proc_mem_get(sigar, sigar_pid_get(sigar), &proc);
	//	if (status != SIGAR_OK) {
	//		printf("sigar_proc_mem_get error: %d (%s)\n",
	//			status, sigar_strerror(sigar, status));
	//		exit(1);
	//	}
	//	//log.info("Proc Mem Size:" + to_string(proc.size / 1024 / 1024));
	//	//log.info("Proc Mem Resident:" + to_string(proc.resident / 1024 / 1024));
	//	//log.info("Proc Mem Share:" + to_string(proc.share / 1024 / 1024));
	//
	//
	//	int procMemUsed = (int)(proc.size / 1024 / 1024);
	//
	//	sigar_mem_t mem;
	//	status = sigar_mem_get(sigar, &mem);
	//	if (status != SIGAR_OK) {
	//		printf("sigar_mem_get error: %d (%s)\n",
	//			status, sigar_strerror(sigar, status));
	//		exit(1);
	//	}
	////			log.info("Ram:" + to_string(mem.ram));
	////			log.info("Total:" + to_string(mem.total / 1024 / 1024));
	////			log.info("Used:" + to_string(mem.used / 1024 / 1024));
	////			log.info("Free:" + to_string(mem.free / 1024 / 1024));
	////			log.info("Actual Used:" + to_string(mem.actual_used / 1024 / 1024));
	////			log.info("Actual Free:" + to_string(mem.actual_free / 1024 / 1024));
	////			log.info("Used %:" + to_string(mem.used_percent));
	////			log.info("Free %:" + to_string(mem.free_percent));
	//
	//	totalMemory = (mem.ram);//rt->totalMemory();
	//	freeMemory = (mem.free / 1024 / 1024);//rt->freeMemory();
	//
	//	usedMemory = procMemUsed;// (totalMemory - freeMemory) / mb;
	//	if (usedMemory > maxUsedMemory)
	//	{
	//		maxUsedMemory = usedMemory;
	//	}
	//
	//	memoryText->text = "Memory Used: " + to_string(usedMemory) + " MB" + " | Max Used: " + to_string(maxUsedMemory) + " MB" + " | Free: " + to_string(freeMemory / mb) + " MB" + " | Total: " + to_string(totalMemory / mb) + " MB" + " | Max: " + to_string(maxMemory / mb) + " MB";
	//
	//#endif


	//---------------------------------
	//vram
	//---------------------------------

	//vramText.getText = "Available VRAM: "+gd.getAvailableAcceleratedMemory()/1024 +" KB";
	//last100Ticks+=100;

	texturesLoadedText->text = "Textures Loaded: " + to_string(GLUtils::texturesLoaded);
	textureBytesLoadedText->text = "Texture MBs Loaded: " + to_string(GLUtils::textureBytesLoaded / 1024 / 1024);


	//---------------------------------
	//threads
	//---------------------------------
	//#ifdef USE_SIGAR
	//
	//	sigar_proc_stat_t procstat;
	//	int status = sigar_proc_stat_get(sigar, &procstat);
	//	if (status != SIGAR_OK) {
	//		printf("sigar_proc_stat_get error: %d (%s)\n",
	//			status, sigar_strerror(sigar, status));
	//		exit(1);
	//	}
	////	log.info("Proc Total:" + to_string(procstat.total));
	////	log.info("Proc Sleeping:" + to_string(procstat.sleeping));
	////	log.info("Proc Running:" + to_string(procstat.running));
	////	log.info("Proc Zombie:" + to_string(procstat.zombie));
	////	log.info("Proc Stopped:" + to_string(procstat.stopped));
	////	log.info("Proc Idle:" + to_string(procstat.idle));
	////	log.info("Proc Threads:" + to_string(procstat.threads));
	//
	//	mxThreadCountText->text = string("Thread Count: "+ to_string(procstat.threads));// +ManagementFactory::getThreadMXBean().getThreadCount() + " | Daemon Thread Count: " + ManagementFactory::getThreadMXBean().getDaemonThreadCount() + " | Peak Thread Count: " + ManagementFactory::getThreadMXBean().getPeakThreadCount() + " | Total Started: " + ManagementFactory::getThreadMXBean().getTotalStartedThreadCount();
	//
	//#endif

}





//=========================================================================================================================
long long System::getPerformanceCounter()
{//=========================================================================================================================
	return SDL_GetPerformanceCounter() - timerOffset;
}


//=========================================================================================================================
long long System::currentHighResTimer()
{//=========================================================================================================================
	return currentHighResTime;
}


//=========================================================================================================================
double System::getTicksBetweenTimes(long long start, long long finish)
{//=========================================================================================================================
	return ((double)(finish - start) / cpuFreq);
}


//=========================================================================================================================
int System::getTotalRenderTicksPassed()
{//=========================================================================================================================
	return (int)totalRenderTicks;
}
//=========================================================================================================================
void System::resetTotalRenderTicksPassed()
{//=========================================================================================================================
	totalRenderTicks = 0;
}




//int System::framesrendered = 0;
//int System::secondspassed = 0;
//int System::lastsecondspassed = 0;
//int System::fps = 0;

//
////==========================================================================================================================
//void System::calculate_fps()
//{//==========================================================================================================================
//	static int secondstotal = 0;
//	secondspassed = (SDL_GetTicks()) / 1000;
//
//	static DEBUG_overlay_STRUCT* fps_overlay = NULL;
//
//	if (secondspassed > lastsecondspassed)
//	{
//		lastsecondspassed = secondspassed;
//		fps = framesrendered;
//		framesrendered = 0;
//
//		secondstotal++;
//
//		if (Main::fpsmeter)
//		{
//			string fpschar = "";// [128];
//			//sprintf(fpschar, "fps:%c%c%c", 48 + ((fps / 100) % 10), 48 + ((fps / 10) % 10), 48 + (fps % 10));
//			fpschar = "fps:" + to_string(fps);
//
//			if (fps_overlay == NULL)fps_overlay = DEBUG_make_overlay(fpschar, (float)((GLUtils::getRealWindowWidth() / 2) - 20), (float)(GLUtils::getRealWindowHeight() - 10));
//			else DEBUG_update_overlay(fps_overlay, fpschar, (float)((GLUtils::getRealWindowWidth() / 2) - (fps_overlay->width / 2)), (float)(GLUtils::getRealWindowHeight() - 10));
//		}
//		else
//		{
//			if(fps_overlay != NULL)DEBUG_delete_overlay(fps_overlay);
//			fps_overlay = NULL;
//		}
//
//		if (secondstotal > 1 && fps > 70 && GLUtils::usingVSync == 1)
//		{
//			GLUtils::usingVSync = 0;
//			//CAPTION_make_caption(NULL,1,CAPTION_CENTERED_X,10,10,"Please Turn VSync On - See Readme",FONT_HUGE_ID,RED,CLEAR,5,1);
//			//fprintf(stderr,"Vsync Hard-Limiter Activated. Please check your Video Settings Control Panel for a \"vertical sync\" option and turn it on for smoother gameplay.\n");
//		}
//	}
//}

//LARGE_INTEGER System::highResTimer;
//LARGE_INTEGER System::highResolutionTicksPerSecond;
