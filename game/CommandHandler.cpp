#include "CommandHandler.h"
unordered_map<string, Handler>CommandHandler::commandHandlerTable;

CommandHandler::CommandHandler() {
	commandHandlerTable[Command::RESOURCE] = { resource };
	commandHandlerTable[Command::PEOPLE] = { people };
	commandHandlerTable[Command::SELECT] = { select };
	commandHandlerTable[Command::WORK] = { work };
	commandHandlerTable[Command::WAIT] = { wait };
	commandHandlerTable[Command::RAIN] = { rain };
	commandHandlerTable[Command::BUILD] = { build };
	commandHandlerTable[Command::MOVE] = { move };
	commandHandlerTable[Command::MAKE_EMPTY] = { makeEmpty };
	commandHandlerTable[Command::MANUFACTURE] = { manufacture };
	commandHandlerTable[Command::DEPOSIT] = { deposit };
	commandHandlerTable[Command::TAKE_RESOURCES] = { takeResources };
	commandHandlerTable[Command::RESOURCES] = { resources };

}
void CommandHandler::select(shared_ptr<Command> c) {
	WorldMap::location.first = stoi(c->arguments[0]) - 1;
	WorldMap::location.second = stoi(c->arguments[1]) - 1;
}
void CommandHandler::work(shared_ptr<Command> c) {
	int locationX = WorldMap::location.first;
	int locationY = WorldMap::location.second;
	if (WorldMap::map[locationY][locationX].getName()==Consts::People) {
		WorldMap::map[locationY][locationX].removePeople();
		WorldMap::location.first = locationX = stoi(c->arguments[0]) - 1;
		WorldMap::location.second = locationY = stoi(c->arguments[1]) - 1;
		WorldMap::map[locationY][locationX].setPeople();
		WorldMap::map[locationY][locationX].getTile()->updateResource(-1);
	}
}
void CommandHandler::wait(shared_ptr<Command>c) {


}
void CommandHandler::rain(shared_ptr<Command> c) {
	int timeToRain = stoi(c->arguments[0]);
	int woodIncreament = timeToRain / Configuration::Rains["Wood"];
	int woolIncreament = timeToRain / Configuration::Rains["Wool"];
	for (int i = 0; i < WorldMap::tilesMap.size(); i++)
	{
		for (int j = 0; j < WorldMap::tilesMap[i].size(); j++)
		{
			if (WorldMap::tilesMap[i][j]->getName() == "Forest")
				WorldMap::tilesMap[i][j]->updateResource(woodIncreament);
			else if (WorldMap::tilesMap[i][j]->getName() == "Field")
				WorldMap::tilesMap[i][j]->updateResource(woolIncreament);
		}
	}
}
void CommandHandler::build(shared_ptr<Command>c) {
	string name = c->arguments[0];
	int coorX = stoi(c->arguments[1]) - 1;
	int coorY =stoi( c->arguments[2]) - 1;
	pair<int, int> size = Configuration::Sizes[name];
	if (name == Consts::Road) {
		if (WorldMap::isPossible(name, coorX, coorY)) {
			for (int i = coorX; i < coorX + size.first; i++)
				for (int j = coorY; j < coorY + size.second; j++)
				{
					WorldMap::map[j][i].setIsRoad();
					if (WorldMap::isInit)
						WorldMap::map[j][i].setIsRoadComplete(true);
				}
		}
		WorldMap::elementsCount[name]++;	
	}
	else {
		if (WorldMap::isPossible(name, coorX, coorY) && (WorldMap::isInit || WorldMap::isHasRoad(name, coorX, coorY))) {
			for (int i = coorX; i < coorX + size.first; i++)
				for (int j = coorY; j < coorY + size.second; j++)
					WorldMap::map[j][i].setSettlement(name);
			WorldMap::elementsCount[name]++;
		}
	}
}
void CommandHandler::resource(shared_ptr<Command> c) {
	string resource = c->arguments[1];
	int coordinate_x = stoi(c->arguments[2])-1;
	int coordinate_y = stoi(c->arguments[3])-1;
	int count = stoi(c->arguments[0]);
	auto element = WorldMap::map[coordinate_y][coordinate_x].getElement();
	if(element)
		element->addResource(resource, count);
	else
		WorldMap::map[coordinate_y][coordinate_x].getTile()->setResource(count);
}
void CommandHandler::people(shared_ptr<Command> c) {
	int numPeople = stoi(c->arguments[0]);
	int coordinate_x = stoi(c->arguments[1]) - 1;
	int coordinate_y = stoi(c->arguments[2]) - 1;
	auto element = WorldMap::map[coordinate_y][coordinate_x].getElement();
	if (element)
		element->addPeople(numPeople);
	else
		WorldMap::map[coordinate_y][coordinate_x].setPeople();	
}
void CommandHandler::makeEmpty(shared_ptr<Command> c) {
	int coordinate_x = stoi(c->arguments[0]) - 1;
	int coordinate_y = stoi(c->arguments[1]) - 1;
	WorldMap::map[coordinate_y][coordinate_x].emptySettlement();
}

void CommandHandler::manufacture(shared_ptr<Command> c) {
	//לבדוק שיש מקום בעיר לכלי רכב???
	//לבדוק שזה עיר או כפר
	//לבדוק שיש מספיק משאבים???
	string name = c->arguments[0];
	int coordinate_x = stoi(c->arguments[1]) - 1;
	int coordinate_y = stoi(c->arguments[2]) - 1;
	shared_ptr<Settlement> settlement = dynamic_pointer_cast<Settlement>(WorldMap::map[coordinate_y][coordinate_x].getElement());
	pair<int, int> size = Configuration::Sizes[name];
	if (settlement) {
		bool isPossible = true;
		auto resources = settlement->getResources();
		vector<int>costs = Configuration::Costs[name];
		for (int i = 0; i < costs.size(); i++)
		{
			if (resources[Configuration::ResourceTypes[i]] - costs[i] < 0) {
				isPossible = false;
			}
		}
		if(isPossible|| WorldMap::isInit)	
			settlement->addTransportation(name);
	}
	else {
		if (WorldMap::isPossible(name, coordinate_y, coordinate_x))
		{
			for (int i = coordinate_x; i < coordinate_x + size.first; i++)
				for (int j = coordinate_y; j < coordinate_y + size.second; j++)
					WorldMap::map[j][i].setElement(make_shared<Transportation>(name));
		}
	}
}
void CommandHandler::deposit(shared_ptr<Command>c) {
	int sourceCoorX = WorldMap::location.first;
	int sourceCoorY = WorldMap::location.second;
	int destinationX = stoi(c->arguments[0]) - 1;
	int destinationY = stoi(c->arguments[1]) - 1;
	auto element = WorldMap::map[sourceCoorY][sourceCoorX].getElement();
	if (element) {
		auto resources = element->getAndRemoveResources();
		for (const auto& pair : resources)
			WorldMap::map[destinationY][destinationX].getElement()->addResource(pair.first, pair.second);
	}
}
void CommandHandler::takeResources(shared_ptr<Command>c) {
	int destinationX = WorldMap::location.first;
	int destinationY = WorldMap::location.second;
	int sourceCoorX = stoi(c->arguments[0]) - 1;
	int sourceCoorY = stoi(c->arguments[1]) - 1;
	auto element = WorldMap::map[destinationY][destinationX].getElement();
	auto sourceElement = WorldMap::map[sourceCoorY][sourceCoorX].getElement();
	int count;
	if (sourceElement) {
		auto resources = element->getResources();
		for (const auto& pair : WorldMap::map[sourceCoorY][sourceCoorX].getElement()->getResources()) {
				count = WorldMap::map[destinationY][destinationX].getElement()->addResource(pair.first, pair.second);
				WorldMap::map[sourceCoorY][sourceCoorX].getElement()->updateResources(pair.first, -count);
		}
	}
}

void CommandHandler::resources(shared_ptr<Command> c) {
	int wood = stoi(c->arguments[0]);
	int wool = stoi(c->arguments[1]);
	int iron = stoi(c->arguments[2]);
	int block = stoi(c->arguments[3]);
	int coordinate_x = stoi(c->arguments[4]) - 1;
	int coordinate_y = stoi(c->arguments[5]) - 1;
	auto element = WorldMap::map[coordinate_y][coordinate_x].getElement();
	if (element) {
		element->addResource(Consts::WOOD, wood);
		element->addResource(Consts::WOOL, wool);
		element->addResource(Consts::IRON, iron);
		element->addResource(Consts::BLOCKS, block);

	}
	//else
		//WorldMap::map[coordinate_y][coordinate_x].getTile()->setResource(count);
}
void CommandHandler::move(shared_ptr<Command>c) {

}