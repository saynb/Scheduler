/*
* File Name : scheduler_thread.hpp
* Creation Date : 20-09-2017
* Last Modified : Mon Sep 25 18:13:00 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/


#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include "scheduler.hpp"
#include "task.hpp"

#pragma once

class SchedulerThread
{
public:
	SchedulerThread(std::shared_ptr<Scheduler> scheduler)
	{
		this->scheduler_p = scheduler;
		exit_for_test = false;
	};

	void init();
	void run();
	void notify();
	void workerThread(std::shared_ptr<Task> T);
	void spawnProcess(std::string command);
	void setExitFlagAndJoin();

private:
	bool exit_for_test;
	std::shared_ptr<Scheduler>	scheduler_p;
	std::shared_ptr<std::thread> thread_p;
};

