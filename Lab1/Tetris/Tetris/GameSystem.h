#pragma once
#include "Tetris.h"
#include "TetrisController.h"
#include "GlassView.h"

class CGameSystem
{
public:
	CGameSystem();
	~CGameSystem();

	void Update(float deltaSeconds);
	bool OnKeyDown(const SDL_KeyboardEvent & event);
	bool OnKeyUp(const SDL_KeyboardEvent & event);
	void SetSizeWindow(unsigned int width, unsigned int height);
	void Draw();
private:
	CTetris m_tetris;
	CGlassView m_glassView;
	std::unique_ptr<CTetrisController> m_control = nullptr;
};

