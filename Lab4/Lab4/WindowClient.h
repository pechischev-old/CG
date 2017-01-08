#pragma once
#include "libchapter3.h"
#include "World.h"
#include "Bodies.h"
#include "ProgramContext.h"
#include <vector>

class CWindowClient : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow() override;
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;
	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;

private:
    void CheckOpenGLVersion();
    void SetupView(const glm::ivec2 &size);
	void SetupLight();
	void Use();

	CArrayObject m_defaultVAO;

    CCamera m_camera;
    CDirectedLightSource m_sunlight;
	CRhombicuboctahedron m_body;
	CWorld m_world;
	CProgramContext m_programContext;
};
