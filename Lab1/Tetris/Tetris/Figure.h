#pragma once
#include <boost\noncopyable.hpp>
#include <glm\vec2.hpp>
#include <vector>
#include <string>

namespace TypeMove
{
	enum Direction
	{
		None,
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
	void SetPosition(glm::ivec2 const & pos);
	glm::ivec2 GetPosition() const;
	glm::ivec2 GetSize() const;
	std::vector<std::string> GetForm() const;
private:
	void CalculateSize();
	void MakeCurrentForm();
private:
	glm::ivec2 m_pos;
	unsigned m_width = 0;
	unsigned m_height = 0;
	TypeMove::Direction m_type = TypeMove::Direction::None;
	std::vector<std::string> m_currentForm;
	Forms m_forms;
};

