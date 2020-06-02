#pragma once
#include <map>
#include <fstream>
#include <filesystem>
#include "FileTaskTypeParser.h"
#include "task_allocator.h"



class TaskLibrary
{
private:
	std::map<std::string, task_allocator*> library_;
public:
	TaskLibrary()
	{
		// Идентификатор задачи
		library_["IntegrateLorenzAttractor"] = new IntegrateLorenzAttractorAllocator();
		// Идентификатор задачи
		library_["IntegrateDoublePendulum"] = new IntegrateDoublePendulumAllocator();
		// library_["myTaskIdentifcator"] = new MyTaskAllocator();
	}

	~TaskLibrary()
	{
		for (auto& pair : library_)
			delete pair.second;
	}

	Task* allocateTask(const std::filesystem::path& file_in_name, const std::filesystem::path& file_out_name)
	{
		std::ifstream file(file_in_name);

		std::string task_type = FileTaskTypeParser::parse_task_type(file);
		std::map<std::string, task_allocator*>::const_iterator pair;

		if ((pair = library_.find(task_type)) != library_.end())
		{
			return pair->second->allocate(std::move(file), file_out_name);
		}

		return nullptr;
	}
};
