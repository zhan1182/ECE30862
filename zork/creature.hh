#ifndef CREATURE_H_
#define CREATURE_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "trigger.hh"
#include "attack.hh"
#include "item.hh"

using namespace std;

class Creature : public Base
{
	list<string> vul_list;
	list<Trigger * > trigger_list;
	Attack * attack;
public:
	Creature(string Name, string Description, string Status, Attack * creature_attack);
	virtual ~Creature();
	virtual void print();

	Attack * getAttack();

	void add_trigger(Trigger * tg);
	void add_vul(string vul);

	// check vul
	bool check_vul(list<Item*> * inventory);
	bool check_vul_with(string weapon);
};

#endif