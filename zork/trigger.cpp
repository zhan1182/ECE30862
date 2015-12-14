
using namespace std;

#include "trigger.hh"

Trigger::Trigger(string Type, string Command, string Print_Message):
type(Type), command(Command), print_message(Print_Message)
{
}

Trigger::~Trigger()
{
}

void Trigger::print()
{
	cout << "Type: " << type << endl;
	cout << "Command: " << command << endl;
	cout << "Print: " << print_message << endl;
}

string Trigger::getType(){
	return type;
}

string Trigger::getPrint_Message(){
	return print_message;
}

string Trigger::getCommand(){
	return command;
}

void Trigger::add_action(string Action){
	action_list.push_back(Action);
}

void Trigger::add_condition(Condition * cdt_ptr){
	condition_list.push_back(cdt_ptr);
}

void Trigger::setType(){
	type = "used";
}

list<Condition *> * Trigger::get_condition_list_ptr(){
	return &condition_list;
}
list<string> * Trigger::get_action_list_ptr(){
	return &action_list;
}

// cout << "Trigger number: " << currRoom->return_trigger_list()->size()<< endl;