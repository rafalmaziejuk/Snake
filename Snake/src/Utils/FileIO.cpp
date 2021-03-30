#include "FileIO.h"

#include <fstream>
#include <sstream>
#include <cassert>

std::string FileIO::file_read(const std::string &filepath)
{
	std::string line;
	std::stringstream stream;
	std::ifstream sourceFile(filepath);
	assert(sourceFile.is_open());

	while (getline(sourceFile, line))
		stream << line << '\n';

	line = stream.str();
	sourceFile.close();

	return line;
}