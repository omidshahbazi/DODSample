// DOD Sample
#include <OOD\OODAnt.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

void OODAnt::Update(void)
{
	m_Position += (m_Target - m_Position) / m_StepCount;

	if (m_StepCount-- == 0)
		FindNewTarget();
}

void OODAnt::Render(Renderer *Renderer)
{
	Renderer->SetPixel(m_Position.X, m_Position.Y);
}

void OODAnt::FindNewTarget(void)
{
	m_Target = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);
	m_StepCount = Utils::GetRandom(Utils::MIN_STEP_COUNT, Utils::MAX_STEP_COUNT);
}