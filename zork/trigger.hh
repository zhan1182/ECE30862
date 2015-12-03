
#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <stdlib.h>
#include <string>

#include "condition.hh"

class Trigger
{
	string type;
	Condition cdt;
public:
	Trigger(Condition CDT, string Type);
	virtual ~Trigger();
	virtual void print();
};


#endif