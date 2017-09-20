/*
* File Name : scheduler/task.cpp
* Creation Date : 19-09-2017
* Last Modified : Wed Sep 20 01:38:15 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* Includes code for class Task.
*
*/


#include <iostream>
#include "task.hpp"

Task::Task()
{

}

uint32_t Task::getStartTime()
{
	return this->startTime;
}

void Task::setStartTime(uint32_t time)
{
	this->startTime = time;
}


bool operator>(const Task &t1, const Task &t2)
{
	return (t1.startTime > t2.startTime);
}

bool operator<(const Task &t1, const Task &t2)
{
	return (t1.startTime < t2.startTime);
}


