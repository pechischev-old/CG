#include "../stdafx.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include "../json.hpp"


using namespace std;
using json = nlohmann::json;


CParser::CParser(std::string const & input)
{
	ParseInputData(input);
}

CParser::~CParser()
{
}

std::vector<SShape> CParser::GetShapesData()
{
	return m_shapesData;
}

void CParser::ParseInputData(std::string const & input)
{
	std::ifstream file(input);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + input);
	}
	
	auto j = json::parse(file);
	auto shapes = j.at("shapes");
	for (auto &shape : shapes)
	{
		auto type = shape.at("type");
		auto shapePos = shape.at("pos");
		auto shapeColor = shape.at("color");
		glm::vec2 pos = { shapePos.at("x"), shapePos.at("y") };
		glm::vec3 color = { shapeColor.at("red"), shapeColor.at("green"), shapeColor.at("blue") };

		if (type == "rectangle")
		{
			auto shapeSize = shape.at("size");
			glm::vec2 size = { shapeSize.at("width"), shapeSize.at("height") };
			auto angle = shape.at("rotation");
			SShape figure = SShape(type, pos, size, color, angle);
			m_shapesData.push_back(figure);
		}
		else if (type == "circle")
		{
			auto radius = shape.at("radius");
			SShape figure = SShape(type, pos, { radius, 0 }, color);
			m_shapesData.push_back(figure);
		}
		else
		{
			throw std::invalid_argument("invalid shape type");
		}
	}
}
