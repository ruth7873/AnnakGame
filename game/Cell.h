#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Tile.h"
#include "Element.h"
#include "Person.h"
#include "Settlement.h"
#include "Consts.h"
#include "WorldMap.h"
using namespace std;
class Cell
{
	shared_ptr<Tile> tile;
	shared_ptr<Element> element;
	bool isRoad;
	bool isRoadCompleted = false;

public:
	Cell(shared_ptr<Tile> tile);
	shared_ptr<Tile> getTile();
	string getName();
	shared_ptr<Element> getElement() { return this->element; }
	bool getIsRoad() { return isRoad; }
	void setIsRoad() { isRoad = true; }
	bool getIsRoadComplete() { return isRoadCompleted; }
	void setIsRoadComplete(bool isRoadCompleted) { this-> isRoadCompleted = isRoadCompleted; }
	void setPeople();
	void setSettlement(string name);
	void emptySettlement();
	void removePeople();
	void setElement(shared_ptr<Element> elem) { element = elem; }
};