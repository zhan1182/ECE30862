#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "trigger.hh"
#include "item.hh"

using namespace std;

class Container : public Base
{
	list<Item> item_list;
	list<Trigger> trigger_list;
	list<string> accept_list;
public:
	Container(string Name, string Description, string Status);
	virtual ~Container();
	virtual void print();
	void add_trigger(Trigger tg);
	void add_item(Item im);
	void add_accept(string acc);
};

#endif