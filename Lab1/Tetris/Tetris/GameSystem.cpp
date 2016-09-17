#include "stdafx.h"
#include "GameSystem.h"


CGameSystem::CGameSystem()
{
}


CGameSystem::~CGameSystem()
{
}

void CGameSystem::Update(float deltaSeconds)
{
}

void CGameSystem::CreateFigure()
{
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
