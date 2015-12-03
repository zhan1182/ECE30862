using namespace std;

#include "condition.hh"

Condition::Condition(string Object, string Owner, string Has, string Status):
object(Object), owner(Owner), has(Has), status(Status)
{
}

Condition::~Condition()
{
	
}

void Condition::print(){
}

string Condition::getObject(){
	return object;
}
string Condition::getOwner(){
	return owner;
}
string Condition::getHas(){
	return has;
}
string Condition::getStatus(){
	return status;
}