#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <string>

bool readFile(const std::string &filename, std::string &content);
std::string replaceAll(const std::string &content, const std::string &s1,
	const std::string &s2);
bool writeFile(const std::string &filename, const std::string &content);

#endif
