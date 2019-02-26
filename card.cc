#include "card.h"
#include <string>

using namespace std;

Card::Card(string n) :name{ n }{};

string Card::getName(){
  return name;
}

int Card::getAct() {
	return act;
}

void Card::setAct(int a) {
	this->act = a;
}
vector<Card*> Card::getEnch() {
  return Ench;
}

void Card::setEnch(Card* c){
  Ench.emplace_back(c);
}

void Card::removeEnch() {
  Ench.pop_back();
}
