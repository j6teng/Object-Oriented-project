#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
#include <vector>
class Card {
  std::string name;  
  int act = 1;
  std::vector<Card*> Ench;
public:
  Card(std::string n);
  std::string getName();
  int getAct();
  void setAct(int a);
  virtual int getAttack()=0;
  virtual void setAttack(int a) = 0;
  virtual int getDefence()=0;
  virtual void setDefence(int d) = 0;
  virtual int getAbility()=0;
  virtual void setAbility(int n)=0;
  virtual int getCost()=0;
  virtual int getAbility_cost()=0;
  virtual void setAbility_cost(int n)=0;
  virtual std::string getDes() = 0;
  virtual void setDes(std::string s) = 0;
  virtual int getCharges() = 0;   
  virtual std::string getType() = 0;
  virtual void setCharges(int c)=0;
  std::vector<Card*> getEnch();
  void setEnch(Card* c);
  void removeEnch();
};
#endif
