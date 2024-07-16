#pragma once


#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Configuration.h"
#include "Tile.h"
#include "Cell.h"
#include "Command.h"
#include "CommandHandler.h"
#include "AssertHandler.h"
using namespace std;
class CommandHandler;
class AssertHandler;
class Cell;

class WorldMap
{
	int row, column;
	int toWait;
	static CommandHandler* commandHandler;
	static AssertHandler* assertHandler;

public:
	static unordered_map<string,int> elementsCount;
	static bool isInit;
	static pair<int, int>location;
	Configuration configuration;
	static vector<vector<shared_ptr<Tile>>> tilesMap;
	static vector<vector<Cell>> map;
	WorldMap(vector <vector<string>> worldInput);
	void initMap(vector<shared_ptr<Command>> start);
	void doTurn(vector<shared_ptr<Command>> steps);
	void printAsserts(vector<string>asserts);
	static bool isPossible(string name, int coorY, int coorX);
	static bool isHasRoad(string name, int coorX, int coorY);
};