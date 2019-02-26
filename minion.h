#ifndef _MINION_H_
#define _MINION_H_
#include <string>
#include "card.h"
#include <vector>

class Minion: public Card {
  int cost;
  std::string name;
  std::string type;    
  int attack;
  int defence;
  int ability;
  int ability_cost;
  std::string description = "None";
public:
  Minion(std::string n);
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
  std::vector<Card*> getEnch();
  void setAbility_cost(int n);
  void setAbility(int n);
};
#endif

