using namespace std;

#include "item.hh"
// #include "trigger.hh"

Item::Item(string Name, string Description, string Status, string Writing, string ToString, string Action):
Base(Name, Description, Status), writing(Writing), toString(ToString), action(Action)
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