#include "Tasks.h"
#include <algorithm>

std::vector<Task> Tasks;

void TaskRunner(Task* ThisTask);

TaskFrame::TaskFrame(Renderer* RendererObject)
{
	_RendererObject = RendererObject;
	std::thread(&TaskFrame::CheckThreads, *this, &TaskList).detach(); //Detachaa Threadin joka pit‰‰ TaskiListan ajantasalla
}

void TaskFrame::CheckThreads(std::vector<Task*> *TaskList)
{
	using namespace std::chrono_literals;

	while (true)
	{
		std::vector<Task*>& Tasks = *TaskList;
		if (sizeof(ThreadList) != 0)
		{
			for (int i = 0; i < Tasks.size(); i++)
			{
				if (Tasks[i]->Single() == true && Tasks[i]->Completed == true)
				{
					Tasks.erase(Tasks.begin() + i);
					std::cout << "\tTask Erased at " << i;
				}
			}
		}
		std::this_thread::sleep_for(0.5s);
	}
}

void TaskFrame::CreateTask(std::string TaskName, bool SingleUse, int TimeInterval)
{
	TriggerTimer tmpa = TriggerTimer(TaskName, SingleUse, TimeInterval);

	Task* NewTask = new Task(tmpa, _RendererObject);
	std::thread(TaskRunner, NewTask).detach();

	TaskList.push_back(NewTask);

	std::cout <<"Task Created within it's thread\n";
}

void TaskRunner(Task* NewTask)
{
	using namespace std::chrono_literals;
	while (NewTask->Completed == false)
	{
		std::this_thread::sleep_for(NewTask->GetTime());
		NewTask->Trigger();
	}
}