#include "stdafx.h"
#include "DescartesSystem.h"

static const float STEP_DIVIDERS = 25.f;
static const int COUNT_DIVIDERS_ON_HALF_X = 16;
static const int COUNT_DIVIDERS_ON_HALF_Y = 12;


CDescartesSystem::~CDescartesSystem()
{
}

void CDescartesSystem::SetupSystem(glm::ivec2 const & pos)
{
	m_systems.clear();
	m_pos = {pos.x / 2, pos.y / 2};	
	static_assert(sizeof(CRectangle) == 24, "wrong size");
}

void CDescartesSystem::Draw() 
{
	if (m_systems.empty())
	{
		InitSystem();
	}
	Redraw();
}

void CDescartesSystem::Redraw() 
{
	for (auto &it : m_systems)
	{
		it.Draw();
	}
}


void CDescartesSystem::InitSystem()
{
	CreateSegment(m_pos, 4, m_pos.y * 2, 0, 0, 1);
	CreateSegment(m_pos, m_pos.x * 2, 4, 0, 0, 1);
	CreateSegment(m_pos, 4, 10, STEP_DIVIDERS, 0, COUNT_DIVIDERS_ON_HALF_X);
	CreateSegment(m_pos, 4, 10, -STEP_DIVIDERS, 0, COUNT_DIVIDERS_ON_HALF_X);
	CreateSegment(m_pos, 10, 4, 0, STEP_DIVIDERS, COUNT_DIVIDERS_ON_HALF_Y);
	CreateSegment(m_pos, 10, 4, 0, -STEP_DIVIDERS, COUNT_DIVIDERS_ON_HALF_Y);

	DrawArrowOnPoints({ m_pos.x, -1 }, { m_pos.x - 10, 10 }, { m_pos.x + 10, 10 });
	DrawArrowOnPoints({ m_pos.x * 2 + 1, m_pos.y }, { m_pos.x * 2 - 10, m_pos.y + 10 }, { m_pos.x * 2 - 10, m_pos.y - 10 });
}

void CDescartesSystem::CreateSegment(glm::vec2 const &pos, float w, float h, float stepX, float stepY, int count)
{
	for (int i = 0; i < count; ++i)
	{
		m_systems.emplace_back(glm::vec2{ pos.x + stepX * i, pos.y + stepY * i }, w, h);
	}
}

void CDescartesSystem::DrawArrowOnPoints(glm::vec2 const &point1, glm::vec2 const &point2, glm::vec2 const &point3)
{
	
	glBegin(GL_TRIANGLES);
	glColor3d(0, 0, 0);      // ������ �����������
	glVertex2f(point1.x, point1.y);
	glVertex2f(point2.x, point2.y);
	glVertex2f(point3.x, point3.y);
	glEnd();
}
