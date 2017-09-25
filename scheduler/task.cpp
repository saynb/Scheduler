/*
* File Name : scheduler/task.cpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 15:59:55 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* Includes code for class Task.
*
*/


#include <iostream>
#include "task.hpp"
#include "task_data.hpp"

Task::Task(uint32_t startTime, uint32_t interval, std::string logFileName,
		   std::string command, uint32_t taskId):
	startTime(startTime),
	interval(interval),
	logFileName(logFileName),
	command(command),
	taskId(taskId)
{

	std::cout << "Received task with \nstartTime: " << startTime
		<< "\ninterval: " << interval
		<< "\nlogFileName: " << logFileName
		<< "\ncommand: " << command
		<< "\ntaskId: " << taskId << std::endl;
}

Task::Task(std::shared_ptr<struct task_data> taskData):
	Task(taskData->startTime, taskData->interval, taskData->logFileName,
		 taskData->command, taskData->taskId)
{ }

void
Task::printTask()
{
	std::cout << "startTime: " << startTime
		<< "\ninterval: " << interval
		<< "\nlogFileName: " << logFileName
		<< "\ncommand: " << command
		<< "\ntaskId: " << taskId << std::endl;
}
uint32_t Task::getStartTime()
{
	return this->startTime;
}

uint32_t Task::getTaskId()
{
	return this->taskId;
}

uint32_t Task::getInterval()
{
	return this->interval;
}

std::string Task::getCommand()
{
	return this->command;
}
void Task::setStartTime(uint32_t time)
{
	this->startTime = time;
}


