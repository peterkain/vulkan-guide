#pragma once
#include <iostream>
#include <tuple>
#include "types.h"

[[maybe_unused]]
static void ExitMsg(conststr& msg) {
	std::cerr << msg << '\n';
	std::exit(EXIT_FAILURE);
}


[[maybe_unused]]
static void Msg(conststr& msg) {
	std::cout << msg << std::endl;
}


[[maybe_unused]]
static std::tuple<uint32, uint32, uint32> GetVersion(uint32 vkVersion) {
	// Implementation as described in manual:
	// (((major) << 22) | ((minor) << 12) | (patch))
	// 32-Bit, which means: 10 Bit for major, 10 Bit for minor and 12 Bit for patch
	uint32 major, minor, patch;
	// 10 Bit for major and minor
	uint32 mask{0b1111111111}; 

	major = ((vkVersion >> 22) & mask);
	minor = ((vkVersion >> 12) & mask);

	// 12 Bit for patch
	mask = 0b111111111111; 

	patch = vkVersion & mask;
	return std::make_tuple(major, minor, patch);
}


[[maybe_unused]]
static void PrintVersion(std::ostream& os, uint32 vkVersion) {
	auto versions{GetVersion(vkVersion)};
	os << std::get<0>(versions) << '.' << std::get<1>(versions) << '.' << std::get<2>(versions) << '\n';
}