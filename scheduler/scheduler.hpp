/*
* File Name : scheduler/scheduler.hpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 11:08:53 2017
* Created By : Sayan Bandyopadhyay
*
* Description :
*
*/


#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include "task.hpp"

#pragma once

class Scheduler
{
public:
	Scheduler();

	void addTask(std::shared_ptr<Task> task);
	bool modifyTask(uint32_t taskId, uint32_t startTime);
	bool removeTask(uint32_t taskId);
	std::shared_ptr<Task> getQueueFront();
	size_t getQueueSize();
	std::mutex& getQueueMutex();
	uint32_t getCurrentTime();
	std::condition_variable& getCV();
	void printQueue();

	void notify();
	void updateCurrentTime();

private:

	// Main queue for the scheduler
	std::vector<std::shared_ptr<Task> > taskQueue;

	// mutex for 2 things ->
	// 1. To lock the queue
	// 2. To monitor the conditional variable used to
	//	signal the scheduler thread to check the queue

	std::mutex queueLock;
	std::condition_variable signalScheduler;
	std::chrono::seconds currentTime;
	std::chrono::system_clock::time_point absoluteSchedulerStart;
};

