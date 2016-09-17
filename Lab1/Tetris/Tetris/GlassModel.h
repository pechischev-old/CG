#pragma once
#include <vector>
#include <string>
#include <boost\noncopyable.hpp>

class CGlassModel : private boost::noncopyable
{
public:
	CGlassModel();
	~CGlassModel();
	void ClearFullLine();
	void MoveFigure();
	void SetFigure();
private:
	void FillField();
private:
	std::vector<std::vector<char>> m_field;
	std::vector<std::vector<char>> m_copyField;

};

