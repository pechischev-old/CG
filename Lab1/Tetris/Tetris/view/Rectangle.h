#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "DrawableObject.h"


class CRectangle : public CDrawableObject
{
public:
	CRectangle(glm::vec2 const & pos, float width, float height, glm::vec3 const & color, float angle);
	CRectangle(CRectangle && obj) = default;
	CRectangle(CRectangle const & obj) = delete;
	CRectangle& operator =(CRectangle && obj) = default;
	CRectangle& operator =(CRectangle const & obj) = delete;
	~CRectangle();

private:
	void Redraw() const override;

	glm::vec2 m_pos;
	glm::vec3 m_color;
	float m_width;
	float m_height;
	float m_angle;
};

