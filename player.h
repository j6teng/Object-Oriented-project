#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "card.h"
#include "minion.h"
#include "enchantment.h"
#include "ritual.h"
#include "spell.h"
#include <random>
#include <algorithm>
#include "ascii_graphics.h"
#include <ostream>

class InvalidMove{};

class NoAct{};

class Player {
public:
  // Test mode Trigger 
  int is_test = 0;
  // player information 
  int life = 20;
  int magic = 3;
  int player_num = 0;
  int h_ritual = 0;
  int trigger_Bone_Golem = 0;
  int trigger_Fire_Elemental = 0;
  int trigger_Potion_Seller = 0;
  int board_num = 0;
  int triiger_card_type = 0;
  //GameDisplay* gameDisplay;
  std::string name;
  // Deck;
  std::vector<Card*>deck;
  // Hand
  std::vector<Card*> hand;
  // player`s card
  std::vector<Card*> graveyard;
  std::vector<Card*> board_M;
  std::vector<Card*> board;
  Card* ritual;
  // track opposite
  Player* opposite;
  Player(std::string n,int num);
  //std::Vector<card> getHand();
  //std::Vector<card> getBoard();
  //std::Vector<Minion> getBoard_M();
 // Player* getOpposite();
 // Card* getRitual();
  void attack_p(int n);
  void attack_m(int n,int m);
  void init_deck(std::string target);
  void play_p(int n);
  void move_to_graveyard(Card* target);
  void move_to_graveyard_for_Spells(Card* target);
  void move_to_graveyard_for_Rituals(Card* target);
  void play_m(int i,int p,int t);
  void play_m(int i,int p,char t);
  void checkBoneGolem();
  void checkFireElemental();
  void checkPotionSeller();
  void use_p(int i);
  void use_m(int i,int p,int t);
  void randomGenerate(int lower, int upper,int size,int* target);
  void shuff();
  void showhand();
  void showInspect(int ith);
  void discard(int n);
};
  std::ostream &operator<<(std::ostream &out, const Player &p);
#endif


