using namespace std;

#include "container.hh"

Container::Container(string Name, string Description, string Status, string Type):Base(Name, Description, Status), type(Type)
{
}

Container::~Container()
{
}

void Container::print(){
}

void Container::add_trigger(Trigger tg){
	trigger_list.push_back(tg);
}

void Container::add_item(Item im){
	item_list.push_back(im);
}

void Container::add_accept(string acc){
	accept_list.push_back(acc);
}