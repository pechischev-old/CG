#include "stdafx.h"
#include "Window.h"
#include "Parser.h"
#include "Circle.h"
#include "Rectangle.h"


CWindow::CWindow()
{
	SetBackgroundColor({ 0.f, 0.5f, 0.2f, 1.f });
	CParser parser("input.json");
	InitEngine(parser.GetShapesData());
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
	for (auto &it : m_engine)
	{
		it->SetSizeWindow(size);
		it->Draw();
	}
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



void CWindow::InitEngine(std::vector<SShape> const & data)
{
	for (auto const &shape : data)
	{
		if (shape.type == "rectangle")
		{
			m_engine.emplace_back(std::make_unique<CRectangle>(glm::vec2(shape.pos), shape.size.x, shape.size.y, shape.color, shape.angle));
		}
		else if (shape.type == "circle")
		{
			m_engine.emplace_back(std::make_unique<CCircle>(glm::vec2(shape.pos), shape.size.x, shape.color));
		}
	}
}