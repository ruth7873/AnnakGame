#include "Configuration.h"
#include <fstream>
using namespace std;

map<int, string> Configuration::Tiles;
map<string, string> Configuration::TilesResources;
map<string, int>Configuration::StartingResources;
vector<string> Configuration::ResourceTypes;
map<string, vector<int>>Configuration::Costs;
map<string, vector<int>>Configuration::Capacities;
map<string, pair<int, int>>Configuration::Sizes;
map<string, double>Configuration::Speeds;
map<string, int>Configuration::Rains;

json Configuration::readFromJson() {
	ifstream file("configuration.json");
	json configuration_file;
	if (file) {
		file >> configuration_file;
		file.close();
	}
	else
		throw "the file isnt open";
	return configuration_file;
}
void Configuration::initialize() {
	configuration_file = readFromJson();
	initTiles();
	initStartingResources();
	initTilesResources();
	initialResourceTypes();
	initialCosts();
	initialCapacities();
	initialSizes();
	initialSpeeds();
	initialRains();


}
void Configuration::initTiles()
{
	auto originalMap =configuration_file["Tiles"].get<map<string, int>>();
	for (const auto& pair : originalMap) {
		Tiles[pair.second] = pair.first;
	}
}
void Configuration::initStartingResources()
{
	StartingResources =configuration_file["StartingResources"].get<map<string, int>>();
}
void Configuration::initTilesResources() {
	TilesResources = configuration_file["TilesResources"];
}
void Configuration::initialResourceTypes() {
	ResourceTypes = configuration_file["ResourceTypes"];
}
void Configuration::initialCosts() {
	Costs = configuration_file["Costs"].get<map<string, vector<int>>>();
}
void Configuration::initialCapacities() {
	Capacities = configuration_file["Capacities"].get < map < string, vector<int>>>();
}
void Configuration::initialSizes() {
	Sizes = configuration_file["Sizes"].get<map<string, pair<int, int>>>();
}
void  Configuration::initialSpeeds() {
	Speeds = configuration_file["Speeds"].get<map<string, double>>();
}
void Configuration::initialRains() {
	Rains = configuration_file["Rains"].get<map<string, int>>();
}
int Configuration::resourseIndex(string resource) {
	auto it = find(ResourceTypes.begin(), ResourceTypes.end(), resource);
	return distance(Configuration::ResourceTypes.begin(), it);
}