using namespace std;

#include "room.hh"

Room::Room(string Name, string Description):Base(Name, Description), type(Type)
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