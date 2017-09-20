/*
* File Name : scheduler/logger_thread.hpp
* Creation Date : 20-09-2017
* Last Modified : Wed Sep 20 01:15:54 2017
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

class LoggerThread
{
public:
	LoggerThread(Scheduler& scheduler)
	{this->scheduler_p = &scheduler;};

	void init();
	void run();

private:
	Scheduler*	scheduler_p;
};
