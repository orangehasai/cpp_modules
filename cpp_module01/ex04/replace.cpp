#include "replace.hpp"
#include <fstream>
#include <iostream>

static bool openStreams(const std::string &filename, std::ifstream &ifs,
	std::ofstream &ofs)
{
	ifs.open(filename.c_str());
	if (!ifs.is_open())
	{
		std::cout << "opening input file failed" << std::endl;
		return (false);
	}
	ofs.open((filename + ".replace").c_str());
	if (!ofs.is_open())
	{
		std::cout << "opening output file failed" << std::endl;
		return (false);
	}
	return (true);
}

static bool writeReplacedLine(std::ofstream &ofs, const std::string &line,
	const std::string &s1, const std::string &s2)
{
	std::string::size_type	start;
	std::string::size_type	found;

	start = 0;
	while (true)
	{
		found = line.find(s1, start);
		if (found == std::string::npos)
			break;
		ofs << line.substr(start, found - start);
		ofs << s2;
		if (!ofs)
			return (false);
		start = found + s1.length();
	}
	ofs << line.substr(start);
	return (!!ofs);
}

bool replaceFile(const std::string &filename, const std::string &s1,
	const std::string &s2)
{
	std::ifstream	ifs;
	std::ofstream	ofs;
	std::string		line;

	if (!openStreams(filename, ifs, ofs))
		return (false);
	while (std::getline(ifs, line))
	{
		if (!writeReplacedLine(ofs, line, s1, s2))
		{
			std::cout << "file processing failed" << std::endl;
			return (false);
		}
		if (!ifs.eof())
			ofs << '\n';
		if (!ofs)
		{
			std::cout << "file processing failed" << std::endl;
			return (false);
		}
	}
	if (!ifs.eof() || !ofs)
	{
		std::cout << "file processing failed" << std::endl;
		return (false);
	}
	return (true);
}
