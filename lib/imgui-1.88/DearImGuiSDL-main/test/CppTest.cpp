#include <stdio.h>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_video.h>
#include <SDL_events.h>

#include "DearImGuiSDL.h"

#include "TestImage.h"
TEST_GRID_IMAGE()

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	/* Create a window */
	SDL_Window* pMainWindow = SDL_CreateWindow(
		"CPP Main Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1920,
		1080,
		0);
	if (!pMainWindow) { return -1; }

	/* Create a renderer */
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pMainWindow, -1, 0);
	if (!pRenderer) { return -2; }

	/* Create a surface */
	SDL_Surface* pMainSurface = SDL_GetWindowSurface(pMainWindow);
	if (!pMainSurface) { return -3; }
	DearImguiSDL_RegisterSurface(pMainSurface, pRenderer);

	/* Create Debug UI */
	DearImguiSDL_Initialize("CPP TEST");

	/* Upload test Image */
	ImTextureID texture;
	DearImguiSDL_RegisterTexture(
		&texture,
		(uint32_t*)test_grid_image.pixel_data,
		test_grid_image.width,
		test_grid_image.height);

	/* Main loop */
	bool running = true;
	while (running)
	{
		/* Poll events*/
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			DearImguiSDL_HandleEvent(&event);
		}
		DearImguiSDL_NewFrame(pMainWindow, pMainSurface, DearImguiSDL_GetFrameTime());

		/* Previous Drawing */
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(pRenderer);

		/* Demo Window */
		ImGui::ShowDemoWindow();

		/* Nodes Test */
		const int hardcoded_node_id = 1;
		const int output_attr_id = 2;
		ImGui::Begin("Node Editor");
		imnodes::BeginNodeEditor();
		imnodes::BeginNode(hardcoded_node_id);
		imnodes::BeginOutputAttribute(output_attr_id);
		ImGui::Text("DOOT");
		imnodes::EndAttribute();
		imnodes::EndNode();
		imnodes::EndNodeEditor();
		ImGui::End();

		/* Custom Image Test */
		ImGui::Begin("Test Image");
		ImGui::Image(texture, ImVec2(128, 128));
		ImGui::End();

		SDL_RenderClear(pRenderer);

		/* Update Debug UI */
		DearImguiSDL_EndFrame();
		DearImguiSDL_RenderSurface(pMainSurface, pRenderer);

		SDL_RenderPresent(pRenderer);
	}

	DearImguiSDL_UnregisterTexture(&texture);
	DearImguiSDL_UnregisterSurface(pMainSurface, pRenderer);
	DearImguiSDL_Shutdown();
	SDL_DestroyWindow(pMainWindow);
	return 0;
}