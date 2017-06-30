
#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



Logger System::log = Logger("System");


string System::internetProviderString = "";
string System::browserUserAgentString = "";
string System::browserAppNameVersionString = "";
string System::browserReferrerString = "";

string System::getEnvProcessorIdentifier = "";
string System::getEnvProcessorArchitecture = "";
string System::getEnvNumberOfProcessors = "";

float System::timeZoneGMTOffset=0.0f;

string System::jreVersion = "";
string System::jreVendor = "";
string System::jreHomeDir = "";
string System::jvmVersion = "";
string System::jvmName = "";
string System::javaClassVersion = "";
string System::javaClassPath = "";
string System::javaLibraryPath = "";
string System::javaTempDir = "";
string System::osName = "";
string System::osArch = "";
string System::osVersion = "";
string System::osUserAccountName = "";
string System::osHomeDir = "";
string System::workingDir = "";

int System::displayWidth = -1;
int System::displayHeight = -1;
int System::displayBPP = -1;
int System::displayFreq = -1;
bool System::shaderCompiled = false;
bool System::canUseFBO = false;
bool System::usingVSync = false;
string System::displayAdapter = "";
string System::displayDriver = "";
string System::lwjglVersion = "";
bool System::lwjglIs64Bit=false;
string System::lwjglPlatformName = "";
int System::numCPUs=-1;

int System::numControllersFound=-1;
string System::controllersNames = "";

string System::glVendor = "";
string System::glVersion = "";
string System::glRenderer = "";
string System::shaderVersion = "";
string System::glExtensions = "";


ConsoleText* System::totalRendersText = nullptr;
ConsoleText* System::totalUpdatesText = nullptr;
ConsoleText* System::rendersPerSecondText = nullptr;
ConsoleText* System::averageRendersPerSecondText = nullptr;
ConsoleText* System::updatesPerSecondText = nullptr;
ConsoleText* System::rendersSkippedText = nullptr;
ConsoleText* System::updatesSkippedText = nullptr;
ConsoleText* System::averageTicksPerFrameText = nullptr;
ConsoleText* System::averageTicksPerUpdateText = nullptr;

ConsoleText* System::upTimeText = nullptr;

ConsoleText* System::ticksText[amtTicksTexts] = {nullptr};


ConsoleText* System::mxThreadCountText = nullptr;

ConsoleText* System::memoryText = nullptr;
ConsoleText* System::texturesLoadedText = nullptr;// = Console::debug("texturesLoadedText");
ConsoleText* System::textureBytesLoadedText = nullptr;// = Console::debug("textureBytesLoadedText");


//#include "Poco/DateTime.h"
//using Poco::DateTime;
//#include "Poco/LocalDateTime.h"
//using Poco::LocalDateTime;
//#include "Poco/Timezone.h"
//#include "Poco/Timestamp.h"
//using Poco::Timezone;
//using Poco::Timestamp;
//
//#include "Poco/Path.h"
//using Poco::Path;

#include "Poco/Environment.h"
using Poco::Environment;

//#define USE_SIGAR
#if defined(__WINDOWS__) && defined(USE_SIGAR)
#include "sigar.h"
#endif

#ifdef USE_SIGAR
sigar_t *sigar = nullptr;
#endif


void System::initSystemInfo()
{ //=========================================================================================================================

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

	//SDL_GetQueuedAudioSize();

	//os
	log.info("SDL_GetBasePath:" + string(SDL_GetBasePath()));
	//log.info("SDL_GetClipboardText:" + string(SDL_GetClipboardText()));


	//log.info("SDL_HINT_ACCELEROMETER_AS_JOYSTICK:" + string(SDL_GetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK)));
	//log.info("SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION:" + string(SDL_GetHint(SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION)));
	//log.info("SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION:" + string(SDL_GetHint(SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION)));
	//log.info("SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH:" + string(SDL_GetHint(SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH)));
	//log.info("SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT:" + string(SDL_GetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT)));
	//log.info("SDL_HINT_FRAMEBUFFER_ACCELERATION:" + string(SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION)));
	//log.info("SDL_HINT_GAMECONTROLLERCONFIG:" + string(SDL_GetHint(SDL_HINT_GAMECONTROLLERCONFIG)));
	//log.info("SDL_HINT_GRAB_KEYBOARD:" + string(SDL_GetHint(SDL_HINT_GRAB_KEYBOARD)));
	//log.info("SDL_HINT_IDLE_TIMER_DISABLED:" + string(SDL_GetHint(SDL_HINT_IDLE_TIMER_DISABLED)));
	//log.info("SDL_HINT_IME_INTERNAL_EDITING:" + string(SDL_GetHint(SDL_HINT_IME_INTERNAL_EDITING)));
	//log.info("SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS:" + string(SDL_GetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS)));
	//log.info("SDL_HINT_MAC_BACKGROUND_APP:" + string(SDL_GetHint(SDL_HINT_MAC_BACKGROUND_APP)));
	//log.info("SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK:" + string(SDL_GetHint(SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK)));
	//log.info("SDL_HINT_MOUSE_RELATIVE_MODE_WARP:" + string(SDL_GetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP)));
	//log.info("SDL_HINT_NO_SIGNAL_HANDLERS:" + string(SDL_GetHint(SDL_HINT_NO_SIGNAL_HANDLERS)));
	//log.info("SDL_HINT_ORIENTATIONS:" + string(SDL_GetHint(SDL_HINT_ORIENTATIONS)));
	//log.info("SDL_HINT_RENDER_DIRECT3D11_DEBUG:" + string(SDL_GetHint(SDL_HINT_RENDER_DIRECT3D11_DEBUG)));
	//log.info("SDL_HINT_RENDER_DIRECT3D_THREADSAFE:" + string(SDL_GetHint(SDL_HINT_RENDER_DIRECT3D_THREADSAFE)));
	//log.info("SDL_HINT_RENDER_DRIVER:" + string(SDL_GetHint(SDL_HINT_RENDER_DRIVER)));
	//log.info("SDL_HINT_RENDER_OPENGL_SHADERS:" + string(SDL_GetHint(SDL_HINT_RENDER_OPENGL_SHADERS)));
	//log.info("SDL_HINT_RENDER_SCALE_QUALITY:" + string(SDL_GetHint(SDL_HINT_RENDER_SCALE_QUALITY)));
	//log.info("SDL_HINT_RENDER_VSYNC:" + string(SDL_GetHint(SDL_HINT_RENDER_VSYNC)));
	//log.info("SDL_HINT_THREAD_STACK_SIZE:" + string(SDL_GetHint(SDL_HINT_THREAD_STACK_SIZE)));
	//log.info("SDL_HINT_TIMER_RESOLUTION:" + string(SDL_GetHint(SDL_HINT_TIMER_RESOLUTION)));
	//log.info("SDL_HINT_VIDEO_ALLOW_SCREENSAVER:" + string(SDL_GetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER)));
	//log.info("SDL_HINT_VIDEO_HIGHDPI_DISABLED:" + string(SDL_GetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED)));
	//log.info("SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES:" + string(SDL_GetHint(SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES)));
	//log.info("SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS:" + string(SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS)));
	//log.info("SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT:" + string(SDL_GetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT)));
	//log.info("SDL_HINT_VIDEO_WIN_D3DCOMPILER:" + string(SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER)));
	////log.info(":" + string(SDL_GetHint(SDL_HINT_VIDEO_X11_NET_WM_PING)));
	//log.info("SDL_HINT_VIDEO_X11_XINERAMA:" + string(SDL_GetHint(SDL_HINT_VIDEO_X11_XINERAMA)));
	//log.info("SDL_HINT_VIDEO_X11_XRANDR:" + string(SDL_GetHint(SDL_HINT_VIDEO_X11_XRANDR)));
	//log.info("SDL_HINT_VIDEO_X11_XVIDMODE:" + string(SDL_GetHint(SDL_HINT_VIDEO_X11_XVIDMODE)));
	//log.info("SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP:" + string(SDL_GetHint(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP)));
	//log.info("SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4:" + string(SDL_GetHint(SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4)));
	//log.info("SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN:" + string(SDL_GetHint(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN)));
	//log.info("SDL_HINT_WINRT_HANDLE_BACK_BUTTON:" + string(SDL_GetHint(SDL_HINT_WINRT_HANDLE_BACK_BUTTON)));
	//log.info("SDL_HINT_WINRT_PRIVACY_POLICY_LABEL:" + string(SDL_GetHint(SDL_HINT_WINRT_PRIVACY_POLICY_LABEL)));
	//log.info("SDL_HINT_WINRT_PRIVACY_POLICY_URL:" + string(SDL_GetHint(SDL_HINT_WINRT_PRIVACY_POLICY_URL)));
	//log.info("SDL_HINT_XINPUT_ENABLED:" + string(SDL_GetHint(SDL_HINT_XINPUT_ENABLED)));
	//log.info("SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING:" + string(SDL_GetHint(SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING)));


	log.info("SDL_GetPerformanceCounter" + to_string(SDL_GetPerformanceCounter()));
	log.info("SDL_GetPerformanceFrequency" + to_string(SDL_GetPerformanceFrequency()));
	log.info("SDL_GetPlatform" + string(SDL_GetPlatform()));
	//log.info("SDL_GetPowerInfo" + to_string(SDL_GetPowerInfo()));
	log.info("SDL_GetPrefPath" + string(SDL_GetPrefPath("Bob Corporation", "bob's game")));
	log.info("SDL_GetRevision" + string(SDL_GetRevision()));
	log.info("SDL_GetRevisionNumber" + to_string(SDL_GetRevisionNumber()));
	log.info("SDL_GetSystemRAM" + to_string(SDL_GetSystemRAM()));
	//log.info("" + to_string(SDL_GetThreadID()));
	//log.info("SDL_GetThreadName" + string(SDL_GetThreadName()));
	log.info("SDL_GetTicks" + to_string(SDL_GetTicks()));


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
	//log.info(":" + to_string(SDL_GetWindowData()));
	log.info("SDL_GetWindowDisplayIndex():" + to_string(SDL_GetWindowDisplayIndex(GLUtils::window)));
	//log.info("SDL_GetWindowDisplayMode():" + to_string(SDL_GetWindowDisplayMode(GLUtils::window)));
	log.info("SDL_GetWindowFlags():" + to_string(SDL_GetWindowFlags(GLUtils::window)));
	//log.info("SDL_GetWindowFromID():" + to_string(SDL_GetWindowFromID()));
	//log.info("SDL_GetWindowGammaRamp():" + to_string(SDL_GetWindowGammaRamp(GLUtils::window)));
	log.info("SDL_GetWindowGrab():" + to_string(SDL_GetWindowGrab(GLUtils::window)));
	log.info("SDL_GetWindowID():" + to_string(SDL_GetWindowID(GLUtils::window)));
	//log.info("SDL_GetWindowMaximumSize():" + to_string(SDL_GetWindowMaximumSize(GLUtils::window)));
	//log.info("SDL_GetWindowMinimumSize():" + to_string(SDL_GetWindowMinimumSize(GLUtils::window)));
	log.info("SDL_GetWindowPixelFormat():" + to_string(SDL_GetWindowPixelFormat(GLUtils::window)));
	//log.info("SDL_GetWindowPosition():" + to_string(SDL_GetWindowPosition(GLUtils::window)));
	//log.info("SDL_GetWindowSize():" + to_string(SDL_GetWindowSize(GLUtils::window)));
	//log.info("SDL_GetWindowSurface():" + to_string(SDL_GetWindowSurface()));
	log.info("SDL_GetWindowTitle():" + string(SDL_GetWindowTitle(GLUtils::window)));
	//SDL_GetWindowWMInfo()));

	//mouse
	//log.info("SDL_GetCursor():" + to_string(SDL_GetCursor()));
	//log.info("SDL_GetDefaultCursor():" + to_string(SDL_GetDefaultCursor()));
	//log.info("SDL_GetGlobalMouseState():" + to_string(SDL_GetGlobalMouseState()));
	//log.info("SDL_GetMouseFocus():" + to_string(SDL_GetMouseFocus()));
	//log.info("SDL_GetMouseState():" + to_string(SDL_GetMouseState()));
	log.info("SDL_GetNumTouchDevices():" + to_string(SDL_GetNumTouchDevices()));
	//log.info("SDL_GetNumTouchFingers():" + to_string(SDL_GetNumTouchFingers()));
	log.info("SDL_GetRelativeMouseMode():" + to_string(SDL_GetRelativeMouseMode()));
	//log.info("SDL_GetRelativeMouseState():" + to_string(SDL_GetRelativeMouseState()));

	//key
	//log.info("SDL_GetKeyFromName():" + to_string(SDL_GetKeyFromName()));
	//log.info("SDL_GetKeyFromScancode():" + to_string(SDL_GetKeyFromScancode()));
	//log.info("SDL_GetKeyName():" + to_string(SDL_GetKeyName()));
	//log.info("SDL_GetKeyboardFocus():" + to_string(SDL_GetKeyboardFocus()));
	//log.info("SDL_GetKeyboardState():" + to_string(SDL_GetKeyboardState()));
	//log.info("SDL_GetModState():" + to_string(SDL_GetModState()));
	//log.info("SDL_GetScancodeFromKey():" + to_string(SDL_GetScancodeFromKey()));
	//log.info("SDL_GetScancodeFromName():" + to_string(SDL_GetScancodeFromName()));
	//log.info("SDL_GetScancodeName():" + to_string(SDL_GetScancodeName()));
	//log.info("SDL_GetTouchDevice():" + to_string(SDL_GetTouchDevice()));
	//log.info("SDL_GetTouchFinger():" + to_string(SDL_GetTouchFinger()));
	log.info("SDL_HasScreenKeyboardSupport():" + to_string(SDL_HasScreenKeyboardSupport()));

	//cpu
	log.info("SDL_GetCPUCacheLineSize():" + to_string(SDL_GetCPUCacheLineSize()));
	log.info("SDL_GetCPUCount():" + to_string(SDL_GetCPUCount()));
	log.info("SDL_Has3DNow():" + to_string(SDL_Has3DNow()));
	log.info("SDL_HasAVX():" + to_string(SDL_HasAVX()));
	//log.info("SDL_HasAVX2():" + to_string(SDL_HasAVX2()));
	log.info("SDL_HasAltiVec():" + to_string(SDL_HasAltiVec()));
	//log.info("SDL_HasClipboardText():" + to_string(SDL_HasClipboardText()));
	//log.info("SDL_HasEvent():" + to_string(SDL_HasEvent()));
	//log.info("SDL_HasEvents():" + to_string(SDL_HasEvents()));
	//log.info("SDL_HasIntersection():" + to_string(SDL_HasIntersection()));
	log.info("SDL_HasMMX():" + to_string(SDL_HasMMX()));
	log.info("SDL_HasRDTSC():" + to_string(SDL_HasRDTSC()));
	log.info("SDL_HasSSE():" + to_string(SDL_HasSSE()));
	log.info("SDL_HasSSE2():" + to_string(SDL_HasSSE2()));
	log.info("SDL_HasSSE3():" + to_string(SDL_HasSSE3()));
	log.info("SDL_HasSSE41():" + to_string(SDL_HasSSE41()));
	log.info("SDL_HasSSE42():" + to_string(SDL_HasSSE42()));


	//video
	//log.info("SDL_GetClipRect():" + to_string(SDL_GetClipRect()));
	//log.info("SDL_GetClosestDisplayMode():" + to_string(SDL_GetClosestDisplayMode()));
	//log.info("SDL_GetColorKey():" + to_string(SDL_GetColorKey()));
	//log.info("SDL_GetCurrentDisplayMode():" + to_string(SDL_GetCurrentDisplayMode()));
	//log.info("SDL_GetCurrentVideoDriver():" + to_string(SDL_GetCurrentVideoDriver()));
	//log.info("SDL_GetDesktopDisplayMode():" + to_string(SDL_GetDesktopDisplayMode()));
	//log.info("SDL_GetDisplayBounds():" + to_string(SDL_GetDisplayBounds()));
	//log.info("SDL_GetDisplayDPI():" + to_string(SDL_GetDisplayDPI()));
	//log.info("SDL_GetDisplayMode():" + to_string(SDL_GetDisplayMode()));
	//log.info("SDL_GetDisplayName():" + to_string(SDL_GetDisplayName()));
	//log.info("SDL_GetNumDisplayModes():" + to_string(SDL_GetNumDisplayModes()));
	log.info("SDL_GetNumRenderDrivers():" + to_string(SDL_GetNumRenderDrivers()));
	log.info("SDL_GetNumVideoDisplays():" + to_string(SDL_GetNumVideoDisplays()));
	log.info("SDL_GetNumVideoDrivers():" + to_string(SDL_GetNumVideoDrivers()));
	//log.info("SDL_GetPixelFormatName():" + to_string(SDL_GetPixelFormatName()));
	//log.info("SDL_GetRGB():" + to_string(SDL_GetRGB()));
	//log.info("SDL_GetRGBA():" + to_string(SDL_GetRGBA()));
	//log.info("SDL_GetRenderDrawBlendMode():" + to_string(SDL_GetRenderDrawBlendMode()));
	//log.info("SDL_GetRenderDrawColor():" + to_string(SDL_GetRenderDrawColor()));
	//log.info("SDL_GetRenderDriverInfo():" + to_string(SDL_GetRenderDriverInfo()));
	//log.info("SDL_GetRenderTarget():" + to_string(SDL_GetRenderTarget()));
	//log.info("SDL_GetRenderer():" + to_string(SDL_GetRenderer()));
	//log.info("SDL_GetRendererInfo():" + to_string(SDL_GetRendererInfo()));
	//log.info("SDL_GetRendererOutputSize():" + to_string(SDL_GetRendererOutputSize()));
	//log.info("SDL_GetSurfaceAlphaMod():" + to_string(SDL_GetSurfaceAlphaMod()));
	//log.info("SDL_GetSurfaceBlendMode():" + to_string(SDL_GetSurfaceBlendMode()));
	//log.info("SDL_GetSurfaceColorMod():" + to_string(SDL_GetSurfaceColorMod()));
	//log.info("SDL_GetTextureAlphaMod():" + to_string(SDL_GetTextureAlphaMod()));
	//log.info("SDL_GetTextureBlendMode():" + to_string(SDL_GetTextureBlendMode()));
	//log.info("SDL_GetTextureColorMod():" + to_string(SDL_GetTextureColorMod()));
	//log.info("SDL_GetVideoDriver():" + to_string(SDL_GetVideoDriver()));


	log.info("Poco::libraryVersion()" + to_string(Environment::libraryVersion()));
	//log.info("Poco::nodeId()" + string(Environment::nodeId()));
	//log.info("Poco::nodeName()" + string(Environment::nodeName()));
	//log.info("Poco::osArchitecture()" + string(Environment::osArchitecture()));
	//log.info("Poco::osDisplayName()" + string(Environment::osDisplayName()));
	log.info("Poco::osName()" + string(Environment::osName()));
	log.info("Poco::osVersion()" + string(Environment::osVersion()));
	log.info("Poco::processorCount()" + to_string(Environment::processorCount()));


#ifdef USE_SIGAR

int status, i;

sigar_cpu_info_list_t cpulist;


sigar_open(&sigar);

status = sigar_cpu_info_list_get(sigar, &cpulist);
if (status != SIGAR_OK) {
	printf("sigar_cpu_info_list_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	exit(1);
}


for (i = 0; i<(int)cpulist.number; i++) {
	sigar_cpu_info_t cpu = cpulist.data[i];
	log.info("CPU "+to_string(i)+" Vendor:"+string(cpu.vendor));
	log.info("CPU "+to_string(i)+" Model:" + string(cpu.model));
	log.info("CPU "+to_string(i)+" Mhz:" + to_string(cpu.mhz));
	log.info("CPU "+to_string(i)+" Cores:" + to_string(cpu.total_cores));
}
sigar_cpu_info_list_destroy(sigar, &cpulist);


sigar_mem_t mem;
status = sigar_mem_get(sigar, &mem);
if (status != SIGAR_OK) {
	printf("sigar_mem_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	exit(1);
}
log.info("Ram:" + to_string(mem.ram));
log.info("Total:" + to_string(mem.total/1024 / 1024));
log.info("Used:" + to_string(mem.used/1024 / 1024));
log.info("Free:" + to_string(mem.free/1024 / 1024));
log.info("Actual Used:" + to_string(mem.actual_used / 1024 / 1024));
log.info("Actual Free:" + to_string(mem.actual_free / 1024 / 1024));
log.info("Used %:" + to_string(mem.used_percent));
log.info("Free %:" + to_string(mem.free_percent));


sigar_sys_info_t sys;
status = sigar_sys_info_get(sigar, &sys);
if (status != SIGAR_OK) {
	printf("sigar_sys_info_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	exit(1);
}

log.info("System Name:"+string(sys.name));
log.info("System Version:"+string(sys.version));
log.info("System Arch:"+string(sys.arch));
log.info("System Machine:"+string(sys.machine));
log.info("System Description:"+string(sys.description));
log.info("System Vendor:"+string(sys.vendor));
log.info("System Vendor Version:"+string(sys.vendor_version));
log.info("System Vendor Name:"+string(sys.vendor_name));
log.info("System Vendor Code Name:"+string(sys.vendor_code_name));


sigar_proc_mem_t proc;
status = sigar_proc_mem_get(sigar, sigar_pid_get(sigar), &proc);
if (status != SIGAR_OK) {
	printf("sigar_proc_mem_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	exit(1);
}
log.info("Proc Mem Size:" + to_string(proc.size / 1024 / 1024));
log.info("Proc Mem Resident:" + to_string(proc.resident / 1024 / 1024));
log.info("Proc Mem Share:" + to_string(proc.share / 1024 / 1024));


sigar_proc_stat_t procstat;
status = sigar_proc_stat_get(sigar, &procstat);
if (status != SIGAR_OK) {
	printf("sigar_proc_stat_get error: %d (%s)\n",
		status, sigar_strerror(sigar, status));
	exit(1);
}
log.info("Proc Total:" + to_string(procstat.total));
log.info("Proc Sleeping:" + to_string(procstat.sleeping));
log.info("Proc Running:" + to_string(procstat.running));
log.info("Proc Zombie:" + to_string(procstat.zombie));
log.info("Proc Stopped:" + to_string(procstat.stopped));
log.info("Proc Idle:" + to_string(procstat.idle));
log.info("Proc Threads:" + to_string(procstat.threads));

//sigar_close(sigar);
#endif
//
//
//log.info("Current Working Dir:  " + Path::current());;
//log.info("Home Dir: " + Path::home());
//log.info("Temp Dir: " + Path::temp());

	//
	//			clientInfo->getEnvProcessorIdentifier = System::getenv("PROCESSOR_IDENTIFIER");
	//			clientInfo->getEnvProcessorArchitecture = System::getenv("PROCESSOR_ARCHITECTURE");
	//			clientInfo->getEnvNumberOfProcessors = System::getenv("NUMBER_OF_PROCESSORS");
	//
	//
	//			clientInfo->jreVersion = "" + systemProperties->getProperty("java.version");
	//			clientInfo->jreVendor = "" + systemProperties->getProperty("java.vendor");
	//			//clientInfo.jreVendorURL			= ""+systemProperties.getProperty("java.vendor.url");
	//			clientInfo->jreHomeDir = "" + systemProperties->getProperty("java.home");
	//			//clientInfo.jvmSpecVersion		= ""+systemProperties.getProperty("java.vm.specification.version");
	//			//clientInfo.jvmSpecVendor		= ""+systemProperties.getProperty("java.vm.specification.vendor");
	//			//clientInfo.jvmSpecName			= ""+systemProperties.getProperty("java.vm.specification.name");
	//			clientInfo->jvmVersion = "" + systemProperties->getProperty("java.vm.version");
	//			//clientInfo.jvmVendor			= ""+systemProperties.getProperty("java.vm.vendor");
	//			clientInfo->jvmName = "" + systemProperties->getProperty("java.vm.name");
	//			//clientInfo.jreSpecVersion		= ""+systemProperties.getProperty("java.specification.version");
	//			//clientInfo.jreSpecVendor		= ""+systemProperties.getProperty("java.specification.vendor");
	//			//clientInfo.jreSpecName			= ""+systemProperties.getProperty("java.specification.name");
	//			clientInfo->javaClassVersion = "" + systemProperties->getProperty("java.class.version");
	//			clientInfo->javaClassPath = "" + systemProperties->getProperty("java.class.path");
	//			clientInfo->javaLibraryPath = "" + systemProperties->getProperty("java.library.path");
	//			clientInfo->javaTempDir = "" + systemProperties->getProperty("java.io.tmpdir");
	//			//clientInfo.javaJITCompiler		= ""+systemProperties.getProperty("java.compiler");
	//			//clientInfo.javaExtensionPath	= ""+systemProperties.getProperty("java.ext.dirs");
	//			clientInfo->osName = "" + systemProperties->getProperty("os.name");
	//			clientInfo->osArch = "" + systemProperties->getProperty("os.arch");
	//			clientInfo->osVersion = "" + systemProperties->getProperty("os.version");
	//			clientInfo->osUserAccountName = "" + systemProperties->getProperty("user.name");
	//			clientInfo->osHomeDir = "" + systemProperties->getProperty("user.home");
	//			clientInfo->workingDir = "" + systemProperties->getProperty("user.dir");
	//
	//
	//			clientInfo->displayWidth = Screen::getDesktopDisplayMode().getWidth();
	//			clientInfo->displayHeight = Screen::getDesktopDisplayMode().getHeight();
	//			clientInfo->displayBPP = Screen::getDesktopDisplayMode().getBitsPerPixel();
	//			clientInfo->displayFreq = Screen::getDesktopDisplayMode().getFrequency();
	//
	//
	//
	//			clientInfo->shaderCompiled = GLUtils::useShaders;
	//			clientInfo->canUseFBO = GLUtils::useFBO;
	//			clientInfo->usingVSync = GLUtils::vsync;
	//
	//
	//			clientInfo->displayAdapter = Screen::getAdapter();
	//			clientInfo->displayDriver = Screen::getVersion();
	//			clientInfo->lwjglVersion = System::getVersion();
	//			clientInfo->lwjglIs64Bit = System::is64Bit();
	//			clientInfo->lwjglPlatformName = System::getPlatformName();
	//
	//			clientInfo->numCPUs = StatsUtils::rt->availableProcessors();
	//			clientInfo->totalMemory = StatsUtils::totalMemory / 1024 / 1024;
	//			clientInfo->maxMemory = StatsUtils::maxMemory / 1024 / 1024;
	//
	//			clientInfo->numControllersFound = GLUtils::numControllers;
	//			clientInfo->controllersNames = GLUtils::controllerNames;
	//
	//
	//
	//			clientInfo->timeZoneGMTOffset = timeZoneGMTOffset;


	char* vendorString = (char*)glGetString(GL_VENDOR);
	char* versionString = (char*)glGetString(GL_VERSION);
	char* rendererString = (char*)glGetString(GL_RENDERER);
	char* shaderVersionString = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	char* extensionsString = (char*)glGetString(GL_EXTENSIONS);

	if (vendorString != NULL)glVendor = string(vendorString);
	if (versionString != NULL)glVersion = string(versionString);
	if (rendererString != NULL)glRenderer = string(rendererString);
	if (shaderVersionString != NULL)shaderVersion = string(shaderVersionString);
	if (extensionsString != NULL)glExtensions = string(extensionsString);

	logSystemInfo();
	log.info("Window Width:" + to_string(GLUtils::getRealWindowWidth()));
	log.info("Window Height:" + to_string(GLUtils::getRealWindowHeight()));



}



void System::initClockAndTimeZone()
{ //=========================================================================================================================

	log.info("Init Clock and Time Zone...");
	//
	//			//put timezone in connection info
	//			Calendar *calendar = Calendar::getInstance();
	//
	//			Date calendarTime = calendar->getTime();
	//			log.info("Local Adjusted Time: " + calendarTime);
	//			string gmtOffset = (new SimpleDateFormat("Z"))->format(calendarTime);
	//			log.info("Local TimeZone GMT offset: " + gmtOffset);
	//
	//
	//
	//			//get the time zone
	//			TimeZone *timezone = calendar->getTimeZone();
	//
	//
	//			//get timezone raw millisecond offset
	//			int offset = timezone->getRawOffset();
	//			int offsetHrs = offset / 1000 / 60 / 60;
	//			int offsetMins = offset / 1000 / 60 % 60;
	//			//log.debug("TimeZone Offset Hours: " + offsetHrs);
	//			//log.debug("TimeZone Offset Mins: " + offsetMins);
	//
	//			timeZoneGMTOffset = offsetHrs + offsetMins / 100.0f;
	//			//log.debug("TimeZone Offset Float: " + offsetFloat);
	//
	//			//add daylight savings offset
	//			int dstOffset = 0;
	//			if (timezone->inDaylightTime(Date()))
	//			{
	//				dstOffset = timezone->getDSTSavings();
	//			}
	//			int dstOffsetHrs = dstOffset / 1000 / 60 / 60;
	//			int dstOffsetMins = dstOffset / 1000 / 60 % 60;
	//			//log.debug("DST Offset Hours: " + dstOffsetHrs);
	//			//log.debug("DST Offset Mins: " + dstOffsetMins);
	//			DSTOffset = dstOffsetHrs + dstOffsetMins / 100.0f;
	//
	//			//combined offset timezone + dst
	//			int combinedOffset = offset + dstOffset;
	//			int combinedOffsetHrs = combinedOffset / 1000 / 60 / 60;
	//			int combinedOffsetMins = combinedOffset / 1000 / 60 % 60;
	//			//log.debug("Total Offset Hours: " + combinedOffsetHrs);
	//			//log.debug("Total Offset Mins: " + combinedOffsetMins);
	//
	//
	//			//make an adjusted calendar to getTime from
	//			Calendar *adjustedCalendar = Calendar::getInstance();
	//			adjustedCalendar->add(Calendar::HOUR_OF_DAY, (-combinedOffsetHrs));
	//			adjustedCalendar->add(Calendar::MINUTE, (-combinedOffsetMins));
	//			//log.debug("GMT Time: " + new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(adjustedCalendar.getTime()) + " + " + combinedOffsetHrs + ":" + combinedOffsetMins);
	//
	//
	//
	//
	//
	//			new Thread([&] ()
	//			{
	//
	//					try
	//					{
	//						Thread::currentThread().setName("ClientMain_initTime");
	//					}
	//					catch (SecurityException e)
	//					{
	//						e->printStackTrace();
	//					}
	//
	//
	//					string NTPhost = "time.nist.gov"; //this goes through lots of servers in round-robin, so keep trying.
	//
	//					NTPUDPClient *ntpUDPClient = new NTPUDPClient();
	//					ntpUDPClient->setDefaultTimeout(5000);
	//
	//					int timeTryCount = 0;
	//					bool haveTime = false;
	//					while (haveTime == false && timeTryCount < 5)
	//					{
	//
	//
	//						if (timeTryCount == 0)
	//						{
	//							NTPhost = "time.nist.gov";
	//						}
	//						if (timeTryCount == 1)
	//						{
	//							NTPhost = "nist1-sj.ustiming.org";
	//						}
	//						if (timeTryCount == 2)
	//						{
	//							NTPhost = "nisttime.carsoncity.k12.mi.us";
	//						}
	//						if (timeTryCount == 3)
	//						{
	//							NTPhost = "wwv.nist.gov";
	//						}
	//						if (timeTryCount == 4)
	//						{
	//							NTPhost = "nist1.symmetricom.com";
	//						}
	//
	//
	//						timeTryCount++;
	//
	//						if (ntpUDPClient->isOpen() == true)
	//						{
	//							ntpUDPClient->close();
	//						}
	//
	//						try
	//						{
	//							ntpUDPClient->open();
	//						}
	//						catch (SocketException e)
	//						{
	//							log.debug("Could not open NTP UDP Client: " + e->getMessage());
	//							continue;
	//						}
	//
	//						InetAddress *hostAddr = nullptr;
	//						try
	//						{
	//							hostAddr = InetAddress::getByName(NTPhost);
	//						}
	//						catch (UnknownHostException e)
	//						{
	//							log.debug("Could not resolve NTP host: " + NTPhost + " | " + e->getMessage());
	//							continue;
	//						}
	//
	//						//log.debug("> " + hostAddr.getHostName() + "/" + hostAddr.getHostAddress());
	//
	//						TimeInfo *timeInfo = nullptr;
	//
	//						try
	//						{
	//							timeInfo = ntpUDPClient->getTime(hostAddr);
	//						}
	//						catch (IOException e)
	//						{
	//							log.debug("Could not get time from NTP host: " + hostAddr->getHostAddress() + " | " + e->getMessage());
	//							continue;
	//						}
	//
	//
	//						NtpV3Packet *message = timeInfo->getMessage();
	//
	//
	//						// Transmit time is time reply sent by server (t3)
	//						TimeStamp *xmitNtpTime = message->getTransmitTimeStamp();
	//						//log.debug(" Transmit Timestamp:\t" + xmitNtpTime + "  "+ xmitNtpTime.toDateString());
	//
	//
	//						Date serverDate = xmitNtpTime->getDate();
	//						log.info("Server Time (Adjusted by local TimeZone + DST): " + serverDate);
	//
	//						// init game clock
	//
	//
	//						Calendar *serverCalendar = Calendar::getInstance();
	//						serverCalendar->setTime(serverDate);
	//
	//
	//						int hour = serverCalendar->get(Calendar::HOUR_OF_DAY);
	//						int minute = serverCalendar->get(Calendar::MINUTE);
	//						int second = serverCalendar->get(Calendar::SECOND);
	//						int day = serverCalendar->get(Calendar::DAY_OF_WEEK) - 1;
	//
	//						gameEngine->clock->setTime(day, hour, minute, second);
	//
	//
	//
	//						ntpUDPClient->close();
	//						haveTime = true;
	//
	//					}
	//
	//					if (haveTime == false)
	//					{
	//						log.error("Could not get time from NTP server!");
	//
	//						//TODO: just set to local clock time.
	//					}
	//
	//			}
	//
	//		   ).start();


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



string System::split(const string& in)
{ //=========================================================================================================================

	//		int l = 300;
	//
	//		String s = "";
	//		for(int i=0; i < Math.floor(in.length()/l); i++)
	//		{
	//			s = s + in.substring(i*l,i*l+l) + " \n ";
	//		}
	//		s = s + in.substring((int)Math.floor(in.length()/l)*l);
	//		return s;
	if (in == "")
	{
		return "null";
	}

	if (in.length() > 100)
	{
		return in.substr(0, 100) + "...";
	}

	return in;
}


string System::printString()
{ //=========================================================================================================================
	
	string s = "";// +"browserUserAgentString: " + split(browserUserAgentString) + "\n" + "browserAppNameVersionString: " + split(browserAppNameVersionString) + "\n" + "browserReferrerString: " + split(browserReferrerString) + "\n" + "getEnvProcessorIdentifier: " + split(getEnvProcessorIdentifier) + "\n" + "getEnvProcessorArchitecture: " + split(getEnvProcessorArchitecture) + "\n" + "getEnvNumberOfProcessors: " + split(getEnvNumberOfProcessors) + "\n" + "internetProviderString: " + split(internetProviderString) + "\n" + "timeZoneGMTOffset: " + timeZoneGMTOffset + "\n" + "jreVersion: " + split(jreVersion) + "\n" + "jreVendor: " + split(jreVendor) + "\n" + "jreHomeDir: " + split(jreHomeDir) + "\n" + "jvmVersion: " + split(jvmVersion) + "\n" + "jvmName: " + split(jvmName) + "\n" + "javaClassVersion: " + split(javaClassVersion) + "\n" + "javaClassPath: " + split(javaClassPath) + "\n" + "javaLibraryPath: " + split(javaLibraryPath) + "\n" + "javaTempDir: " + split(javaTempDir) + "\n" + "osName: " + split(osName) + "\n" + "osArch: " + split(osArch) + "\n" + "osVersion: " + split(osVersion) + "\n" + "osUserAccountName: " + split(osUserAccountName) + "\n" + "osHomeDir: " + split(osHomeDir) + "\n" + "workingDir: " + split(workingDir) + "\n" + "displayWidth: " + displayWidth + "\n" + "displayHeight: " + displayHeight + "\n" + "displayBPP: " + displayBPP + "\n" + "displayFreq: " + displayFreq + "\n" + "shaderCompiled: " + (StringConverterHelper::toString(shaderCompiled) + "\n" + "canUseFBO: " + (StringConverterHelper::toString(canUseFBO) + "\n" + "usingVSync: " + (StringConverterHelper::toString(usingVSync) + "\n" + "displayAdapter: " + split(displayAdapter) + "\n" + "displayDriver: " + split(displayDriver) + "\n" + "lwjglVersion: " + split(lwjglVersion) + "\n" + "lwjglIs64Bit: " + (StringConverterHelper::toString(lwjglIs64Bit) + "\n" + "lwjglPlatformName: " + split(lwjglPlatformName) + "\n" + "numCPUs: " + numCPUs + "\n" + "totalMemory: " + totalMemory + "\n" + "maxMemory: " + maxMemory + "\n" + "numControllersFound: " + numControllersFound + "\n" + "controllersNames: " + split(controllersNames) + "\n" + "glVendor: " + split(glVendor) + "\n" + "glVersion: " + split(glVersion) + "\n" + "glRenderer: " + split(glRenderer) + "\n" + "shaderVersion: " + split(shaderVersion) + "\n" + "glExtensions: " + split(glExtensions))->toString())->toString())->toString())->toString();


	//"jreVendorURL: "+split(jreVendorURL)+"\n"+
	//"jvmSpecVersion: "+split(jvmSpecVersion)+"\n"+
	//"jvmSpecVendor: "+split(jvmSpecVendor	)+"\n"+
	//"jvmSpecName: "+split(jvmSpecName)+"\n"+
	//"jvmVendor: "+split(jvmVendor	)+"\n"+
	//"jreSpecVersion: "+split(jreSpecVersion)+"\n"+
	//"jreSpecVendor: "+split(jreSpecVendor	)+"\n"+
	//"jreSpecName: "+split(jreSpecName)+"\n"+
	//"javaJITCompiler: "+split(javaJITCompiler)+"\n"+
	//"javaExtensionPath: "+split(javaExtensionPath)+"\n"+


	return s;
}


string System::encode()
{ //=========================================================================================================================

	
	string s = "";
	// +"`" + timeZoneGMTOffset + "`" + "," + "`" + browserUserAgentString + "`" + "," + "`" + browserAppNameVersionString + "`" + "," + "`" + browserReferrerString + "`" + "," + "`" + getEnvProcessorIdentifier + "`" + "," + "`" + getEnvProcessorArchitecture + "`" + "," + "`" + getEnvNumberOfProcessors + "`" + "," + "`" + internetProviderString + "`" + "," + "`" + jreVersion + "`" + "," + "`" + jreVendor + "`" + "," + "`" + jreHomeDir + "`" + "," + "`" + jvmVersion + "`" + "," + "`" + jvmName + "`" + "," + "`" + javaClassVersion + "`" + "," + "`" + javaClassPath + "`" + "," + "`" + javaLibraryPath + "`" + "," + "`" + javaTempDir + "`" + "," + "`" + osName + "`" + "," + "`" + osArch + "`" + "," + "`" + osVersion + "`" + "," + "`" + osUserAccountName + "`" + "," + "`" + osHomeDir + "`" + "," + "`" + workingDir + "`" + "," + "`" + displayWidth + "`" + "," + "`" + displayHeight + "`" + "," + "`" + displayBPP + "`" + "," + "`" + displayFreq + "`" + "," + "`" + (StringConverterHelper::toString(shaderCompiled) + "`" + "," + "`" + (StringConverterHelper::toString(canUseFBO) + "`" + "," + "`" + (StringConverterHelper::toString(usingVSync) + "`" + "," + "`" + displayAdapter + "`" + "," + "`" + displayDriver + "`" + "," + "`" + lwjglVersion + "`" + "," + "`" + (StringConverterHelper::toString(lwjglIs64Bit) + "`" + "," + "`" + lwjglPlatformName + "`" + "," + "`" + numCPUs + "`" + "," + "`" + totalMemory + "`" + "," + "`" + maxMemory + "`" + "," + "`" + numControllersFound + "`" + "," + "`" + controllersNames + "`" + "," + "`" + glVendor + "`" + "," + "`" + glVersion + "`" + "," + "`" + glRenderer + "`" + "," + "`" + shaderVersion + "`" + "," + "`" + glExtensions + "`")->toString())->toString())->toString())->toString();


	//"`"+jreVendorURL+"`"+","+
	//"`"+jvmSpecVersion+"`"+","+
	//"`"+jvmSpecVendor	+"`"+","+
	//"`"+jvmSpecName+"`"+","+
	//"`"+jvmVendor	+"`"+","+
	//"`"+jreSpecVersion+"`"+","+
	//"`"+jreSpecVendor	+"`"+","+
	//"`"+jreSpecName+"`"+","+
	//"`"+javaJITCompiler+"`"+","+
	//"`"+javaExtensionPath+"`"+","+

	return s;
}

void System::decode(string& s)
{ //=========================================================================================================================

	{
		//		"`"+timeZoneGMTOffset+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				timeZoneGMTOffset = stof(t);
			}
			catch (exception)
			{
				log.error("Could not parse timeZoneGMTOffset");
			}
		}

		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+browserUserAgentString+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			browserUserAgentString = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+browserAppNameVersionString+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			browserAppNameVersionString = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+browserReferrerString+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			browserReferrerString = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+getEnvProcessorIdentifier+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			getEnvProcessorIdentifier = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+getEnvProcessorArchitecture+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			getEnvProcessorArchitecture = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+getEnvNumberOfProcessors+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			getEnvNumberOfProcessors = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+internetProviderString+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			internetProviderString = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	//string----------------------

	{
		//		"`"+jreVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			jreVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+jreVendor+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			jreVendor = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+jreHomeDir+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			jreHomeDir = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+jvmVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			jvmVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+jvmName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			jvmName = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+javaClassVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			javaClassVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+javaClassPath+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			javaClassPath = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+javaLibraryPath+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			javaLibraryPath = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+javaTempDir+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			javaTempDir = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+osName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			osName = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+osArch+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			osArch = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+osVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			osVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+osUserAccountName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			osUserAccountName = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+osHomeDir+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			osHomeDir = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+workingDir+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			workingDir = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	//int----------------------

	{
		//		"`"+displayWidth+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			
			try
			{
				displayWidth = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse displayWidth");
			}
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+displayHeight+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			
			try
			{
				displayHeight = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse displayHeight");
			}
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+displayBPP+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			
			try
			{
				displayBPP = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse displayBPP");
			}
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+displayFreq+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			
			try
			{
				displayFreq = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse displayFreq");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	//boolean----------------------

	{
		//		"`"+shaderCompiled+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			shaderCompiled = StringConverterHelper::fromString<bool>(t);
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+canUseFBO+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			canUseFBO = StringConverterHelper::fromString<bool>(t);
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+usingVSync+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			usingVSync = StringConverterHelper::fromString<bool>(t);
		}
		s = s.substr(s.find('`') + 1);
	}


	//string----------------------

	{
		//		"`"+displayAdapter+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			displayAdapter = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+displayDriver+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			displayDriver = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+lwjglVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			lwjglVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	//boolean ----------------------

	{
		//		"`"+lwjglIs64Bit+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			lwjglIs64Bit = StringConverterHelper::fromString<bool>(t);
		}
		s = s.substr(s.find('`') + 1);
	}

	//string----------------------

	{
		//		"`"+lwjglPlatformName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			lwjglPlatformName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	//int----------------------

	{
		//		"`"+numCPUs+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			
			try
			{
				numCPUs = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse numCPUs");
			}
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+totalMemory+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{

			try
			{
				totalMemory = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse totalMemory");
			}
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//		"`"+maxMemory+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				maxMemory = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse maxMemory");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+numControllersFound+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				numControllersFound = stoi(t);
			}
			catch (exception)
			{
				log.error("Could not parse numControllersFound");
			}
		}
		s = s.substr(s.find('`') + 1);
	}


	//string----------------------

	{
		//		"`"+controllersNames+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			controllersNames = t;
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//		"`"+glVendor+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			glVendor = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+glVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			glVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+glRenderer+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			glRenderer = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+shaderVersion+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			shaderVersion = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//		"`"+glExtensions+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			glExtensions = t;
		}
		s = s.substr(s.find('`') + 1);
	}
}

//
//			PreparedStatement *System::getInsertStatement(Connection *databaseConnection, const string &emailAddress, Client *cc, const string &ipAddress)
//			{ //=========================================================================================================================
//
//
//				//keep the boolean strings blank if no information is provided
//				string shaderCompiledString = "";
//				string canUseFBOString = "";
//				string usingVSyncString = "";
//				string lwjglIs64BitString = "";
//
//
//
//
//						//
//						//		InetAddress addr = null;
//						//		try
//						//		{
//						//			addr = InetAddress.getByName(cc.channel.getRemoteAddress().toString());
//						//		}
//						//		catch(UnknownHostException e)
//						//		{
//						//			e.printStackTrace();
//						//		}
//						//
//						//		if(addr!=null)
//						//		internetProviderString = addr.getHostName();
//
//
//
//
//
//				if (jreVersion.length() > 0)
//				{
//					shaderCompiledString = "" + StringConverterHelper::toString(shaderCompiled);
//					canUseFBOString = "" + StringConverterHelper::toString(canUseFBO);
//					usingVSyncString = "" + StringConverterHelper::toString(usingVSync);
//					lwjglIs64BitString = "" + StringConverterHelper::toString(lwjglIs64Bit);
//				}
//
//
//				PreparedStatement *ps = nullptr;
//
//				try
//				{
//					ps = databaseConnection->prepareStatement("INSERT INTO connections ( " + "browserUserAgentString , " + "browserAppNameVersionString , " + "browserReferrerString , " + "getEnvProcessorIdentifier , " + "getEnvProcessorArchitecture , " + "getEnvNumberOfProcessors , " + "internetProviderString , " + "emailAddress , " + "userID , " + "sessionToken , " + "encryptionKey , " + "startTime , " + "ipAddress , " + "jreVersion , " + "jreVendor , " + "jreHomeDir , " + "jvmVersion , " + "jvmName , " + "javaClassVersion , " + "javaClassPath , " + "javaLibraryPath , " + "javaTempDir , " + "osName , " + "osArch , " + "osVersion , " + "osUserAccountName , " + "osHomeDir , " + "workingDir , " + "displayWidth , " + "displayHeight , " + "displayBPP , " + "displayFreq , " + "shaderCompiled , " + "canUseFBO , " + "usingVSync , " + "displayAdapter , " + "displayDriver , " + "lwjglVersion , " + "lwjglIs64Bit , " + "lwjglPlatformName , " + "numCPUs , " + "totalMemory , " + "maxMemory , " + "numControllersFound , " + "controllersNames , " + "timeZoneGMTOffset , " + "glVendor , " + "glVersion , " + "glRenderer , " + "shaderVersion , " + "glExtensions" + " ) VALUES ( " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?, ?, ?, ?, ?, " + "?" + ")");
//
//				int c = 1;
//
//				ps->setString(c++, browserUserAgentString);
//				ps->setString(c++, browserAppNameVersionString);
//				ps->setString(c++, browserReferrerString);
//
//				ps->setString(c++, getEnvProcessorIdentifier);
//				ps->setString(c++, getEnvProcessorArchitecture);
//				ps->setString(c++, getEnvNumberOfProcessors);
//
//				ps->setString(c++, internetProviderString);
//				ps->setString(c++, emailAddress);
//				ps->setInt(c++, cc->userID);
//				ps->setString(c++, sessionToken);
//				ps->setString(c++, cc->encryptionKey);
//				ps->setLong(c++, cc->startTime);
//				ps->setString(c++, ipAddress);
//
//				ps->setString(c++, jreVersion);
//				ps->setString(c++, jreVendor);
//				ps->setString(c++, jreHomeDir);
//				ps->setString(c++, jvmVersion);
//				ps->setString(c++, jvmName);
//				ps->setString(c++, javaClassVersion);
//				ps->setString(c++, javaClassPath);
//				ps->setString(c++, javaLibraryPath);
//				ps->setString(c++, javaTempDir);
//
//				ps->setString(c++, osName);
//				ps->setString(c++, osArch);
//				ps->setString(c++, osVersion);
//				ps->setString(c++, osUserAccountName);
//				ps->setString(c++, osHomeDir);
//				ps->setString(c++, workingDir);
//
//				ps->setInt(c++, displayWidth);
//				ps->setInt(c++, displayHeight);
//				ps->setInt(c++, displayBPP);
//				ps->setInt(c++, displayFreq);
//
//				ps->setString(c++, shaderCompiledString);
//				ps->setString(c++, canUseFBOString);
//				ps->setString(c++, usingVSyncString);
//				ps->setString(c++, displayAdapter);
//				ps->setString(c++, displayDriver);
//
//				ps->setString(c++, lwjglVersion);
//				ps->setString(c++, lwjglIs64BitString);
//				ps->setString(c++, lwjglPlatformName);
//				ps->setInt(c++, numCPUs);
//				ps->setLong(c++, totalMemory);
//				ps->setLong(c++, maxMemory);
//
//				ps->setInt(c++, numControllersFound);
//				ps->setString(c++, controllersNames);
//				ps->setFloat(c++, timeZoneGMTOffset);
//
//				ps->setString(c++, glVendor);
//				ps->setString(c++, glVersion);
//				ps->setString(c++, glRenderer);
//				ps->setString(c++, shaderVersion);
//				ps->setString(c++, glExtensions);
//
//				}
//				catch (exception &ex)
//				{
//					System::err::println("DB ERROR: " + ex.what());
//				}
//
//				//statement = statement.replace("\\", "\\\\");
//				//Using PreparedStatement makes this unnecessary, dont need to escape strings
//				//NEVERMIND  clean this better, clean all user input on both client and server side
//
//				//System.out.println(statement);
//
//				return ps;
//			}

void System::logSystemInfo()
{
//	log.log("browserUserAgentString: " + (browserUserAgentString));
//	log.log("browserAppNameVersionString: " + (browserAppNameVersionString));
//	log.log("browserReferrerString: " + (browserReferrerString));
//
//	log.log("getEnvProcessorIdentifier: " + (getEnvProcessorIdentifier));
//	log.log("getEnvProcessorArchitecture: " + (getEnvProcessorArchitecture));
//	log.log("getEnvNumberOfProcessors: " + (getEnvNumberOfProcessors));
//
//	log.log("internetProviderString: " + (internetProviderString));
//
//	log.log("timeZoneGMTOffset: " + to_string(timeZoneGMTOffset));
//
//	log.log("jreVersion: " + (jreVersion));
//	log.log("jreVendor: " + (jreVendor));
//	//"jreVendorURL: "+split(jreVendorURL));
//
//	log.log("jreHomeDir: " + (jreHomeDir));
//	//"jvmSpecVersion: "+split(jvmSpecVersion));
//	//"jvmSpecVendor: "+split(jvmSpecVendor	));
//	//"jvmSpecName: "+split(jvmSpecName));
//	log.log("jvmVersion: " + (jvmVersion));
//
//	//"jvmVendor: "+split(jvmVendor	));
//	log.log("jvmName: " + (jvmName));
//	//"jreSpecVersion: "+split(jreSpecVersion));
//	//"jreSpecVendor: "+split(jreSpecVendor	));
//	//"jreSpecName: "+split(jreSpecName));
//
//	log.log("javaClassVersion: " + (javaClassVersion));
//	log.log("javaClassPath: " + (javaClassPath));
//	log.log("javaLibraryPath: " + (javaLibraryPath));
//	log.log("javaTempDir: " + (javaTempDir));
//	//"javaJITCompiler: "+split(javaJITCompiler));
//
//	//"javaExtensionPath: "+split(javaExtensionPath));
//	log.log("osName: " + (osName));
//	log.log("osArch: " + (osArch));
//	log.log("osVersion: " + (osVersion));
//	log.log("osUserAccountName: " + (osUserAccountName));
//
//	log.log("osHomeDir: " + (osHomeDir));
//	log.log("workingDir: " + (workingDir));
//
//	log.log("displayWidth: " + to_string(displayWidth));
//	log.log("displayHeight: " + to_string(displayHeight));
//	log.log("displayBPP: " + to_string(displayBPP));
//	log.log("displayFreq: " + to_string(displayFreq));
//	log.log("shaderCompiled: " + StringConverterHelper::toString(shaderCompiled));
//	log.log("canUseFBO: " + StringConverterHelper::toString(canUseFBO));
//	log.log("usingVSync: " + StringConverterHelper::toString(usingVSync));
//	log.log("displayAdapter: " + (displayAdapter));
//	log.log("displayDriver: " + (displayDriver));
//	log.log("lwjglVersion: " + (lwjglVersion));
//	log.log("lwjglIs64Bit: " + StringConverterHelper::toString(lwjglIs64Bit));
//	log.log("lwjglPlatformName: " + (lwjglPlatformName));
//	log.log("numCPUs: " + to_string(numCPUs));
//	log.log("totalMemory: " + to_string(totalMemory));
//	log.log("maxMemory: " + to_string(maxMemory));
//	log.log("numControllersFound: " + to_string(numControllersFound));
//	log.log("controllersNames: " + (controllersNames));

	//log.log("glVendor: " + (glVendor));
	//log.log("glVersion: " + (glVersion));
	//log.log("glRenderer: " + (glRenderer));
	//log.log("shaderVersion: " + (shaderVersion));
	//log.log("glExtensions: " + (glExtensions));
}


void System::initThreadStats()
{ //=========================================================================================================================


	//mxThreadCountText = Console::debug("mxThreadCountText");
}

void System::updateThreadStats()
{ //=========================================================================================================================


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

int System::mb = 1024 * 1024;
long long System::usedMemory = 0;
long long System::maxUsedMemory = 0;
long long System::totalMemory = 0;
long long System::freeMemory = 0;
long long System::maxMemory = 0;

void System::initMemoryStats()
{ //=========================================================================================================================

	//memoryText = Console::debug("memoryText");
	texturesLoadedText = Console::debug(" ");
	textureBytesLoadedText = Console::debug(" ");

	//vramText = DebugConsole.add("vramText");

	totalMemory = 0;
	freeMemory = 0;
	maxMemory = 0;
}

void System::updateMemoryStats()
{ //=========================================================================================================================

	
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



	//vramText.getText = "Available VRAM: "+gd.getAvailableAcceleratedMemory()/1024 +" KB";
	//last100Ticks+=100;

	texturesLoadedText->text = "Textures Loaded: " + to_string(GLUtils::texturesLoaded);
	textureBytesLoadedText->text = "Texture MBs Loaded: " + to_string(GLUtils::textureBytesLoaded / 1024 / 1024);
	
}

void System::initDebugInfo()
{ //=========================================================================================================================


	//------------------------------
	// debug console
	//------------------------------

	if (GLUtils::usingVSync)
	{
		Console::debug("Vsync: on");
	}
	else
	{
		Console::debug("Vsync: off");
	}

	//		Console.debug("Display Adapter: " + Display.getAdapter());
	//		Console.debug("Display Driver Version: " + Display.getVersion());
	//Console::debug("LWJGL Version: ");// +System::getVersion() + " | 64 Bit: " + Sys::is64Bit());
	//		Console.debug("LWJGL Platform: " + LWJGLUtil.getPlatformName());
	//		Console.debug("Num CPUs: " +rt.availableProcessors());


	//TODO: mxbeans get arch, cores, more OS information
	//TODO: lwjgl can get graphics driver information, need to get more of that.
	//TODO: slick-network-game example gets sound card info, joystick info, part of slick. need to use this.

	initFrameStats();
	initMemoryStats();
	initThreadStats();
}


//=========================================================================================================================
void System::updateDebugInfo()
{ //=========================================================================================================================

	updateFrameStats();
	updateMemoryStats();
	updateThreadStats();
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
  //-----------------------------
  //old timer setup
  //-----------------------------
	

//	framesrendered=0;
//	secondspassed=0;
//	lastsecondspassed=0;
//	fps=0;

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
	averageFPSTestTotalRenders++;


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


long long System::lastRenderTime = 0;
long long System::lastUpdateTime = 0;

int System::ticksTextCount = 0;

long long System::averageTicksPerRenderLastSecond = 0;
long long System::averageTicksPerUpdateLastSecond = 0;

void System::initFrameStats()
{ //=========================================================================================================================

	upTimeText = Console::debug(" ");

	totalRendersText = Console::debug(" ");
	totalUpdatesText = Console::debug(" ");

	rendersPerSecondText = Console::add(" ");
	updatesPerSecondText = Console::debug(" ");
	averageRendersPerSecondText = Console::add(" ");

	rendersSkippedText = Console::debug(" ");
	updatesSkippedText = Console::debug(" ");

	averageTicksPerFrameText = Console::debug(" ");
	averageTicksPerUpdateText = Console::debug(" ");



#ifdef _DEBUG
	for(int i=0;i<amtTicksTexts;i++)
		ticksText[i] = Console::debug(" ");
#endif

}

void System::updateFrameStats()
{ //=========================================================================================================================

	upTimeText->text = "Uptime: " + to_string(totalUpdateTicks / 1000) + "s (" + to_string(totalUpdateTicks) + "ms)";


	totalRendersText->text = "Total Renders: " + to_string(totalRenders);
	totalUpdatesText->text = "Total Updates: " + to_string(totalUpdates);

	rendersSkippedText->text = "Renders Skipped: " + to_string(rendersSkipped);
	updatesSkippedText->text = "Updates Skipped: " + to_string(updatesSkipped);



	//if a second has passed
	int ticksPassed = (int)(System::getTicksBetweenTimes(lastSecondTime, currentHighResTime));
	if (ticksPassed >=  1000)
	{
		
		

		averageTicksPerRenderLastSecond = (long long)((double)(ticksPassed) / rendersThisSecond);
		averageTicksPerUpdateLastSecond = (long long)((double)(ticksPassed) / updatesThisSecond);

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
		averageRendersPerSecondText->text = "Average FPS: " + to_string(averageRendersPerSecond);

		averageTicksPerFrameText->text = "Average Ticks Per Frame (Last Second): " + to_string(averageTicksPerRenderLastSecond);
		averageTicksPerUpdateText->text = "Average Ticks Per Update (Last Second): " + to_string(averageTicksPerUpdateLastSecond);

		lastSecondTime += (long long)(1000 * cpuFreq);
		rendersThisSecond = 0;
		updatesThisSecond = 0;


		totalSecondsPassed++;
		averageFPSTestSecondsPassed++;

		averageRendersPerSecond = totalRenders/totalSecondsPassed;
		int averageFPSTestRendersPerSecond = averageFPSTestTotalRenders/ averageFPSTestSecondsPassed;
		

		if (averageFPSTestSecondsPassed>15&&averageFPSTestRendersPerSecond<50)
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


#ifdef _DEBUG
	long long thisRenderTime = currentHighResTime;
	int debugTicksPassed = (int)(System::getTicksBetweenTimes(lastRenderTime, thisRenderTime));
	lastRenderTime = thisRenderTime;

	for (int i = 0; i < amtTicksTexts; i++)
	{
		if (ticksTextCount == i)
		{
			ticksText[i]->text = string("Ticks Passed "+to_string(i)+": ") + to_string(debugTicksPassed);
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
