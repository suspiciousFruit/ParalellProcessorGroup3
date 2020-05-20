#include <iostream>
#include "FixThreadPool.h"
#include <fstream>
#include "FolderTaskPool.h"


void process_function(ThreadPool* thread_pool, TaskPool* task_pool)
{
	if (thread_pool && task_pool)
		thread_pool->processTasks(task_pool);
}




int main()
{
	Task* task;
	FolderTaskPool task_pool("source_folder", "destination_folder");
	while (1)
	{
		task = task_pool.getTask();
		if (task == nullptr) break;
		task->complete();
		task_pool.setCompleted(task);
	}
}
