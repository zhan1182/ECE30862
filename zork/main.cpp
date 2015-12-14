#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include "rapidxml/rapidxml.hpp"
#include "base.hh"
#include "border.hh"
#include "room.hh"
#include "turnon.hh"
#include "item.hh"
using namespace std;
using namespace rapidxml;
bool victory = false;

Condition* addCondition(const xml_node<char>* condition_node);

void parse_command(string command_str, list<Room*>* room_list, Room** currRoom, list<Item*>* inventory, xml_node<char>* root_node);
/* Note:
   Default destructor may case memory leak??
   Map files contain status??

*/

const xml_node<char>* breadth_search(const char* type, const string name, const xml_node<char>* node){
    if(node == 0){
        return NULL;
    }
    else if(!string(node->name()).compare(type) & !string(node->first_node("name")->value()).compare(name)){
        return node;
    }
    return breadth_search(type, name, node->next_sibling(type));
}
 
Turnon* addTurnon(const xml_node<char>* node){
    return new Turnon(node->first_node("print")->value(), node->first_node("action")->value());
}

Border* addBorder(const xml_node<char>* node){
    return new Border(node->first_node("name")->value(), node->first_node("direction")->value());
}

Room* searchRoomName(list<Room*>* room_list, const string room_name){
    list<Room*>::iterator iter = room_list->begin();
    while(iter != room_list->end()){
        Room* room = (Room*) *iter;
        if(room->getName().compare(room_name))
            iter++;
        else
            return room;
    }
    return NULL;
}

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


Item* addItem(const xml_node<char>* node, Room* currRoom){
    if(node == NULL){
        cout << "item node is null" << endl;
        return NULL;
    }
    if(string(node->name()).compare("item")){
        cout << node->name() << endl;
        cout << "Type of node is not item" << endl;
        return NULL;
    }

    string name;
    string description;
    string status;
    string writing;

    if(node->first_node("name"))
        name = node->first_node("name")->value();
    if(node->first_node("description"))
        description = node->first_node("description")->value();
    if(node->first_node("status"))
        status = node->first_node("status")->value();
    if(node->first_node("writing"))
        writing = node->first_node("writing")->value();
    Item* new_item = new Item(name, description, status, writing);
    
    //Add turnon
    if(node->first_node("turnon"))
        new_item->set_turnon(addTurnon(node->first_node("turnon")));

    //Add Trigger in item
    xml_node<char>* trigger_node = node->first_node("trigger");
    while(trigger_node){
        Trigger * trigger_tmp = addTrigger(trigger_node);
        new_item->add_trigger(trigger_tmp);
        currRoom->add_trigger(trigger_tmp);
        trigger_node = trigger_node->next_sibling("trigger");
    }

    return new_item;
}

Container* addContainer(const xml_node<char>* container_node, const xml_node<char>* root_node, Room* currRoom){
    if(string(container_node->name()).compare("container")){
        cout << container_node->name() << endl;
        cout << "Type of node is not room" << endl;
        return NULL;
    }
    string name;
    string description;
    string status;
    
    if(container_node->first_node("name"))
        name = container_node->first_node("name")->value();
    if(container_node->first_node("description"))
        description = container_node->first_node("description")->value();
    if(container_node->first_node("status"))
        status = container_node->first_node("status")->value();
    else
        status = "unopened";
    Container* new_container = new Container(name, description, status);
    
    //Add item
    xml_node<char>* item_name_node = container_node->first_node("item");
    while(item_name_node){
        string item_name = item_name_node->value();
        new_container->add_item(addItem(breadth_search("item", item_name,
                                                       root_node->first_node("item")), currRoom));
        item_name_node = item_name_node->next_sibling("item");
    }
    
    //Add accpet
    xml_node<char>* accept_node = container_node->first_node("accept");
    while(accept_node){
        string accept_name = accept_node->value();
        new_container->add_accept(accept_name);
        accept_node = accept_node->next_sibling("accept");
    }

    //Add Trigger in container
    xml_node<char>* trigger_node = container_node->first_node("trigger");
    while(trigger_node){
        Trigger * trigger_tmp = addTrigger(trigger_node);
        new_container->add_trigger(trigger_tmp);
        currRoom->add_trigger(trigger_tmp);
        trigger_node = trigger_node->next_sibling("trigger");
    }

    return new_container;
}

Condition* addCondition(const xml_node<char>* condition_node){
    string object;
    string owner;
    string has;
    string status;
    if(condition_node->first_node("object"))
        object = condition_node->first_node("object")->value();
    if(condition_node->first_node("owner"))
        owner = condition_node->first_node("owner")->value();
    if(condition_node->first_node("has"))
        has = condition_node->first_node("has")->value();
    if(condition_node->first_node("status"))
        status = condition_node->first_node("status")->value();
    return new Condition(object, owner, has, status);
}

Attack* addAttack(const xml_node<char>* attack_node){
    string print;
    Condition* condition = NULL;
    if(attack_node->first_node("print")){
        print = attack_node->first_node("print")->value();
    }
    if(attack_node->first_node("condition")){
        condition = addCondition(attack_node->first_node("condition"));
    }
    Attack* attack_tmp = new Attack(print, condition);

    xml_node<char>* action_node = attack_node->first_node("action");
    while(action_node){
        attack_tmp->add_action(action_node->value());
        action_node = action_node->next_sibling("action");
    }
    return attack_tmp;
}

Creature* addCreature(const xml_node<char>* creature_node, Room* currRoom){
    string name = creature_node->first_node("name")->value();
    string description;
    string status;
    Attack* attack = NULL;
    if(creature_node->first_node("description"))
        description = creature_node->first_node("description")->value();
    if(creature_node->first_node("status"))
        status = creature_node->first_node("status")->value();
    if(creature_node->first_node("attack"))
        attack = addAttack(creature_node->first_node("attack"));
    Creature* creature_tmp = new Creature(name, description, status, attack);

    //Add vulnerability
    xml_node<char>* vul_node = creature_node->first_node("vulnerability");
    while(vul_node){
        creature_tmp->add_vul(vul_node->value());
        vul_node = vul_node->next_sibling("vulnerability");
    }

    //Add Trigger in creature
    xml_node<char>* trigger_node = creature_node->first_node("trigger");
    while(trigger_node){
        Trigger * trigger_tmp = addTrigger(trigger_node);
        creature_tmp->add_trigger(trigger_tmp);
        currRoom->add_trigger(trigger_tmp);
        trigger_node = trigger_node->next_sibling("trigger");
    }



    return creature_tmp;

}

Room* addRoom(const xml_node<char>* node, const xml_node<char>* root_node){
    if(string(node->name()).compare("room")){
        cout << node->name() << endl;
        cout << "Type of node is not room" << endl;
        return NULL;
    }
     
    string name;
    string description;
    string status;
    string type;
   
    if(node->first_node("name"))
        name = node->first_node("name")->value();
    if(node->first_node("description"))
        description = node->first_node("description")->value();
    if(node->first_node("status"))
        status = node->first_node("status")->value();
    if(node->first_node("type"))
        type = node->first_node("type")->value();
    Room* new_room = new Room(name, description, status, type);

    //Add Border
    xml_node<char>* border_name_node = node->first_node("border");
    while(border_name_node){
        new_room->add_border(addBorder(border_name_node));
        border_name_node = border_name_node->next_sibling("border");
    }

    //Add Item
    xml_node<char>* item_name_node = node->first_node("item");
    while(item_name_node){
        string item_name = item_name_node->value();
        new_room->add_item(addItem(breadth_search("item", item_name, root_node->first_node("item")), new_room));
        item_name_node = item_name_node->next_sibling("item");
    }

    //Add Container
    xml_node<char>* container_name_node = node->first_node("container");
    while(container_name_node){
        string container_name = container_name_node->value();

        Container * cont_tmp = addContainer(breadth_search("container", container_name,
                                                           root_node->first_node("container")),
                                            root_node, new_room);

        new_room->add_container(cont_tmp);

        container_name_node = container_name_node->next_sibling("container");
    }

    //Add creature
    xml_node<char>* creature_name_node = node->first_node("creature");
    while(creature_name_node){
        string creature_name = creature_name_node->value();
        Creature * new_creature = addCreature(breadth_search("creature", creature_name, 
                                                             root_node->first_node("creature")), new_room);
        // cout << "Creature name second: " << new_creature->getName() << " to room: " << new_room->getName() << endl;
        new_room->add_creature(new_creature);
        creature_name_node = creature_name_node->next_sibling("creature");
    }

    // add trigger
    xml_node<char>* trigger_node = node->first_node("trigger");
    while(trigger_node){
        Trigger * trigger_tmp = addTrigger(trigger_node);
        new_room->add_trigger(trigger_tmp);
        trigger_node = trigger_node->next_sibling("trigger");
    }


    return new_room;
    
}//Need add more attribute

void print_inventory(list<Item*>* inventory){
    list<Item*>::iterator iter = inventory->begin();
    if(inventory->begin() == inventory->end()){
        cout << "Inventory: empty" << endl;
        return;
    }
    bool first = true;
    cout << "Inventory: ";
    while(iter != inventory->end()){
        Item* item = (Item*) *iter;
        if(first){
            cout << item->getName();
            first = false;
        }else{
            cout << ", "+item->getName();
        }
        iter++;
    }
    cout <<endl;
}
Item* search_inventory(list<Item*>* inventory, const string item_name){
    list<Item*>::iterator iter = inventory->begin();
    if(inventory->begin() == inventory->end()){
        cout << "Error! Not found in inventory." << endl;
        return NULL;
    }
    while(iter != inventory->end()){
        Item* item = (Item*) *iter;
        if(!item->getName().compare(item_name))
            return item;
        iter++;
    }
    cout << "Error! Not found in inventory." << endl;
    return NULL;
}
void remove_inventory(const string item_name, list<Item*>* inventory){
    list<Item*>::iterator iter = inventory->begin();
    while(iter != inventory->end()){
        Item* item = (Item*) *iter;
        if(!item->getName().compare(item_name)){
            inventory->erase(iter);
            return;
        }
        iter++;
    }
}
void take_eval(const string item_name, Room** currRoom, list<Item*>* inventory){
    Item* item = (*currRoom)->get_item(item_name);
    if(!item){
        cout << "Error, item is not found" << endl;
        return;
    }
    inventory->push_back(item);
    cout << "Item "+item->getName()+" added to inventory." << endl;

}

void drop_eval(const string item_name, Room** currRoom, list<Item*>* inventory){
    Item* item = search_inventory(inventory, item_name);
    if(!item){
        cout << "Error, item is not found in inventory" << endl;
        return;
    }
    cout << item_name+" dropped." << endl;
    (*currRoom)->add_item(item);
    remove_inventory(item_name, inventory);
}
string get_creature_from_attack(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 4).compare("with"))
            return command.substr(0, i-1);

    }
    return string("");

}

string get_item_from_attack(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 4).compare("with"))
            return command.substr(i+5, command.size());

    }
    return string("");
}

void attack_eval(const string command, list<Room*>* room_list, Room** currRoom,
                 list<Item*>* inventory, xml_node<char>* root_node){
    string creature_str = get_creature_from_attack(command);
    string item_str = get_item_from_attack(command);
    if(!creature_str.compare("") | !item_str.compare("")){
        cout << "Error. Unknow attack command" << endl;
    }
    Item* item = search_inventory(inventory, item_str);
    if(!item){
        return;
    }

    // cout << "Creature name: " << creature_str << endl;
    // cout << "Size: " << (*currRoom)->

    Creature* creature = (*currRoom)->search_creature(creature_str);
    if(!creature){
        cout << "Error. Unknown creature." << endl;
        return;
    }
    if(creature->check_vul_with(item_str)){
        cout << "You assault the "+creature_str+" with "+item_str << endl;
        Attack * attack_tmp = creature->getAttack();
        if(attack_tmp == NULL){
        	return;
        }
		cout << attack_tmp->get_print_message() << endl;
        string command = attack_tmp->get_action();
        while(command.compare("")){
        	parse_command(command, room_list, currRoom, inventory, root_node);
        	command = attack_tmp->get_action();
        }
    }
}

string get_name_from_put(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 2).compare("in"))
            return command.substr(0, i-1);

    }
    return string("");

}

string get_container_from_put(const string command){
    int i;
    for(i = 0; i < command.size() - 1; ++i){
        if(!command.substr(i, 2).compare("in"))
            return command.substr(i+3, command.size());

    }
    return string("");
}

void put_eval(const string command, Room** currRoom, list<Item*>* inventory){
    string item_name = get_name_from_put(command);
    string container_name = get_container_from_put(command);
     if(!item_name.compare("") | !container_name.compare("")){
        cout << "Error. Unknown command" << endl;
        return;
    }
    Item* item = search_inventory(inventory, item_name);
    if(!item)
        return;
    Container* container = (*currRoom)->search_container(container_name);
    if(!container){
        cout << "Error. Container could not be fond." << endl;
        return;
    }
    if(container->look_acceptance_by_item_name(item_name)){
        remove_inventory(item_name, inventory);
        container->add_item(item);
        cout << "Item "+item_name+" added to "+ container_name+"." << endl;
        return;
    }
    cout << "Error. Cannot put in container" << endl;
}


void read_eval(const string item_name, list<Item*>* inventory){
    Item* item = search_inventory(inventory, item_name);
    if(!item)
        return;

    if(!item->getWriting().compare("")){
        cout << "Nothing written." << endl;
        return;
    }
    cout << item->getWriting() << endl;
}

void turnon_eval(const string item_name, list<Room*>* room_list, Room** currRoom, list<Item*>* inventory, xml_node<char>* root_node){
    Item* item = search_inventory(inventory, item_name);
    if(!item){
        return;
    }
    if(!item->get_turnon()){
        cout << "Error! Item does not have turnon." << endl;
        return;
    }
    cout << "You activate the "+item_name+"." << endl;
    cout << item->get_turnon()->getToString() << endl;
    if(item->get_turnon()->getAction().compare(""))        
        parse_command(item->get_turnon()->getAction(), room_list, currRoom, inventory, root_node);

}

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
void delete_eval(string creature_str, Room** currRoom, list<Room*>* room_list){
    list<Room*>::iterator iter = room_list->begin();
    while(iter != room_list->end()){
        Room* room = (Room*) *iter;
        Creature* creature = room->get_creature(creature_str);
        iter++;
    }
    return;
}

void add_eval(string command, list<Room*>* room_list, xml_node<char>* root_node, Room** currRoom){

    string object_name = get_object_from_add(command);
    string room_name = get_room_from_add(command);

    if(!object_name.compare("") | !room_name.compare("")){
        cout << "Error. Unknown command" << endl;
        return;
    }

    xml_node<char>* node = root_node;
    string node_name;
    string node_tag;

    list<Room*>::iterator iter;
    Room * room_tmp;

    while(node){

    	node_name = node->first_node("name")->value();

    	if(object_name == node_name){

            node_tag = node->name();

            if( node_tag == "creature"){
                Creature * creature_tmp = addCreature(node, *currRoom);
                // Add this creature to the room
                for(iter = room_list->begin(); iter != room_list->end(); iter++){
                    room_tmp = (Room *) *iter;
                    if(room_tmp->getName() == room_name){
                        // Add the creature here

                        // cout << "Creature name first: " << creature_tmp->getName() << endl;

                        room_tmp->add_creature(creature_tmp);
                    }
                }
            }
            else if(node_tag == "item"){
                Item * item_tmp = addItem(node, *currRoom);
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

void open_eval(const string container_name, Room** currRoom){
    Container* container = (*currRoom)->search_container(container_name);
    if(container){
        container->open_print();
        if(!container->getStatus().compare("unopened"))
            container->changeStatus("opened");
        return;
    }
    cout << "Container "+container_name+" does nbot exist." << endl;
    return;
}
Base* find_base_in_room(Room* room, const string item_name){
    Base* base = (Base*) room->search_item(item_name);
    if(base != NULL)
        return base;

    base = (Base*) room->search_creature(item_name);
    if(base != NULL)
        return base; 
    return NULL;
    
    
}
Base* find_base(list<Room*>* room_list, list<Item*>* inventory, const string item_name){
    Base* base = (Base*) search_inventory(inventory, item_name);
    if(base != NULL)
        return base;
    list<Room*>::iterator iter = room_list->begin();
    while(iter != room_list->end()){
        Room* room_tmp = (Room*) *iter;
        base = find_base_in_room(room_tmp, item_name);
        if(base != NULL)
            return base;
        iter++;
    }
    return NULL;
}

void update_eval(const string command, list<Room*>* room_list, list<Item*>* inventory){
    string item = get_object_from_add(command);
    string status = get_room_from_add(command);
    Base* base = find_base(room_list, inventory, item);
    
    if(base == NULL){
        cout << "Error, "+item+" not found" << endl;
        return;
    }
    base->changeStatus(status);
    // cout << item +" updated to "+status << endl;
    
}

void exec_trigger(Trigger* trigger, string command_str, list<Room*>* room_list, Room** currRoom,
                  list<Item*>* inventory, xml_node<char>* root_node){
    if(!trigger->getPrint_Message().compare("")){
        cout << trigger->getPrint_Message() << endl;
    }
    

}
void parse_command(string command_str, list<Room*>* room_list, Room** currRoom,
                   list<Item*>* inventory, xml_node<char>* root_node){
    if(!command_str.compare("n")){
        Room* nextRoom = searchRoomName(room_list, (*currRoom)->search_direction("north"));//Need search
        if(!nextRoom)
            cout << "Can't go" << endl;
        else{
            *currRoom = nextRoom;
            cout << (*currRoom)->getDes() << endl;
        }
    }else if(!command_str.compare("w")){
        Room* nextRoom = searchRoomName(room_list, (*currRoom)->search_direction("west"));//Need search
        if(!nextRoom)
            cout << "Can't go" << endl;
        else{
            *currRoom = nextRoom;
            cout << (*currRoom)->getDes() << endl;
        }
    }else if(!command_str.compare("e")){
        Room* nextRoom = searchRoomName(room_list, (*currRoom)->search_direction("east"));//Need search
        if(!nextRoom)
            cout << "Can't go" << endl;
        else{
            *currRoom = nextRoom;
            cout << (*currRoom)->getDes() << endl;
        }
    }else if(!command_str.compare("s")){
        Room* nextRoom = searchRoomName(room_list, (*currRoom)->search_direction("south"));//Need search
        if(!nextRoom)
            cout << "Can't go" << endl;
        else{
            *currRoom = nextRoom;
            cout << (*currRoom)->getDes() << endl;
        }
    }else if(!command_str.compare("i")){
        print_inventory(inventory);
    }else if(!command_str.compare("open exit")){
        if(!(*currRoom)->getType().compare("exit")){
            *currRoom = NULL;
            victory = false;
        }
        else
            cout << "Cannot Exit!" << endl;
    }else if(!command_str.substr(0,7).compare("turn on")){
        turnon_eval(command_str.substr(8, command_str.size()-8), room_list, currRoom, inventory, root_node);
    }else if(!command_str.substr(0,4).compare("drop")){
        drop_eval(command_str.substr(5, command_str.size()-5), currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("take")){
        take_eval(command_str.substr(5, command_str.size()-5), currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("read")){
        read_eval(command_str.substr(5, command_str.size()-5), inventory);
    }else if(!command_str.substr(0,3).compare("put")){
        put_eval(command_str.substr(4, command_str.size()-4), currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("open")){
        open_eval(command_str.substr(5, command_str.size()-5), currRoom);
    }else if(!command_str.substr(0,6).compare("attack")){
        attack_eval(command_str.substr(7, command_str.size()-7), room_list, currRoom, inventory, root_node);
    }else if(!command_str.substr(0,6).compare("Delete")){
        delete_eval(command_str.substr(7, command_str.size()-7), currRoom, room_list);
    }
    else if(!command_str.substr(0,6).compare("Update")){
        update_eval(command_str.substr(7, command_str.size()-7), room_list, inventory);
    } 
    else if(!command_str.substr(0,3).compare("Add")){
        add_eval(command_str.substr(4, command_str.size()-4), room_list, root_node, currRoom);
    }else if(!command_str.compare("Game Over")){
        *currRoom = NULL;
        return;
    }
}

Room* enterRoom(list<Room*>* room_list, Room* currRoom, list<Item*>* inventory, xml_node<char>* root_node){
    cout << currRoom->getDes() << endl;
    char input[256];

    Trigger * trigger_tmp;
   
    while(currRoom){
        Room* nextRoom;
        cin.getline(input, 255);
        string input_str(input);

        // cout << "Trigger number: " << currRoom->return_trigger_list()->size()<< endl;

        // Check if a trigger happens
        trigger_tmp = currRoom->room_check_trigger(input_str, inventory, currRoom->return_container_list(),
                                                   currRoom->return_item_list());
        if(trigger_tmp == NULL){
            // cout << "NULL !!!!!!!!!!!!!!" << endl;
        }
        else{
            cout << trigger_tmp->getPrint_Message() << endl;
            list<string>* action_list = trigger_tmp->get_action_list_ptr();
            list<string>::iterator iter = action_list->begin();
            while(iter != action_list->end()){
                string command = (string) *iter;
                parse_command(command, room_list, &currRoom, inventory, root_node);
                iter++;
            }
            if(trigger_tmp->getCommand() != ""){
                continue;
            }
        }
        

        parse_command(input_str, room_list, &currRoom, inventory, root_node);
    }
    if(victory)
        cout << "Victory!" << endl;
    else
        cout << "Game Over" << endl;

}


int main(int argc, char ** argv)
{
    if(argc != 2){
        cerr << "Usage: ./a.out <xmlfile>." << endl;
        return EXIT_FAILURE;
    }
    ifstream ifs(argv[1]);
    string text((istreambuf_iterator<char>(ifs)),
                istreambuf_iterator<char>());

    //Use xml parser
    xml_document<> doc;
    //Cast const char* to non-const, don't try to modify it
    doc.parse<0>(const_cast<char *>(text.c_str()));
    
    list<Room*> room_list;
    xml_node<char>* new_room_node = doc.first_node()->first_node("room");
    while(new_room_node){
        room_list.push_back(addRoom(new_room_node, doc.first_node()));
        new_room_node = new_room_node->next_sibling("room");
    }
    list<Item*> inventory;
    Room* currRoom = searchRoomName(&room_list, "Entrance");
    while(currRoom){
        Room* nextRoom = enterRoom(&room_list, currRoom, &inventory, doc.first_node()->first_node());
        currRoom = nextRoom;
    }
    return EXIT_SUCCESS;
}

