#pragma once
#include "DrawableObject.h"
#include <glm/vec2.hpp>


class CGrafic : public CDrawableObject
{
public:
	CGrafic() = default;
	~CGrafic();

	void SetupShape(glm::vec2 const & pos, float m_scale);

private:
	void Redraw()const override;

	glm::vec2 m_pos;
	float m_scale;
};

