#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include <glm/vec2.hpp>

class CDescartesSystem : private boost::noncopyable
{
public:
	CDescartesSystem() = default;
	~CDescartesSystem();
	void SetupSystem(glm::ivec2 const & pos);
	void Draw();

private:
	void Redraw();
	void InitSystem(); 
	void CreateSegment(glm::vec2 const &pos, float w, float h, float stepX, float stepY, int count);
	void DrawArrowOnPoints(glm::vec2 const &point1, glm::vec2 const &point2, glm::vec2 const &point3);
	std::vector<CRectangle> m_systems;
	glm::vec2 m_pos;
};

