
/*
 * File: scheduler.cpp
 *
 * This file contains definition for the Scheduler class.
 */

#pragma once
#include <iostream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <task_data.hpp>

class ServerRuntimeError : public std::runtime_error
{
public:
	ServerRuntimeError(const char *w) : std::runtime_error(w) {}
};

class SchedulerClient
{
public:
	SchedulerClient(std::string ip, uint32_t port);
	int connectServer(struct sockaddr_in& serv_addr, uint32_t port);
	int sendTask(const struct task_data& taskData);

private:
	struct sockaddr_in serv;
	int clientSockFd;
};



