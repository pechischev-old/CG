#include "stdafx.h"
#include "WindowClient.h"

namespace
{
const glm::vec2 QUAD_TOPLEFT = { -250, -200 };
const glm::vec2 QUAD_SIZE = { 500, 350 };

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
    , m_quadObj(QUAD_TOPLEFT, QUAD_SIZE)
{
    const glm::vec4 WHITE = { 1.f, 1.f, 1.f, 1.f };
    GetWindow().SetBackgroundColor(WHITE);
    CheckOpenGLVersion();
    SetupOpenGLState();

	const std::string vertexShader = CFilesystemUtils::LoadFileAsString("res/copytexture.vert");
    const std::string checkersShader = CFilesystemUtils::LoadFileAsString("res/checkers.frag");
    const std::string pictureShader = CFilesystemUtils::LoadFileAsString("res/checkers-and-triangle.frag");

	m_programCheckers.CompileShader(vertexShader, ShaderType::Vertex);
    m_programCheckers.CompileShader(checkersShader, ShaderType::Fragment);
    m_programCheckers.Link();

	m_programPicture.CompileShader(vertexShader, ShaderType::Vertex);
    m_programPicture.CompileShader(pictureShader, ShaderType::Fragment);
    m_programPicture.Link();

    m_programQueue = { &m_programPicture, &m_programCheckers };
}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    (void)deltaSeconds;
}

void CWindowClient::OnDrawWindow()
{
    SetupView(GetWindow().GetWindowSize());

    // Активной будет первая программа из очереди.
    m_programQueue.front()->Use();
    m_quadObj.Draw();
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
    // Передвигаем очередь программ,
    // если была нажата и отпущена клавиша "Пробел"
    if (event.keysym.sym == SDLK_SPACE)
    {
        std::rotate(m_programQueue.begin(), m_programQueue.begin() + 1, m_programQueue.end());
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
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const float halfWidth = float(size.x) * 0.5f;
    const float halfHeight = float(size.y) * 0.5f;
    const glm::mat4 matrix = glm::ortho<float>(-halfWidth, halfWidth, -halfHeight, halfHeight);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
