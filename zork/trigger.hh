
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "condition.hh"

class Trigger
{
	// default type = single, unless specify type as permernent
	string type;

	string command;
	string print_message;

	list<Condition *> condition_list;
	list<string> action_list;
	
public:
	Trigger(string Type, string Command, string Print_Message);
	virtual ~Trigger();
	virtual void print();

	string getType();
	string getPrint_Message();
	string getCommand();
	void add_action(string Action);
	void add_condition(Condition * cdt_ptr);
};


#endif