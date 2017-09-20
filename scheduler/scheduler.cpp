/*
* File Name : scheduler/scheduler.cpp
* Creation Date : 19-09-2017
* Last Modified : Wed Sep 20 00:43:26 2017
* Created By : Sayan Bandyopadhyay
*
*
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

}

void Scheduler::notify()
{
	// Assumption:: the lock has been unlocked already
	// So we can safely notify the scheduler Thread to continue

	this->signalScheduler.notify_one();
}

void Scheduler::addTask(Task& T)
{

	// We need to increment the startTime of the process with the currentTime
	// before inserting in the queue.
	T.setStartTime(T.getStartTime() + this->currentTime);
	this->taskQueue.push(&T);

}



