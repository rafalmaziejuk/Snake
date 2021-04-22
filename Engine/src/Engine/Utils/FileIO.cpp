#include "Engine/Utils/FileIO.h"
#include "Engine/Core/EngineAssert.h"

#include <fstream>
#include <sstream>

std::string FileIO::file_read(const std::string &filepath)
{
	std::string line;
	std::stringstream stream;
	std::ifstream sourceFile(filepath);
	EN_ASSERT(sourceFile.is_open());

	while (getline(sourceFile, line))
		stream << line << '\n';

	line = stream.str();
	sourceFile.close();

	return line;
}