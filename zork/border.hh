#ifndef BORDER_H_
#define BORDER_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

class Border
{
    string name;
    string direction;
public:
    Border(string Name, string Direction);
    virtual ~Border();
    virtual void print();
    string getName();
    string getDirection();
};

#endif
