#pragma once
#include "DispatchEvent.h"
#include "Engine.h"


class CWindow : public CAbstractInputControlWindow
{
public:
	CWindow();

	// CAbstractWindow interface
protected:
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;

private:
	void SetupView(const glm::ivec2 &size);
	float m_time = 0.f;
	std::unique_ptr<CEngine> m_engine;
};