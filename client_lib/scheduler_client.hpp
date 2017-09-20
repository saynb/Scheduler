
/*
 * File: scheduler.cpp
 *
 * This file contains definition for the Scheduler class.
 */

#include <iostream>
#include <vector>
#include <queue>
#include "task.hpp"

class Scheduler
{
public:
	void Scheduler();

	void addTask(Task& task);
	void modifyTask(Task& task);
	void removeTask(Task& task);

private:
	priority_quque<Task> taskQueue;
};

