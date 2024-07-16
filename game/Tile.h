#pragma once
#include <iostream>
#include <string>
#include "Configuration.h"
using namespace std;
class Tile
{
	string name;
	int resourceCount;
	int peopleCount;
public:
	Tile(string name);
	void setResource(int count);
	void updatePeople(int count);
	void updateResource(int count);
	void printResources();
	string getName() { return name; }
};

