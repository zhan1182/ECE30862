#include <iostream>
#include <string>
#include <list>

#include "rapidxml/rapidxml.hpp"
#include "trigger.hh"
#include "condition.hh"


using namespace std;

using namespace rapidxml;

Condition* addCondition(const xml_node<char>* condition_node);


Trigger * addTrigger(const xml_node<char>* node){
	if(node == NULL){
        cout << "item node is null" << endl;
        return NULL;
    }
    if(string(node->name()).compare("trigger")){
        cout << node->name() << endl;
        cout << "Type of node is not item" << endl;
        return NULL;
    }

    string type = "single";
    string command;
    string print_message;

    if(node->first_node("type")){
        type = node->first_node("type")->value();
    }
    if(node->first_node("command")){
        command = node->first_node("command")->value();
    }
    if(node->first_node("print")){
        print_message = node->first_node("print")->value();
    }

    Trigger * new_trigger = new Trigger(type, command, print_message);

    // add actions
    xml_node<char>* action_node = node->first_node("action");
    while(action_node){
        new_trigger->add_action(action_node->value());
        action_node = action_node->next_sibling("action");
    }

    // add condition
    xml_node<char>* condition_node = node->first_node("condition");
    while(condition_node){
        new_trigger->add_condition(addCondition(condition_node));
        condition_node = condition_node->next_sibling("condition");
    }

    return new_trigger;
}