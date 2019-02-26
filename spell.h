//
//  spell.hpp
//  A5
//
//  Created by LuoJingming on 2017-11-28.
//  Copyright © 2017 LuoJingming. All rights reserved.
//

#ifndef _SPELL_H_
#define _SPELL_H_
#include <string>
#include "card.h"
#include <vector>

class Spell: public Card {
    int cost;
    std::string name;
    std::string description;
    std::string type;
public:
   
    Spell(std::string n);
    int getAttack();
    void setAttack(int a);
    int getDefence();
    void setDefence(int d);
    int getAbility();
    int getAbility_cost();
    int getCost();
    int getCharges();
    void setCharges(int c);
    std::string getDes();
    void setDes(std::string s);
    std::string getType();
    void setAbility_cost(int n );
    void setAbility(int n);
};
#endif

