// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

struct DODAntData1
{
public:
	Vector2F Step;
	int StepCount;
};

struct DODAntData2
{
public:
	Vector2F Position;
};

class DODAntsLogic
{
public:
	static void Update(DODAntData1* Data1, DODAntData2* Data2, int Index, int Count);

	static void Render(DODAntData2 *Data, int Count, Renderer *Renderer);

	static void FindNewTarget(DODAntData1 &Data1, DODAntData2 &Data2);
};