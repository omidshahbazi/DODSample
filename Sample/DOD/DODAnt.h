// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

struct DODAntData
{
public:
	Vector2F Position;
	Vector2F Step;
	int StepCount;
};

class DODAntsLogic
{
public:
	static void Update(DODAntData *Data, int Index, int Count);

	static void Render(DODAntData *Data, int Count, Renderer *Renderer);

	static void FindNewTarget(DODAntData &Data);
};