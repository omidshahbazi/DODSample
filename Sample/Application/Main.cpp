// DOD Sample
#include <Common\Renderer.h>
#include <Common\Utils.h>
#include <OOD\OODSimulation.h>
#include <DOD\DODSimulation.h>
#include <iostream>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int ANT_COUNT = 1000;

void main(void)
{
	Renderer renderer;
	renderer.Initialize("DOD Sample", 800, 600);

	OODSimulation simulation(&renderer, ANT_COUNT);
	//DODSimulation simulation(&renderer, ANT_COUNT);

	std::cout << simulation.GetName() << " is running" << std::endl;

	float lastCountTime = Utils::GetTime();
	unsigned int frameCount = 0;
	float lastTime = 0.0F;
	float totalFrameTime = 0.0F;
	float avgFPS = 0.0F;

	while (renderer.IsWindowOpen())
	{
		float nowTime = Utils::GetTime();

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