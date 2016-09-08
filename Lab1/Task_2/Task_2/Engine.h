#pragma once
#include "stdafx.h"
#include "DrawableObject.h"


class CEngine
{
public:
	CEngine() = default;
	~CEngine();

	void SetupEngine(glm::vec2 const & pos);
	void Draw();
private:
	void Redraw();
	void ClearArray();
	void InitEngine();

	glm::vec2 m_pos;
	std::vector<std::shared_ptr<CDrawableObject>> m_segments;
};

