#pragma once
#include "IDrawable.h"
#include <boost/noncopyable.hpp>

class CDrawableObject : public IDrawable, private boost::noncopyable
{
public:
	CDrawableObject() = default;
	virtual ~CDrawableObject();
	void Draw() const override;
protected:
	void DeleteList();
	virtual void Redraw() const = 0;

	mutable unsigned m_displayList = 0;
};

