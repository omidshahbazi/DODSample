// DOD Sample
//#define NO_RENDER

#include <Common\Renderer.h>
#include <SDL.h>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void Renderer::Initialize(const char *Title, int Width, int Height)
{
	if (window != nullptr)
		return;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	m_IsWindowOpen = true;
}

void Renderer::Shutdown(void)
{
	if (window == nullptr)
		return;

	SDL_Quit();

	m_IsWindowOpen = false;
}

void Renderer::Clear(void)
{
#ifndef NO_RENDER
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
#endif
}

void Renderer::Present(void)
{
	if (window == nullptr)
		return;

	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_IsWindowOpen = false;
			break;
		}
	}

	SDL_RenderPresent(renderer);
}

void Renderer::SetPixel(int X, int Y)
{
#ifndef NO_RENDER
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, X, Y);
#endif
}
