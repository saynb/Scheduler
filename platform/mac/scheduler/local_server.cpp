/*
* File Name : scheduler/local_server.cpp
* Creation Date : 20-09-2017
* Last Modified : Mon Sep 25 13:56:31 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/

#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "local_server.hpp"

uint32_t global_id = 0;

namespace
{
	uint32_t SERV_PORT_NUM = 9001;
}
LocalServer::LocalServer()
{
	// create socket here
	struct sockaddr_in serv_addr;

	this->sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	// Find better local Logging functionality
	if (this->sock_fd < 0) 
		std::cout << "ERROR opening socket" << std::endl;

	// TODO: find better bzero alternative for C++
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(SERV_PORT_NUM);

	if (bind(this->sock_fd, (struct sockaddr *) &serv_addr,
			 sizeof(serv_addr)) < 0) 
		std::cout << "ERROR on binding:" << errno <<std::endl;

}

LocalServer::~LocalServer()
{
	close(this->sock_fd);
}

std::shared_ptr<struct task_data> LocalServer::getEvent()
{
	// Read from the socket blockingly
	// If there is nothing to be read, return nullptr
	char buffer[4096];

	// TODO: find better bzero alternative for C++
	bzero(buffer, 4096);
	int n;
	struct sockaddr_in client;
	socklen_t l = sizeof(client);
	n = recvfrom(this->sock_fd, buffer, 4095, 0,
			(struct sockaddr *)&client, &l);
	if (n < 0)
	{
		std::cout << "ERROR reading from socket" << std::endl;
		return nullptr;
	}

	if (n != sizeof(struct task_data))
	{
		std::cout<< "Wrong data received: " <<n<< std::endl;
		return nullptr;
	}
	struct task_data* taskData = (struct task_data*)buffer;

	// Lets assign a taskId here if addTask
	// and send it back to client
	// TODO: Make ID generation and maintenance better
	if (taskData->taskType == TASK_TYPE_ADD)
	{
		taskData->taskId = ++global_id;
		sendto(this->sock_fd,
				(char*)&taskData->taskId, 
				sizeof(taskData->taskId),
				0, (struct sockaddr *)&client, l);
	}

	auto data = std::make_shared<struct task_data>(*taskData);

	return data;
}

