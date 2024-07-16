#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Consts.h"
#include "Configuration.h"

using namespace std;
class Element
{
protected:
	string name;
	pair<int, int> location;
	unordered_map<string, int> resources;
public:
	Element(string name);
	virtual ~Element() {} // Virtual destructor
	string getName();
	pair<int, int> getLocation();
	virtual int getPeopleCount() { return 1; }
	unordered_map<string, int> getResources();
	unordered_map<string, int> getAndRemoveResources();
	int addResource(string resource, int count);
	void updateResources(string resource, int count);
	virtual void addPeople(int count = 1) {};
	void printResources();
	/*int getResourcesCount(string name);
	int countCities();*/
};