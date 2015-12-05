using namespace std;

#include "item.hh"
#include "turnon.hh"

Item::Item(string Name, string Description, string Status,
           string Writing):
    Base(Name, Description, Status), writing(Writing)
{
    turnon = NULL;
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
    
    if(turnon){
        cout << "Contain turnon:" << endl;
        turnon->print();
        cout << endl;
    }
    
}

string Item::getWriting(){
    return writing;
}

void Item::set_turnon(Turnon* turnon){
    this->turnon = turnon;
}
void Item::add_trigger(Trigger* tg){
    trigger_list.push_back(tg);
}


// Item * Item::clone_object_return_pointer(){

//     string name = this.getName();
//     string des = this.getDes();
//     string status = this.getStatus();
//     string writing = this.getWriting();

//     Item it(name, des, status, writing);

//     list<Trigger * >::iterator iter;
//     for (iter = trigger_list.begin(); iter != trigger_list.end(); iter++){
//         it.add_trigger(iter);
//     }


// }