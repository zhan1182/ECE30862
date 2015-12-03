using namespace std;

#include "room.hh"

Room::Room(string Name, string Description, string Status, string Type):Base(Name, Description, Status), type(Type)
{
}

Room::~Room()
{
	
}

void Room::print(){
	cout << "Name: " << name << " " << "Type: " << type << endl;
	cout << "Trigger number: " << trigger_list.size() << endl;
}

void Room::add_trigger(Trigger tg){
	trigger_list.push_back(tg);
}

void Room::add_item(Item im){
	item_list.push_back(im);
}

void Room::add_border(Border br){
	border_list.push_back(br);
}