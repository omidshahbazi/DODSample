// DOD Sample
#include <DOD\DODAnt.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

void DODAntsLogic::Update(DODAntData *Data, int Index, int Count)
{
	for (int i = Index; i < Index + Count; ++i)
	{
		DODAntData &antData = Data[i];

		antData.Position += antData.Step;

		if (--antData.StepCount == 0)
			DODAntsLogic::FindNewTarget(antData);
	}
}

void DODAntsLogic::Render(DODAntData *Data, int Count, Renderer *Renderer)
{
	::Renderer& ren = *Renderer;

	for (int i = 0; i < Count; ++i)
	{
		DODAntData &antData = Data[i];

		ren.SetPixel(antData.Position.X, antData.Position.Y);
	}
}

void DODAntsLogic::FindNewTarget(DODAntData &Data)
{
	Vector2F target = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);

	Data.StepCount = Utils::GetRandom(Utils::MIN_STEP_COUNT, Utils::MAX_STEP_COUNT);

	Data.Step = (target - Data.Position) / Data.StepCount;
}
