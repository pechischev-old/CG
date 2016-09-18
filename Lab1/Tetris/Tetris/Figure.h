#pragma once
#include <boost\noncopyable.hpp>
#include <glm\vec2.hpp>
#include <vector>
#include <string>

namespace TypeMove
{
	enum Direction
	{
		Left,
		Right,
		Down
	};
}
using Forms = std::vector<std::vector<std::string>>;

class CFigure : private boost::noncopyable
{
public:
	CFigure(Forms const & forms);
	~CFigure();

	void SetTypeMove(TypeMove::Direction const & type);
	TypeMove::Direction GetTypeMove() const;
	void Rotate();
	void SetPosition(glm::vec2 const & pos);
	glm::vec2 GetPosition() const;
	glm::vec2 GetSize() const;
private:
	void CalculateSize();
	void MakeCurrentForm();
private:
	glm::vec2 m_pos;
	unsigned m_width = 0;
	unsigned m_height = 0;
	TypeMove::Direction m_type = TypeMove::Direction::Down;
	std::vector<std::string> m_currentForm;
	Forms m_forms;
};

