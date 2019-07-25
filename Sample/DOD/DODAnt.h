// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

struct DODAnt
{
public:
	Vector2F Position;
	Vector2F Target;
};

class DODAntsLogic
{
public:
	static void UpdateDODAnts(DODAnt *Ants, int Count);

	static void RenderDODAnts(DODAnt *Ants, int Count, Renderer *Renderer);
};