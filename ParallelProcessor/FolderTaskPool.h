#pragma once
#include "TaskPool.h"
#include "FileTaskTypeParser.h"
#include <filesystem>
#include <fstream>

// Tasks
#include "IntegrateTask1.h"
#include "GraphTask.h"




class FolderTaskPool : public TaskPool
{
private:
	std::filesystem::directory_iterator current_entry_;
	const std::filesystem::path folder_out_path_;
	FileTaskTypeParser type_parser_;
	size_t task_number_;
public:
	FolderTaskPool(const std::filesystem::path&, const std::filesystem::path&);
	virtual ~FolderTaskPool();
	virtual Task* getTask() override;
	virtual void setCompleted(Task*) override;
private:
	std::wstring generateName(size_t task_number);
};



FolderTaskPool::FolderTaskPool(const std::filesystem::path& folder_from, const std::filesystem::path& folder_to) :
	current_entry_(std::filesystem::directory_iterator(folder_from)), // Считаем что переданная директория существует
	folder_out_path_(folder_to), // Считаем что директория существует
	task_number_(0)
{ }

FolderTaskPool::~FolderTaskPool()
{ }

Task* FolderTaskPool::getTask()
{
	Task* task = nullptr;

	while (1)
	{
		if (current_entry_ == std::filesystem::directory_iterator())
			break;

		if (current_entry_->is_regular_file())
		{
			std::ifstream file(current_entry_->path());

			TaskType::TaskType task_type = type_parser_.identify_type(std::ref(file));

			if (task_type != TaskType::TaskType::UndefineType)
			{
				++task_number_;
				std::filesystem::path file_out_name = folder_out_path_;
				file_out_name /= generateName(task_number_);

				switch (task_type)
				{
				case TaskType::Graph:
					task = new GraphTask(std::move(file), std::ofstream(file_out_name));
					break;
				case TaskType::Integrate1:
					task = new IntegrateTask1(std::move(file), std::ofstream(file_out_name));
					break;
				case TaskType::Integrate2:
					// task = new IntegrateTask2(file, std::ostream( (folder_out_path_ /= generateName(task_number_)).c_str() );
					break;
				default:
					break;
				}
			}
			++current_entry_; // Будет переписано более красиво
			break;
		}
		++current_entry_;
	}

	return task;
}

void FolderTaskPool::setCompleted(Task* task)
{
	delete task;
}

std::wstring FolderTaskPool::generateName(size_t task_number)
{
	return std::wstring(L"result_" + std::to_wstring(task_number) + L".txt");
}
