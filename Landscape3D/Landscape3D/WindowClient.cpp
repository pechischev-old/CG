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
	, m_camera({ 0, 2000, 0 }, {M_PI, 0, 0})
	, m_sunlight(GL_LIGHT0)
	, m_world("res/12.png", "res/12_normals.png")
{
    window.SetBackgroundColor(SKYBLUE_RGBA);
    CheckOpenGLVersion();
    SetupOpenGLState();
	SetupLight();

	CTexture2DLoader loader;

	m_grassTexture = loader.Load("res/sand.jpg");

	const auto vertShader = CFilesystemUtils::LoadFileAsString("res/phong.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res/phong.frag");
	m_programEarth.CompileShader(vertShader, ShaderType::Vertex);
	m_programEarth.CompileShader(fragShader, ShaderType::Fragment);
	m_programEarth.Link();
}

void CWindowClient::Use()
{
	glActiveTexture(GL_TEXTURE1);
	m_grassTexture->Bind();


	m_programEarth.Use();
	m_programEarth.FindUniform("material.diffuse") = glm::vec4(1.f, 0.353f, 0.051f, 1);
	m_programEarth.FindUniform("material.specular") = glm::vec4(0, 0.3, 0, 1);
	m_programEarth.FindUniform("material.emissive") = glm::vec4(0, 0, 0, 1);
	m_programEarth.FindUniform("textureDiffuseMap") = 1;


	const glm::mat4 mv = m_camera.GetViewTransform() * glm::mat4();
	m_programEarth.FindUniform("view") = m_camera.GetViewTransform();
	m_programEarth.FindUniform("modelView") = mv;
	m_programEarth.FindUniform("normalModelView") = glm::transpose(glm::inverse(mv));
	m_programEarth.FindUniform("projection") = m_projection;


	m_programEarth.FindUniform("light0.position") = m_sunlight.GetUniformPosition();
	m_programEarth.FindUniform("light0.diffuse") = m_sunlight.GetDiffuse();
	m_programEarth.FindUniform("light0.specular") = m_sunlight.GetSpecular();
}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);
}

void CWindowClient::OnDrawWindow()
{
    SetupView(GetWindow().GetWindowSize());
    m_sunlight.Setup();

	CVertexAttribute vertexAttr = m_programEarth.FindAttribute("vertex");
	CVertexAttribute normalAttr = m_programEarth.FindAttribute("normal");
	CVertexAttribute texCoordAttr = m_programEarth.FindAttribute("textureUV");

	Use();
	CRenderer3D renderer(vertexAttr, normalAttr, texCoordAttr);
	
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
	m_projection = glm::perspective(fieldOfView, aspect, zNear, zFar);

	glViewport(0, 0, size.x, size.y);
}

void CWindowClient::SetupLight()
{
	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);
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
