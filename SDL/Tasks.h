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
	Task(struct TriggerTimer a, Renderer* Rendererobject) { _TaskData = a; _Renderer = Rendererobject; Completed = false; };
	std::string printname() { std::cout << _TaskData.TaskName; return _TaskData.TaskName; }
	void SetToNormal()
	{
		_TaskData.TimeNow = std::chrono::system_clock::now();
		_TaskData.TimeToTrigger = false;
	}

	bool Single()
	{
		return _TaskData._Singleuse;
	}

	std::chrono::duration<float, std::milli> GetTime()
	{
		std::chrono::system_clock::time_point NewTime = std::chrono::system_clock::now() + std::chrono::seconds(_TaskData.RecallInterval);
		std::chrono::system_clock::time_point Now = std::chrono::system_clock::now();
		std::chrono::duration<float, std::milli> NewDura = std::chrono::duration_cast<std::chrono::microseconds>(NewTime - Now);
		return NewDura;
	}
	
	bool Completed;
	void Trigger()
	{
		MessageBox(NULL, _TaskData.TaskName.c_str(), "elixiirit kehiin", MB_OK | MB_ICONQUESTION | MB_SYSTEMMODAL | MB_SERVICE_NOTIFICATION);
		if (Single() == true)
		{
			Completed = true;
		}
	}

private:
	TriggerTimer _TaskData;
	Renderer* _Renderer;
};

class TaskFrame
{
public:
	TaskFrame(Renderer* RendererObject);
	~TaskFrame()
	{
		for each (std::thread* Var in ThreadList)
		{
			if (Var->joinable())
			{
				Var->join();
			}
			delete Var;
		}
		ThreadList.clear();
		for each(Task* Var in TaskList)
		{
			delete Var;
		}
		TaskList.clear();
	}
	std::vector<Task*> TaskList;
	std::vector<std::thread*> ThreadList;
	
	void CheckThreads(std::vector<Task*> *TaskList);
	void CreateTask(std::string TaskName, bool SingleUse, int TimeInterval);
private:
	Renderer* _RendererObject;
};
