#pragma once
#include "DispatchEvent.h"
#include "DrawableObject.h"


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
	void InitEngine(std::vector<SShape> const & data);

	std::vector<std::unique_ptr<CDrawableObject>> m_engine;
	float m_time = 0.f;

};