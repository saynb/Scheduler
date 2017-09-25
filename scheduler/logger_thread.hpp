/*
* File Name : scheduler/logger_thread.hpp
* Creation Date : 20-09-2017
* Last Modified : Mon Sep 25 05:20:53 2017
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
	LoggerThread(std::shared_ptr<Scheduler> scheduler)
	{this->scheduler_p = scheduler;};

	void init();
	void run();

private:
	std::shared_ptr<Scheduler>	scheduler_p;
};
