#include "stdafx.h"
#include "Rectangle.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


CRectangle::~CRectangle()
{
}

void CRectangle::SetupShape(glm::vec2 const & pos, float width, float height, glm::vec3 const & color, float angle)
{
	CDrawableObject::DeleteList();
	m_pos = pos;
	m_width = width;
	m_height = height;
	m_color = color;
	m_angle = angle;
}

void CRectangle::Redraw() const
{
	glm::vec3 offset = { m_pos.x, m_pos.y , 0.f };
	glm::vec3 shapeOrigin = { m_width / 2,  m_height / 2, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	
	transform = glm::rotate(transform, m_angle, glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));

	glColor3f(m_color.x, m_color.y, m_color.z);
	glRectf( 0, 0, m_width, m_height);

	glPopMatrix();
}
