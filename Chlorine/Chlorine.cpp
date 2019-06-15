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
#include <time.h>
//---
#include "Loop.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	Loop loop;

	loop.concat();
	
	return 0;
}
