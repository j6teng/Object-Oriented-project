//
//  spell.cpp
//  A5
//
//  Created by LuoJingming on 2017-11-28.
//  Copyright © 2017 LuoJingming. All rights reserved.
//

#include "spell.h"
#include <string>
#include "card.h"

using namespace std;


Spell::Spell(string n):Card{n}{
    if(n == "Banish"){
        cost = 2;
        description = "Destroy target minion or ritual";
        type = "Spell";
    }
    else if(n == "Unsummon"){
        cost = 1;
        description = "Return target minion to its owner's hand";
        type = "Spell";}
    else if(n == "Recharge"){
        cost = 1;
        description = "Your ritual gains 3 charges";
        type = "Spell";}
    else if(n == "Disenchant"){
        cost = 1;
        description = "Destroy the top enchantment on target minion";
        type = "Spell";}
    else if(n == "Raise Dead"){
        cost = 1;
        description = "Resurrect the top minion in your graveyard and set its defence to 1";
        type = "Spell";}
    else if(n == "Blizzard"){
        cost = 3;
        description = "Deal 2 damage to all minions";
        type = "Spell";}
}

int Spell::getAttack(){};

void Spell::setAttack(int a) {};

int Spell::getDefence(){};

void Spell::setDefence(int d){};

int Spell::getAbility(){};

int Spell::getAbility_cost(){};

int Spell::getCharges(){};

void Spell::setCharges(int c){};

void Spell::setDes(std::string s){};

int Spell::getCost(){
    return cost;
}
string Spell::getType(){
    return type;
}
string Spell::getDes(){
    return description;
}
void Spell::setAbility_cost(int n){};

void Spell::setAbility(int n){};

