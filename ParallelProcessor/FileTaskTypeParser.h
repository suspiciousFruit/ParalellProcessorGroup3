#pragma once
#include <fstream>
#include <string>



class FileTaskTypeParser
{
public:
	static std::string parse_task_type(std::ifstream&);
};

std::string FileTaskTypeParser::parse_task_type(std::ifstream& file)
{
	std::string task_type;
	file.seekg(0);
	file >> task_type;

	size_t open_bracket = task_type.find("<");
	size_t close_bracket = task_type.find(">");

	if (open_bracket != std::string::npos && close_bracket != std::string::npos && open_bracket < close_bracket)
	{
		size_t length = close_bracket - open_bracket; // Не может быть 0 по условию
		task_type = task_type.substr(open_bracket + 1, length - 1); // Извлекаем подстроку

		return task_type;
	}
	return std::string();
}
