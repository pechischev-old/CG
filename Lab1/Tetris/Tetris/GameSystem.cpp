#include "stdafx.h"
#include "GameSystem.h"
#include "random"

using namespace std;


CGameSystem::CGameSystem()
{
	m_control = std::make_unique<CTetrisController>(&m_tetris);
}


CGameSystem::~CGameSystem()
{
}

void CGameSystem::Update(float deltaSeconds)
{
	m_control->Update(deltaSeconds);
}


bool CGameSystem::OnKeyDown(const SDL_KeyboardEvent & event)
{
	
	return m_control->OnKeyDown(event);
}

bool CGameSystem::OnKeyUp(const SDL_KeyboardEvent & event)
{
	return m_control->OnKeyUp(event);
}

void CGameSystem::Draw() const
{
}
