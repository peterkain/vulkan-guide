#pragma once
#include <iostream>
#include "types.h"

void ExitMsg(conststr& msg)
{
	std::cerr << msg << '\n';
	std::exit(EXIT_FAILURE);
}

void Msg(conststr& msg)
{
	std::cout << msg << std::endl;
}