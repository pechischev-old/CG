#pragma once
#include <vector>
#include <string>
#include <boost\noncopyable.hpp>
#include "Figure.h"
#include "Observer.h"
#include <memory>

using Field = std::vector<std::vector<char>>;


namespace UsingSymbols
{
	
	static const char SYMBOL_WALL = '1';
	static const char SYMBOL_STATIC_FIGURE = '@';
	static const char SYMBOL_EMPTY_SPACE = ' ';
}

class CGlass : public CObservable<Field>
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

	void FieldChanged();
protected:
	Field GetChangedData()const override;
private:
	void FillField();
	void ProcessCollisions(glm::ivec2 & newPos, glm::ivec2 const & oldPos );
	glm::ivec2 GetNextPosition(glm::ivec2 const & oldPos ) const;
private:
	bool m_isFull = false;
	int m_numberDeletedLines = 0;
	std::vector<char> m_emptyLine;
	Field m_field;
	Field m_copyField;
	CFigure* m_figure = nullptr;
};

