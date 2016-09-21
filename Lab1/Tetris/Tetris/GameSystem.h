#pragma once
#include <map>
#include <vector>
#include "GlassModel.h"
#include "Figure.h"
#include <memory>

using FormsFigures = std::map<std::string, std::vector<std::vector<std::string>>>;

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
	float m_time = 0;
	float m_speed = 0.03f;
	bool m_isPause = false;
	FormsFigures m_formsFiqures;
	CGlassModel m_glassModel;
	std::shared_ptr<CFigure> m_pFigure;
};

