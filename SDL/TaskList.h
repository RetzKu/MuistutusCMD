#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <functional>

class TaskList
{
public:
	TaskList();
	~TaskList();

	void CreateTask(std::string, int);
	class Task;
	std::vector<Task> Tasks = std::vector<Task>();
	
	


	struct TriggerTimer
	{
		TriggerTimer() {}
		TriggerTimer(std::string Name, std::chrono::system_clock::time_point Now, bool Triggered) { TaskName = Name; TimeNow = Now; TimeToTrigger = Triggered; }
		std::string TaskName;
		std::chrono::system_clock::time_point TimeNow;
		bool TimeToTrigger;
	}TriggerTime;
private:

};

