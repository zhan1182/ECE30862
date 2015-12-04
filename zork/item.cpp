using namespace std;

#include "item.hh"
#include "turnon.hh"

Item::Item(string Name, string Description, string Status,
           string Writing):
    Base(Name, Description, Status), writing(Writing)
{
}

Item::~Item()
{
}

void Item::print(){
    cout << "Type: Turnon Object" << endl;
    if(name.compare(""))
        cout << "Name = "+name << endl;
    if(description.compare(""))
        cout << "Description = "+description << endl;
    if(status.compare(""))
        cout << "Status = "+status << endl;
    if(writing.compare(""))
        cout << "Writing = "+writing << endl;
    
    cout << "Contain turnon:" << endl;
    turnon->print();
    cout << endl;
    
}
void Item::set_turnon(Turnon* turnon){
    this->turnon = turnon;
}
void Item::add_trigger(Trigger* tg){
    trigger_list.push_back(tg);
}

