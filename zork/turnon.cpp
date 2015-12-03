#include <iostream>
#include <string>

#include "turnon.hh"
using namespace std;
Turnon::Turnon(string tostring, string action):
    tostring(tostring), action(action){
}
Turnon::~Turnon(){
}
void Turnon::print(){
    cout << "Type: Turnon Object" << endl;
    cout << "tostring = "+tostring+", action = "+action << endl;
}
