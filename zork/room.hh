#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "trigger.hh"

using namespace std;

class Room : public Base
{
	string type;
	list<Trigger> trigger_list;
public:
	Room(string Name, string Description, string Type);
	virtual ~Room();
	virtual void print();
	void add_trigger(Trigger tg);
};

#endif