#pragma once
#include "Rect.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>


using namespace std;

class RectLoader
{
public:
	RectLoader();
	RectLoader(const string&);
	~RectLoader();

	vector<Rect> load(string);

private:

};

