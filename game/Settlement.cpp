#include "Settlement.h"
#include "WorldMap.h"
void Settlement::empty() {
    resources.clear();
    people.clear();
    transportations.clear();
}
//void Settlement::setPeople(int numPeople) {
//    int maxCapacity = Configuration::Capacities[this->getName()][Configuration::resourseIndex(Consts::People)];
//    if (numPeople + peopleCount > maxCapacity)
//        peopleCount = maxCapacity;
//    else peopleCount = numPeople;
//}
int Settlement::getPeopleCount()  {
    return people.size();
}
void Settlement::addTransportation(string name) {
    vector<int>costs = Configuration::Costs[name];
    if (!WorldMap::isInit) {
        for (int i = 0; i < costs.size(); i++)
        {
            if (resources[Configuration::ResourceTypes[i]] - costs[i] < 0) {
                throw "cant manufacture" + name;
            }
            resources[Configuration::ResourceTypes[i]] -= costs[i];
        }
    }
    transportations[name].push_back(make_shared<Transportation>(name));   
}
void Settlement::addPeople(int count) {
    int maxCapacity = Configuration::Capacities[this->getName()][Configuration::resourseIndex(Consts::People)];
    for (int i = 0; i < count && people.size() < maxCapacity; i++)
    {
        people.push_back(make_shared<Person>());
    }
}
