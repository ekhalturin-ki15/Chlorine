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
#include <tuple>
#include <chrono>
//---
#include "Loop.h"


using namespace std;

int main()
{
	//srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	setlocale(LC_ALL, "Russian");

	Loop loop;

	loop.concat();
	//loop.ma();

	
	return 0;
}
