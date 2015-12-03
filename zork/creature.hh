#ifndef CREATURE_H_
#define CREATURE_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "trigger.hh"

using namespace std;

class Creature : public Base
{
	list<string> vul_list;
	list<Trigger> trigger_list;
public:
	Creature(string Name, string Description, string Writing, string ToString, string Action);
	virtual ~Creature();
	virtual void print();
	void add_trigger(Trigger tg);
};

#endif