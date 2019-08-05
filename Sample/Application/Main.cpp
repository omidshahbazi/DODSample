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
	std::cout << std::endl << "Average FPS: " << avgFPS << " - Average Frame Time: " << (totalTime / frameCount) * 1000 << "ms" << std::endl << std::endl;

template<bool DoUpdate, bool DoRender>
void Loop(Renderer & Renderer, Simulation & Simulation)
{
	std::cout << std::endl;

	if constexpr (DoUpdate && DoRender)
		std::cout << "Update And Render";
	else	if constexpr (DoUpdate)
		std::cout << "Just Update";
	else if constexpr (DoRender)
		std::cout << "Just Render";

	std::cout << std::endl;

	DECLARE_FPS_COUNTER();

	PRINT_PROFILER_TABLE_COLUMN();
	BEGIN_PROFILE_COLLECTOR(Update);
	BEGIN_PROFILE_COLLECTOR(Render);

	while (Renderer.IsWindowOpen())
	{
		BEGIN_PROFILE_COLLECT(Update);
		if constexpr (DoUpdate)
			Simulation.Update();
		END_PROFILE_COLLECT(Update);

		BEGIN_PROFILE_COLLECT(Render);
		Renderer.Clear();

		if constexpr (DoRender)
			Simulation.Render();

		Renderer.Present();
		END_PROFILE_COLLECT(Render);

		++frameCount;
	}

	END_PROFILE_COLLECTOR(Update);
	END_PROFILE_COLLECTOR(Render);

	CALCULATE_AND_PRINT_FPS();

	if constexpr (!(DoUpdate && DoRender))
		Renderer.SetIsWindowOpen(true);
}

void main(void)
{
	BEGIN_PROFILE(Init);

	Renderer renderer;
	renderer.Initialize("DOD Sample", Utils::WIDTH, Utils::HEIGHT);

	OODSimulation simulation(&renderer, Utils::ANT_COUNT);
	//OODSimulationOptimized simulation(&renderer, Utils::ANT_COUNT);
	//DODSimulation simulation(&renderer, Utils::ANT_COUNT);
	//DODSimulationMultithreaded simulation(&renderer, Utils::ANT_COUNT);

	std::cout << simulation.GetName() << " is running for " << Utils::ANT_COUNT << " ant(s)" << std::endl << std::endl;

	PRINT_PROFILER_TABLE_COLUMN();
	END_PROFILE(Init);

	Loop<true, false>(renderer, simulation);

	Loop<false, true>(renderer, simulation);

	Loop<true, true>(renderer, simulation);

	renderer.Shutdown();

	system("pause");
}