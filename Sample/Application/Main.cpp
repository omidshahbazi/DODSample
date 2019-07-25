// DOD Sample
#include <Common\Renderer.h>
#include <OOD\OODSimulation.h>
#include <DOD\DODSimulation.h>
#include <Windows.h>
#include <iostream>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int ANT_COUNT = 1000;

long GetFrequency(void)
{
	LARGE_INTEGER var;
	QueryPerformanceFrequency(&var);
	return var.QuadPart;
}

float GetTimestamp(void)
{
	static long frequency = GetFrequency();

	LARGE_INTEGER clock;
	QueryPerformanceCounter(&clock);

	return (float(clock.QuadPart * 1000000) / frequency) / 1000000;
}

float GetTime(void)
{
	static float start = GetTimestamp();

	return GetTimestamp() - start;
}

void main(void)
{
	Renderer renderer;
	renderer.Initialize("DOD Sample", 800, 600);

	OODSimulation simulation(&renderer, ANT_COUNT);
	//DODSimulation simulation(&renderer, ANT_COUNT);

	float lastCountTime = GetTime();
	unsigned int frameCount = 0;
	float lastTime = 0.0F;
	float totalFrameTime = 0.0F;
	float avgFPS = 0.0F;

	while (renderer.IsWindowOpen())
	{
		float nowTime = GetTime();

		simulation.Update();

		renderer.Render();

		totalFrameTime += nowTime - lastTime;
		++frameCount;
		lastTime = nowTime;

		if (nowTime - lastCountTime >= 1.0F)
		{
			avgFPS = frameCount / totalFrameTime;

			std::cout << "Average FPS: " << avgFPS << " - Average Frame Time: " << ((nowTime - lastCountTime) / avgFPS) << std::endl;

			frameCount = 0;
			lastCountTime = nowTime;
			totalFrameTime = 0.0F;
		}
	}

	renderer.Shutdown();
}