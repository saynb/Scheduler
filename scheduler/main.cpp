/*
* File Name : scheduler/main.cpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 17:00:31 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* Contains init code for scheduler process
*
*/

#include <iostream>
#include "scheduler.hpp"
#include "scheduler_thread.hpp"
#include "logger_thread.hpp"
#include <local_server.hpp>
#include <task_data.hpp>

int main()
{
	// create scheduler object
	std::shared_ptr<Scheduler> scheduler = std::make_shared<Scheduler>();

	// create and init scheduler thread
	SchedulerThread schedulerThread(scheduler);
	schedulerThread.init();

	// create and init logger thread
	LoggerThread loggerThread(scheduler);
	loggerThread.init();

	// listen for events on local address
	// if any event comes, insert in priority queue
	// indicate/notify scheduler to start processing
	// go back to listening to events

	LocalServer localServer;

	while (true)
	{
		std::shared_ptr<struct task_data> taskData = localServer.getEvent();
		if (taskData == nullptr)
		{
			std::cout << "Error reading from socket. Continuing" << std::endl;
			continue;
		}
		switch(taskData->taskType)
		{
		case TASK_TYPE_ADD:
			{
				std::cout << "Add task received" << std::endl;
				std::shared_ptr<Task> t = std::make_shared<Task>(taskData);
				scheduler->addTask(t);
				scheduler->notify();
			}
			break;
		case TASK_TYPE_MODIFY:
			std::cout << "Modify task received" << std::endl;
			scheduler->modifyTask(taskData->taskId, taskData->startTime);
			scheduler->notify();
			break;
		case TASK_TYPE_REMOVE:
			std::cout << "Remove task received" << std::endl;
			scheduler->removeTask(taskData->taskId);
			scheduler->notify();
			break;
		default:
			std::cout << "Unknown task received" << std::endl;
		}
	}
}
