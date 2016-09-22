#include "stdafx.h"
#include "Shedule.h"


CShedule::CShedule(unsigned int width, unsigned int height)
	: m_windowWidth(width)
	, m_windowHeigth(height)
{
}


CShedule::~CShedule()
{
}

void CShedule::Update(float deltaSeconds)
{
	m_system.Update(deltaSeconds);
}

void CShedule::SetSizeWindow(unsigned int width, unsigned int height)
{
	m_windowWidth = width;
	m_windowHeigth = height;
}

bool CShedule::OnKeyDown(const SDL_KeyboardEvent & event)
{
	return m_system.OnKeyDown(event);
}

bool CShedule::OnKeyUp(const SDL_KeyboardEvent & event)
{
	return m_system.OnKeyUp(event);
}

void CShedule::Draw() const
{
	m_system.Draw();
}
