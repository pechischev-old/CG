#pragma once
#include "stdafx.h"
#include "DrawableObject.h"


class CEngine
{
public:
	CEngine();
	~CEngine();

	void Draw();
private:
	void Redraw();
	void InitEngine(std::vector<SShape> const & data);

	glm::vec2 m_pos;
	std::vector<std::shared_ptr<CDrawableObject>> m_segments;
};

