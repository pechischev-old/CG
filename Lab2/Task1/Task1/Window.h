#pragma once
#include "DispatchEvent.h"
#include "Bodies.h"


class CWindow : public CAbstractInputControlWindow
{
public:
	CWindow();

	// CAbstractWindow interface
protected:
	void OnWindowInit(const glm::ivec2 &size) override;
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;

private:
	void SetupView(const glm::ivec2 &size);
	float m_time = 0.f;

	CIdentityCube m_cube;
};