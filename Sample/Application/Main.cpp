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

	END_PROFILE(Init);

	unsigned int frameCount = 0;
	float startTime = Utils::GetTime();

	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);

	while (renderer.IsWindowOpen())
	{
		BEGIN_PROFILE_COLLECT(Update);
		simulation.Update();
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		renderer.Clear();

		simulation.Render();

		renderer.Present();
		END_PROFILE_COLLECT(Render);

		++frameCount;
	}

	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);

	float totalTime = (Utils::GetTime() - startTime);
	float avgFPS = frameCount / totalTime;
	std::cout << std::endl << "Average FPS: " << avgFPS << " - Average Frame Time: " << (totalTime / avgFPS) * 1000 << "ms" << std::endl << std::endl;

	renderer.Shutdown();

	system("pause");
}