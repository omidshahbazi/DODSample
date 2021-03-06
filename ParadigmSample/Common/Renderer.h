// DOD Sample
#pragma once

class Renderer
{
public:
	void Initialize(const char *Title, int Width, int Heigth);
	void Shutdown(void);

	void Clear(void);

	void Present(void);

	void SetPixel(int X, int Y);

	bool IsWindowOpen(void)
	{
		return m_IsWindowOpen;
	}

	void SetIsWindowOpen(bool Value)
	{
		m_IsWindowOpen = true;
	}

private:
	bool m_IsWindowOpen;
};