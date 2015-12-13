#include <iostream>
#include <string>
#include <list>

#include "rapidxml/rapidxml.hpp"
#include "trigger.hh"
#include "condition.hh"
#include "room.hh"
#include "creature.hh"

using namespace std;

using namespace rapidxml;

Item* addItem(const xml_node<char>* node);
Creature* addCreature(const xml_node<char>* creature_node);

string get_room_from_add(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 2).compare("to")){
            return command.substr(i+3, command.size());
        }

    }
    return string("");
}

string get_object_from_add(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 2).compare("to")){
            return command.substr(0, i - 1);
        }
    }
    return string("");
}

void add_eval(string command, list<Room*>* room_list, const xml_node<char>* root_node){

	string object_name = get_object_from_add(command);
	string room_name = get_room_from_add(command);

	if(!object_name.compare("") | !room_name.compare("")){
        cout << "Error. Unknown command" << endl;
        return;
    }

    xml_node<char>* node = root_node->first_node();
    string node_name;
    string node_tag;

    list<Room*>::iterator iter;
    Room * room_tmp;

    while(node){

    	node_name = node->first_node("name")->value();

    	if(object_name == node_name){

    		node_tag = node->name();

    		if( node_tag == "creature"){
    			Creature * creature_tmp = addCreature(node);
    			// Add this creature to the room
    			for(iter = room_list->begin(); iter != room_list->end(); iter++){
    				room_tmp = (Room *) *iter;
    				if(room_tmp->getName() == room_name){
    					// Add the creature here
    					room_tmp->add_creature(creature_tmp);
    				}
    			}
    		}
    		else if(node_tag == "item"){
    			Item * item_tmp = addItem(node);
    			// Add this item to the room
    			for(iter = room_list->begin(); iter != room_list->end(); iter++){
    				room_tmp = (Room *) *iter;
    				if(room_tmp->getName() == room_name){
    					// Add the creature here
    					room_tmp->add_item(item_tmp);
    				}
    			}
    		}
    		else{
    			cout << "Error. Unknown object" << endl;
    		}
    		return;
    	}
        node = node->next_sibling();
    }

    cout << "Error. object not found" << endl;

    return;
}