#pragma once
#include "FileToFileTask.h"



class GraphTask : public FileToFileTask
{
public:
	GraphTask(std::ifstream&& a, std::ofstream&& b) : FileToFileTask(std::move(a), std::move(b))
	{ }

	virtual void complete() override
	{
		fileout_ << "This is completed GraphTask" << std::endl;
	}

	virtual ~GraphTask()
	{ }
};
