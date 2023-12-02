#pragma once

#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>

namespace aoc_util
{

	std::vector<std::string> readFile(const std::string&);
	std::vector<std::string> splitString(const std::string&, const std::string&);

}
