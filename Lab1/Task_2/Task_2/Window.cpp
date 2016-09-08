#include "stdafx.h"
#include "Window.h"



CWindow::CWindow()
{
	SetBackgroundColor({ 0.f, 0.5f, 0.2f, 1.f });
	m_engine = std::make_unique<CEngine>();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
	m_engine->SetupEngine({ size.x / 2, size.y / 3 });
	m_engine->Draw();
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