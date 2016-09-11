#pragma once
#include <glm/vec2.hpp>
#include "DrawableObject.h"


class CRectangle : public CDrawableObject
{
public:
	CRectangle() = default;
	~CRectangle();

	void SetupShape(glm::vec2 const & pos, float width, float height);

private:
	void Redraw() const override;

	glm::vec2 m_pos;
	float m_width;
	float m_height;
};

