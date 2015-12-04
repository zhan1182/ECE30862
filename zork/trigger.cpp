
using namespace std;

#include "trigger.hh"

Trigger::Trigger(Condition CDT, string Type, string Action, string ToString, string Command):
cdt(CDT), type(Type), action(Action), toString(ToString), command(Command)
{
}

Trigger::~Trigger()
{
}

void Trigger::print()
{
	cout << "Object: " << cdt.getObject() << endl;
	cout << "Status: " << cdt.getStatus() << endl;
	cout << "Action: " << action << endl;
	cout << "Print: " << toString << endl;
	cout << "Command: " << command << endl;
}

string Trigger::getType(){
	return type;
}

string Trigger::getAction(){
	return action;
}

string Trigger::getToString(){
	return toString;
}

string Trigger::getCommand(){
	return command;
}