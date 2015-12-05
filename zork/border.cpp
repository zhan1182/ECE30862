#include "border.hh"
using namespace std;


Border::Border(string Name, string Direction):
name(Name), direction(Direction)
{
}
Border::~Border()
{
}
void Border::print(){
}
string Border::getName(){
    return name;
}
string Border::getDirection(){
    return direction;
}
