#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "DrawableObject.h"


class CCircle : public CDrawableObject
{
public:
	CCircle(glm::vec2 const & pos, float radius, glm::vec3 const & color);
	CCircle(CCircle && obj) = default;
	CCircle(CCircle const & obj) = delete;
	CCircle& operator =(CCircle && obj) = default;
	CCircle& operator =(CCircle const & obj) = delete;
	~CCircle();

	
private:
	void Redraw() const override;
	void Scale();

	glm::vec2 m_pos;		
	glm::vec3 m_color;
	float m_radius;
};


