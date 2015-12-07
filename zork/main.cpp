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

void parse_command(string command_str, list<Room*>* room_list, Room** currRoom, list<Item*>* inventory);
/* Note:
   Default destructor may case memory leak??
  

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
Item* addItem(const xml_node<char>* node){
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
    return new_item;
}
Room* addRoom(xml_node<char>* node, xml_node<char>* root_node){
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
    xml_node<char>* border_node = node->first_node("border");
    while(border_node){
        new_room->add_border(addBorder(border_node));
        border_node = border_node->next_sibling("border");
    }
    //Add Item
    xml_node<char>* item_node = node->first_node("item");
    while(item_node){
        string item_name = item_node->value();
        new_room->add_item(addItem(breadth_search("item", item_name, root_node->first_node("item"))));
        item_node = item_node->next_sibling("item");
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
    cout << endl;
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
    cout << item_name << endl;
    Item* item = (*currRoom)->get_item(item_name);
    if(!item){
        cout << "Error, item is not found" << endl;
        return;
    }
    inventory->push_back(item);
    cout << "Item "+item->getName()+" added to inventory" << endl;

}
void drop_eval(const string item_name, Room** currRoom, list<Item*>* inventory){
    Item* item = search_inventory(inventory, item_name);
    if(!item){
        cout << "Error, item is not found in inventory" << endl;
        return;
    }
    (*currRoom)->add_item(item);
    remove_inventory(item_name, inventory);
}

void read_eval(const string item_name, list<Item*>* inventory){
    Item* item = search_inventory(inventory, item_name);
    if(!item)
        return;

    if(!item->getWriting().compare("")){
        cout << "Error! Item does not have writing." << endl;
        return;
    }
    cout << item->getWriting() << endl;
}
void turnon_eval(const string item_name, list<Room*>* room_list, Room** currRoom, list<Item*>* inventory){
    Item* item = search_inventory(inventory, item_name);
    if(!item)
        return;

    if(!item->get_turnon()){
        cout << "Error! Item does not have turnon." << endl;
        return;
    }
    cout << item->get_turnon()->getToString() << endl;
    if(item->get_turnon()->getAction().compare(""))
        
        parse_command(item->get_turnon()->getAction(), room_list, currRoom, inventory);

}

void parse_command(string command_str, list<Room*>* room_list, Room** currRoom, list<Item*>* inventory){
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
        if(!(*currRoom)->getType().compare("exit"))
            *currRoom = NULL;
        else
            cout << "Cannot Exit!" << endl;
    }else if(!command_str.substr(0,7).compare("turn on")){
        turnon_eval(command_str.substr(8, command_str.size()-8), room_list, currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("drop")){
        drop_eval(command_str.substr(5, command_str.size()-5), currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("take")){
        take_eval(command_str.substr(5, command_str.size()-5), currRoom, inventory);
    }else if(!command_str.substr(0,4).compare("read")){
        read_eval(command_str.substr(5, command_str.size()-5), inventory);
    }
}

Room* enterRoom(list<Room*>* room_list, Room* currRoom, list<Item*>* inventory){
    cout << currRoom->getDes() << endl;
    char input[256];
    while(currRoom){
        Room* nextRoom;
        cin.getline(input, 255);
        string input_str(input);
        parse_command(input_str, room_list, &currRoom, inventory);
    }
}


int main(int argc, char ** argv)
{
    ifstream ifs("samples/itemsample.xml");
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
        Room* nextRoom = enterRoom(&room_list, currRoom, &inventory);
        currRoom = nextRoom;
    }
    cout << "Game Over" << endl;
    return EXIT_SUCCESS;
}

