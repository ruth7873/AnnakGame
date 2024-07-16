#include "Transportation.h"
#include "WorldMap.h"


Transportation::Transportation(string name) :Element(name) {
    WorldMap::elementsCount[name]++;
};


void Transportation::addPeople(int count) {
    int maxCapacity = Configuration::Capacities[this->getName()][Configuration::resourseIndex(Consts::People)];
    for (int i = 0; i < count && people.size() < maxCapacity; i++)
    {
        people.push_back(make_shared<Person>());
    }
}
