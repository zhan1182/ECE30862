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
    bool first = true;
    list<Item*>::iterator iter = item_list.begin();
    while(iter != item_list.end()){
        Item* item = (Item*) *iter;
        if(first)
            cout << name+" contains "+item->getName();
        else
            cout << ", "+item->getName();
        iter++;
    }
    cout << "." << endl;
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


bool Container::look_acceptance_by_item_name(string it_name){
    if (accept_list.empty()){
        return true;
    }
    list<string>::iterator iter;
    for (iter = accept_list.begin(); iter != accept_list.end(); iter++){
        if( *iter == it_name){
            return true;
        }
    }
    return false;
}


list<Item *> * Container::get_item_list_ptr(){
    return &item_list;
}

void Container::remove_item_from_list(string it_name){

    list<Item *>::iterator iter;
    Item * it_tmp;

    for (iter = item_list.begin(); iter != item_list.end(); iter++){

        it_tmp = (Item *) *iter;

        if( it_tmp->getName() == it_name){
            item_list.erase(iter);
            break;
        }
    }
    return;
}
