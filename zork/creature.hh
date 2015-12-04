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
	list<Trigger * > trigger_list;
	string attack;
public:
	Creature(string Name, string Description, string Status, string Attack);
	virtual ~Creature();
	virtual void print();
	void add_trigger(Trigger * tg);
	void add_vul(string vul);
	
};

#endif