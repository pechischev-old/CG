#include "Figure.h"
#include <algorithm>


CFigure::CFigure(Forms const & forms)
	: m_forms(forms)
{
	MakeCurrentForm();
	CalculateSize();
}

CFigure::~CFigure()
{
}

void CFigure::SetTypeMove(TypeMove::Direction const & type)
{
	m_type = type;
}

TypeMove::Direction CFigure::GetTypeMove() const
{
	return m_type;
}

void CFigure::Rotate()
{
	if (!m_canRotate)
	{
		return;
	}
	m_forms.push_back(m_currentForm);
	MakeCurrentForm();

	m_pos.x = (m_height > m_width) ? m_pos.x - m_height / 2  : m_pos.x + m_width / 2;
	CalculateSize();
}

void CFigure::SetPosition(glm::ivec2 const & pos)
{
	m_pos = pos;
}

void CFigure::CanRotate(bool canRotate)
{
	m_canRotate = canRotate;
}

glm::ivec2 CFigure::GetPosition() const
{
	return m_pos;
}

glm::ivec2 CFigure::GetSize() const
{
	return glm::ivec2(m_width, m_height);
}

std::vector<std::string> CFigure::GetForm() const
{
	return m_currentForm;
}

void CFigure::CalculateSize()
{
	m_height = m_currentForm.size();
	m_width = 0;
	for (auto const & line : m_currentForm)
	{
		m_width = std::max(m_width, line.size());
	}
}

void CFigure::MakeCurrentForm()
{
	m_currentForm = m_forms.front();
	m_forms.erase(m_forms.begin(), ++m_forms.begin());
}
