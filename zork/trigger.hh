
#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <stdlib.h>
#include <string>

#include "condition.hh"

class Trigger
{
	Condition cdt;
	string type;
	string action;
	string toString;
	string command;
public:
	Trigger(Condition CDT, string Type, string Action, string ToString, string Command);
	virtual ~Trigger();
	virtual void print();
};


#endif