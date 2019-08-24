// DOD Sample
#include <DOD\DODAnt.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

void DODAntsLogic::Update(DODAntData1 *Data1, DODAntData2 *Data2, int Index, int Count)
{
	for (int i = Index; i < Index + Count; ++i)
	{
		DODAntData1 &antData1 = Data1[i];
		DODAntData2 &antData2 = Data2[i];

		antData2.Position += antData1.Step;

		if (--antData1.StepCount == 0)
			DODAntsLogic::FindNewTarget(antData1, antData2);
	}
}

void DODAntsLogic::Render(DODAntData2 *Data, int Count, Renderer *Renderer)
{
	::Renderer& ren = *Renderer;

	for (int i = 0; i < Count; ++i)
	{
		DODAntData2 &antData = Data[i];

		ren.SetPixel(antData.Position.X, antData.Position.Y);
	}
}

void DODAntsLogic::FindNewTarget(DODAntData1& Data1, DODAntData2& Data2)
{
	Vector2F target = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);

	Data1.StepCount = Utils::GetRandom(Utils::MIN_STEP_COUNT, Utils::MAX_STEP_COUNT);

	Data1.Step = (target - Data2.Position) / Data1.StepCount;
}
