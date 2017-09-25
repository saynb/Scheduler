/*
* File Name : client_lib/scheduler_client.cpp
* Creation Date : 19-09-2017
* Last Modified : Mon Sep 25 10:06:55 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
* This file contains code for the API library. The schedulerClient class
* reference : http://www.cplusplus.com/forum/unices/76180/
*
*/

#include <iostream>
#include <unistd.h>
#include <string.h>
#include "scheduler_client.hpp"

namespace
{
	bool checkDataSanity(const struct task_data& taskData)
	{
		switch(taskData.taskType)
		{
		case TASK_TYPE_ADD:
			if (strlen(taskData.command) <= 0)
			{
				std::cout << "Need a command for add task" << std::endl;
				return false;
			}
			return true;
		case TASK_TYPE_MODIFY:
		case TASK_TYPE_REMOVE:
			if (taskData.taskId <= 0)
			{
				std::cout << "Need a taskId" << std::endl;
				return false;
			}
			return true;
		default:
			std::cout << "Unknown task received" << std::endl;
			return false;
		}
	}
}

SchedulerClient::SchedulerClient(std::string ip, uint32_t port)
{
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = inet_addr(ip.c_str());
	clientSockFd = socket(AF_INET,SOCK_DGRAM,0);
	if(clientSockFd == -1)
	{
		throw ServerRuntimeError(("could not create socket for: \"" +
			ip+ ":" + "\"").c_str());
	}
}

int
SchedulerClient::sendTask(const struct task_data& taskData)
{
	struct sockaddr_in client;
	if (!checkDataSanity(taskData))
	{
		std::cout << "Please check the task Data" << std::endl;
		return -1;
	}
	socklen_t serv_size = sizeof(this->serv);
	socklen_t client_size = sizeof(client);
	std::cout<<"\ngoing to send\n";

	char buffer[4096];
	memcpy(buffer, &taskData, 4096);
	int status = sendto(this->clientSockFd, buffer,
		sizeof(struct task_data), 0,
		(struct sockaddr *)&this->serv, serv_size);

	std::cout << "send status: " << status << std::endl;
	int recv_bytes = 0;
	if (taskData.taskType == TASK_TYPE_ADD)
	{
		recv_bytes = recvfrom(clientSockFd, buffer, 256, 0,
				 (struct sockaddr *)&client, &client_size);
		if (recv_bytes > 0)
		{
			// return the taskId received
			std::cout<<"\n Received taskID\n";
			return atoi(buffer);
		}
	}
	if (status > 0)
	{
		// from here just send 0 if send was success
		return 0;
	}
	else
	{
		return -1;
	}
}


