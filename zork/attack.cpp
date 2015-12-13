using namespace std;

#include "attack.hh"

Attack::Attack(string Print_Message, Condition * Condition_Ptr):print_message(Print_Message), condition_ptr(Condition_Ptr)
{
}

Attack::~Attack()
{
}


void Attack::print(){
	cout << "Print Message: " << print_message << endl;
	cout << "Number of actions: " << action_list.size() << endl;
}

void Attack::add_action(string action){
	action_list.push_back(action);
}

string Attack::get_print_message(){
	return print_message;
}

string Attack::get_action(){
	if(action_list.empty()){
		return "";
	}
	string return_str = action_list.front();
	action_list.pop_front();
	return return_str;
}