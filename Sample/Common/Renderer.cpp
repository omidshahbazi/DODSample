// DOD Sample
#include <Common\Renderer.h>
#include <SDL.h>

SDL_Window *window = nullptr;

void Renderer::Initialize(const char *Title, int Width, int Height)
{
	if (window != nullptr)
		return;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);

	m_IsWindowOpen = true;
}

void Renderer::Shutdown(void)
{
	if (window == nullptr)
		return;

	SDL_Quit();

	m_IsWindowOpen = false;
}

void Renderer::Render(void)
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

		SDL_UpdateWindowSurface(window);
	}
}

void Renderer::SetPixel(int X, int Y)
{
}
