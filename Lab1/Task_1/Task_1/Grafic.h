#pragma once
#include "DrawableObject.h"
#include <glm/vec2.hpp>


class CGrafic : public CDrawableObject
{
public:
	CGrafic(glm::vec2 const & pos, float scale);
	CGrafic(CGrafic && obj) = default;
	CGrafic(CGrafic const & obj) = delete;
	CGrafic& operator =(CGrafic && obj) = default;
	CGrafic& operator =(CGrafic const & obj) = delete;
	~CGrafic();

	void SetupShape(glm::vec2 const & pos, float m_scale);

private:
	void Redraw()const override;

	glm::vec2 m_pos;
	float m_scale;
};

