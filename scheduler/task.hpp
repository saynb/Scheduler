/*
* File Name : scheduler/task.hpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 15:59:53 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* Includes definition for class Task.
*/

#include <iostream>
#include <vector>

#pragma once

class Task
{
public:
	Task(uint32_t startTime, uint32_t interval, std::string logFileName,
		 std::string command, uint32_t taskId);
	Task(std::shared_ptr<struct task_data> taskData);

	uint32_t getStartTime();
	uint32_t getInterval();
	uint32_t getTaskId();
	void printTask();
	void setStartTime(uint32_t time);
	std::string getCommand();

private:
	uint32_t startTime;
	uint32_t interval;
	std::string logFileName;
	std::string command;
	uint32_t taskId;
};
