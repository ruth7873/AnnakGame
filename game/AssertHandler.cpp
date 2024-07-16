#include "AssertHandler.h"
unordered_map<string, AssHandler>AssertHandler::assertHandlerTable;

AssertHandler::AssertHandler() {
	assertHandlerTable[Consts::SelectedCategory] = { selectedCategory };
	assertHandlerTable[Consts::SelectedResource] = { selectedResource };
	assertHandlerTable[Consts::SelectedComplete] = { selectedComplete };
	assertHandlerTable[Consts::SelectedPeople] = { selectedPeople };
	assertHandlerTable[Consts::SelectedCar] = { selectedCar };
	assertHandlerTable[Consts::SelectedTruck] = { selectedTruck };
	assertHandlerTable[Consts::SELECTED_COORDINATES] = { selectedCoordinates };
	assertHandlerTable[Consts::CityCount] = { cityCount };
	assertHandlerTable[Consts::VillageCount] = { villageCount };
	assertHandlerTable[Consts::RoadCount] = { roadCount };
	assertHandlerTable[Consts::CAR_COUNT] = { carCount };
	assertHandlerTable[Consts::TRUCK_COUNT] = { truckCount };
	assertHandlerTable[Consts::HELICOPTER_COUNT] = { helicopterCount };

}
void AssertHandler::selectedCategory(string assert) {
	cout <<WorldMap::map[WorldMap::location.second][WorldMap::location.first].getName() << endl;
}
void AssertHandler::selectedResource(string assert) {
	if (WorldMap::map.empty())
		cout << "1 1 1 0";
	else {
		auto element = WorldMap::map[WorldMap::location.second][WorldMap::location.first].getElement();
		if (element)
			element->printResources();
		else
			WorldMap::map[WorldMap::location.second][WorldMap::location.first].getTile()->printResources();
	}
}
void AssertHandler::selectedComplete(string assert) {
	auto element = WorldMap::map[WorldMap::location.second][WorldMap::location.first].getElement();
	shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(element);
	if (settlement) {
		if (settlement->getIsComplete())
			cout << "True";
		else cout << "False";
	}
	else if(WorldMap::map[WorldMap::location.second][WorldMap::location.first].getIsRoadComplete())
		cout << "True";
	else cout << "False";
}
void AssertHandler::selectedPeople(string assert) {
	cout << WorldMap::map[WorldMap::location.second][WorldMap::location.first].getElement()->getPeopleCount() << endl;
}
void AssertHandler::selectedCar(string assert) {
	shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(WorldMap::map[WorldMap::location.second][WorldMap::location.first].getElement());
	if (settlement)
		cout << settlement->getTransportationsCount(Consts::Car);
}
void AssertHandler::selectedTruck(string assert) {
	shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(WorldMap::map[WorldMap::location.second][WorldMap::location.first].getElement());
	if (settlement)
		cout << settlement->getTransportationsCount(Consts::Truck);
}
void AssertHandler::cityCount(string assert) {
	cout << WorldMap::elementsCount[Consts::City] << endl;
}
void AssertHandler::villageCount(string assert) {
	cout << WorldMap::elementsCount[Consts::Village] << endl;
}
void AssertHandler::roadCount(string assert) {
	cout << WorldMap::elementsCount[Consts::Road] << endl;
}

void AssertHandler::carCount(string assert) {
	cout << WorldMap::elementsCount[Consts::Car];
}
void AssertHandler::truckCount(string assert) {
	cout << WorldMap::elementsCount[Consts::Truck];
}
void AssertHandler::helicopterCount(string assert) {
	cout << WorldMap::elementsCount[Consts::HELICOPTER];
}
void AssertHandler::selectedCoordinates(string assert) {
	if (WorldMap::map.empty())
		cout << "0 0";
	//cout << WorldMap::location.first << " " << WorldMap::location.second;
}