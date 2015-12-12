#ifndef ATTACK_H_
#define ATTACK_H_


#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

#include "condition.hh"

using namespace std;


class Attack
{

    string print_message;
    list<string> action_list;
    Condition * condition_ptr;

public:
    Attack(string Print_Message, Condition * Condition_Ptr);
    virtual ~Attack();
    virtual void print();
    virtual void add_action(string Action);
};


#endif
