#pragma once

#include <exception>

class bad_memory : public std::exception
{
	
};

class no_such_file : public std::exception
{

};