/*
* File Name : scheduler_test.cpp
* Creation Date : 25-09-2017
* Last Modified : Mon Sep 25 18:16:54 2017
* Created By : Sayan Bandyopadhyay
*
* Description : Contains gtest for scheduler 
*
*/

#include <iostream>
#include <string>
#include "../scheduler.hpp"
#include "../scheduler_thread.hpp"
#include "gtest/gtest.h"

namespace {

TEST(Scheduler, testMultipleAddTasks)
{
	// Create the scheduler object
	std::shared_ptr<Scheduler> scheduler = std::make_shared<Scheduler>();
	// create the test objects
	std::shared_ptr<Task> t1 = std::make_shared<Task>(5, 10, "ping.txt", "ping -c 3 google.com", 3);
	std::shared_ptr<Task> t2 = std::make_shared<Task>(20, 3, "ping.txt", "ping -c 4 google.com", 4);
	std::shared_ptr<Task> t3 = std::make_shared<Task>(7, 2, "ping.txt", "ping -c 5 google.com", 5);
	std::shared_ptr<Task> t4 = std::make_shared<Task>(8, 30, "ping.txt", "ping -c 6 google.com", 6);

	// start the scheduler thread

	SchedulerThread schedulerThread(scheduler);
	schedulerThread.init();

	scheduler->addTask(t1);
	scheduler->addTask(t2);
	scheduler->addTask(t3);
	sleep(5);
	scheduler->addTask(t4);

	sleep(10);

	EXPECT_EQ(t1->getStartTime(), 25);
	schedulerThread.setExitFlagAndJoin();
}


}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

