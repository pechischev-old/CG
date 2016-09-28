#pragma once
#include "DispatchEvent.h"
#include "Bodies.h"
#include "Camera.h"
#include "Light.h"


class CWindow : public CAbstractInputControlWindow
{
public:
	CWindow();

	// CAbstractWindow interface
protected:
	void OnWindowInit(const glm::ivec2 &size) override;
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;

	// IInputEventAcceptor interface
	void OnKeyDown(const SDL_KeyboardEvent &) override;
	void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
	void SetupView(const glm::ivec2 &size);
	void SetupFog();
	float m_time = 0.f;

	CIdentityCube m_cube;
	CCamera m_camera;
	CDirectedLightSource m_sunlight;
	bool m_isFogEnabled = true;
};