#pragma once
#include "../stdafx.h"



class CParser
{
public:
	CParser(std::string const & input);
	~CParser();
	std::vector<SShape> GetShapesData();
private:
	void ParseInputData(std::string const & input);
	std::vector<SShape> m_shapesData;
};

