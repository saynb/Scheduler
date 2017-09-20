/*
* File Name : scheduler/main.cpp
* Creation Date : 19-09-2017
* Last Modified : Wed Sep 20 01:30:45 2017
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
#include "local_server.hpp"

int main()
{
	// create scheduler object
	Scheduler scheduler;

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

	while (localServer.listen())
	{
		Task t = localServer.getEvent();
		scheduler.addTask(t);
		scheduler.notify();
	}
}
