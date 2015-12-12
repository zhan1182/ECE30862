using namespace std;

#include "room.hh"

Room::Room(string Name, string Description, string Status, string Type):
    Base(Name, Description, Status), type(Type)
{
}

Room::~Room()
{
	
}

void Room::print(){
	cout << "Name: " << name << " " << "Type: " << type << endl;
	cout << "Trigger number: " << trigger_list.size() << endl;
}


string Room::getType(){
	return type;
}


// Add element to list
void Room::add_trigger(Trigger * tg){
	trigger_list.push_back(tg);
}

void Room::add_item(Item * im){
	item_list.push_back(im);
}

void Room::add_border(Border * br){
	border_list.push_back(br);
}

void Room::add_container(Container * cont){
	container_list.push_back(cont);
}
void Room::add_creature(Creature * cr){
	creature_list.push_back(cr);
}


// Search element in list
string Room::search_direction(const char* direction){
    list<Border*>::iterator iter = border_list.begin();
    while(iter != border_list.end()){
        Border* border = (Border*) *iter;
        if(!border->getDirection().compare(direction))
            return border->getName();
        else
            iter++;
    }
    return "";
}

// Get element from list (POP element by name)

// Trigger * Room::get_trigger(string trigger_name){
//     list<Trigger*>::iterator iter;
//     for (iter = trigger_list.begin(); iter != trigger_list.end(); iter++){
//         Trigger * tr = (Trigger *) *iter;
//         if( tr->getName() == trigger_name){
//             cout << tr->getName() << endl;
//         }
//     }
//     return NULL;
// }


Item * Room::get_item(string item_name){
    // Iters
    list<Item*>::iterator iter;
    list<Container *>::iterator cont_iter;

    // Tmp variable
    Item * it_tmp;
    Item * return_item;
    Container * cont_tmp;

    // Search item under room
    for (iter = item_list.begin(); iter != item_list.end(); iter++){

        it_tmp = (Item *) *iter;

        if( it_tmp->getName() == item_name){
            // tmp variable
            return_item = *iter;
            item_list.erase(iter);
            return return_item;
        }
    }

    // Search item under every container
    for (cont_iter = container_list.begin(); cont_iter != container_list.end(); cont_iter++){

        cont_tmp = (Container *) *cont_iter;

        if( cont_tmp->getStatus() == "locked" || cont_tmp->getStatus() == "unopened"){
            continue;
        }
        for (iter = cont_tmp->get_item_list_ptr()->begin(); iter != cont_tmp->get_item_list_ptr()->end(); iter++){

            it_tmp = (Item *) *iter;

            if( it_tmp->getName() == item_name){
                // tmp variable
                return_item = *iter;

                cont_tmp->get_item_list_ptr()->erase(iter);

                return return_item;
            }
        }
    }

    return NULL;
}


Border * Room::get_border(string border_name){
    list<Border*>::iterator iter;
    for (iter = border_list.begin(); iter != border_list.end(); iter++){
        if( ((Border *) *iter)->getName() == border_name){
            // tmp variable
            Border * return_border = *iter;
            border_list.erase(iter);
            return return_border;
        }
    }
    return NULL;
}

Container * Room::get_container(string container_name){
    list<Container*>::iterator iter;
    for (iter = container_list.begin(); iter != container_list.end(); iter++){
        if( ((Container *) *iter)->getName() == container_name){
            // tmp variable
            Container * return_container = *iter;
            container_list.erase(iter);
            return return_container;
        }
    }
    return NULL;
}



Creature * Room::get_creature(string creature_name){
    list<Creature*>::iterator iter;
    for (iter = creature_list.begin(); iter != creature_list.end(); iter++){
        if( ((Creature *) *iter)->getName() == creature_name){
            // tmp variable
            Creature * return_creature = *iter;
            creature_list.erase(iter);
            return return_creature;
        }
    }
    return NULL;
}

// Need search_item in container class
// Item* Room::search_item_container(string name){
//     list<Container*>::iterator iter = container_list.begin();
//     while(iter != container_list.end()){
        

//     }
// }

Container * Room::search_container(string cont_name){
    list<Container*>::iterator iter;
    for (iter = container_list.begin(); iter != container_list.end(); iter++){
        if( ((Container *) *iter)->getName() == cont_name){
            // tmp variable
            Container * return_container = *iter;
            return return_container;
        }
    }
    return NULL;
}