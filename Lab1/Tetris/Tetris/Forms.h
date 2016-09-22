#pragma once
#include <map>
#include <vector>
#include <string>



namespace FormsFigures
{
	static const std::string SQUARE = "square";
	static const std::string LINE = "line";
	static const std::string L_L = "l-L";
	static const std::string R_L = "r-L";
	static const std::string R_ZIGZAG = "r-zigzag";
	static const std::string L_ZIGZAG = "l-zigzag";
	static const std::string Y = "y";


	std::vector<std::string> namesFigures = { SQUARE, LINE, L_L, R_L, R_ZIGZAG, L_ZIGZAG, Y };

	using FormsFigures = std::map<std::string, std::vector<std::vector<std::string>>>;

	FormsFigures formsFiqures = {
		{ SQUARE, { { "##", "##" } } },
		{ LINE, { { "####" }, { "#", "#", "#", "#" } } },
		{ L_L, { { "#", "#", "##" }, { "###", "#" }, { "##", " #", " #" }, { "  #", "###" } } },
		{ R_L, { { " #", " #", "##" },{ "#", "###" },{ "##", "#", "#" },{ "###", "  #" } } },
		{ R_ZIGZAG, { { "##", " ##" }, { "#", "##", " #" } } },
		{ L_ZIGZAG, { { " ##", "##" },{ "#", "##", " #" } } },
		{ Y, { { " #", "###"},{ "#", "##", "#" }, { "###", " #" }, { " #", "##", " #" } } }
	};
}