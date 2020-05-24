#include <iostream>
#include "FixThreadPool.h"
#include "FolderTaskPool.h"



class UserInterface
{
private:
	struct Settings
	{
		std::filesystem::path sourse_folder;
		std::filesystem::path destination_folder;
		size_t threads_number;
		Settings() : threads_number(1) { }
	};

	Settings settings_;
	bool error_;
public:
	UserInterface() : error_(false)
	{ }

	void work()
	{
		ask_with_user();
		if (error_ != true)
		{
			FixThreadPool thread_pool(settings_.threads_number);
			FolderTaskPool task_pool(settings_.sourse_folder, settings_.destination_folder);
			thread_pool.processTasks(&task_pool);
		}
	}
private:
	void ask_with_user()
	{
		settings_.sourse_folder = "source_folder";
		settings_.destination_folder = "destination_folder";
		if (!std::filesystem::is_directory(settings_.sourse_folder) ||
			!std::filesystem::is_directory(settings_.destination_folder))
		{
			error_ = true;
		}
	}
};





int main()
{
	UserInterface ui;
	ui.work();
}
