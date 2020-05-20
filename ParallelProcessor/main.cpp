#include <iostream>
#include "FixThreadPool.h"
#include <fstream>
#include "FileTaskTypeParser.h"


int main()
{
	FileTaskTypeParser type_parser;
	std::ifstream file("file1.txt");
	switch (type_parser.identify_type(std::ref(file)))
	{
	case TaskType::Graph:
		std::cout << "Graph";
		break;
	case TaskType::Integrate1:
		std::cout << "Integrate1";
		break;
	case TaskType::Integrate2:
		std::cout << "Integrate2";
		break;
	default:
		std::cout << "Undef";
	}
}
