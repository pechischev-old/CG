#include "stdafx.h"
#include "GlassModel.h"

namespace
{
	static const unsigned int FIELD_WIDTH = 12;
	static const unsigned int FIELD_HEIGHT = 21;
	static const char SYMBOL_WALL = '1';
	static const char SYMBOL_STATIC_FIGURE = '+';
	static const char SYMBOL_EMPTY_SPACE = ' ';
}

void OutputField(std::vector<std::vector<char>> const & field)
{
	for (auto & line : field)
	{
		for (auto & cell : line)
		{
			std::cout << cell;
		}
		std::cout << std::endl;
	}
}

CGlassModel::CGlassModel()
{
	FillField();
	OutputField(m_field);
}

CGlassModel::~CGlassModel()
{
}

void CGlassModel::ClearFullLine()
{
}

void CGlassModel::MoveFigure() // смотреть тип движения и задавать соответствующие координаты
{
	if (!CanMoveFigure())
	{
		return;
	}
	m_field = m_copyField;
	auto shift = m_figure->GetPosition();
	switch (m_figure->GetTypeMove()) 
	{
	case TypeMove::Direction::Left:
		shift.x = (--shift.x > 0 ? shift.x : 1);
		break;
	case TypeMove::Direction::Right:
		shift.x = (++shift.x < FIELD_WIDTH ? shift.x : FIELD_WIDTH - 1);
		break;
	case TypeMove::Direction::Down:
		shift.y = (++shift.y < FIELD_HEIGHT ? shift.y : FIELD_HEIGHT - 1);
		break;
	}
	shift.y = (++shift.y < FIELD_HEIGHT ? shift.y : FIELD_HEIGHT - 1);
	m_figure->SetPosition(glm::vec2(shift));
	std::cout << m_figure->GetPosition().x << "  " << m_figure->GetPosition().y << std::endl;
	auto sizeFigure = m_figure->GetSize();



}

void CGlassModel::SetFigure(CFigure* figure)
{
	m_copyField = m_field;
	m_figure = figure;
	m_figure->SetPosition(glm::vec2(FIELD_WIDTH / 3, 0));
}

bool CGlassModel::CanMoveFigure()
{
	return m_figure;
}

void CGlassModel::FillField()
{
	m_field.resize(FIELD_HEIGHT);
	for (auto & line : m_field)
	{
		line.resize(FIELD_WIDTH, SYMBOL_EMPTY_SPACE);
		line.front() = SYMBOL_WALL;
		line.back() = SYMBOL_WALL;
	}
	for (auto & cell : m_field.back())
	{
		cell = SYMBOL_WALL;
	}

	m_copyField = m_field;
}
