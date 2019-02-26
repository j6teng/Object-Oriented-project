#include "minion.h"
#include <string>
#include "card.h"

using namespace std;


Minion::Minion(string n):Card{n}{
  if(n == "Air Elemental"){
    cost = 0;
    attack = 1;
    defence = 1;
    ability = 0;
    ability_cost = 0;
    type = "Minion";
    }
  else if(n == "Earth Elemental"){
    cost = 3;
    attack = 4;
    defence = 4;
    ability = 0;
    ability_cost = 0;
    type = "Minion";}
  else if(n == "Fire Elemental"){
    cost = 2;
    attack = 2;
    defence = 2;
    ability = 1;
    ability_cost = 0;
    description = "Whenever an opponent`s minion entres play, deal 1 damage to it.";
    type = "Minion";}
  else if(n == "Bone Golem"){
    cost = 0;
    attack = 1;
    defence = 3;
    ability = 1;
    ability_cost = 0;
    description = "Gain +1/+1 whenever a minion leaves play.";
    type = "Minion";}
  else if(n == "Potion Seller"){
    cost = 2;
    attack = 1;
    defence = 3;
    ability = 1;
    ability_cost = 0;
    description = "At the end of your turn, all your minions gain +0/+1.";
    type = "Minion";}
  else if(n == "Novice Pyromancer"){
    cost = 1;
    attack = 0;
    defence = 1;
    ability = 1;
    ability_cost = 1;
    description = "Deal 1 damage to target minion.";
    type = "Minion";}
  else if(n == "Apprentice Summoner"){
    cost = 1;
    attack = 1;
    defence = 1;
    ability = 1;
    ability_cost = 1;
    description = "Summon a 1/1 air elemental";
    type = "Minion";}
  else if(n == "Master Summoner"){
    cost = 3;
    attack = 2;
    defence = 3;
    ability = 1;
    ability_cost = 2;
    description = "Summon up to three 1/1 air elementals";
    type = "Minion";}
}

int Minion::getAttack(){
  return attack;
}

void Minion::setAttack(int a) {
	this->attack = a;
}

int Minion::getCost(){
  return cost;
}

int Minion::getDefence(){
  return defence;
}

void Minion::setDefence(int d) {
	this->defence = d;
}

int Minion::getAbility(){
  return ability;
}

int Minion::getAbility_cost(){
 return ability_cost;
}

string Minion::getDes(){
  return description;
}

void Minion::setDes(string s) {
	this->description = s;
}

string Minion::getType(){
  return type;
}

int Minion::getCharges(){};

void Minion::setCharges(int c){};

void Minion::setAbility_cost(int n){
  ability_cost = n;
}

void Minion::setAbility(int n){
  ability = n;
}


