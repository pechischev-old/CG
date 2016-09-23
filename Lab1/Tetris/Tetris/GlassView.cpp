#include "stdafx.h"
#include "GlassView.h"

namespace
{
	static const float SIZE_RECTANGLE = 25.f;
	static const glm::vec3 WHITE_COLOR = { 1.f, 1.f, 1.f};
	static const glm::vec3 GREY_COLOR = { 0.7f, 0.7f, 0.7f };
	static const glm::vec3 RED_COLOR = { 1.f, 0.f, 0.f };
	static const glm::vec3 GREEN_COLOR = { 0.f, 1.f, 0.f };
}

CGlassView::~CGlassView()
{
}

void CGlassView::SetupGlass(glm::vec2 const & pos)
{
	m_system.clear();
	m_pos = {50.f, 50.f};
}

void CGlassView::Draw()
{
	if (m_system.empty())
	{
		InitGlass();
	}
	Redraw();
}

void CGlassView::Update(Field const & glass)
{
	m_system.clear();
	m_glass = glass;
	
}

void CGlassView::Redraw()
{
	for (auto &it : m_system)
	{
		it.Draw();
	}
}

void CGlassView::InitGlass()
{
	for (size_t height = 0; height < m_glass.size(); ++height)
	{
		for (size_t width = 0; width < m_glass[height].size(); ++width)
		{
			auto symbol = m_glass[height][width];
			auto pos = glm::vec2(m_pos.x +  width * SIZE_RECTANGLE, m_pos.y + height * SIZE_RECTANGLE);
			if (symbol == UsingSymbols::SYMBOL_WALL)
			{
				m_system.emplace_back(CRectangle(pos, SIZE_RECTANGLE, SIZE_RECTANGLE, GREY_COLOR));
			}
			else if (symbol == UsingSymbols::SYMBOL_STATIC_FIGURE)
			{
				m_system.emplace_back(CRectangle(pos, SIZE_RECTANGLE, SIZE_RECTANGLE, RED_COLOR));
			}
			else if (symbol == '#')
			{
				m_system.emplace_back(CRectangle(pos, SIZE_RECTANGLE, SIZE_RECTANGLE, GREEN_COLOR));
			}
		}
	}
}
