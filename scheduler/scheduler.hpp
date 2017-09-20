/*
* File Name : scheduler/scheduler.hpp
* Creation Date : 19-09-2017
* Last Modified : Tue Sep 19 03:12:15 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "task.hpp"

class Scheduler
{
public:
	Scheduler();

	void addTask(Task& task);
	void modifyTask(Task& task);
	void removeTask(Task& task);

	void notify();

private:
	void addTaskInternal(Task& task);

	// Main queue for the scheduler
	std::priority_queue<Task*> taskQueue;

	// mutex for 2 things ->
	// 1. To lock the queue
	// 2. To monitor the conditional variable used to
	//	signal the scheduler thread to check the queue

	std::mutex queueLock;
	std::condition_variable signalScheduler;
	uint32_t currentTime;
};

