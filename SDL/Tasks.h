#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "Renderer.h"
#include <thread>

struct TriggerTimer
{
public:
	TriggerTimer() {}
	TriggerTimer(std::string Name, bool Singleuse, int _RecallInterval) { TaskName = Name; _Singleuse = Singleuse; TimeNow = std::chrono::system_clock::now(); RecallInterval = _RecallInterval; TimeToTrigger = false; }
	std::string TaskName;
	bool _Singleuse;
	int RecallInterval;
	std::chrono::system_clock::time_point TimeNow;
	bool TimeToTrigger;

};

class Task
{
public:
	Task(struct TriggerTimer a, Renderer* Rendererobject) { _TaskData = a; _Renderer = Rendererobject; };
	std::string printname() { std::cout << _TaskData.TaskName; return _TaskData.TaskName; }
	void SetToNormal()
	{
		_TaskData.TimeNow = std::chrono::system_clock::now();
		_TaskData.TimeToTrigger = false;
	}
	bool GetTimeDifference()
	{
		std::chrono::duration<double> Seconds = std::chrono::system_clock::now() - _TaskData.TimeNow;
		auto i = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _TaskData.TimeNow);
		int c = (int)Seconds.count();
		if (c > _TaskData.RecallInterval)
		{
			_TaskData.TimeToTrigger = true;
			//run main task
		}
		return _TaskData.TimeToTrigger;
	}
	bool Single()
	{
		return _TaskData._Singleuse;
	}

private:
	TriggerTimer _TaskData;
	Renderer* _Renderer;
};

class TaskFrame
{
public:
	TaskFrame(Renderer* RendererObject) { _RendererObject = RendererObject; }
	std::vector<Task*> TaskList;

	void CheckTasks();
	void CreateTask(std::string TaskName, bool SingleUse, int TimeInterval);
private:
	Renderer* _RendererObject;
};
