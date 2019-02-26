//
//  ritual.hpp
//  A5
//
//  Created by LuoJingming on 2017-11-28.
//  Copyright © 2017 LuoJingming. All rights reserved.
//

#ifndef _RITUAL_H_
#define _RITUAL_H_
#include <string>
#include "card.h"
#include <vector>
class Ritual: public Card {
    int cost;
    int ability_cost;
    int charge;
    std::string name;
    std::string type;
    std::string description;
public:
    Ritual(std::string n);
    int getAttack();
    void setAttack(int a);
    int getDefence();
    void setDefence(int d);
    int getAbility();
    int getCost();
    int getAbility_cost();
    std::string getDes();
    void setDes(std::string s);
    int getCharges();
    void setCharges(int c);
    int getAct();
    std::string getType();
    void setAbility_cost(int n);
    void setAbility(int n);
};
#endif

