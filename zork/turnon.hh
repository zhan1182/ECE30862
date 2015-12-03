#ifndef TURNON_H_
#define TURNON_H_

#include <string>
using namespace std;
class Turnon{
    string tostring;
    string action;
public:
    Turnon(string Tostring, string Action);
    virtual ~Turnon();
    virtual void print();
};

#endif
