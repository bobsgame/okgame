#include "DearImGuiSDL.h"

/* SDL Includes */
#include <SDL_clipboard.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_video.h>
#include <SDL_timer.h>

#include "imgui_software/imgui_sw.hpp"

#include <stdlib.h>

uint64_t TIME_NOW = 60;
uint64_t TIME_LAST = 0;

const char* dearimguisdl_error_codes[_DEARIMGUISDL_ERROR_COUNT]
{
	"SUCCESS",
	"ERROR_INCOMPATIBLE_FORMAT",
	"ERROR_OUT_OF_MEMORY",
	"ERROR_UNREGISTERED",
	"ERROR_UNKNOWN"
};

static SDL_Cursor* _mouseCursors[ImGuiMouseCursor_COUNT];

/*Clipboard*/
void _imguiSetClipboard(void* userData, const char* text)
{
	SDL_SetClipboardText(text);
}

char* _clipboardContent = NULL;
const char* _imguiGetClipboard(void* userData)
{
	if (_clipboardContent)
		SDL_free(_clipboardContent);
	_clipboardContent = SDL_GetClipboardText();
	return _clipboardContent;
}

ImGuiIO* pImGuiIo;

const char* DearImguiSDL_GetResultString(DearImguiSDL_Result result)
{
	if (result >= _DEARIMGUISDL_ERROR_COUNT || result < 0) { result = DEARIMGUISDL_ERROR_UNKNOWN; }
	return dearimguisdl_error_codes[result];
}

DearImguiSDL_Result DearImguiSDL_Initialize(const char* appName)
{
	/*Context*/
	ImGui::CreateContext();
	pImGuiIo = &ImGui::GetIO();

	/*Input Mapping*/
	{
		pImGuiIo->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		pImGuiIo->BackendPlatformName = appName;

		pImGuiIo->KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
		pImGuiIo->KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		pImGuiIo->KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		pImGuiIo->KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		pImGuiIo->KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		pImGuiIo->KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		pImGuiIo->KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		pImGuiIo->KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		pImGuiIo->KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		pImGuiIo->KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
		pImGuiIo->KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
		pImGuiIo->KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
		pImGuiIo->KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
		pImGuiIo->KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
		pImGuiIo->KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
		pImGuiIo->KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
		pImGuiIo->KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
		pImGuiIo->KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
		pImGuiIo->KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
		pImGuiIo->KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
		pImGuiIo->KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
		pImGuiIo->KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

		pImGuiIo->ClipboardUserData = NULL;
		pImGuiIo->SetClipboardTextFn = _imguiSetClipboard;
		pImGuiIo->GetClipboardTextFn = _imguiGetClipboard;

		_mouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		_mouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
		_mouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		_mouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
		_mouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
		_mouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
		_mouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
		_mouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		_mouseCursors[ImGuiMouseCursor_NotAllowed] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);

		//pImGuiIo->IniFilename = NULL;
		//pImGuiIo->LogFilename = NULL;
	}
	/* Optimize Style */
	{
		imgui_sw::make_style_fast();
		/*for (int i = 0; i < ImGuiCol_COUNT; i++) {
			ImGui::GetStyle().Colors[i].w = 1.0f;
		}*/
	}

	/* Software Rasterizer */
	imgui_sw::bind_imgui_painting();

	/* Imnodes */
	imnodes::Initialize();

	return DEARIMGUISDL_SUCCESS;
}

DearImguiSDL_Result DearImguiSDL_Shutdown()
{
	imnodes::Shutdown();
	imgui_sw::unbind_imgui_painting();
	ImGui::DestroyContext();
	return DEARIMGUISDL_SUCCESS;
}

bool DearImguiSDL_IsFocused()
{
	return ImGui::IsAnyItemActive() |
		ImGui::IsAnyItemHovered() |
		ImGui::IsAnyItemFocused() |
		ImGui::IsWindowFocused(ImGuiHoveredFlags_AnyWindow) |
		ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
}

DearImguiSDL_Result DearImguiSDL_NewFrame(SDL_Window* pActiveWindow, SDL_Surface* pSurface, float deltaTime)
{
	if (!pSurface || !pActiveWindow) { return DEARIMGUISDL_ERROR_UNKNOWN; }
	/*Mouse Cursor*/
	if (!(pImGuiIo->ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange))
	{
		ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
		if (pImGuiIo->MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
		{
			SDL_ShowCursor(SDL_FALSE);
		}
		else
		{
			SDL_SetCursor(_mouseCursors[imgui_cursor] ? _mouseCursors[imgui_cursor] : _mouseCursors[ImGuiMouseCursor_Arrow]);
			SDL_ShowCursor(SDL_TRUE);
		}
	}
	/*Mouse Input (from https://github.com/ocornut/imgui/blob/master/examples/imgui_impl_sdl.cpp )*/
	{
		if (pImGuiIo->WantSetMousePos && pActiveWindow)
			SDL_WarpMouseInWindow(pActiveWindow, (int)pImGuiIo->MousePos.x, (int)pImGuiIo->MousePos.y);
		else
			pImGuiIo->MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

		int mx = 0, my = 0;
		Uint32 mouse_buttons = SDL_GetMouseState(&mx, &my);

		/*The original has handling for global mouse states here... this targets desktop only*/
		if (pActiveWindow) {
			if (SDL_GetWindowFlags(pActiveWindow)) {
				pImGuiIo->MousePos.x = (float)mx;
				pImGuiIo->MousePos.y = (float)my;
			}
		}

	}
	/* Resolution */
	pImGuiIo->DisplaySize.x = (float)pSurface->w;
	pImGuiIo->DisplaySize.y = (float)pSurface->h;

	pImGuiIo->DeltaTime = deltaTime;
	ImGui::NewFrame();
	return DEARIMGUISDL_SUCCESS;
}

DearImguiSDL_Result DearImguiSDL_EndFrame()
{
	TIME_LAST = TIME_NOW;
	TIME_NOW = SDL_GetPerformanceCounter();
	ImGui::EndFrame();
	return DEARIMGUISDL_SUCCESS;
}

float DearImguiSDL_GetFrameTime()
{
	return (float)((TIME_NOW - TIME_LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001f;
}

struct surfaceRemap
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	uint32_t* pixelData;
};

surfaceRemap surfaceRemapList[256] = { 0 };

DearImguiSDL_Result DearImguiSDL_RegisterSurface(SDL_Surface* pSurface, SDL_Renderer* pRenderer)
{
	for (int i = 0; i < 256; i++)
	{
		if (surfaceRemapList[i].surface == NULL)
		{
			surfaceRemapList[i].texture = SDL_CreateTexture(pRenderer,
				SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, pSurface->w, pSurface->h);
			surfaceRemapList[i].surface = pSurface;
			surfaceRemapList[i].pixelData = (uint32_t*)calloc(pSurface->w * pSurface->h, sizeof(uint32_t));
			return surfaceRemapList[i].texture && surfaceRemapList[i].pixelData ?
				DEARIMGUISDL_SUCCESS :
				DEARIMGUISDL_ERROR_UNKNOWN;
		}
	}
	return DEARIMGUISDL_ERROR_OUT_OF_MEMORY;
}

DearImguiSDL_Result DearImguiSDL_UnregisterSurface(SDL_Surface* pSurface, SDL_Renderer* pRenderer)
{
	for (int i = 0; i < 256; i++)
	{
		if (surfaceRemapList[i].surface == pSurface)
		{
			surfaceRemapList[i].surface = NULL;
			free(surfaceRemapList[i].pixelData);
			SDL_DestroyTexture(surfaceRemapList[i].texture);
			return DEARIMGUISDL_SUCCESS;
		}
	}
	return DEARIMGUISDL_ERROR_OUT_OF_MEMORY;
}

DearImguiSDL_Result DearImguiSDL_RenderSurface(SDL_Surface* pSurface, SDL_Renderer* pRenderer)
{
	/* Find blit format */
	SDL_Texture* pTargetTexture = NULL;
	uint32_t* pPixelData = NULL;
	for (int i = 0; i < 256; i++)
	{
		if (surfaceRemapList[i].surface == pSurface)
		{
			pTargetTexture = surfaceRemapList[i].texture;
			pPixelData = surfaceRemapList[i].pixelData;
			break;
		}
	}
	if (!pTargetTexture || !pPixelData) { return DEARIMGUISDL_ERROR_UNREGISTERED; }

	/* Render */
	ImGui::Render();

	/* Draw */
	memset(pPixelData, 0, sizeof(uint32_t) * pSurface->w * pSurface->h);

	imgui_sw::SwOptions options = {};
	options.optimize_rectangles = true;
	options.optimize_text = true;

	imgui_sw::paint_imgui(
		pPixelData,
		pSurface->w,
		pSurface->h,
		options
	);

	SDL_SetTextureBlendMode(pTargetTexture, SDL_BLENDMODE_BLEND);
	SDL_UpdateTexture(pTargetTexture, nullptr, pPixelData, pSurface->w * sizeof(Uint32));
	SDL_RenderCopy(pRenderer, pTargetTexture, nullptr, nullptr);

	return DEARIMGUISDL_SUCCESS;
}

void DearImguiSDL_HandleEvent(SDL_Event* pEvent)
{
	/*DearImgui input handling
	https://github.com/ocornut/imgui/blob/58b3e02b95b4c7c5bb9128a28c6d55546501bf93/examples/imgui_impl_sdl.cpp */
	switch (pEvent->type)
	{
	case SDL_MOUSEWHEEL:
	{
		if (pEvent->wheel.x > 0) pImGuiIo->MouseWheelH += 1;
		if (pEvent->wheel.x < 0) pImGuiIo->MouseWheelH -= 1;
		if (pEvent->wheel.y > 0) pImGuiIo->MouseWheel += 1;
		if (pEvent->wheel.y < 0) pImGuiIo->MouseWheel -= 1;
		return;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (pEvent->button.button == SDL_BUTTON_LEFT) pImGuiIo->MouseDown[0] = true;
		if (pEvent->button.button == SDL_BUTTON_RIGHT) pImGuiIo->MouseDown[1] = true;
		if (pEvent->button.button == SDL_BUTTON_MIDDLE) pImGuiIo->MouseDown[2] = true;
		return;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (pEvent->button.button == SDL_BUTTON_LEFT) pImGuiIo->MouseDown[0] = false;
		if (pEvent->button.button == SDL_BUTTON_RIGHT) pImGuiIo->MouseDown[1] = false;
		if (pEvent->button.button == SDL_BUTTON_MIDDLE) pImGuiIo->MouseDown[2] = false;
		return;
	}
	case SDL_TEXTINPUT:
	{
		pImGuiIo->AddInputCharactersUTF8(pEvent->text.text);
		return;
	}
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	{
		int key = pEvent->key.keysym.scancode;
		if (key >= 0 && key < 512)
		{
			pImGuiIo->KeysDown[key] = (pEvent->type == SDL_KEYDOWN);
			pImGuiIo->KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
			pImGuiIo->KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
			pImGuiIo->KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
		}
#ifdef _WIN32
		pImGuiIo->KeySuper = false;
#else
		pImGuiIo->KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif
		return;
	}
	}
}

void DearImguiSDL_ShowSoftwareStats()
{
	imgui_sw::show_stats();
}

DearImguiSDL_Result DearImguiSDL_RegisterTexture(ImTextureID* pTexture, uint32_t* pixels, uint32_t width, uint32_t height)
{
	*pTexture = (ImTextureID)imgui_sw::create_texture(pixels, width, height);
	return DEARIMGUISDL_SUCCESS;
}

DearImguiSDL_Result DearImguiSDL_UnregisterTexture(ImTextureID* pTexture)
{
	imgui_sw::release_texture(*pTexture);
	return DEARIMGUISDL_SUCCESS;
}
