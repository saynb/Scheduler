/*
* File Name : scheduler/task_data.hpp
* Creation Date : 22-09-2017
* Last Modified : Mon Sep 25 04:30:31 2017
* Created By : Sayan Bandyopadhyay
*
* Description :
* This header file contains the structure and the
* information neded to communicate the task data from the clients
* to the server
*
*/


#pragma once

#include <iostream>
#include <vector>

enum
{
	TASK_TYPE_ADD,
	TASK_TYPE_MODIFY,
	TASK_TYPE_REMOVE
};
struct task_data
{
	uint32_t startTime;
	uint32_t interval;
	uint32_t taskType;
	// TODO: Definitely a better way to specify size
	// Maybe dynamically do this and serialize later?
	char logFileName[100];
	char command[512];
	int taskId;
};

