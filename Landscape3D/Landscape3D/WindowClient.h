#pragma once
#include "libchapter3.h"
#include "World.h"
#include "ProgramContext.h" 


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
    void SetupView(const glm::ivec2 &size);
	void SetupLight0();
	
	CProgramContext m_context;

    CCamera m_camera;
    CDirectedLightSource m_sunlight;
	CWorld m_world;
};
