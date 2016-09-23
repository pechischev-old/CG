#include "stdafx.h"
#include "GameSystem.h"
#include "random"

using namespace std;


CGameSystem::CGameSystem()
{
	m_tetris.GetGlass()->RegisterObserver(m_glassView);
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

void CGameSystem::SetSizeWindow(unsigned int width, unsigned int height)
{
	m_glassView.SetupGlass(glm::vec2{ width / 2, height / 2 });
}

void CGameSystem::Draw() 
{
	m_glassView.Draw();
}
