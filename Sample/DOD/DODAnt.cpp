// DOD Sample
#pragma once
#include <DOD\DODAnt.h>
#include <Common\Renderer.h>

void DODAntsLogic::UpdateDODAnts(DODAnt *Ants, int Count)
{
	for (int i = 0; i < Count; ++i)
	{
		DODAnt &ant = Ants[i];

		ant.Position.X++;
		ant.Position.Y++;
	}
}

void DODAntsLogic::RenderDODAnts(DODAnt *Ants, int Count, Renderer *Renderer)
{
	for (int i = 0; i < Count; ++i)
	{
		DODAnt &ant = Ants[i];

		Renderer->SetPixel(ant.Position.X, ant.Position.Y);
	}
}