#include "TetrisController.h"



CTetrisController::CTetrisController(CTetris* tetris)
	: m_pTetris(tetris)
{
}


CTetrisController::~CTetrisController()
{
}

void CTetrisController::Update(float deltaSeconds)
{
	if (m_isPause)
	{
		return;
	}
	if (!m_pTetris->Update(deltaSeconds))
	{
		// TODO: переключение окна
	}
}

bool CTetrisController::OnKeyDown(const SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym)
	{
	case SDLK_LEFT:
	case SDLK_a:
		m_pTetris->SetAction(TetrisAction::Action::left);
		return true;
	case SDLK_RIGHT:
	case SDLK_d:
		m_pTetris->SetAction(TetrisAction::Action::right);
		return true;
	case SDLK_UP:
	case SDLK_w:
		m_pTetris->SetAction(TetrisAction::Action::rotate);
		return true;
	case SDLK_DOWN:
	case SDLK_s:
		m_pTetris->SetAction(TetrisAction::Action::boostDown);
		return true;
	}
	return false;
}

bool CTetrisController::OnKeyUp(const SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym)
	{
	case SDLK_DOWN:
	case SDLK_s:
		m_pTetris->SetAction(TetrisAction::Action::none);
		return true;
	case SDLK_p:
		m_isPause = !m_isPause;
		return true;
	}
	return false;
}
