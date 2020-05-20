#pragma once
#include <fstream>
#include <string>
namespace TaskType
{
	enum TaskType
	{
		Graph,
		Integrate1,
		Integrate2,
		UndefineType
	};
}


class FileTaskTypeParser
{
public:
	FileTaskTypeParser();
	~FileTaskTypeParser();
	typename TaskType::TaskType identify_type(std::ifstream&);
};

FileTaskTypeParser::FileTaskTypeParser()
{ }

FileTaskTypeParser::~FileTaskTypeParser()
{ }

// Функция работает в соответствие с протоколом
typename TaskType::TaskType FileTaskTypeParser::identify_type(std::ifstream& file)
{
	std::string tag;
	file.seekg(0);
	file >> tag;

	size_t open_bracket = tag.find("<");
	size_t close_bracket = tag.find(">");
	
	if (open_bracket != std::string::npos && close_bracket != std::string::npos && open_bracket < close_bracket)
	{
		size_t length = close_bracket - open_bracket; // Не может быть 0 по условию
		tag = tag.substr(open_bracket + 1, length - 1); // Извлекаем подстроку

		if (tag == "Graph") return TaskType::TaskType::Graph; // Позже можно заменить на std::map
		if (tag == "Integrate1") return TaskType::TaskType::Integrate1;
		if (tag == "Integrate2") return TaskType::TaskType::Integrate2;
	}
	return TaskType::TaskType::UndefineType;
}
