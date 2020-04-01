#pragma once
#include <iostream>
#include "types.h"

[[maybe_unused]]
static void ExitMsg(conststr& msg)
{
	std::cerr << msg << '\n';
	std::exit(EXIT_FAILURE);
}


[[maybe_unused]]
static void Msg(conststr& msg)
{
	std::cout << msg << std::endl;
}