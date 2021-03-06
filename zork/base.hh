#ifndef BASE_H_
#define BASE_H_


#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Base
{
public:
    Base(string Name, string Description, string Status);
    virtual ~Base();
    virtual void print();
    virtual string getName();
    virtual string getDes();
    virtual string getStatus();
    virtual void changeStatus(string Status);
protected:
    const string name;
    const string description;
    string status;
};


#endif
