/*
* File Name : scheduler/local_server.hpp
* Creation Date : 20-09-2017
* Last Modified : Mon Sep 25 17:13:04 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/

#include <iostream>
#include <task_data.hpp>
#pragma once


class LocalServer
{

	int sock_fd; // For windows, it can be if-defed to HANDLE
public:
	LocalServer();
	virtual ~LocalServer();
	std::shared_ptr<struct task_data> getEvent();
};
