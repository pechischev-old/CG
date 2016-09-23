#pragma once
#include "stdafx.h"
#include <boost\noncopyable.hpp>
#include "GameSystem.h"
#include "view\DrawableObject.h"

class CShedule :  private boost::noncopyable
			    
{
public:
	CShedule(unsigned int width, unsigned int height);
	~CShedule();

	void Update(float deltaSeconds);
	void SetSizeWindow(unsigned int width, unsigned int height);
	bool OnKeyDown(const SDL_KeyboardEvent &event);
	bool OnKeyUp(const SDL_KeyboardEvent & event);
	void Draw();
private:
	CGameSystem m_system;
	unsigned int m_windowWidth = 0;
	unsigned int m_windowHeigth = 0;
};

