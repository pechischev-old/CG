#pragma once
#include <boost\noncopyable.hpp>
#include <glm\vec2.hpp>
#include "view\Rectangle.h"
#include "Glass.h"
#include "Observer.h"

class CGlassView : public IObserver<Field>, private boost::noncopyable
{
public:
	CGlassView() = default;
	~CGlassView();

	void SetupGlass(glm::vec2 const & pos);
	void Draw();
	void Update(Field const & glass) override;
private:
	void Redraw();
	void InitGlass();
private:
	glm::vec2 m_pos;
	std::vector<CRectangle> m_system;
	Field m_glass;
};

