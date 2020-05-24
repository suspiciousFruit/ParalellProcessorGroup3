#pragma once
#include <filesystem>
#include <iostream>
#include <string>



struct Settings
{
	std::filesystem::path sourse_folder;
	std::filesystem::path destination_folder;
	size_t threads_number;
	Settings() : threads_number(1) { }
};


class UserInterface
{
public:
	void work();
};

/*

show <attribute_name>
set <attribute_name> <value>
md <directory_path>

*/

void UserInterface::work()
{
	while (1)
	{
		std::string command;
		std::cin >> command;
		if (command == "set")
		{

		}
		else if (command == "show")
		{

		}
	}
}



