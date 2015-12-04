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
};

#endif
