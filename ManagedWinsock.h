#pragma once
#include <winsock2.h>
#include <exception>
#include <iostream>
#include <string>


class ManagedWinsock
{
public:
	ManagedWinsock();
	//ManagedWsa(const ManagedWsa& other) = delete;
	~ManagedWinsock();
};