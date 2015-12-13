
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "condition.hh"
// #include "item.hh"

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

	list<Condition *> * get_condition_list_ptr();
	list<string> * get_action_list_ptr();

	void setType();

	void add_action(string Action);
	void add_condition(Condition * cdt_ptr);

	// Check condition
	// bool trigger_check_condition();

};


#endif