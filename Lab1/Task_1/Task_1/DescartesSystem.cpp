#include "stdafx.h"
#include "DescartesSystem.h"

static const float STEP_DIVIDERS = 25.f;
static const int COUNT_DIVIDERS_ON_HALF_X = 18;
static const int COUNT_DIVIDERS_ON_HALF_Y = 14;


CDescartesSystem::~CDescartesSystem()
{
}

void CDescartesSystem::SetupSystem(glm::ivec2 const & pos)
{
	ClearVector();
	m_pos = {pos.x / 2, pos.y / 2};
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
		it->Draw();
	}
}

void CDescartesSystem::ClearVector()
{
	m_systems.erase(m_systems.begin(), m_systems.end());
}


void CDescartesSystem::InitSystem()
{
	CreateSegment(m_pos, 4, m_pos.y * 2, 0, 0, 1);
	CreateSegment(m_pos, m_pos.x * 2, 4, 0, 0, 1);
	CreateSegment(m_pos, 4, 10, STEP_DIVIDERS, 0, COUNT_DIVIDERS_ON_HALF_X);
	CreateSegment(m_pos, 4, 10, -STEP_DIVIDERS, 0, COUNT_DIVIDERS_ON_HALF_X);
	CreateSegment(m_pos, 10, 4, 0, STEP_DIVIDERS, COUNT_DIVIDERS_ON_HALF_Y);
	CreateSegment(m_pos, 10, 4, 0, -STEP_DIVIDERS, COUNT_DIVIDERS_ON_HALF_Y);
}

void CDescartesSystem::CreateSegment(glm::vec2 const &pos, float w, float h, float stepX, float stepY, int count)
{
	for (auto i = 0; i < count; ++i)
	{
		auto segment = std::make_shared<CRectangle>();
		segment->SetupShape({ pos.x + stepX * i, pos.y + stepY * i }, w, h);
		m_systems.push_back(segment);
	}
}
