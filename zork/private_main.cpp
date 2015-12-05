#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#include "base.hh"
#include "room.hh"
#include "item.hh"
#include "container.hh"
#include "creature.hh"

#include "trigger.hh"
#include "condition.hh"

int main(int argc, char ** argv)
{
	string name = "base";
	string des = "test";
	string status = "status";
	// Base b(s1, s2);
	Room r(name, des, status, "exit");

	// b.print();

	// r.print();

	string object = "object";
	string owner = "owner";
	string has = "has";
	// string status = "status";
	string type = "type";
	string action = "action";
	string toString = "toString";
	string command = "n";

	Condition cdt(object, owner, has, status);
	Trigger trigger(cdt, type, action, toString, command);

	trigger.print();

	r.print();
	r.add_trigger(&trigger);
	r.print();

	Item it(name, des, status, "");
	Container cont(name, des, status);

	Creature cr(name, des, status, "");

	r.add_item(&it);
	cout << "!!!!!!!!!!!!" << endl;
	Item * itt = r.get_item("dsfs");
	if(itt){
		itt->print();
	}
	else{
		cout << "not exist" << endl;
	}
	


	return EXIT_SUCCESS;
}