#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Consts.h"
#include "WorldMap.h"
using namespace std;

struct AssHandler
{
	void (*handler)(string assert);
};
class AssertHandler
{
public:
		static unordered_map<string, AssHandler> assertHandlerTable;

		AssertHandler();
		static void selectedCategory(string assert);
		static void selectedResource(string assert);
		static void selectedComplete(string assert);
		static void selectedPeople(string assert);
		static void selectedCar(string assert);	
		static void selectedTruck(string assert);
		static void selectedCoordinates(string assert);
		static void cityCount(string assert);
		static void villageCount(string assert);
		static void roadCount(string assert);
		static void carCount(string assert);
		static void truckCount(string assert);
		static void helicopterCount(string assert);

};

