#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <iostream>
#include <stdlib.h>
#include <string>

#include "base.hh"

using namespace std;

class Room : public Base
{
	string type;
public:
	Room(string Name, string Description, string Type);
	virtual ~Room();
	virtual void print();
};

#endif