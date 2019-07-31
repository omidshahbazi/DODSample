// DOD Sample
#include <Common\Renderer.h>
#include <Common\Utils.h>
#include <OOD\OODSimulation.h>
#include <DOD\DODSimulation.h>
#include <DOD.Multithreaded\DOD.MultithreadedSimulation.h>

void main(void)
{
	BEGIN_PROFILE(Init);

	Renderer renderer;
	renderer.Initialize("DOD Sample", Utils::WIDTH, Utils::HEIGHT);

	//OODSimulation simulation(&renderer, Utils::ANT_COUNT);
	DODSimulation simulation(&renderer, Utils::ANT_COUNT);
	//DODMultithreadedSimulation simulation(&renderer, Utils::ANT_COUNT);

	std::cout << simulation.GetName() << " is running for " << Utils::ANT_COUNT << " ant(s)" << std::endl << std::endl;

	PRINT_PROFILER_TABLE_COLUMN();

	END_PROFILE_AND_PRINT(Init);

	float lastCountTime = Utils::GetTime();
	unsigned int frameCount = 0;
	float lastTime = 0.0F;
	float totalFrameTime = 0.0F;
	float avgFPS = 0.0F;

	BEGIN_PROFILE_COLLECTOR(Clear);
	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);
	BEGIN_PROFILE_COLLECTOR(Present);

	while (renderer.IsWindowOpen())
	{
		float nowTime = Utils::GetTime();

		BEGIN_PROFILE_COLLECT(Clear);
		renderer.Clear();
		END_PROFILE_COLLECT(Clear);

		BEGIN_PROFILE_COLLECT(Update);
		simulation.Update();
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		simulation.Render();
		END_PROFILE_COLLECT(Render);

		BEGIN_PROFILE_COLLECT(Present);
		renderer.Present();
		END_PROFILE_COLLECT(Present);

		totalFrameTime += nowTime - lastTime;
		++frameCount;
		lastTime = nowTime;

		if (nowTime - lastCountTime >= 1.0F)
		{
			avgFPS = frameCount / totalFrameTime;

			//std::cout << "Average FPS: " << avgFPS << " - Average Frame Time: " << ((nowTime - lastCountTime) * 1000 / avgFPS) << "ms" << std::endl;

			frameCount = 0;
			lastCountTime = nowTime;
			totalFrameTime = 0.0F;
		}
	}

	END_PROFILE_COLLECTOR(Clear);
	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);
	END_PROFILE_COLLECTOR(Present);

	renderer.Shutdown();

	system("pause");
}