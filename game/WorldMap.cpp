#include "WorldMap.h"

using namespace std;

bool WorldMap::isInit = false;
unordered_map<string, int> WorldMap::elementsCount;
pair<int, int>WorldMap::location;
vector<vector<Cell>> WorldMap::map;
vector<vector<shared_ptr<Tile>>> WorldMap::tilesMap;

CommandHandler* WorldMap::commandHandler;
AssertHandler* WorldMap::assertHandler;

WorldMap::WorldMap(vector <vector<string>> worldInput):toWait(false) {
	commandHandler = new CommandHandler();
	assertHandler = new AssertHandler();
	configuration.initialize();
	if (!worldInput.empty()) {
		row = configuration.Sizes["Tile"].first * worldInput.size();
		column = configuration.Sizes["Tile"].second * worldInput[0].size();
		map = vector<vector<Cell>>(row);
		tilesMap = vector<vector<shared_ptr<Tile>>>(worldInput.size());
		for (int i = 0; i < worldInput.size(); i++)
			for (int j = 0; j < worldInput[i].size(); j++)
			{
				string tileName = Configuration::Tiles[stoi(worldInput[i][j])];
				tilesMap[i].push_back(shared_ptr<Tile>(new Tile(tileName)));
			}

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				map[i].push_back(Cell(tilesMap[i / 5][j / 5]));
		
	}
}
void WorldMap::initMap(vector<shared_ptr<Command>> start){
	int startSize = start.size();
	isInit = true;
	for (const auto& start_item : start)
		CommandHandler::commandHandlerTable[start_item->name].handler(start_item);
	isInit = false;
	
}
void WorldMap::doTurn(vector<shared_ptr<Command>> steps) {
	for (const auto& step : steps)
			CommandHandler::commandHandlerTable[step->name].handler(step);
}
void WorldMap::printAsserts(vector<string>asserts) {
	int coorX = location.first;
	int coorY = location.second;
	for (auto assert : asserts) {
		cout << assert<<" ";
		AssertHandler::assertHandlerTable[assert].handler(assert);
	}
}
bool WorldMap::isPossible(string name ,int coorY, int coorX) {
	pair<int,int> size = Configuration::Sizes[name];
	if (coorX + size.first > map.size() || coorY + size.second > map[0].size())
		return false;
	for (int i = coorX; i < coorX + size.first; i++)
		for (int j = coorY; j < coorY + size.second; j++)
			if (map[i][j].getTile()->getName() != "Ground")
				return false;
	return true;
}
bool WorldMap::isHasRoad(string name, int coorX, int coorY) {
	pair<int, int> citySize = Configuration::Sizes[name], roadSize = Configuration::Sizes["Road"];
	for (int y = coorY; y < coorY + citySize.second; y += roadSize.second)
	{
		if ((coorX - 1 > 0 && map[y][coorX - 1].getIsRoad())||( coorX + citySize.first + 1 <map[0].size() && map[y][coorX + citySize.first + 1].getIsRoad()))
			return true;
	}
	for (int x = coorX; x < coorX + citySize.first; x += roadSize.first)
	{
		if ((coorY - 1 > 0 && map[coorY - 1][x].getIsRoad()) ||( coorY + citySize.second + 1 < map.size() && map[coorY + citySize.second + 1][x].getIsRoad()))
			return true;
	}
	return false;
}