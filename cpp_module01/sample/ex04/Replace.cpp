#include "Replace.hpp"

#include <fstream>
#include <sstream>

bool readFile(const std::string &filename, std::string &content)
{
	std::ifstream input(filename.c_str());
	if (!input.is_open())
		return false;

	std::ostringstream buffer;
	buffer << input.rdbuf();
	if (input.bad())
		return false;

	content = buffer.str();
	return true;
}

std::string replaceAll(const std::string &content, const std::string &s1,
	const std::string &s2)
{
	if (s1.empty())
		return content;

	std::string result;
	std::string::size_type start = 0;
	std::string::size_type found = content.find(s1, start);

	while (found != std::string::npos)
	{
		result += content.substr(start, found - start);
		result += s2;
		start = found + s1.length();
		found = content.find(s1, start);
	}
	result += content.substr(start);
	return result;
}

bool writeFile(const std::string &filename, const std::string &content)
{
	std::ofstream output(filename.c_str());
	if (!output.is_open())
		return false;

	output << content;
	return !output.fail();
}
