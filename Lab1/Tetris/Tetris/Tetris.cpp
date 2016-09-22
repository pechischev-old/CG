#include "Tetris.h"
#include "Forms.h"
#include <random>
#include <iostream>

using namespace std;

namespace
{

}

int GetRandomNumberForSection(int begin, int end) 
{
	assert(begin < end);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(begin, end);
	return dist(gen);
}

CTetris::CTetris()
{
	ResetState();
}


CTetris::~CTetris()
{
}

bool CTetris::Update(float deltaSeconds)
{
	if (m_isFull) 
	{
		return false;
	}
	m_time += deltaSeconds;
	if (m_time >= m_speed)
	{
		if (!m_glassModel.CanMoveFigure())
		{
			m_glassModel.ClearFullLine();
			m_isFull = m_glassModel.HasFull();
			IncreaseGameValue();
			InitFigure();
			CalculateNextFigure();
		}
		m_glassModel.MoveFigure();
		m_time = 0;
	}
	return true;
}

void CTetris::SetAction(TetrisAction::Action const & action)
{
	if (!m_pFigure)
	{
		return;
	}
	switch (action)
	{
	case TetrisAction::Action::rotate:
		m_pFigure->Rotate();
		break;
	case TetrisAction::Action::left:
		m_pFigure->SetTypeMove(TypeMove::Left);
		break;
	case TetrisAction::Action::right:
		m_pFigure->SetTypeMove(TypeMove::Right);
		break;
	case TetrisAction::Action::boostDown:
		if (m_isBoost) 
		{
			break;
		}
		m_speed /= 3.f;
		m_isBoost = true;
		break;
	case TetrisAction::Action::none:
		m_speed *= 3.f;
		m_isBoost = false;
		break;
	}
}

void CTetris::ResetState()
{
	m_isFull = false;
	m_speed = 0.035f;
	m_time = 0.f;
	m_glassModel = CGlass();
	m_info.level = 1;
	m_info.lineLeft = 0;
	m_info.lineTarget = 10;
	m_info.scope = 0;
	CalculateNextFigure();
}

void CTetris::InitFigure()
{
	auto nameFigure = FormsFigures::namesFigures[m_info.nextFigure];
	m_pFigure = std::make_unique<CFigure>(FormsFigures::formsFiqures[nameFigure]);
	m_glassModel.SetFigure(m_pFigure.get());
}

void CTetris::CalculateNextFigure()
{
	auto namesFigures = FormsFigures::namesFigures;
	m_info.nextFigure = GetRandomNumberForSection(0, namesFigures.size() - 1);
}

void CTetris::IncreaseGameValue()
{
	if (m_info.lineLeft == m_info.lineTarget)
	{
		++m_info.level;
		m_info.lineTarget += 5;
		m_info.lineLeft = 0;
		m_info.scope = m_glassModel.GetCountEmptyLine() * 10;
		m_glassModel = CGlass();
	}
	else
	{
		auto countRemovedLine = m_glassModel.GetCountDeletedLines();
		m_info.lineLeft += countRemovedLine;
		switch (countRemovedLine) 
		{
		case 1:
			m_info.scope += 10;
			break;
		case 2:
			m_info.scope += 30;
			break;
		case 3:
			m_info.scope += 70;
			break;
		case 4:
			m_info.scope += 150;
			break;
		}
	}
}
