#include <iostream>
#include <fstream>
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "base.hh"
#include "border.hh"
#include "room.hh"
#include "turnon.hh"
using namespace std;
using namespace rapidxml;
/* Note:
   Default destructor may case memory leak??
  

 */
xml_node<char>* breadth_search(const char* type, const char* name, xml_node<char>* node){
    if(node == 0){
        return NULL;
    }
    else if(!string(node->first_node("name")->value()).compare(name)){
        return node;
    }
    return breadth_search(type, name, node->next_sibling(type));
} 
Turnon* addTurnon(xml_node<char>* node){
    return new Turnon(node->first_node("tostring")->value(), node->first_node("action")->value());
}
Border* addBorder(xml_node<char>* node){
    return new Border(node->first_node("name")->value(), node->first_node("direction")->value());
}
Room* addRoom(xml_node<char>* node){
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

    return new_room;
    
}//Need add more attribute

Item* addItem(xml_node<char>* node){
    if(string(node->name()).compare("room")){
        cout << node->name() << endl;
        cout << "Type of node is not room" << endl;
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
int main(int argc, char ** argv)
{
    ifstream ifs("samples/roomsample.xml");
    string text((istreambuf_iterator<char>(ifs)),
                istreambuf_iterator<char>());

    //Use xml parser
    xml_document<> doc;
    //Cast const char* to non-const, don't try to modify it
    doc.parse<0>(const_cast<char *>(text.c_str()));

    
    return EXIT_SUCCESS;
}
