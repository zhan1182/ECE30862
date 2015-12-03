#include <iostream>
#include <string>

#include "turnon.hh"
using namespace std;
Turnon::Turnon(string Tostring, string Action):
    tostring(Tostring), action(Action){
}
Turnon::~Turnon(){
}
void Turnon::print(){
    cout << "Type: Turnon Object" << endl;
    cout << "tostring = "+tostring+", action = "+action << endl;
}
