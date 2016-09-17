#pragma once
#include <boost\noncopyable.hpp>
#include <glm\vec2.hpp>

namespace TypeMove
{
	enum Direction
	{
		Left,
		Right,
		Down
	};
}

class CFigure : private boost::noncopyable
{
public:
	CFigure();
	~CFigure();

	void SetTypeMove(TypeMove::Direction const & type);
	void Rotate();
	void SetPosition(glm::vec2 const & pos);
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
private:
	glm::vec2 m_pos;
	unsigned m_width;
	unsigned m_height;
	TypeMove::Direction m_type;
};

