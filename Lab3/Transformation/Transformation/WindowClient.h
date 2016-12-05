#pragma once
#include "libchapter3.h"
#include "TwistValueController.h"
#include "WhitneyUmbrella.h"
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

private:
    void CheckOpenGLVersion();
    void SetupView(const glm::ivec2 &size);

    CPhongModelMaterial m_umbrellaMat;
    CCamera m_camera;
    CDirectedLightSource m_sunlight;
    CPositionLightSource m_lamp;
    CShaderProgram m_programTwist;
    CShaderProgram m_programFixed;
	CParaboloid m_object;
    CTwistValueController m_twistController;
};
