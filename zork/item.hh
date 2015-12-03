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
    list<Trigger> trigger_list;
    string writing;
    string action;
    Turnon* turnon;
public:
    Item(string Name, string Description, string Status, string Writing);
    virtual ~Item();
    virtual void print();
    void add_trigger(Trigger tg);
    void set_turnon(Turnon* turnon);
};

#endif
