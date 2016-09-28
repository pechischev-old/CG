#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const float CAMERA_INITIAL_ROTATION = 0;
	const float CAMERA_INITIAL_DISTANCE = 5.f;

	void SetupOpenGLState()
	{
		// включаем механизмы трЄхмерного мира.
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}
}


CWindow::CWindow()
	: m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
{
	SetBackgroundColor(BLACK);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
	(void)size;
	SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
	m_cube.Update(deltaSeconds);
	m_camera.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
		
	m_cube.Draw();
	
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	glViewport(0, 0, size.x, size.y);

	// ћатрица вида возвращаетс€ камерой и составл€ет
	// начальное значение матрицы GL_MODELVIEW.
	glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

	// ћатрица перспективного преобразовани€ вычисл€етс€ функцией
	// glm::perspective, принимающей угол обзора, соотношение ширины
	// и высоты окна, рассто€ни€ до ближней и дальней плоскостей отсечени€.
	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
	m_camera.OnKeyDown(event);
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_camera.OnKeyUp(event);
}