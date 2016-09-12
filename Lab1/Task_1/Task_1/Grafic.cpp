#include "stdafx.h"
#include "Grafic.h"


CGrafic::CGrafic(glm::vec2 const & pos, float scale)
	: m_pos(pos)
	, m_scale(scale)
{
}

CGrafic::~CGrafic()
{
}

void CGrafic::SetupShape(glm::vec2 const & pos, float scale)
{
	CDrawableObject::DeleteList();
	m_pos = pos;
	m_scale = scale;
}

void CGrafic::Redraw() const
{
	const float step = float(2 * M_PI / 360);

	glLineWidth(2.f);
	glColor3f(1, 1, 1);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle < float(2 * M_PI); angle += step)
	{
		const float r = m_scale * (1 - cosf(angle));
	
		glVertex2f(r * cosf(angle) + m_pos.x, r * sinf(angle) + m_pos.y);
	}
	glEnd();
}
