#include "stdafx.h"
#include "Rectangle.h"


CRectangle::~CRectangle()
{
}

void CRectangle::SetupShape(glm::vec2 const & pos, float width, float height, glm::vec3 const & color)
{
	CDrawableObject::DeleteList();
	m_pos = pos;
	m_width = width;
	m_height = height;
	m_color = color;
}

void CRectangle::Redraw() const
{
	glColor3f(m_color.x, m_color.y, m_color.z);
	glRectf(m_pos.x - m_width / 2, m_pos.y - m_height / 2, m_pos.x + m_width / 2, m_pos.y + m_height / 2);
}
