#include <iostream>
#include <fstream>
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "base.hh"
#include "room.hh"
#include "turnon.hh"
using namespace std;
using namespace rapidxml;

xml_node<char>* breadth_search(const char* type, const char* name, xml_node<char>* node){
    if(node == 0){
        return NULL;
    }
    else if(!string(node->first_node("name")->value()).compare(name)){
        return node;
    }
    return breadth_search(type, name, node->next_sibling(type));
} 
Turnon addTurnon(xml_node<char>* node){
    return Turnon(node->first_node("tostring")->value(), node->first_node("action")->value());
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
    Room* ret = new Room(name, description, status, type); 
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
    Turnon* turnon;
    if(node->first_node("name"))
        name = node->first_node("name")->value();
    if(node->first_node("description"))
        description = node->first_node("description")->value();
    if(node->first_node("status"))
        status = node->first_node("status")->value();
    if(node->first_node("writing"))
        writing = node->first_node("writing")->value();
    if(node->first_node("turnon"))
        turnon = addTurnon(node->first_node("turnon"));
    return new item(name, description, status, writing, turnon);
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

    xml_node<char>* room_node = breadth_search("room", "room3", doc.first_node()->first_node());
    if(room_node){
        cout << room_node->first_node("description")->value() << endl;
    }
    return EXIT_SUCCESS;
}
