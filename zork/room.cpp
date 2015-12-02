using namespace std;

#include "room.hh"

Room::Room(string Name, string Description, string Type):Base(Name, Description), type(Type)
{
}

Room::~Room()
{
	
}

void Room::print(){
	cout << "Name: " << name << " " << "Type: " << type << endl;
}