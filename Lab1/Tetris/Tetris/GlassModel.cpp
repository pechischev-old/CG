#include "stdafx.h"
#include "GlassModel.h"

namespace
{
	static const int FIELD_WIDTH = 12;
	static const int FIELD_HEIGHT = 21;
	static const char SYMBOL_WALL = '1';
	static const char SYMBOL_STATIC_FIGURE = '@';
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
	if (!CanMoveFigure())
	{
		return;
	}
	auto shift = m_figure->GetPosition();

	switch (m_figure->GetTypeMove()) 
	{
	case TypeMove::Direction::Left:
		shift.x = (--shift.x > 0 ? shift.x : 1);
		break;
	case TypeMove::Direction::Right:
		shift.x = (++shift.x < FIELD_WIDTH ? shift.x : FIELD_WIDTH - 1 );
		break;
	}
	shift.y = (++shift.y < FIELD_HEIGHT ? shift.y : FIELD_HEIGHT - 1 );
	ProcessCollisions(shift, m_figure->GetPosition());
	bool flag = (shift == m_figure->GetPosition()) ;

	m_figure->SetTypeMove(TypeMove::Direction::None);
	m_figure->SetPosition(glm::vec2(shift));
	
	auto i = shift.y;
	auto shape = m_figure->GetForm();
	for (auto const & line : shape)
	{
		auto j = shift.x;
		for (auto const & symbol : line)
		{
			m_field[i][j] = (m_field[i][j] != SYMBOL_STATIC_FIGURE) ? symbol : m_field[i][j];
			++j;
		}
		++i;
	}
	
	if (flag)
	{
		m_figure = nullptr;
		for (size_t i = 0; i < FIELD_HEIGHT; ++i)
		{
			for (size_t j = 1; j < FIELD_WIDTH; ++j)
			{
				m_field[i][j] = (m_field[i][j] == '#') ? SYMBOL_STATIC_FIGURE : m_field[i][j];
			}
		}
	}
	for (size_t i = 0; i < 3; ++i)
	{
	std::cout << std::endl;
	}
	OutputField(m_field);

}

void CGlassModel::SetFigure(CFigure* figure)
{
	m_copyField = m_field;
	m_figure = figure;
	m_figure->SetPosition(glm::vec2(FIELD_WIDTH / 3, 0));
}

bool CGlassModel::CanMoveFigure()
{
	return m_figure != nullptr;
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

void CGlassModel::ProcessCollisions(glm::ivec2 & newPos, glm::ivec2 const & oldPos)
{
	auto shape = m_figure->GetForm();
	auto size = m_figure->GetSize();
	newPos.x = ((0 < newPos.x) && (newPos.x < FIELD_WIDTH - size.x)) ? newPos.x : FIELD_WIDTH - size.x - 1;
	newPos.y = ((newPos.y < FIELD_HEIGHT - size.y) ? newPos.y : FIELD_HEIGHT - size.y - 1);

	for (size_t height = 0; height < shape.size(); ++height)
	{
		for (size_t width = 0; width < shape[height].size(); ++width)
		{
			
			if (shape[height][width] == SYMBOL_EMPTY_SPACE)
			{
				
				continue;
			}
			
			auto nextSymbol = m_field[newPos.y + height][newPos.x + width];
			if (nextSymbol == SYMBOL_STATIC_FIGURE || nextSymbol == SYMBOL_WALL)
			{
				newPos.x = oldPos.x;
			}
			nextSymbol = m_field[newPos.y + height][oldPos.x + width];
			if (nextSymbol == SYMBOL_STATIC_FIGURE || nextSymbol == SYMBOL_WALL)
			{
				newPos.y = oldPos.y;
			}
		}		
	}
	
}
