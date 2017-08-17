#include "TaskList.h"

void TaskName(TaskList::TriggerTimer* _TaskData);

TaskList::TaskList()
{
}



TaskList::~TaskList()
{
}


class TaskList::Task
{
public:
	Task() {};
	Task(struct TaskList::TriggerTimer * a){ _TaskData = a; };

	std::function<void(TaskList::TriggerTimer*)> asd = TaskName;

		
private:
	TaskList::TriggerTimer* _TaskData;
};

void TaskName(TaskList::TriggerTimer* _TaskData)
{
	TaskList::TriggerTimer a = *_TaskData;
	std::cout << a.TaskName;
}


void TaskList::CreateTask(std::string TaskName, int SleepDuration)
{
	std::chrono::system_clock::time_point TimeNow = std::chrono::system_clock::now();

	TriggerTimer a = TriggerTimer(TaskName, TimeNow, false);
	Task *e = new Task(&a);

	Tasks.push_back(*e);


}




	
