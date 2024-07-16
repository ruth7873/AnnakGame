#pragma once
#include "Element.h"
#include "Person.h"
#include "Transportation.h"
#include "Configuration.h"
#include "Consts.h"
class Settlement:public Element
{
	vector<shared_ptr<Person>> people;
	unordered_map<string,vector<shared_ptr<Transportation>>> transportations;
	bool isComplete;
public:
	Settlement(string name) :Element(name),isComplete(false) {};
	void empty();
	bool getIsComplete() { return isComplete; }
	void setIsComplete(bool isComplete) { this->isComplete = isComplete; }
	//void setPeople(int numPeople);
	//void setCar(int numCar);
	int getPeopleCount() override;
	void addTransportation(string name);
	void addPeople(int count = 1) override;
	int getTransportationsCount(string name) { return transportations[name].size(); }
};

