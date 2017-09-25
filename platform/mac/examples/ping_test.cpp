/*
* File Name : ping_test.cpp
* Creation Date : 25-09-2017
* Last Modified : Mon Sep 25 16:47:58 2017
* Created By : Sayan Bandyopadhyay
*
* Description : Contains example code to run ping in intervals using the scheduler
*
*/
#include <iostream>
#include <scheduler_client.hpp>
#include "task_data.hpp"

int main(int argc, char* argv[])
{
	// Create a scheduler client object

	SchedulerClient	schedulerClient("127.0.0.1", 9001);

	// Create a task_data object

	auto data = std::make_shared<struct task_data>();

	data->startTime = 10;
	data->interval = 20;
	strncpy(data->command, "ping -c 2 google.com", strlen("ping -c 2 google.com"));
	strncpy(data->logFileName, "ping.txt", strlen("ping.txt"));

	// send add task and wait for reply

	int taskId = schedulerClient.sendTask(*data);
	std::cout << "taskId received: " << taskId << std::endl;

}
