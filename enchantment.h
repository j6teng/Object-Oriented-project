#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include <string>
#include "card.h"
#include <vector>

class Enchantment: public Card {
  int cost;
  std::string name;
  std::string type;
  std::string description = "";
public:
  Enchantment(std::string n);
  int getAttack();
  void setAttack(int a);
  int getDefence();
  void setDefence(int d);
  int getAbility();
  int getAbility_cost();
  int getCost();
  int getCharges();
  std::string getDes();
  void setDes(std::string s);
  std::string getType();
  void setCharges(int c);  
  void setAbility_cost(int n);
  void setAbility(int n);
};

#endif

