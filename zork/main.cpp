#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#include "base.hh"
#include "room.hh"
#include "condition.hh"
#include "trigger.hh"

int main(int argc, char ** argv)
{
	// string s1 = "base";
	// string s2 = "test";

	// Base b(s1, s2);
	// Room r(s1, s2, "exit");

	// b.print();

	// r.print();

	string object = "object";
	string owner = "owner";
	string has = "has";
	string status = "status";
	string type = "type";
	string action = "action";
	string toString = "toString";
	string command = "n";

	Condition cdt(object, owner, has, status);
	Trigger trigger(cdt, type, action, toString, command);

	trigger.print();

	return EXIT_SUCCESS;
}