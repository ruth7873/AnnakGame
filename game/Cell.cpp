#include "Cell.h"
Cell::Cell(shared_ptr<Tile> tile) :tile(tile), isRoad(false){}

shared_ptr<Tile> Cell::getTile() {
	return tile;
}

string Cell::getName() {
	if (element)
		return element->getName();
	if (isRoad)
		return Consts::Road;
	return tile->getName();
}

void Cell::setSettlement(string name) {
	element = make_shared<Settlement>(name);
	if (WorldMap::isInit)
	{
		shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(element);
		settlement->setIsComplete(true);
	}
}

void Cell::emptySettlement() {
	shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(element);
	if (settlement)
		settlement->empty();
}

void Cell::setPeople() {
	if(element==nullptr)
		element = make_shared<Person>();
	/*if (isPeopleExist)
		throw "this cell is full";
	isPeopleExist = true;*/
	tile->updatePeople(1);
}

void Cell::removePeople() {
	element = nullptr;
	/*if (!isPeopleExist)
		throw "this cell is empty";
	isPeopleExist = false;*/
	tile->updatePeople(-1);
}