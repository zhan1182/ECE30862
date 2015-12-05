#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "border.hh"
#include "base.hh"
#include "trigger.hh"
#include "item.hh"
#include "container.hh"
#include "creature.hh"

using namespace std;
/* Note:
   1. Add following search fcn
      list  keyword  return   
      border  direction room_name
      


 */
class Room : public Base
{
    string type;
    list<Item *> item_list;
    list<Trigger *> trigger_list;
    list<Border *> border_list;
    list<Container *> container_list;
    list<Creature *> creature_list;
public:
    Room(string Name, string Description, string Status, string Type);
    virtual ~Room();
    virtual void print();

    // access private fields
    virtual string getType();
    
    // add element to list
    void add_trigger(Trigger * tg);
    void add_item(Item * im);
    void add_border(Border * br);
    void add_container(Container * cont);
    void add_creature(Creature * cr);

    // Search item
    string search_direction(const char* direction);

    // Get element from list
    Trigger * get_trigger(string trigger_name);
    Item * get_item(string item_name);
    Border * get_border(string br_name);
    Container * get_container(string cont_name);
    Creature * get_creature(string cr_name);

    // Remove element from list
};

#endif
