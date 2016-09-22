#pragma once
#include "DispatchEvent.h"
#include "Shedule.h"


static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGTH = 600;

class CWindow : public CAbstractInputControlWindow
{
public:
	CWindow();

	// CAbstractWindow interface
protected:
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;
	void OnKeyDown(const SDL_KeyboardEvent & event) override;
	void OnKeyUp(const SDL_KeyboardEvent & event) override;
private:
	void SetupView(const glm::ivec2 &size);
	CShedule m_shedule;
};