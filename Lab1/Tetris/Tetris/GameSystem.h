#pragma once
#include "model\Parser.h"
#include <map>
#include <vector>
#include "GlassModel.h"
#include "Figure.h"

class CGameSystem
{
public:
	CGameSystem();
	~CGameSystem();

	void Update(float deltaSeconds);
	bool OnKeyDown(const SDL_KeyboardEvent & event);
protected:
	void CreateFigure();
private:
	std::map<std::string, std::vector<std::vector<std::string>>> m_formsFiqures;
	CGlassModel m_glassModel;
	CFigure* m_pFigure = nullptr;
};

