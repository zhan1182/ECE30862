using namespace std;

#include "creature.hh"

Creature::Creature(string Name, string Description, string Status, string Attack):
Base(Name, Description, Status), attack(Attack)
{
}

Creature::~Creature()
{
}

void Creature::print(){
}

void Creature::add_trigger(Trigger * tg){
	trigger_list.push_back(tg);
}

void Creature::add_vul(string vul){
	vul_list.push_back(vul);
}