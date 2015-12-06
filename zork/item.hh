#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "base.hh"
#include "turnon.hh"
#include "trigger.hh"

using namespace std;

class Item : public Base
{
    list<Trigger * > trigger_list;
    string writing;
    Turnon* turnon;
public:
    Item(string Name, string Description, string Status, string Writing);
    virtual ~Item();
    virtual void print();

    string getWriting();

    void add_trigger(Trigger * tg);
    void set_turnon(Turnon* turnon);
    Turnon* get_turnon();
    // special clone
    // Item * clone_object_return_pointer();

};

#endif
