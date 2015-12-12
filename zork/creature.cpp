using namespace std;

#include "creature.hh"

Creature::Creature(string Name, string Description, string Status, Attack * creature_attack):
Base(Name, Description, Status), attack(creature_attack)
{
}

Creature::~Creature()
{
}

void Creature::print(){
	cout << "Name: " << name << endl;
	cout << "Status: " << status << endl;
	cout << "# of vul: " << vul_list.size() << endl;
	cout << "# of trigger: " << trigger_list.size() << endl;
	if(attack == NULL){
		cout << "Attack: No" << endl;
	}
	else{
		cout << "Attack: Yes" << endl;
	}
}


Attack * Creature::getAttack(){
	return attack;
}



void Creature::add_trigger(Trigger * tg){
	trigger_list.push_back(tg);
}

void Creature::add_vul(string vul){
	vul_list.push_back(vul);
}



bool check_vul(list<Item*> * inventory){
	
}



