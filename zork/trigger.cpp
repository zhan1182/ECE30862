
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


// bool Trigger::trigger_check_condition(){

// 	if(type == "used"){
// 		return false;
// 	}

// 	if(type == "single"){
// 		type = "used";
// 	}

// 	list<Condition*>::iterator iter;
// 	Condition * condition_tmp;
// 	string owner;
// 	string object;

// 	list<Item*>::iterator iter_it;
// 	Item * item_tmp;

// 	for(iter = condition_list.begin(); iter != condition_list.end(); iter++){
// 		condition_tmp = (Condition *) *iter;
// 		owner = condition_tmp->getOwner();
// 		object = condition_tmp->getObject();

// 		// The condition is HAS
// 		if(condition_tmp->has_exist()){
// 			if(owner == "inventory"){
// 				for(iter_it = inventory->begin(); iter_it != inventory->end(); iter_it++){
// 					item_tmp = (Item *) * iter_it;
// 					if(item_tmp->getName() == object){
// 						if(condition_tmp->getHas() == "yes"){
// 							return true;
// 						}
// 					}
// 				}
// 				if(condition_tmp->getHas() == "no"){
// 					return true;
// 				}
// 				else{
// 					cout << "Error. Unknown Has type"<< endl;
// 					return false;
// 				}
// 			}
// 			else{

// 			}
// 		}
// 		else{ // The condition is Status

// 		}
// 	}

// 	return false;
// }