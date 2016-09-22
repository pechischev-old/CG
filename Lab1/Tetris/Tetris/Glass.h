#pragma once
#include <vector>
#include <string>
#include <boost\noncopyable.hpp>
#include "Figure.h"
#include <memory>

class CGlass
{
public:
	CGlass();
	~CGlass();
	void ClearFullLine();
	void MoveFigure();
	void SetFigure(CFigure* figure);
	bool CanMoveFigure();
	int GetCountDeletedLines() const;
	int GetCountEmptyLine() const;
	bool HasFull() const;
private:
	void FillField();
	void ProcessCollisions(glm::ivec2 & newPos, glm::ivec2 const & oldPos );
	glm::ivec2 GetNextPosition(glm::ivec2 const & oldPos ) const;
private:
	bool m_isFull = false;
	int m_numberDeletedLines = 0;

	std::vector<std::vector<char>> m_field;
	std::vector<std::vector<char>> m_copyField;
	std::vector<char> m_emptyLine;
	CFigure* m_figure = nullptr;
};

