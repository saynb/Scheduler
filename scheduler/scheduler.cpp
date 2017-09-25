/*
* File Name : scheduler/scheduler.cpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 15:56:40 2017
* Created By : Sayan Bandyopadhyay
*
* Description :
*
*/

#include <iostream>
#include <vector>
#include "scheduler.hpp"
#include "task.hpp"

Scheduler::Scheduler()
	:currentTime(0)
{
	absoluteSchedulerStart = std::chrono::system_clock::now();
}

void Scheduler::notify()
{
	// Assumption:: the lock has been unlocked already
	// So we can safely notify the scheduler Thread to continue

	this->updateCurrentTime();
	this->signalScheduler.notify_one();
}

void Scheduler::addTask(std::shared_ptr<Task> T)
{

	// We need to increment the startTime of the process with the currentTime
	// before inserting in the heap.
	std::lock_guard<std::mutex> lk(this->queueLock);
	T->setStartTime(T->getStartTime() + this->getCurrentTime());
	T->printTask();
	this->taskQueue.push_back(T);
	std::make_heap(this->taskQueue.begin(), this->taskQueue.end(),
			[](const std::shared_ptr<Task> lhs, const std::shared_ptr<Task>& rhs)
			{
				return lhs->getStartTime() > rhs->getStartTime();
			});
}

bool
Scheduler::modifyTask(uint32_t taskId, uint32_t startTime)
{
	std::lock_guard<std::mutex> lk(this->queueLock);
	// Find the Task using taskId
	// remove, modify, push

	// Assumption: taskId can only be present at most once
	std::vector<std::shared_ptr<Task> >::iterator it = 
		std::find_if (this->taskQueue.begin(), this->taskQueue.end(),
		[taskId](std::shared_ptr<Task> T) { return T->getTaskId() == taskId;});

	if (it != this->taskQueue.end())
	{
		(*it)->setStartTime(startTime + this->getCurrentTime());
		std::make_heap(this->taskQueue.begin(), this->taskQueue.end(),
			[](const std::shared_ptr<Task> lhs, const std::shared_ptr<Task>& rhs)
			{
				return lhs->getStartTime() > rhs->getStartTime();
			});
		return true;
	}
	return false;
}

void
Scheduler::updateCurrentTime()
{
	currentTime = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now () - absoluteSchedulerStart);
}

void
Scheduler::printQueue()
{
	// print the queue
	std::cout << "*********PRINTING ENTIRE QUEUE**********" << std::endl;
	for (auto element: this->taskQueue)
	{
		element->printTask();
		std::cout << "**************" << std::endl;
	}
	std::cout << "************STOP PRINTING************" << std::endl;
}
bool
Scheduler::removeTask(uint32_t taskId)
{
	std::lock_guard<std::mutex> lk(this->queueLock);
	// Find the Task using taskId
	// remove
	// Assumption: taskId can only be present at most once
	std::vector<std::shared_ptr<Task> >::iterator it = 
		std::remove_if (this->taskQueue.begin(), this->taskQueue.end(),
		[taskId](std::shared_ptr<Task> T) { return T->getTaskId() == taskId;});

	if (it != this->taskQueue.end())
	{
		std::make_heap(this->taskQueue.begin(), this->taskQueue.end());
		return true;
	}
	return false;
}

std::shared_ptr<Task> Scheduler::getQueueFront()
{
	return this->taskQueue.front();
}

size_t
Scheduler::getQueueSize()
{
	return this->taskQueue.size();
}

std::mutex&
Scheduler::getQueueMutex()
{
	return this->queueLock;
}

uint32_t
Scheduler::getCurrentTime()
{
	this->updateCurrentTime();
	return this->currentTime.count();
}

std::condition_variable&
Scheduler::getCV()
{
	return signalScheduler;
}

