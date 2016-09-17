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

void CShedule::Redraw() const
{
}