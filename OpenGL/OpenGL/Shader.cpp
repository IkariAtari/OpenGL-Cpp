#include <iostream>
#include "Shader.h"

GLchar read_from_file(GLchar path_to_file)
{
	std::string content;
	std::ifstream file_stream(path_to_file, std::ios::in);

	if (!file_stream.is_open())
	{

	}
}