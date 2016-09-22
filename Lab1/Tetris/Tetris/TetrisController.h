#pragma once
#include "Tetris.h"
#include <SDL2\SDL_events.h>

class CTetrisController
{
public:
	CTetrisController(CTetris* m_tetris);
	~CTetrisController();
	void Update(float deltaSeconds);
	bool OnKeyDown(const SDL_KeyboardEvent & event);
	bool OnKeyUp(const SDL_KeyboardEvent & event);
private:
	bool m_isPause = false;
	CTetris *m_pTetris;
};

