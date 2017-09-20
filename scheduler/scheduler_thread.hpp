/*
* File Name : schedulerThread.hpp
* Creation Date : 20-09-2017
* Last Modified : Wed Sep 20 01:06:04 2017
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
#include "scheduler.hpp"

class SchedulerThread
{
public:
	SchedulerThread(Scheduler& scheduler)
	{this->scheduler_p = &scheduler;};

	void init();
	void run();
	void notify();

private:
	Scheduler*	scheduler_p;
};

