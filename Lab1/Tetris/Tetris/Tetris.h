#pragma once
#include <memory>
#include "Glass.h"
#include "Figure.h"

namespace TetrisAction
{
	enum Action
	{
		none,
		left,
		right,
		boostDown,
		rotate
	};
}

struct InfoPanel
{
	int level;
	int lineTarget;
	int lineLeft;
	int scope;
	int nextFigure;
};

class CTetris
{
public:
	CTetris();
	~CTetris();
	bool Update(float deltaSeconds);
	void SetAction(TetrisAction::Action const & action);
	void ResetState();
private:
	void InitFigure();
	void CalculateNextFigure();
	void IncreaseGameValue();
private:
	bool m_isFull;
	bool m_isBoost = false;
	float m_time;
	float m_speed;
	InfoPanel m_info;
	std::unique_ptr<CFigure> m_pFigure;
	CGlass m_glassModel;
};

