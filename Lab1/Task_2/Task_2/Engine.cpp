#include "stdafx.h"
#include "Engine.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Parser.h"



CEngine::CEngine()
{
	CParser parser("input.json");
	InitEngine(parser.GetShapesData());
}

CEngine::~CEngine()
{
}

void CEngine::Draw()
{
	for (auto &it : m_segments)
	{
		it->Draw();
	}
}

void CEngine::Redraw()
{
	for (auto &it : m_segments)
	{
		it->Draw();
	}
}

void CEngine::InitEngine(std::vector<SShape> const & data)
{
	for (auto const &shape : data)
	{
		if (shape.type == "rectangle")
		{
			auto rect = std::make_shared<CRectangle>();
			rect->SetupShape(shape.pos, shape.size.x, shape.size.y, shape.color);
			m_segments.push_back(rect);
		}
		else if (shape.type == "circle")
		{
			auto rect = std::make_shared<CCircle>();
			rect->SetupShape(shape.pos, shape.size.x, shape.color);
			m_segments.push_back(rect);
		}
	}
}
