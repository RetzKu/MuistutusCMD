#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <chrono>

class Task;

class TaskFrame
{
public:
	TaskFrame();
	~TaskFrame();

	void TaskFrame::CreateTask(std::string, float, bool);
	std::vector<Task*> TaskList;


};

