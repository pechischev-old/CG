#pragma once
#include "model\Parser.h"
#include <map>
#include <vector>

class CGameSystem
{
public:
	CGameSystem();
	~CGameSystem();

	void Update(float deltaSeconds);
protected:
	void CreateFigure();

private:
	std::map<std::string, std::vector<std::vector<std::string>>> m_formsFiqures;
};

