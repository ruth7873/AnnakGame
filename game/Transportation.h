#pragma once

#include <memory>
#include <vector>
#include "Person.h"
#include "Consts.h"
#include "Element.h"

class Transportation :public Element
{
	vector<shared_ptr<Person>> people;
public:
	Transportation(string name="");
	void addPeople(int count = 1);
};

