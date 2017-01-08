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

	// включаем механизмы трёхмерного мира.
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);*/
}
}

CWindowClient::CWindowClient(CWindow &window)
	: CAbstractWindowClient(window)
	, m_defaultVAO(CArrayObject::do_bind_tag())
	, m_camera({ 0, 2000, 0 }, {M_PI, 0, 0})
	, m_sunlight(GL_LIGHT0)
	, m_world("res/12.png", "res/12_normals.png")
	//, m_world("res/heightmap.png", "res/normalmap.png")
{
    window.SetBackgroundColor(SKYBLUE_RGBA);
    CheckOpenGLVersion();
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

	SetupLight();

	CRenderer3D renderer(m_programContext);
	
	m_world.Draw(renderer);
	m_body.Draw();
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
}

void CWindowClient::CheckOpenGLVersion()
{
    // В OpenGL 2.0 шейдерные программы вошли в спецификацию API.
    if (!GLEW_VERSION_2_0)
    {
        throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
    }
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    //glViewport(0, 0, size.x, size.y);
    const glm::mat4 mv = m_camera.GetViewTransform();
    //glLoadMatrixf(glm::value_ptr(mv));

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
	const float fieldOfView = glm::radians(60.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 1.f;
	const float zFar = 10000.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);

	glViewport(0, 0, size.x, size.y);

	m_programContext.SetView(mv);
	m_programContext.SetProjection(proj);
}

void CWindowClient::SetupLight()
{
	

	CProgramContext::SLightSource light0;
	light0.specular = m_sunlight.GetSpecular();
	light0.diffuse = m_sunlight.GetDiffuse();
	light0.position = m_sunlight.GetUniformPosition();
	m_programContext.SetLight0(light0);
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
