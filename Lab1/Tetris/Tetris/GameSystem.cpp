#include "stdafx.h"
#include "GameSystem.h"
#include "random"

using namespace std;

namespace 
{
	enum TypeFigure
	{
		square = 0,
		line,
		l_L
	};
	static const std::string SQUARE = "square";
	static const std::string LINE = "line";
	static const std::string L_L = "l-L";

	int GetRandomNumberForSection(int begin, int end) {
		assert(begin < end);
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dist(begin, end);
		return dist(gen);
	}
}

CGameSystem::CGameSystem()
{
	m_formsFiqures = { { SQUARE, { { "##", "##" }} },
					   { LINE, {{ "####" }, { "#", "#", "#", "#" }} },
					   { L_L, { { "#", "#", "##" },{ "###", "#" },{ "##", " #", " #"}, {"  #", "###"} } } };
}


CGameSystem::~CGameSystem()
{
}

void CGameSystem::Update(float deltaSeconds)
{
	if (m_isPause)
	{
		return;
	}

	m_time += deltaSeconds;
	if (m_time >= m_speed)
	{
		if (!m_glassModel.CanMoveFigure())
		{
			m_glassModel.ClearFullLine();
			CreateFigure();
		}
		m_glassModel.MoveFigure();
		//m_glassModel.ClearFullLine();
		
		m_time = 0;
	}
}

void CGameSystem::CreateFigure()
{
	auto id = static_cast<TypeFigure> (GetRandomNumberForSection(0, 2));
	std::string typeFigure;
	switch (id)
	{
	case TypeFigure::line:
		typeFigure = LINE;
		break;
	case TypeFigure::square:
		typeFigure = SQUARE;
		break;
	case TypeFigure::l_L:
		typeFigure = L_L;
		break;
	}
	m_pFigure = std::make_shared<CFigure>(m_formsFiqures[typeFigure]);
	m_glassModel.SetFigure(m_pFigure.get());
}

bool CGameSystem::OnKeyDown(const SDL_KeyboardEvent & event)
{
	if (m_pFigure)
	{
		switch (event.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			m_pFigure->SetTypeMove(TypeMove::Direction::Left);
			return true;
		case SDLK_RIGHT:
		case SDLK_d:
			m_pFigure->SetTypeMove(TypeMove::Direction::Right);
			return true;
		case SDLK_UP:
		case SDLK_w:
			m_pFigure->Rotate();
			return true;
		case SDLK_DOWN:
		case SDLK_s:
			//m_speed = 0.02f;
			return true;
		case SDLK_p:
			m_isPause = !m_isPause;
			return true;
		}
		//m_speed = 0.05f;
	}
	return false;
}
