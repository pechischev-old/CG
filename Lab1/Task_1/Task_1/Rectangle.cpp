#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(glm::vec2 const & pos, float width, float height)
	: m_pos(pos)
	, m_width(width)
	, m_height(height)
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::SetupShape(glm::vec2 const & pos, float width, float height)
{
	CDrawableObject::DeleteList();
	m_pos = pos;
	m_width = width;
	m_height = height;
}

void CRectangle::Redraw() const
{
	glColor3f(0.f, 0.f, 0.f);
	glRectf(m_pos.x - m_width / 2, m_pos.y - m_height / 2, m_pos.x + m_width / 2, m_pos.y + m_height / 2);
}
