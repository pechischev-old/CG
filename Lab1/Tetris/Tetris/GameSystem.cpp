#include "stdafx.h"
#include "GameSystem.h"

using namespace std;

CGameSystem::CGameSystem()
{
	m_formsFiqures = { { "square", { { "##", "##" }} },
					   { "line", {{ "####" }, { "#", "#", "#", "#" }} } };
	
	/*for (auto key : m_formsFiqures)
	{
		for (auto forms : key.second)
		{
			for (auto form : forms)
			{
				cout << form << endl;
			}
		}
		cout << endl;
	}*/
}


CGameSystem::~CGameSystem()
{
}

void CGameSystem::Update(float deltaSeconds)
{
	m_time += deltaSeconds;
	if (m_time >= 0.15)
	{
		if (!m_glassModel.CanMoveFigure())
		{
			CreateFigure();
		}
		m_glassModel.MoveFigure();
		m_glassModel.ClearFullLine();
		
		m_time = 0;
	}
}

void CGameSystem::CreateFigure()
{
	m_pFigure = std::make_shared<CFigure>(m_formsFiqures["line"]);
	m_glassModel.SetFigure(m_pFigure.get());
}

bool CGameSystem::OnKeyDown(const SDL_KeyboardEvent & event)
{
	if (m_pFigure)
	{
		switch (event.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			m_pFigure->SetTypeMove(TypeMove::Direction::Left);
			return true;
		case SDLK_RIGHT:
		case SDLK_d:
			m_pFigure->SetTypeMove(TypeMove::Direction::Right);
			return true;
		case SDLK_UP:
		case SDLK_w:
			m_pFigure->Rotate();
			return true;
		case SDLK_DOWN:
		case SDLK_s:
			m_pFigure->SetTypeMove(TypeMove::Direction::Down);
			return true;
		}
	}
	return false;
}
