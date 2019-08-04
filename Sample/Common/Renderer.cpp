// DOD Sample
//#define NO_RENDER

#include <Common\Renderer.h>
#include <SDL.h>
#include <memory>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *target = nullptr;
Uint32* pixels = nullptr;
int pitch = 0;
SDL_Rect destinationRect;
const unsigned char CLEAR_COLOR[3] = { 0, 0, 0 };
const unsigned char PIXEL_COLOR[4] = { 255, 0, 0, 255 };
Uint32 mappedPixelColor = 0;

void Renderer::Initialize(const char *Title, int Width, int Height)
{
	if (window != nullptr)
		return;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, Width, Height);

	SDL_PixelFormat pixelFormat;
	memset(&pixelFormat, 0, sizeof(SDL_PixelFormat));
	pixelFormat.format = SDL_PIXELFORMAT_RGB888;
	mappedPixelColor = SDL_MapRGB(&pixelFormat, PIXEL_COLOR[0], PIXEL_COLOR[1], PIXEL_COLOR[2]);

	destinationRect = { 0, 0, Width, Height };

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
	SDL_SetRenderDrawColor(renderer, CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], 255);
	SDL_RenderClear(renderer);

	SDL_LockTexture(target, nullptr, reinterpret_cast<void**>(&pixels), &pitch);

	memset(pixels, CLEAR_COLOR[0], destinationRect.h * pitch);
#endif
}

void Renderer::Present(void)
{
	if (window == nullptr)
		return;

	SDL_UnlockTexture(target);

	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_IsWindowOpen = false;
			break;

		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_SPACE)
				m_IsWindowOpen = false;
		}
	}

	SDL_RenderCopy(renderer, target, NULL, &destinationRect);

	SDL_RenderPresent(renderer);
}

void Renderer::SetPixel(int X, int Y)
{
#ifndef NO_RENDER
	Uint32 pixelPosition = Y * (pitch / sizeof(Uint32)) + X;

	pixels[pixelPosition] = mappedPixelColor;
#endif
}
