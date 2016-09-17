#include "stdafx.h"
#include "Window.h"


CWindow::CWindow()
	: m_shedule(WINDOW_WIDTH, WINDOW_HEIGTH)
{
	SetBackgroundColor({ 1.f, 1.f, 1.f, 1.f });
	
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_shedule.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);

	m_shedule.SetSizeWindow(size.x, size.y);
	m_shedule.Draw();
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_shedule.OnKeyDown(event);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}