#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "DrawableObject.h"


class CCircle : public CDrawableObject
{
public:
	CCircle() = default;
	~CCircle();

	void SetupShape(glm::vec2 const & pos, float radius, glm::vec3 const & color);

private:
	void Redraw() const override;

	glm::vec2 m_pos;
	glm::vec3 m_color;
	float m_radius;
};


