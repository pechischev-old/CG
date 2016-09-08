#include "stdafx.h"
#include "Circle.h"


CCircle::~CCircle()
{
}

void CCircle::SetupShape(glm::vec2 const & pos, float radius, glm::vec3 const & color)
{
	CDrawableObject::DeleteList();
	m_pos = pos;
	m_radius = radius;
	m_color = color;
}

void CCircle::Redraw() const
{
	const float step = float(2 * M_PI) / 360;

	glColor3f(m_color.x, m_color.y, m_color.z);
	
	glBegin(GL_TRIANGLE_FAN);
	
	glVertex2f(m_pos.x, m_pos.y);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = m_radius * cosf(a);
		const float dy = m_radius * sinf(a);
		glVertex2f(dx + m_pos.x, dy + m_pos.y);
	}
	glEnd();
}
