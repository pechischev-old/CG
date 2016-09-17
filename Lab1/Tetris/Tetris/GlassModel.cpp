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

void CGlassModel::MoveFigure()
{
	m_field = m_copyField;
}

void CGlassModel::SetFigure()
{
	m_copyField = m_field;

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
