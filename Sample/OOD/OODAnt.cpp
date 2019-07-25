// DOD Sample
#include <OOD\OODAnt.h>
#include <Common\Renderer.h>

void OODAnt::Update(void)
{
	m_Position.X++;
	m_Position.Y++;
}

void OODAnt::Render(Renderer *Renderer)
{
	Renderer->SetPixel(m_Position.X, m_Position.Y);
}