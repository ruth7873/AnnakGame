#include "Tile.h"
Tile::Tile(string name):name(name),peopleCount(0){
	resourceCount = Configuration::StartingResources[Configuration::TilesResources[name]];
}
void Tile::setResource(int count) {
	resourceCount = count;
}
void Tile::updatePeople(int count) {
	//if (peopleCount + count < 0)
	//	throw "not enough people";
	peopleCount += count;
}
void Tile::updateResource(int count)
{
	//if ((resourceCount + count) < 0)
	//	throw "can't take!";
	resourceCount += count;
}
void Tile::printResources() {
	int wood = 0, wool = 0, iron = 0, blocks = 0;
	if (Configuration::TilesResources[name] == "Wood")
		wood = resourceCount;
	else if (Configuration::TilesResources[name] == "Wool")
		wool = resourceCount;
	else if (Configuration::TilesResources[name] == "Iron")
		iron = resourceCount;
	else
		blocks = resourceCount;
	cout << wood << " " << wool << " " << iron << " " << blocks << endl;

}

