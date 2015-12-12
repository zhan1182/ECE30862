using namespace std;

#include "container.hh"

Container::Container(string Name, string Description, string Status):
Base(Name, Description, Status)
{
}

Container::~Container()
{
}

void Container::print(){
}

void Container::open_print(){
    if(item_list.begin() == item_list.end()){
        cout << name+" is empty." << endl;
        return;
    }
    cout << name+" contains ";
    bool first = true;
    list<Item*>::iterator iter = item_list.begin();
    while(iter != item_list.end()){
        Item* item = (Item*) *iter;
        if(first)
            cout << " contains "+item->getName();
        else
            cout << ", "+item->getName();

    }
}

void Container::add_trigger(Trigger * tg){
	trigger_list.push_back(tg);
}

void Container::add_item(Item * im){
	item_list.push_back(im);
}

void Container::add_accept(string acc){
	accept_list.push_back(acc);
}


string Container::getAcceptByName(string name){
    
}