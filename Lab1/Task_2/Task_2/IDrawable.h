#pragma once

class IDrawable
{
public:
	virtual void Draw() const = 0;
protected:
	virtual void Redraw() const = 0;
};