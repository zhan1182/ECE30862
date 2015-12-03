#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "trigger.hh"
#include "item.hh"

using namespace std;

class Room : public Base
{
	string type;
	list<Item> item_list;
	list<Trigger> trigger_list;
public:
	Room(string Name, string Description, string Status, string Type);
	virtual ~Room();
	virtual void print();
	void add_trigger(Trigger tg);
	void add_item(Item im);
};

#endif