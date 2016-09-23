#include "../stdafx.h"
#include "Rectangle.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


CRectangle::CRectangle(glm::vec2 const & pos, float width, float height, glm::vec3 const & color)
	: m_pos(pos)
	, m_width(width)
	, m_height(height)
	, m_color(color)
{
}

CRectangle::~CRectangle()
{
}

void CRectangle::Redraw() const
{
	glm::vec3 offset = { m_pos.x, m_pos.y , 0.f };
	glm::vec3 shapeOrigin = { m_width / 2,  m_height / 2, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	
	transform = glm::translate(transform, -shapeOrigin);

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));

	glColor3f(m_color.x, m_color.y, m_color.z);
	glRectf( 0, 0, m_width, m_height);

	glPopMatrix();
}
