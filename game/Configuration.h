#pragma once
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <cctype>
using namespace std;
using json = nlohmann::json;
class Configuration
{
	void initTiles();
	void initStartingResources();
    void initTilesResources();
	void initialResourceTypes();
	void initialCosts();
	void initialCapacities();
	void initialSizes();
	void initialSpeeds();
	void initialRains();
	json configuration_file;
public:
	static map<int, string> Tiles;
	static map<string, string>TilesResources;
	static map<string,int>StartingResources;
	static vector<string> ResourceTypes;
	static map<string, vector<int>>Costs;
	static map<string, vector<int>>Capacities;
	static map<string, pair<int,int>>Sizes;
	static map<string,double>Speeds;
	static map<string, int>Rains;

	json readFromJson();
	void initialize();
	static int resourseIndex(string resource);

};

