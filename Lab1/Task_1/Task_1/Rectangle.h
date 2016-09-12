#pragma once
#include <glm/vec2.hpp>
#include "DrawableObject.h"


class CRectangle : public CDrawableObject
{
public:
	CRectangle(glm::vec2 const & pos, float width, float height);
	CRectangle(CRectangle && obj) = default;
	CRectangle(CRectangle const & obj) = delete;
	CRectangle& operator =(CRectangle && obj) = default;
	CRectangle& operator =(CRectangle const & obj) = delete;
	~CRectangle();

	void SetupShape(glm::vec2 const & pos, float width, float height);

private:
	void Redraw() const override;

	float m_width;
	float m_height;
	glm::vec2 m_pos;
};

