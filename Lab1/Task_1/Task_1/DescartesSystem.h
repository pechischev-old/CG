#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include <glm/vec2.hpp>

class CDescartesSystem 
{
public:
	CDescartesSystem() = default;
	~CDescartesSystem();
	void SetupSystem(glm::ivec2 const & pos);
	void Draw();

private:
	void Redraw();
	void ClearVector();
	void InitSystem(); 
	void CreateSegment(glm::vec2 const &pos, float w, float h, float stepX, float stepY, int count);

	std::vector<std::shared_ptr<CRectangle>> m_systems;
	glm::vec2 m_pos;
};

