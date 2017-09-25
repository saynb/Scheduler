/*
* File Name : schedulerThread.cpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 18:09:40 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
* Contains code for the Thread which processes all the tasks
*
*/


#include <iostream>
#include <spawn.h>
#include "scheduler_thread.hpp"

void
SchedulerThread::setExitFlagAndJoin()
{
	exit_for_test = true;
	thread_p->join();
}

void SchedulerThread::init()
{
	// start thread on run and save it
	thread_p = std::make_shared<std::thread>( [&]{this->run();} );
}

void SchedulerThread::run()
{
	// sit on the conditional variable
	// and wait for the lock and the queue to
	// contain something. Also the front time
	// should be equal to the currentTime else
	// waking up has no use
	auto time_to_check = std::chrono::seconds(100);
	while (true && !exit_for_test)
	{
		std::unique_lock<std::mutex> lk(this->scheduler_p->getQueueMutex());
		bool process_further = false;

		bool status = this->scheduler_p->getCV().wait_for(lk,
			time_to_check,
			[this, &time_to_check, &process_further]{
				if(this->scheduler_p->getQueueSize() > 0)
				{
					// First check whether the time to check is
					// correct or not. If it is correct, then
					// we want to return false and wait for timeout
					if (time_to_check == std::chrono::seconds(
						this->scheduler_p->getQueueFront()->getStartTime() -
						this->scheduler_p->getCurrentTime()))
					{
						return false;
					}
				// update time to check
					time_to_check = std::chrono::seconds(
						this->scheduler_p->getQueueFront()->getStartTime() -
						this->scheduler_p->getCurrentTime());
					return true;
				}
				// If queue is empty then we need to wait long
				time_to_check = std::chrono::seconds(100);
				return false;
			});


		if (status == false )
		{
			// Timed out. continue loop
			continue;
		}

		// The queue contains something.
		// Loop while front contains startTime equal to
		// currentTime. pop it and spawn workerThread.
		while (this->scheduler_p->getQueueFront()->getStartTime()
			<= this->scheduler_p->getCurrentTime())
		{
			auto T = this->scheduler_p->getQueueFront();
			std::cout << "Starting job TaskId "<< T->getTaskId()
				<< " " << T->getCommand() << " Process time:" << T->getStartTime()
				<<" at current time "
				<<  this->scheduler_p->getCurrentTime() << std::endl;
			std::thread work( [&] {workerThread(T);});
			work.detach();
			// The task needs to be modified in the queue
			// according to the interval
			if (lk.owns_lock())
			{
				lk.unlock();
			}
			if (T->getInterval() > 0)
			{
				this->scheduler_p->modifyTask(T->getTaskId(), T->getInterval());
			}
			else
			{
				this->scheduler_p->removeTask(T->getTaskId());
			}
		}
		if (lk.owns_lock())
		{
			lk.unlock();
		}
	}
}

void SchedulerThread::workerThread(std::shared_ptr<Task> T)
{
	// Spawn a process to run the workerThread
	spawnProcess(T->getCommand());
	// wait for the process
	// collect status, output and send to logger thread
}


