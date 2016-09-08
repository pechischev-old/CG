#include "stdafx.h"
#include "Engine.h"
#include "Circle.h"
#include "Rectangle.h"



CEngine::~CEngine()
{
}

void CEngine::SetupEngine(glm::vec2 const & pos)
{
	ClearArray();
	m_pos = pos;
}

void CEngine::Draw()
{
	if (m_segments.empty())
	{
		InitEngine();
	}
	Redraw();
}

void CEngine::Redraw()
{
	for (auto &it : m_segments)
	{
		it->Draw();
	}
}

void CEngine::ClearArray()
{
	m_segments.erase(m_segments.begin(), m_segments.end());
}

void CEngine::InitEngine()
{
	auto rect = std::make_shared<CRectangle>();
	rect->SetupShape(m_pos, 150, 250, {0.f, 0.f, 0.f});
	m_segments.push_back(rect);


	auto rect2 = std::make_shared<CRectangle>();
	rect2->SetupShape(m_pos, 120, 220, {1.f, 1.f, 1.f});
	m_segments.push_back(rect2);
}
