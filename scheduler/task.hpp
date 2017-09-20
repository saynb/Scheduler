/*
* File Name : scheduler/task.hpp
* Creation Date : 19-09-2017
* Last Modified : Wed Sep 20 01:39:17 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* Includes definition for class Task.
*/

#pragma once

#include <iostream>
#include <vector>



class Task
{
public:
	Task();

	uint32_t getStartTime();
	void setStartTime(uint32_t time);

	friend bool operator>(const Task &t1, const Task &t2);
	friend bool operator<(const Task &t1, const Task &t2);

private:
	uint32_t startTime;
	uint32_t interval;
	std::string logFileName;
	int taskId;
};
