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
#include <unordered_map>
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

	void concat();

	void conwert(string name);

	vector<string> extractWAV(string path);

	void parsingProbability();

	int getRand(int state);

private:
	ofstream out;
	_WAV wav;


	unordered_map<string, int> conformity; //Соответствие названию индекса
	vector<vector<int>> probability;//цепь Маркова Александра (по умолчанию у всех вероятность 1)
	vector<int> sum; //Суммы для вероятности
	vector<string> all_dir;//Все каталоги в библиотеке

};

