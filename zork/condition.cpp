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


void Condition::setObject(string Object){
	object = Object;
}
void Condition::setOwner(string Owner){
	owner = Owner;
}
void Condition::setHas(string Has){
	has = Has;
}
void Condition::setStatus(string Status){
	status = Status;
}