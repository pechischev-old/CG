#include "stdafx.h"
#include "Glass.h"

namespace
{
	static const int FIELD_WIDTH = 12;
	static const int FIELD_HEIGHT = 21;
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

CGlass::CGlass()
{
	FillField();
}

CGlass::~CGlass()
{
}

void CGlass::ClearFullLine()
{
	m_numberDeletedLines = 0;
	for (size_t it = 0; it < m_field.size() - 1;)
	{
		bool isFullLine = true;
		for (auto const & symbol : m_field[it])
		{
			if (symbol == UsingSymbols::SYMBOL_WALL)
			{
				continue;
			}
			if (symbol != UsingSymbols::SYMBOL_STATIC_FIGURE)
			{
				isFullLine = false;
				break;
			}
		}
		if (isFullLine)
		{
			m_field.erase(m_field.begin() + it);
			m_field.insert(m_field.begin(), m_emptyLine);
			++m_numberDeletedLines;
			continue;
		}
		++it;
	}
	for (auto const & symbol : m_field[1]) // TODO: заменить на is_any_of
	{
		if (symbol == UsingSymbols::SYMBOL_STATIC_FIGURE)
		{
			m_isFull = true;
		}
	}
}

void CGlass::MoveFigure() 
{
	m_field = m_copyField;
	
	if (!CanMoveFigure())
	{
		return;
	}
	auto oldPos = m_figure->GetPosition();
	auto newPos = GetNextPosition(oldPos);

	ProcessCollisions(newPos, oldPos);
	
	m_figure->SetPosition(glm::vec2(newPos));
	
	auto i = newPos.y;
	auto shape = m_figure->GetForm();
	for (auto const & line : shape)
	{
		auto j = newPos.x;
		for (auto const & symbol : line)
		{
			m_field[i][j] = (m_field[i][j] != UsingSymbols::SYMBOL_STATIC_FIGURE) ? symbol : m_field[i][j];
			++j;
		}
		++i;
	}
	
	if (newPos == oldPos)
	{
		m_figure = nullptr; // TODO заменить на replace all
		for (size_t i = 0; i < FIELD_HEIGHT; ++i)
		{
			for (size_t j = 1; j < FIELD_WIDTH; ++j)
			{
				m_field[i][j] = (m_field[i][j] == '#') ? UsingSymbols::SYMBOL_STATIC_FIGURE : m_field[i][j];
			}
		}
	}
	FieldChanged();
	/*for (size_t i = 0; i < 3; ++i)
	{
	std::cout << std::endl;
	}
	OutputField(m_field);*/

}

void CGlass::SetFigure(CFigure* figure)
{
	m_copyField = m_field;
	m_figure = figure;
	m_figure->SetPosition(glm::vec2(FIELD_WIDTH / 3, 0));
	FieldChanged();
}

bool CGlass::CanMoveFigure()
{
	return m_figure != nullptr;
}

int CGlass::GetCountDeletedLines() const
{
	return m_numberDeletedLines;
}

int CGlass::GetCountEmptyLine() const
{
	int countEmptyLine = 0;
	for (auto const & line : m_field)
	{
		bool isEmptyLine = true;
		for (auto const & cell : line)
		{
			if (cell != UsingSymbols::SYMBOL_EMPTY_SPACE)
			{
				isEmptyLine = true;
				break;
			}
			++countEmptyLine;
		}
		if (isEmptyLine)
		{
			break;
		}
	}
	return countEmptyLine;
}

bool CGlass::HasFull() const
{
	return m_isFull;
}

void CGlass::FieldChanged()
{
	NotifyObservers();
}

Field CGlass::GetChangedData() const
{
	return m_field;
}

void CGlass::FillField()
{
	m_field.resize(FIELD_HEIGHT);
	m_emptyLine.resize(FIELD_WIDTH, UsingSymbols::SYMBOL_EMPTY_SPACE);
	m_emptyLine.front() = UsingSymbols::SYMBOL_WALL;
	m_emptyLine.back() = UsingSymbols::SYMBOL_WALL;

	for (auto & line : m_field)
	{
		line = m_emptyLine;
	}
	for (auto & cell : m_field.back())
	{
		cell = UsingSymbols::SYMBOL_WALL;
	}

	m_copyField = m_field;
}

void CGlass::ProcessCollisions(glm::ivec2 & newPos, glm::ivec2 const & oldPos)
{
	auto shape = m_figure->GetForm();
	auto size = m_figure->GetSize();

	newPos.x = (newPos.x < FIELD_WIDTH - size.x) ? newPos.x : FIELD_WIDTH - size.x - 1;
	newPos.x = (newPos.x <= 0) ? newPos.x + size.x / 2: newPos.x ;
	newPos.y = ((newPos.y < FIELD_HEIGHT - size.y) ? newPos.y : FIELD_HEIGHT - size.y - 1);

	bool canRotate = true;
	for (float height = 1; height <= size.y; ++height)
	{
		for (float width = -size.y / 2; width < size.y / 2 + 1; ++width)
		{

			if (!(width + newPos.x < FIELD_WIDTH - 1 && width + newPos.x > 0) || !(height + newPos.y < FIELD_HEIGHT))
			{
				continue;
			}
			auto nextSymbol = m_field[newPos.y + height][newPos.x + width];
			//std::cout << "Pos " << newPos.x + width << " " << newPos.y + height << std::endl;
			if (nextSymbol == UsingSymbols::SYMBOL_STATIC_FIGURE || nextSymbol == UsingSymbols::SYMBOL_WALL)
			{
				canRotate = false;
			}
		}
	}
	//std::cout << canRotate << std::endl;

	m_figure->CanRotate(canRotate);

	for (size_t height = 0; height < shape.size(); ++height)
	{
		for (size_t width = 0; width < shape[height].size(); ++width)
		{
			if (shape[height][width] == UsingSymbols::SYMBOL_EMPTY_SPACE)
			{				
				continue;
			}
			
			auto line = m_field[newPos.y + height];
			auto nextSymbol = line[newPos.x + width];
			if (nextSymbol == UsingSymbols::SYMBOL_STATIC_FIGURE || nextSymbol == UsingSymbols::SYMBOL_WALL)
			{
				newPos.x = oldPos.x;
			}
			auto x = (oldPos.x <= 0) ? 0 : oldPos.x;
			nextSymbol = line[x + width];
			if (nextSymbol == UsingSymbols::SYMBOL_STATIC_FIGURE || nextSymbol == UsingSymbols::SYMBOL_WALL)
			{
				newPos.y = oldPos.y;
			}
		}		
	}	
}

glm::ivec2 CGlass::GetNextPosition(glm::ivec2 const & oldPos) const
{
	auto nexPos = oldPos;

	switch (m_figure->GetTypeMove())
	{
	case TypeMove::Direction::Left:
		nexPos.x = (--nexPos.x > 0 ? nexPos.x : 1);
		break;
	case TypeMove::Direction::Right:
		nexPos.x = (++nexPos.x < FIELD_WIDTH ? nexPos.x : FIELD_WIDTH - 1);
		break;
	}
	nexPos.y = (++nexPos.y < FIELD_HEIGHT ? nexPos.y : FIELD_HEIGHT - 1);
	m_figure->SetTypeMove(TypeMove::Direction::None);
	return nexPos;
}
