#include <string>
#include "card.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

Player::Player(std::string n,int num):name{n},player_num{num}{};

string minion_set[8] = {"Air Elemental","Earth Elemental","Fire Elemental","Bone Golem","Potion Seller","Novice Pyromancer","Apprentice Summoner","Master Summoner"};
string spell_set[6] = {"Banish","Unsummon","Recharge","Disenchant","Raise Dead","Blizzard"};
string enchantment_set[5] = {"Giant Strength","Enrage","Haste","Magic Fatigue","Silence"};
string ritual_set[3] ={"Dark Ritual","Aura of Power","Standstill"};

void Player::init_deck(string name){
    for(int i = 0;i<8;i++){
        if(minion_set[i] == name){
            Card* my_card = new Minion{name};
            deck.push_back(my_card);
        }
    }
    for(int i = 0;i<6;i++){
        if(spell_set[i] == name){
            Card* my_card = new Spell{name};
            deck.push_back(my_card);
        }
    }
    for(int i = 0;i<5;i++){
        if(enchantment_set[i] == name){
            Card* my_card = new Enchantment{name};
            deck.push_back(my_card);
        }
    }
    for(int i = 0;i<3;i++){
        if(ritual_set[i] == name){
            Card* my_card = new Ritual{name};
            deck.push_back(my_card);
        }
    }
}
void Player::shuff(){
    random_device r;
    mt19937 g(r());
    shuffle(deck.begin(),deck.end(),g);
}
void Player::checkBoneGolem(){
    const string name = "Bone Golem";
    int trigger = -1;
    for(unsigned i = 0; i<board_M.size();i++){
        if(board_M[i]->getName() == name){
            trigger = i;
        }
    }
    if(trigger != -1){
       if(board_M[trigger]->getAbility() == 1){
        int is_available = board_M[trigger]->getAbility();
        if(is_available != 0){
            int cA = board_M[trigger]->getAttack();
            int cD = board_M[trigger]->getDefence();
            board_M[trigger]->setAttack(cA + 1);
            board_M[trigger]->setDefence(cD + 1);
        }
    }
  }
}

void Player::checkFireElemental(){
    const string name = "Fire Elemental";
    int trigger = -1;
    for(unsigned i = 0; i<opposite->board_M.size();i++){
        if(opposite->board_M[i]->getName() == name){
            trigger = i;
        }
    }
    if(trigger != -1){
        int is_available = opposite->board_M[trigger]->getAbility();
        if(is_available != 0){
            if(board_M.back()->getType() == "Minion"){
                int cD = board_M.back()->getDefence();
                board_M.back()->setDefence(cD - 1);
                if(board_M.back()->getDefence() <= 0){
                    move_to_graveyard(board_M.back());
                    opposite->checkBoneGolem();
                }
            }
        }
  }
}

void Player::checkPotionSeller(){
    const string name = "Potion Seller";
    int trigger = -1;
    for(unsigned i = 0; i<board_M.size();i++){
        if(board_M[i]->getName() == name){
            trigger = i;
        }
    }
    if(trigger != -1){
       if(board_M[trigger]->getAbility() == 1){
        for(unsigned i = 0; i < board_M.size();i++){
            int aD = board_M[i]->getDefence();
            board_M[i]->setDefence(aD + 1);
        }
    }
  }
}

void Player::move_to_graveyard(Card* target){
    checkBoneGolem();
    int index = 0;
    const string cname = target->getName();
    Card* my_card = new Minion{cname};
    for(unsigned i = 0; i<board_M.size();i++){
        if(board_M[i]->getName() == cname){
            index = i;
        }
    }
    board_M.erase(board_M.begin()+ index);
    graveyard.push_back(my_card);
}

void Player::attack_p(int n){
    if(n< 1 || n > 5){
        cerr << "invalid ranged" << endl;
    }
    else{
        Card* my_card = board_M[n-1];
        int attack = my_card->getAttack();
        int act = my_card->getAct();
        if(act == 0){
            throw InvalidMove();       
        }
        else {
            opposite->life = opposite->life - attack;
            int act_c = my_card->getAct();
            my_card->setAct(act_c - 1);
        }
    }
}

void Player::attack_m(int n,int m){
    Card* my_card = board_M[n-1];
    int act = my_card->getAct();
    Card* oppo_card = opposite->board_M[m-1];
    int mAttack = my_card->getAttack();
    int oAttack = oppo_card->getAttack();
    int mDefence = my_card->getDefence();
    int oDefence = oppo_card->getDefence();
    int diff_m = oDefence-= mAttack;
    int diff_o = mDefence-= oAttack;
    if(act == 0){
        throw InvalidMove();
    }
    else{
        int act_c = my_card->getAct();
        my_card->setAct(act_c - 1);
        if(diff_m <= 0){
            opposite->move_to_graveyard(oppo_card);
            checkBoneGolem();
        }
        else {
            oppo_card->setDefence(diff_m);
        }
        if(diff_o <= 0){
            move_to_graveyard(my_card);
            opposite->checkBoneGolem();
        }
        else{
            int cD_update = my_card->getDefence();
            my_card->setDefence(cD_update - oAttack);
            
        }
    }
}

void Player::move_to_graveyard_for_Spells(Card* target){
    int index = 0;
    const string cname = target->getName();
    Card* my_card = new Spell{cname};
    for(unsigned i = 0; i<board_M.size();i++){
        if(board_M[i]->getName() == cname){
            index = i;
        }
    }
}

void Player::play_p(int n){
    if(n< 1 || n > 5){
        throw InvalidMove();
    }
    else{
        Card* my_card = hand[n-1];
        int cost = my_card->getCost(); 
        if(magic - cost < 0) {
          if(is_test == 0){
            throw InvalidMove();
          }
          else{
            magic =0;
          }
        }
        string name = my_card->getName();
        if(name == "Blizzard"){
            int size_o = opposite->board_M.size();
            int size_m = board_M.size();
            for(int i = 0;i<size_o;i++){
                int de = opposite->board_M[i]->getDefence();
                if(de - 2 <= 0){
                    Card* o_card = opposite->board_M[i];
                    opposite->move_to_graveyard(o_card);
                    checkBoneGolem();
                }
                else{
                    opposite->board_M[i]->setDefence(de-2);
                }
            }
            for(int i = 0;i<size_m;i++){
                int ae = board_M[i]->getDefence();
                if(ae - 2 <= 0){
                    move_to_graveyard(board_M[i]);
                    opposite->checkBoneGolem();
                }
                else{
                    board_M[i]->setDefence(ae-2);
                }
            }
            move_to_graveyard_for_Spells(my_card);
        }
        else if (name == "Recharge") {
            int oc = ritual->getCharges();
            if(h_ritual == 1){
                ritual->setCharges(oc + 3);
                move_to_graveyard_for_Spells(my_card);
            }
            else{
                return;
            }
        }
        else if(name == "Air Elemental"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            checkFireElemental();
        }
        else if(name == "Earth Elemental"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            checkFireElemental();
        }
        else if(name == "Bone Golem"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            trigger_Bone_Golem = 1;
            checkFireElemental();
        }
        else if(name == "Fire Elemental"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            trigger_Fire_Elemental = 1;
            checkFireElemental();
        }
        else if(name == "Potion Seller"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            trigger_Potion_Seller = 1;
            checkFireElemental();
        }
        else if(name == "Novice Pyromancer"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            checkFireElemental();
        }
        else if(name == "Apprentice Summoner"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            checkFireElemental();
        }
        else if(name == "Master Summoner"){
            triiger_card_type = 1;
            board_M.push_back(my_card);
            checkFireElemental();
        }
        else if(name == "Dark Ritual"){
            h_ritual = 1;
            ritual = my_card;
        }
        else if(name == "Aura of Power"){
            h_ritual = 1;
            ritual = my_card;
        }
        else if(name == "Standstill"){
            h_ritual = 1;
            ritual = my_card;
        }
        else if(name == "Raise Dead"){
            if(graveyard.size() != 0){
                for(int i = graveyard.size() - 1;i>=0;i--){
                    Card* my_card = graveyard[i];
                    string type = my_card->getType();
                    if(type == "Minion"){
                        my_card->setDefence(1);
                        board_M.push_back(my_card);
                        graveyard.erase(graveyard.begin()+ i);
                    }
                }
            }
        }
        else{
            throw InvalidMove();
        }
        hand.erase(hand.begin() + (n - 1));
        magic -= cost;    
    }    
}

void Player::move_to_graveyard_for_Rituals(Card* target){
    delete ritual;
}

void Player::play_m(int i, int p, char t) {
    Card* my_card = hand[i - 1];
    int cost = my_card->getCost();      
    if(magic - cost < 0) {
        if(is_test == 0){
            throw InvalidMove();
          }
        else{
            magic =0;
          }
    }
    const string type = my_card->getType();
    if (type == "Spell") {
        const string name = my_card->getName();
        if (name == "Banish" && t == 'r') {
            if (p == 1) {
                Card* my_board_card = ritual;
                move_to_graveyard_for_Rituals(my_board_card);
                h_ritual = 0;
            }
            else {
                Card* my_board_card = opposite->ritual;
                opposite->move_to_graveyard_for_Rituals(my_board_card);
                opposite->h_ritual = 0;
            }
        }
    }
    magic -= cost;  
}


void Player::play_m(int i,int p,int t){
    Card* my_card = hand[i-1];
    int cost = my_card->getCost();
    magic -= cost;         
    if(magic - cost < 0) {
        if(is_test = 0){
            throw NoAct();
            return;
          }
        else{
            magic =0;
          }
    }
    if(opposite->hand.size() == 0 && p == 2){
        throw InvalidMove();
        return;
    }
    Card* oppo_card = opposite->hand[t-1];
    const string type = my_card->getType();
    if (type == "Enchantment") {
        const string name = my_card->getName();
        if (name == "Giant Strength") {
            if(p == 1){
                Card* my_board_card = board_M[t];
                int ca = my_board_card->getAttack();
                int cd = my_board_card->getDefence();
                my_board_card->setAttack(ca + 2);
                my_board_card->setDefence(cd + 2);
                my_board_card->setEnch(my_card);
            }
            else{
                Card* oppo_board_card = opposite->board_M[t];
                int ca = oppo_board_card->getAttack();
                int cd = oppo_board_card->getDefence();
                oppo_board_card->setAttack(ca + 2);
                oppo_board_card->setDefence(cd + 2);
                oppo_board_card->setEnch(my_card);
            }
        }
        else if (name == "Enrage") {
            if(p == 1){
                Card* my_board_card = board_M[t];
                int ca = my_board_card->getAttack();
                int cd = my_board_card->getDefence();
                my_board_card->setAttack(ca * 2);
                my_board_card->setDefence(cd * 2);
                my_board_card->setEnch(my_card);
            }
            else{
                Card* oppo_board_card = opposite->board_M[t];
                int ca = oppo_board_card->getAttack();
                int cd = oppo_board_card->getDefence();
                oppo_board_card->setAttack(ca * 2);
                oppo_board_card->setDefence(cd * 2);
                oppo_board_card->setEnch(my_card);
            }
        }
        else if (name == "Haste") {
            if(p == 1){
                Card* my_board_card = board_M[t];
                int mA = my_board_card->getAct();
                my_board_card->setAct(mA + 1);
                my_board_card->setEnch(my_card);
            }
            else{
                Card* oppo_board_card = opposite->board_M[t];
                int mA = oppo_board_card->getAct();
                oppo_board_card->setAct(mA + 1);                
                oppo_board_card->setEnch(my_card);
            }
        }
        else if (name == "Magic Fatigue") {
            if(p == 1){
                Card* my_board_card = board_M[t];
                my_board_card->setEnch(my_card);
                int my_board_card_AC = my_board_card->getAbility_cost();
                my_board_card->setAbility_cost(my_board_card_AC + 2);
            }
            else{
                Card* oppo_board_card = opposite->board_M[t];
                oppo_board_card->setEnch(my_card);
                int oppo_board_card_AC = oppo_board_card->getAbility_cost();
                oppo_board_card->setAbility_cost(oppo_board_card_AC + 2);
            }
        }
        else if(name == "Silence"){
            if(p == 1){
                Card* my_board_card = board_M[t];
                my_board_card->setAbility(0);
                my_board_card->setEnch(my_card);
            }
            else{
                Card* oppo_board_card = opposite->board_M[t];
                oppo_board_card->setAbility(0);
                oppo_board_card->setEnch(my_card);
            }
        }
    }
    else if(type == "Spell"){
        const string name = my_card->getName();
        if (name == "Banish") {
            if (p == 1) {
                Card* my_board_card = board_M[t];
                move_to_graveyard(my_board_card);
            }
            else {
                Card* my_board_card = opposite->board_M[t];
                opposite->move_to_graveyard(my_board_card);
            }
        }
        else if(name == "Unsummon"){
            if(p == 1){
                Card* my_card = board_M[t];
                const string cname = my_card->getName();
                Card* n_card = new Minion{cname};
                board_M.erase(board_M.begin()+ t);
                checkBoneGolem();
                opposite->checkBoneGolem();
                if(hand.size() <5){
                    hand.push_back(n_card);
                }
            }
            else{
                Card* my_card = opposite->board_M[t];
                const string cname = my_card->getName();
                Card* n_card = new Minion{cname};
                opposite->board_M.erase(opposite->board_M.begin()+ t);
                checkBoneGolem();
                opposite->checkBoneGolem();                
                if(opposite->hand.size() <5){
                    opposite->hand.push_back(n_card);
                }
            }
        }
        else if(name == "Disenchant"){
            if(p == 1){
                Card* my_card = board_M[t];
                Card* Ench_c = my_card->getEnch().back();
                if(Ench_c->getName() == "Silence"){
                    my_card->setAbility(1);
                }
                else if(Ench_c->getName() == "Giant Strenth"){
                    int aC = my_card->getAttack();
                    int aD = my_card->getDefence();
                    if(aD - 2 <= 0){
                        move_to_graveyard(my_card);
                    }
                    else{
                        my_card->setAttack(aC - 2);
                        my_card->setDefence(aC - 2);
                        my_card->removeEnch();
                    }
                }
                else if(Ench_c->getName() == "Enrage"){
                    int aC = my_card->getAttack();
                    int aD = my_card->getDefence();
                    if(aD % 2 == 1){
                        my_card->setAttack(aC % 2);
                        my_card->setDefence(1);
                    }
                    else{
                        my_card->setAttack(aC % 2);
                        my_card->setDefence(aD % 2);
                    }
                    my_card->removeEnch();
                }
              else{
                my_card->removeEnch();
              }
            }
            else{
                Card* my_card = opposite->board_M[t];
                Card* Ench_c = my_card->getEnch().back();
                if(Ench_c->getName() == "Silence"){
                    my_card->setAbility(1);
                }
                else if(Ench_c->getName() == "Giant Strenth"){
                    int aC = my_card->getAttack();
                    int aD = my_card->getDefence();
                    if(aD - 2 <= 0){
                        opposite->move_to_graveyard(my_card);
                    }
                    else{
                        my_card->setAttack(aC - 2);
                        my_card->setDefence(aC - 2);
                        my_card->removeEnch();
                    }
                }
                else if(Ench_c->getName() == "Enrage"){
                    int aC = my_card->getAttack();
                    int aD = my_card->getDefence();
                    if(aD % 2 == 1){
                        my_card->setAttack(aC % 2);
                        my_card->setDefence(1);
                    }
                    else{
                        my_card->setAttack(aC % 2);
                        my_card->setDefence(aD % 2);
                    }
                    
                    my_card->removeEnch();
                }
              else{
                my_card->removeEnch();
              }
            }
        }
    }
    hand.erase(hand.begin() + (i - 1));
    
}

void Player::use_p(int i){
    Card* my_card = board_M[i-1];
    int cost = my_card->getAbility_cost();
    string name = my_card->getName(); 
    if(magic - cost <= 0) {
        if(is_test == 0){
            throw NoAct();
          }
        else{
            magic =0;
          }
    }
    if(my_card->getAbility() == 1){
    if(name == "Apprentice Summoner"){
        if(board_M.size() < 6){
            Card* aC = new Minion{"Air Elemental"};
            board_M.push_back(aC);
            if(h_ritual == 1){
              string name = ritual->getName();
              int charges_p = ritual->getCharges();
                if (name == "Aura of Power") {
                    Card* target_c = board_M.back();
                    int tA = target_c->getAttack();
                    int tD = target_c->getDefence();
                    target_c->setAttack(tA + 1);
                    target_c->setDefence(tD + 1);
                    ritual->setCharges(charges_p - 1);
                      if (ritual->getCharges() <= 0) {
                        move_to_graveyard_for_Rituals(ritual);
                        h_ritual = 0;
                        }
                   checkFireElemental();      
                }
                else if(name == "Standstill"){
                  Card* target_c = board_M.back();
                  move_to_graveyard(target_c);
                  ritual->setCharges(charges_p - 2);
                      if (ritual->getCharges() <= 0) {
                        move_to_graveyard_for_Rituals(ritual);
                        h_ritual = 0;
                        }
                }                  
              }
            else{            
            checkFireElemental(); 
             }
       }
    }
    else if(name == "Master Summoner"){
        int count = 3;
        while(board_M.size() < 6){
            if(count > 0){
                string name = "Air Elemental";
                Card* aC = new Minion{name};
                board_M.push_back(aC);
            if(h_ritual == 1){
              string name = ritual->getName();
              int charges_p = ritual->getCharges();
                if (name == "Aura of Power") {
                    Card* target_c = board_M.back();
                    int tA = target_c->getAttack();
                    int tD = target_c->getDefence();
                    target_c->setAttack(tA + 1);
                    target_c->setDefence(tD + 1);
                    ritual->setCharges(charges_p - 1);
                      if (ritual->getCharges() <= 0) {
                        move_to_graveyard_for_Rituals(ritual);
                        h_ritual = 0;
                        }
                   checkFireElemental();      
                }
                else if(name == "Standstill"){
                  Card* target_c = board_M.back();
                  move_to_graveyard(target_c);
                  ritual->setCharges(charges_p - 2);
                      if (ritual->getCharges() <= 0) {
                        move_to_graveyard_for_Rituals(ritual);
                        h_ritual = 0;
                        }
                }                  
              }
            else{            
            checkFireElemental(); 
             }
                count --;
            }
            else{
                break;
            }
        }
    }
  }
  magic -= cost; 
}

void Player::use_m(int i,int p,int t){
    Card* my_card = board_M[i-1];
    int cost = my_card->getAbility_cost();
    string name = my_card->getName();      
    if(magic - cost <= 0) {
        if(is_test == 0){
            throw NoAct();
          }
        else{
            magic =0;
          }
    }
    if(my_card->getAbility() == 1){
    if(name == "Novice Pyromancer"){
        if(p == 1){
            int aD = board_M[t]->getDefence();
            board_M[t]->setDefence(aD - 1);
            if(aD - 1 <= 0){
                move_to_graveyard(board_M[t]);
            }
        }
        else{
            int aD = opposite->board_M[t]->getDefence();
            opposite->board_M[t]->setDefence(aD - 1);
            if(aD - 1 <= 0){
                opposite->move_to_graveyard(opposite->board_M[t]);
            }
        }
    }
        magic -= cost;   
  }
}

bool not_member(int* nums, int n,int size) {
    for(int i = 0; i < size; i++) {
        if(n == nums[i]) {
            return false;
        }
    }
    return true;
}

void Player::randomGenerate(int lower, int upper,int size,int* target) {
    int i = 0;
    while(i < size) {
        srand(time(0));
        int n = rand()%23;
        if(not_member(target,n,23)){
            target[i] = n;
            i++;
        }
    }
}


void Player::discard(int n){
  hand.erase(hand.begin()+ n);
}

 
void Player::showhand() {
    vector <card_template_t> h;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i]->getType() == "Minion") {
            if (hand[i]->getAbility() == 0) {
                Card *m = hand[i];
                h.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
            }
            else if (hand[i]->getAbility_cost() == 0) {
                Card *m = hand[i];
                h.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
            }
            else {
                Card *m = hand[i];
                h.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(),
                                                             m->getAbility_cost(), m->getDes()));
            }
        }
        else if (hand[i]->getType() == "Ritual") {
            string n = hand[i]->getName();
            int c = hand[i]->getCost();
            int rc = hand[i]->getAbility_cost();
            string rd = hand[i]->getDes();
            int rch = hand[i]->getCharges();
            h.push_back(display_ritual(n, c, rc, rd, rch));
            
        }
        else if (hand[i]->getType() == "Spell") {
            Card *m = hand[i];
            h.push_back(display_spell(m->getName(), m->getCost(), m->getDes()));
        }
        else if (hand[i]->getType() == "Enchantment") {
            Card *m = hand[i];
            if (m->getName() == "Giant Strength") {
                h.push_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDes(), "+2", "+2"));
            }
            else if (m->getName() == "Enrage") {
                h.push_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDes(), "*2", "*2"));
            }else{
                h.push_back(display_enchantment(m->getName(), m->getCost(), m->getDes()));
            }
        }
        
    }
    
    for (int x = 0; x <= 10; x++) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (int y = 0; y < hand.size(); y++) {
            cout << h.at(y).at(x);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    
    
}


void Player::showInspect(int ith){
    int i = ith - 1;
    
    // print ith minion
    vector <card_template_t> pp;
    if (board_M[i]->getAbility() == 0) {
        Card *m = board_M[i];
        pp.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
    }
    else if (board_M[i]->getAbility_cost() == 0) {
        Card *m = board_M[i];
        pp.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
    }
    else {
        Card *m = board_M[i];
        pp.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(),m->getAbility_cost(), m->getDes()));
    }
    
    for(int x=0;x<=10;x++) {
        cout<<EXTERNAL_BORDER_CHAR_UP_DOWN;
        cout<<pp.at(0).at(x);
        cout<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
    }
    
    // print all enchantments
    vector <card_template_t> ench;
    for(int a = 0; a < board_M[i]->getEnch().size(); a++){
        Card *m = board_M[i]->getEnch()[a];
        if (m->getName() == "Giant Strength") {
            ench.push_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDes(), "+2", "+2"));
        }
        else if (m->getName() == "Enrage") {
            ench.push_back(display_enchantment_attack_defence(m->getName(), m->getCost(), m->getDes(), "*2", "*2"));
        }else{
            ench.push_back(display_enchantment(m->getName(), m->getCost(), m->getDes()));
        }
    }
    for (int j = 0; j < board_M[i]->getEnch().size(); j++) {
        if (j%5 == 0){
            cout << endl;
        }
        ench.push_back(CARD_TEMPLATE_BORDER);
    }
    
    for(int x=0;x<=10;x++) {
        cout<<EXTERNAL_BORDER_CHAR_UP_DOWN;
        for(int y=0;y<board_M[i]->getEnch().size();y++) {
            cout<<ench.at(y).at(x);
        }
        cout<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
    }
}


ostream &operator<<(ostream &out, const Player &p) {
    if (p.player_num == 1) {
        /////the upper line
        cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for (int x = 1; x <= 165; x++) {
            cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
        vector <card_template_t> upper;
        /////now print the ritual
        if (p.h_ritual == 1) {
            string n = p.ritual->getName();
            int c = p.ritual->getCost();
            int rc = p.ritual->getAbility_cost();
            string rd = p.ritual->getDes();
            int rch = p.ritual->getCharges();
            upper.push_back(display_ritual(n, c, rc, rd, rch));
        }
        else {
            upper.push_back(CARD_TEMPLATE_BORDER);
        }
        /////now print the player and the empty part
        upper.push_back(CARD_TEMPLATE_EMPTY);
        upper.push_back(display_player_card(1, p.name, p.life, p.magic));
        upper.push_back(CARD_TEMPLATE_EMPTY);
        
        /////now print the graveyard
        if (p.graveyard.size() != 0) {
            if (p.graveyard.back()->getAbility() == 0) {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
            }
            else if (p.graveyard.back()->getAbility_cost() == 0) {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
            }
            else {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getAbility_cost(), m->getDes()));
            }
        }
        else {
            upper.push_back(CARD_TEMPLATE_BORDER);
        }
        /*	for (int i = 0; i < 5; i++) {
         for (int j = 0; j < 11; j++) {
         out << upper[i][j];
         }
         }
         */
        for(int x=0;x<=10;x++) {
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN;
            for(int y=0;y<=4;y++) {
                out<<upper.at(y).at(x);
            }
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
        }
        ////now print the 5 minion.
        vector <card_template_t> lower;
        int num = p.board_M.size();
        for (int i = 0; i < num; i++) {
            if (p.board_M[i]->getAbility() == 0) {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
            }
            else if (p.board_M[i]->getAbility_cost() == 0) {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
            }
            else {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(),
                                                                 m->getAbility_cost(), m->getDes()));
            }
        }
        for (int j = num; j < 5; j++) {
            lower.push_back(CARD_TEMPLATE_BORDER);
        }
        for(int x=0;x<=10;x++) {
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN;
            for(int y=0;y<=4;y++) {
                out<<lower.at(y).at(x);
            }
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
        }
        /////now print the mid part
        
        for (int x = 0; x <= CENTRE_GRAPHIC.size() - 1; x++) {
            out << CENTRE_GRAPHIC.at(x) << endl;
        }
        /////now print the second player
    }
    else {
        /////print the minion
        vector <card_template_t> lower;
        int num = p.board_M.size();
        for (int i = 0; i < num; i++) {
            if (p.board_M[i]->getAbility() == 0) {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
            }
            else if (p.board_M[i]->getAbility_cost() == 0) {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
            }
            else {
                Card *m = p.board_M[i];
                lower.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(),
                                                                 m->getAbility_cost(), m->getDes()));
            }
        }
        for (int j = num; j < 5; j++) {
            lower.push_back(CARD_TEMPLATE_BORDER);
        }
        for(int x=0;x<=10;x++) {
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN;
            for(int y=0;y<=4;y++) {
                out<<lower.at(y).at(x);
            }
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
        }
        /////now print the upper
        vector <card_template_t> upper;
        if (p.h_ritual == 1) {
            string n = p.ritual->getName();
            int c = p.ritual->getCost();
            int rc = p.ritual->getAbility_cost();
            string rd = p.ritual->getDes();
            int rch = p.ritual->getCharges();
            upper.push_back(display_ritual(n, c, rc, rd, rch));
        }
        else {
            upper.push_back(CARD_TEMPLATE_BORDER);
        }
        /////now print the player and the empty part
        upper.push_back(CARD_TEMPLATE_EMPTY);
        upper.push_back(display_player_card(1, p.name, p.life, p.magic));
        upper.push_back(CARD_TEMPLATE_EMPTY);
        
        /////now print the graveyard
        if (p.graveyard.size() != 0) {
            if (p.graveyard.back()->getAbility() == 0) {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_no_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence()));
            }
            else if (p.graveyard.back()->getAbility_cost() == 0) {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_triggered_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(), m->getDes()));
            }
            else {
                Card *m = p.graveyard.back();
                upper.push_back(display_minion_activated_ability(m->getName(), m->getCost(), m->getAttack(), m->getDefence(),
                                                                 m->getAbility_cost(), m->getDes()));
            }
        }
        else {
            upper.push_back(CARD_TEMPLATE_BORDER);
        }
        for(int x=0;x<=10;x++) {
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN;
            for(int y=0;y<=4;y++) {
                out<<upper.at(y).at(x);
            }
            out<<EXTERNAL_BORDER_CHAR_UP_DOWN<<endl;
        }
        //print bottom_boarder
        cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
        for (int x = 1; x <= 165; x++) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
    }
    return out;
}
