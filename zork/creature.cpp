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



bool Creature::check_vul(list<Item*> * inventory){

	list<Item *>::iterator iter;
	Item * item_tmp;

	list<string>::iterator iter_str;

	for (iter = inventory->begin(); iter != inventory->end(); iter++){

		item_tmp = (Item *) *iter;

		for(iter_str = vul_list.begin(); iter_str != vul_list.end(); iter_str++){
			if( item_tmp->getName() == *iter_str){
            	return true;
        	}
		}

    }
    return false;
}


bool Creature::check_vul_with(string weapon){
	list<string>::iterator iter_str;

	for(iter_str = vul_list.begin(); iter_str != vul_list.end(); iter_str++){
		if( *iter_str == weapon){
            return true;
        }
	}
	
    return false;
}


