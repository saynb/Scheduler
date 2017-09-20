/*
* File Name : scheduler/local_server.hpp
* Creation Date : 20-09-2017
* Last Modified : Wed Sep 20 01:29:37 2017
* Created By : Sayan Bandyopadhyay
*
*
*
* Description :
*
*/


#include <iostream>
#include "task.hpp"

class LocalServer
{
public:
	LocalServer();
	int listen();
	Task& getEvent();
};
