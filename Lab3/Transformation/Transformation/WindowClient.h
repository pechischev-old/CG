#pragma once
#include "libchapter3.h"
#include "TwistValueController.h"
#include "Paraboloid.h"
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

    CPhongModelMaterial m_umbrellaMat;
    CCamera m_camera;
    CDirectedLightSource m_sunlight;
    CShaderProgram m_programTwist;
    CShaderProgram m_programFixed;
	CParaboloid m_object;
    CTwistValueController m_twistController;

	bool m_programEnabled = true;
	bool m_isLinesOnly = false;

};
