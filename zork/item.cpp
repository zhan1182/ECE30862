using namespace std;

#include "item.hh"
// #include "trigger.hh"

Item::Item(string Name, string Description):Base(Name, Description), type(Type)
{
}

Item::~Item()
{
}

void Item::print(){
}

void Item::add_trigger(Trigger tg){
	trigger_list.push_back(tg);
}