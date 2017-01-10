#include "stdafx.h"
#include "WindowClient.h"
#include "Renderer3D.h"

namespace
{
const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, -1.f, -1.f };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 SKYBLUE_RGBA = { 0.529f, 0.808f, 0.922f, 1.f };

const float CAMERA_INITIAL_ROTATION = float(M_PI);
const float CAMERA_INITIAL_DISTANCE = 30;
const int SPHERE_PRECISION = 40;

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);

    // включаем систему освещения с режимом двустороннего освещения
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
}

CWindowClient::CWindowClient(CWindow &window)
	: CAbstractWindowClient(window)
	, m_camera({ 5000, 3000, 10000 }, {M_PI, 0, 0})
	, m_sunlight(GL_LIGHT0)
	, m_world("res/12.png", "res/12_normals.png")
{
    window.SetBackgroundColor(SKYBLUE_RGBA);
    SetupOpenGLState();

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);

}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);
}

void CWindowClient::OnDrawWindow()
{
    SetupView(GetWindow().GetWindowSize());
    m_sunlight.Setup();
	SetupLight0();
	
	CRenderer3D renderer(m_context);
	
	m_world.Draw(renderer);
}

void CWindowClient::OnKeyDown(const SDL_KeyboardEvent &event)
{
    if (m_camera.OnKeyDown(event))
    {
        return;
    }
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
    if (m_camera.OnKeyUp(event))
    {
        return;
    }
	if (event.keysym.sym == SDLK_SPACE)
	{
		m_world.ChangeMode();
	}
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);
    const glm::mat4 view = m_camera.GetViewTransform();
    glLoadMatrixf(glm::value_ptr(view));

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
	const float fieldOfView = glm::radians(60.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 1.f;
	const float zFar = 10000.f;
	const glm::mat4 projection = glm::perspective(fieldOfView, aspect, zNear, zFar);
	
	glViewport(0, 0, size.x, size.y);

	m_context.SetProjection(projection);
	m_context.SetView(view);
}

void CWindowClient::SetupLight0()
{
	CProgramContext::SLightSource light0;
	light0.specular = m_sunlight.GetSpecular();
	light0.diffuse = m_sunlight.GetDiffuse();
	light0.position = m_sunlight.GetUniformPosition();
	m_context.SetLight0(light0);
}

void CWindowClient::OnDragBegin(const glm::vec2 &pos)
{
	//m_camera.OnDragBegin(pos);
}

void CWindowClient::OnDragMotion(const glm::vec2 &pos)
{
	//m_camera.OnDragMotion(pos);
}

void CWindowClient::OnDragEnd(const glm::vec2 &pos)
{
	//m_camera.OnDragEnd(pos);
}
