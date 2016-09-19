#pragma once
#include "IDrawable.h"
#include <boost/noncopyable.hpp>

class CDrawableObject : public IDrawable
{
public:
	CDrawableObject() = default;
	CDrawableObject(CDrawableObject && obj) = default;
	CDrawableObject(CDrawableObject const & obj) = delete;
	CDrawableObject& operator =(CDrawableObject && obj) = default;
	CDrawableObject& operator =(CDrawableObject const & obj) = delete;

	virtual ~CDrawableObject();
	void Draw() const override;
	void SetSizeWindow(glm::ivec2 const &size);
protected:
	void DeleteList();
	virtual void Redraw() const = 0;

	mutable unsigned m_displayList = 0;
	glm::ivec2 m_sizeWindow;
};

