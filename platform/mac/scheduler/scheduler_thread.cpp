/*
* File Name : scheduler_thread.cpp
* Creation Date : 25-09-2017
* Last Modified : Mon Sep 25 16:32:11 2017
* Created By : Sayan Bandyopadhyay
*
* Description : platform specific scheduler_thread functions
*
*/

#include <iostream>
#include <spawn.h>
#include <scheduler_thread.hpp>

namespace
{
	uint32_t CMD_PATH_MAX = 1024;
}

extern char **environ;

void SchedulerThread::spawnProcess(std::string cmd)
{
	pid_t pid;
	char cmdPath[CMD_PATH_MAX];

	strncpy(cmdPath, cmd.c_str(), CMD_PATH_MAX);

	const char* argv[] = {"sh", "-c", cmdPath, NULL};
	int status;
	printf("Run command: %s\n", cmd.c_str());
	status = posix_spawn(&pid, "/bin/sh", NULL, NULL, const_cast<char**>(argv), environ);
	// TODO: send output to logger thread for logging
	if (status == 0) {
		if (waitpid(pid, &status, 0) != -1) {
			printf("Child exited with status %i\n", status);
		} else {
			perror("waitpid");
		}
	} else {
		printf("posix_spawn: %s\n", strerror(status));
	}
}

