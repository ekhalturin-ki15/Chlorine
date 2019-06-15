#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <ctime>
#include <cmath>
#include "wav.h"

using namespace std;

template <typename ... Ts>
std::string ToString(const Ts& ... ts) {
	std::stringstream ss;
	const char* sep = "";
	(((ss << sep << ts), sep = " "), ...);
	return ss.str();
}

template <typename... Args>
std::string ToString(const std::tuple<Args...> & t) {
	return std::apply([](const auto & ... ts) { return ToString(ts...); }, t);
}

class Loop
{
public:
	Loop();
	~Loop();

	void ma();

	void concat();

private:
	ofstream out;
	_WAV wav;
};

