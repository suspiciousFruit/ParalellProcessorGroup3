#pragma once
#include "FileToFileTask.h"



class IntegrateTask1 : public FileToFileTask
{
public:
	IntegrateTask1(std::ifstream&& a, std::ofstream&& b) : FileToFileTask(std::move(a), std::move(b))
	{ }

	virtual void complete() override
	{
		fileout_ << "This is completed integrate task" << std::endl;
	}

	virtual ~IntegrateTask1()
	{ }
};