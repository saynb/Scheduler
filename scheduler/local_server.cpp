/*
* File Name : scheduler/local_server.cpp
* Creation Date : 20-09-2017
* Last Modified : Wed Sep 20 01:36:46 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/

#include <iostream>
#include "local_server.hpp"

LocalServer::LocalServer()
{
	// create socket here

}

int LocalServer::listen()
{
	// Listen to the socket for incoming msgs
	// Lets assume that the incoming msgs are all
	// Task structures
	return 0;
}

Task& LocalServer::getEvent()
{
	Task* t = new(Task);
	return *t;
}

