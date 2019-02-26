//
//  ritual.cpp
//  A5
//
//  Created by LuoJingming on 2017-11-28.
//  Copyright © 2017 LuoJingming. All rights reserved.
//

#include "ritual.h"
#include <string>
#include "card.h"

using namespace std;


Ritual::Ritual(string n):Card{n}{
    if(n == "Dark Ritual"){
        cost = 0;
        ability_cost = 1;
        charge = 5;
        description = "At the start of your turn, gain 1 magic";
        type = "Ritual";
    }
    else if(n == "Aura of Power"){
        cost =1;
        ability_cost = 1;
        charge = 4;
        description = "Whenever a minion enters play under your control, it gains +1/+1";
        type = "Ritual";}
    else if(n == "Standstill"){
        cost =3;
        ability_cost = 2;
        charge = 4;
        description = "Whenever a minion enters play destroy it";
        type = "Ritual";}
}


int Ritual::getAttack(){};

void Ritual::setAttack(int a){};

int Ritual::getDefence(){};

void Ritual::setDefence(int d){};

int Ritual::getAbility(){};

int Ritual::getCost(){
    return cost;
}

int Ritual::getAbility_cost(){
  return ability_cost;
};

string Ritual::getDes(){
    return description;
}

void Ritual::setDes(std::string s){};

int Ritual::getCharges(){
    return charge;
}
void Ritual::setCharges(int c){
  charge = c;
};

int Ritual::getAct(){};

string Ritual::getType(){
    return type;
}
void Ritual::setAbility_cost(int n){};

void Ritual::setAbility(int n){};




