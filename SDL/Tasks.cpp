#include "Tasks.h"

std::vector<Task> Tasks;

void TaskRunner(Task* ThisTask);

void TaskFrame::CheckTasks()
{
	using namespace std::chrono_literals;
	while (true)
	{
		if (Tasks.size() != 0)
		{
			for (int i = 0; i < Tasks.size(); i++)
			{
				if (Tasks[i].GetTimeDifference() == true)
				{
					std::string o = Tasks[i].printname();
					const char *Taskname = o.c_str();
					Tasks[i].printname();
					std::cout << "\n";
					MessageBox(NULL, Taskname, "elixiirit kehiin", MB_OK | MB_ICONQUESTION | MB_SYSTEMMODAL | MB_SERVICE_NOTIFICATION);
					Tasks[i].SetToNormal();
					if (Tasks[i].Single() == true)
					{
						Tasks.erase(Tasks.begin()+i);
					}
				}
			}
		}
		std::this_thread::sleep_for(0.5s);
	}
}

void TaskFrame::CreateTask(std::string TaskName, bool SingleUse, int TimeInterval)
{
	TriggerTimer tmpa = TriggerTimer(TaskName, SingleUse, TimeInterval);
	//std::thread(TaskRunner(new Task(tmpa, _RendererObject))).detach();
	std::thread(TaskRunner, new Task(tmpa, _RendererObject)).detach();
	std::cout <<"kek";
}

void TaskRunner(Task* ThisTask)
{
	using namespace std::chrono_literals;

	while (true)
	{
		std::cout << "\nRunning like nigga this thread is";
		std::this_thread::sleep_for(1s);
	}
}