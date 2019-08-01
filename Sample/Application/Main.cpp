// DOD Sample
#include <Common\Renderer.h>
#include <Common\Utils.h>
#include <OOD\OODSimulation.h>
#include <OOD.Optimized\OODSimulation.Optimized.h>
#include <DOD\DODSimulation.h>
#include <DOD.Multithreaded\DODSimulation.Multithreaded.h>

#define DECLARE_FPS_COUNTER() \
	unsigned int frameCount = 0; \
	float startTime = Utils::GetTime();

#define CALCULATE_AND_PRINT_FPS() \
	float totalTime = (Utils::GetTime() - startTime); \
	float avgFPS = frameCount / totalTime; \
	std::cout << std::endl << "Average FPS: " << avgFPS << " - Average Frame Time: " << (totalTime / avgFPS) * 1000 << "ms" << std::endl << std::endl;

void JustUpdate(Renderer &Renderer, Simulation &Simulation)
{
	std::cout << std::endl << "JustUpdate" << std::endl;

	DECLARE_FPS_COUNTER();

	PRINT_PROFILER_TABLE_COLUMN();
	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);

	while (Renderer.IsWindowOpen())
	{
		BEGIN_PROFILE_COLLECT(Update);
		Simulation.Update();
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		Renderer.Present();
		END_PROFILE_COLLECT(Render);

		++frameCount;
	}

	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);

	CALCULATE_AND_PRINT_FPS();

	Renderer.SetIsWindowOpen(true);
}

void JustRender(Renderer &Renderer, Simulation &Simulation)
{
	std::cout << std::endl << "JustRender" << std::endl;

	DECLARE_FPS_COUNTER();

	PRINT_PROFILER_TABLE_COLUMN();
	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);

	while (Renderer.IsWindowOpen())
	{
		BEGIN_PROFILE_COLLECT(Update);
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		Renderer.Clear();

		Simulation.Render();

		Renderer.Present();
		END_PROFILE_COLLECT(Render);

		++frameCount;
	}

	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);

	CALCULATE_AND_PRINT_FPS();

	Renderer.SetIsWindowOpen(true);
}

void UpdateAndRender(Renderer &Renderer, Simulation &Simulation)
{
	std::cout << std::endl << "UpdateAndRender" << std::endl;

	DECLARE_FPS_COUNTER();

	PRINT_PROFILER_TABLE_COLUMN();
	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);

	while (Renderer.IsWindowOpen())
	{
		BEGIN_PROFILE_COLLECT(Update);
		Simulation.Update();
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		Renderer.Clear();

		Simulation.Render();

		Renderer.Present();
		END_PROFILE_COLLECT(Render);

		++frameCount;
	}

	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);

	CALCULATE_AND_PRINT_FPS();
}

void main(void)
{
	BEGIN_PROFILE(Init);

	Renderer renderer;
	renderer.Initialize("DOD Sample", Utils::WIDTH, Utils::HEIGHT);

	//OODSimulation simulation(&renderer, Utils::ANT_COUNT);
	//OODSimulationOptimized simulation(&renderer, Utils::ANT_COUNT);
	DODSimulation simulation(&renderer, Utils::ANT_COUNT);

	//DODSimulationMultithreaded simulation(&renderer, Utils::ANT_COUNT);

	std::cout << simulation.GetName() << " is running for " << Utils::ANT_COUNT << " ant(s)" << std::endl << std::endl;

	PRINT_PROFILER_TABLE_COLUMN();
	END_PROFILE(Init);

	JustUpdate(renderer, simulation);

	JustRender(renderer, simulation);

	UpdateAndRender(renderer, simulation);

	renderer.Shutdown();

	system("pause");
}