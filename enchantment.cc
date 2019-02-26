#include "enchantment.h"
#include <string>
#include "card.h"

using namespace std;


Enchantment::Enchantment(string n):Card{n}{
  if(n == "Giant Strength"){
    cost = 1;
    type = "Enchantment";
    }
  else if(n == "Enrage"){
    cost = 2;
    type = "Enchantment";}
  else if(n == "Haste"){
    cost = 1;
    description = "Enchanted minion gains +1 action each turn";
    type = "Enchantment";}
  else if(n == "Magic Fatigue"){
    cost = 0;
    description = "Enchanted minion`s activated ability costs 2 more";
    type = "Enchantment";}
  else if(n == "Silence"){
    cost = 1;
    description = "Enchanted minion cannot use abilities";
    type = "Enchantment";}
}


int Enchantment::getCost(){
  return cost;
}
string Enchantment::getType(){
  return type;
}
string Enchantment::getDes(){
  return description;
}

void Enchantment::setDes(string s) {
	this->description = s;
}

int Enchantment::getAttack(){};
void Enchantment::setAttack(int a) {};

int Enchantment::getDefence(){};

void Enchantment::setDefence(int d) {};

int Enchantment::getAbility(){};

int Enchantment::getAbility_cost(){};

int Enchantment::getCharges(){}

void Enchantment::setCharges(int c){};
void Enchantment::setAbility_cost(int n){};
void Enchantment::setAbility(int n){};
