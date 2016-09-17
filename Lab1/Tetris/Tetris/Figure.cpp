#include "Figure.h"



CFigure::CFigure()
{
}


CFigure::~CFigure()
{
}

void CFigure::SetTypeMove(TypeMove::Direction const & type)
{
	m_type = type;
}

void CFigure::Rotate()
{
}

void CFigure::SetPosition(glm::vec2 const & pos)
{
	m_pos = pos;
}

glm::vec2 CFigure::GetPosition()
{
	return glm::vec2();
}

glm::vec2 CFigure::GetSize()
{
	return glm::vec2(m_width, m_height);
}
