#include "Element.h"
//int Element::getResourcesCount(string name){
//	return resources[name].first;
//}
//int countCities();
Element::Element(string name) {
	this->name = name;
}
string Element::getName() {
	return name; 
}
pair<int, int> Element::getLocation() {
	return location;
}
unordered_map<string, int> Element::getResources() {
	return resources;
}
void Element::updateResources(string resource,int count) {
	resources[resource] += count;
}
int Element::addResource(string resource, int count) {
	int maxCapacity = Configuration::Capacities[name][Configuration::resourseIndex(resource)];
	if (count + resources[resource] > maxCapacity) {
		int temp = resources[resource];
		resources[resource] = maxCapacity;
		return  maxCapacity - temp;
	}
	this->resources[resource] += count;
	return count;
}
unordered_map<string, int> Element::getAndRemoveResources(){
	auto temp = this->resources;
	this->resources.clear();
	return temp;
}
void Element::printResources() {
		int wood = resources[Consts::WOOD], wool = resources[Consts::WOOL], iron =resources[Consts::IRON], blocks = resources[Consts::BLOCKS];
		cout << wood << " " << wool << " " << iron << " " << blocks << endl;

	
}