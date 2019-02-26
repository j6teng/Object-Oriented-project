#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include "card.h"
#include "player.h"
#include "ascii_graphics.h"
#include "Graphdisplay.h"

using namespace std;

void updateAllAct(Player* p){
    for(int i = 0; i < p->board_M.size() ; i++){
        int count = 0;
        vector<Card*> Ench = (p->board_M[i])->getEnch();
        for(int j = 0;j < Ench.size();j++){
            string name = Ench[j]->getName();
            if(name == "Haste"){
                count += 1;
            }
        }
        p->board_M[i]->setAct(1 + count);
    }
}


int main(int argc, char* argv[]){
    GraphDisplay* gameDisplay;
    int p1_magic = 3;
    int p2_magic = 3;
    int p1_deck_index = 4;
    int p2_deck_index = 4;
    //commond
    const string init_i = "-init";
    const string testing = "-testing";
    const string deck1 = "-deck1";
    const string deck2 = "-deck2";
    const string graphics = "-graphics";
    //Player`s name
    string p1_name = "";
    string p2_name = "";
    //Check commond line
    int init = 0;
    int test_mode = 0;
    int init_deck1 = 0;
    int init_deck2 = 0;
    int graphics_mode = 0;
    //Check who`s turn
    int turn = 1;
    //Starting fill in commond
    for(int i = 0 ; i<argc;i++){
        if(argv[i] == init_i){
            init = i;
        }
        if(argv[i] == testing){
            test_mode++;
        }
        if(argv[i] == deck1){
            init_deck1 = i;
        }
        if(argv[i] == deck2){
            init_deck2 = i;
        }
        if(argv[i] == graphics){
          graphics_mode++;
        }
    }
    //Starting initializing the game.
    ifstream initi{argv[init+1]};
    if(getline(initi,p1_name)){
        getline(initi,p2_name);
        turn = 1;
    }
    else{
        cout << "p1 name?" << endl;
        cin >> p1_name;
        cout << "p2 name?" << endl;
        cin >> p2_name;
    }
    //Initializing the player.
    Player* p1 = new Player(p1_name,1);
    Player* p2 = new Player(p2_name,2);
    //Connecting two players.
    p1->opposite = p2;
    p2->opposite = p1;
    if(graphics_mode != 0){
      gameDisplay = new GraphDisplay(1);
    }
    else{
      gameDisplay = new GraphDisplay(0);
    }
    //Number of Cards
    int p1_cards = 0;
    int p2_cards = 0;
    gameDisplay->setPlayer(p1, 1);
    gameDisplay->setPlayer(p2, 2);
    gameDisplay->boardDisplay();
    //Display if test_mode shows up;
    if(test_mode == 1){
      cout << "Running Testing Mode Be Aware" << endl;
    }
    //Initializing the decks for both players, p1 first.
    if(init_deck1 == 0){
      string card_n;
      while(cin >> card_n){
        p1_cards++;
        p1->init_deck(card_n);
    }
    if(test_mode == 0){
      p1->shuff();
    }
    }
    else{
      string deck_p1 = argv[init_deck1 + 1];
      string single_card;
      ifstream d1{deck_p1};
      while(getline(d1,single_card)){
        p1_cards++;
        p1->init_deck(single_card);
    }
    if(test_mode == 0){
      p1->shuff();
    }
  }
    //p2
    if(init_deck2 == 0){
      string card_n;
      while(cin >> card_n){
        p2_cards++;
        p2->init_deck(card_n);
    }
    if(test_mode == 0){
      p2->shuff();
    }
    }
    else{
      string deck_p2 = argv[init_deck2 + 1];
      string single_card;
      ifstream d2{deck_p2};
      while(getline(d2,single_card)){
        p2_cards++;
        p2->init_deck(single_card);
    }
    if(test_mode == 0){
      p2->shuff();
    }
  }
    //Generalizing size deck`s size random number array
    //Initializing the hands for both players, p1 first.
    for(int i = 0;i<5;i++){
        p1->hand.push_back((p1->deck).back());
        p1->deck.pop_back();
    }
    cout << endl;
    //p2
    for(int i = 0;i<5;i++){
        p2->hand.push_back((p2->deck).back());
        p2->deck.pop_back();
    }
    //Variable for chasing in-game step;
    int end = 0;
    //Game begin
    string cmd_l;
    int n = -1;
    int m = -1;
    int t = -1;
    gameDisplay->handDisplay(p1->hand);
    while(true){
        getline(cin, cmd_l);
        istringstream s1{cmd_l};
        s1 >> cmd_l;
        if(cmd_l == "attack"){
            s1 >> n;
            if(s1 >> m) {
                if(turn == 1){
                    try {
                        p1->attack_m(n,m);
                        gameDisplay->notify(p1,1);
                    } catch(InvalidMove i) {
                        cout << "Invalid Move." << endl;
                    }
                } else{
                    try {
                        p2->attack_m(n,m);
                        gameDisplay->notify(p2,2);
                    } catch(InvalidMove i) {
                        cout << "Invalid Move." << endl;
                    }
                }
            } else {
                if(turn == 1){
                    try {
                        p1->attack_p(n);
                        if(p2->life <= 0){
                          cout << "Player 1 Wins!" << endl;
                          break;
                        }
                        gameDisplay->notify(p1,1);
                    } catch(InvalidMove i) {
                        cout << "Invalid Move" << endl;
                    }
                }
                else{
                    try {
                        p2->attack_p(n);
                        if(p1->life <= 0){
                          cout << "Player 2 Wins!" << endl;
                          break;
                        }
                        gameDisplay->notify(p2,2);
                    } catch(InvalidMove i) {
                        cout << "Invalid Move" << endl;
                    }
                }
            }
        }
        else if(cmd_l == "play"){
            s1 >> n;
            if(s1 >> m) {
                char rit;
                s1 >> rit;
                if (rit == 'r') {
                    if (turn == 1) {
                        try {
                            p1->play_m(n, m, rit);
                            gameDisplay->notify(p1,1);
                            gameDisplay->handDisplay(p1->hand);
                        }
                        catch (InvalidMove i) {
                            cout << "Invalid Cards." << endl;
                        }
                    }else{
                        try {
                            if (m == 1) {
                                m = 2;
                            }
                            else {
                                m = 1;
                            }
                            p2->play_m(n, m, rit);
                            gameDisplay->notify(p2,2);
                            gameDisplay->handDisplay(p2->hand);                            
                        }
                        catch (InvalidMove i) {
                            cout << "Invalid Cards." << endl;
                        }
                    }
                    
                }
                else {
                  t = rit - '0';
                    if (turn == 1) {
                        try {
                            p1->play_m(n, m, t - 1);
                            gameDisplay->notify(p1,1);
                            gameDisplay->handDisplay(p1->hand);                        
                        }
                        catch (InvalidMove i) {
                            cout << "Invalid Cards." << endl;
                        }
                    }
                    else {
                        try {
                            if (m == 1) {
                                m = 2;
                            }
                            else {
                                m = 1;
                            }
                            p2->play_m(n, m, t - 1);
                            gameDisplay->notify(p2,2);
                            gameDisplay->handDisplay(p2->hand);                            
                        }
                        catch (InvalidMove i) {
                            cout << "Invalid Cards." << endl;
                        }
                    }
                }
            }  else {
                if(turn == 1){
                    try {
                        p1->play_p(n);
                        gameDisplay->handDisplay(p1->hand);                     
                        if (p1->h_ritual == 1) {
                            Card* p1_ritual = p1->ritual;
                            string name = p1_ritual->getName();
                            int charges_p = p1_ritual->getCharges();
                            if (name == "Aura of Power") {
                                if (p1->triiger_card_type == 1) {
                                    Card* target_c = p1->board_M.back();
                                    int tA = target_c->getAttack();
                                    int tD = target_c->getDefence();
                                    target_c->setAttack(tA + 1);
                                    target_c->setDefence(tD + 1);
                                    p1_ritual->setCharges(charges_p - 1);
                                    if (p1_ritual->getCharges() <= 0) {
                                        p1->move_to_graveyard_for_Rituals(p1_ritual);
                                        p1->h_ritual = 0;
                                    }
                                }
                            }
                           else if(name == "Standstill"){
                             if(p1->triiger_card_type == 1){
                               Card* target_c = p1->board_M.back();
                               p1->move_to_graveyard(target_c);
                               p1_ritual->setCharges(charges_p -2);
                               if(p1_ritual->getCharges() <= 0){
                                 p1->move_to_graveyard_for_Rituals(p1_ritual);
                                 p1->h_ritual = 0;
                               }
                             }
                           }   
                        }
                        gameDisplay->notify(p1,1);
                        p1->triiger_card_type = 0;
                    }catch(InvalidMove i) {
                        cout << "Invalid Cards." << endl;
                    }
                }
                else{
                    try {
                        p2->play_p(n);
                        gameDisplay->handDisplay(p2->hand);                        
                        if (p2->h_ritual == 1) {
                            Card* p2_ritual = p2->ritual;
                            string name = p2_ritual->getName();
                            int charges_p = p2_ritual->getCharges();
                            if (name == "Aura of Power") {
                                if (p2->triiger_card_type == 1) {
                                    Card* target_c = p2->board_M.back();
                                    int tA = target_c->getAttack();
                                    int tD = target_c->getDefence();
                                    target_c->setAttack(tA + 1);
                                    target_c->setDefence(tD + 1);
                                    p2_ritual->setCharges(charges_p - 1);
                                    if (p2_ritual->getCharges() <= 0) {
                                        p2->move_to_graveyard_for_Rituals(p2_ritual);
                                        p2->h_ritual = 0;
                                    }
                                }
                            }
                           else if(name == "Standstill"){
                             if(p2->triiger_card_type == 1){
                               Card* target_c = p2->board_M.back();
                               p2->move_to_graveyard(target_c);
                               p2_ritual->setCharges(charges_p - 2);
                               if(p2_ritual->getCharges() <= 0){
                                 p2->move_to_graveyard_for_Rituals(p2_ritual);
                                 p2->h_ritual = 0;
                               }
                             }
                           }
                        }
                        gameDisplay->notify(p2,2);
                        p2->triiger_card_type = 0;                 
                    }catch(InvalidMove i) {
                        cout << "Invalid Cards." << endl;
                    }
                }
            }
        }
        else if(cmd_l == "end"){
            if(turn == 1){
                p1->checkPotionSeller();
                updateAllAct(p2);
                p2_magic++;
                p2->magic = p2_magic;
                if(p2->deck.size() >0){
                    if(p2->hand.size() <5){
                        p2->hand.push_back(p2->deck[p2_deck_index + 1]);
                        p2_deck_index++;
                    }
                }
                if(p2->h_ritual == 1){
                    Card* p2_ritual = p2->ritual;
                    string name = p2_ritual->getName();
                    int charges_p = p2_ritual->getCharges();
                    if(name == "Dark Ritual"){
                        p2->magic++;
                        p2_ritual->setCharges(charges_p - 1);
                        if(p2_ritual->getCharges() <= 0){
                            p2->move_to_graveyard_for_Rituals(p2_ritual);
                            p2->h_ritual = 0;
                        }
                    }  
                }
                gameDisplay->notify(p1,1);
                gameDisplay->handDisplay(p2->hand);
                turn = 2;         
            }
            else{
                p2->checkPotionSeller();
                updateAllAct(p1);
                p1_magic++;
                p1->magic = p1_magic;
                if(p1->deck.size() >0){
                    if(p1->hand.size() <5){
                        p1->hand.push_back(p1->deck[p1_deck_index + 1]);
                        p1_deck_index++;
                    }
                }
                if(p1->h_ritual == 1){
                    Card* p1_ritual = p1->ritual;
                    string name = p1_ritual->getName();
                    int charges_p = p1_ritual->getCharges();
                    if(name == "Dark Ritual"){
                        p1->magic++;
                        p1_ritual->setCharges(charges_p - 1);
                        if(p1_ritual->getCharges() <= 0){
                            p1->move_to_graveyard_for_Rituals(p1_ritual);
                            p1->h_ritual = 0;
                        }
                    }      
                }
                gameDisplay->notify(p2,2);
                gameDisplay->handDisplay(p1->hand);
                turn = 1; 
            }
        } 
        else if(cmd_l == "use"){
            s1 >> n;
            if(s1 >> m) {
                s1 >> t;
                if(turn == 1){
                   try{
                    p1->use_m(n,m,t-1);
                    gameDisplay->notify(p1,1);
                   }catch(NoAct i){
                     cout << "No Enough Act" << endl;
                }
                }
                else{
                   if (m == 1) {
                     m = 2;
                       }
                     else {
                     m = 1;
                     }                
                   try{
                    p2->use_m(n,m,t-1);
                    gameDisplay->notify(p2,2);
                   }catch(NoAct i){
                     cout << "No Enough Act" << endl;
                }
                }
            }
            else{
                if(turn == 1){
                   try{
                    p1->use_p(n);
                    gameDisplay->notify(p1,1);                   
                }catch(NoAct i){
                  cout << "No Enough Act" << endl;
                }
            }
                else{
                   if (m == 1) {
                     m = 2;
                       }
                     else {
                     m = 1;
                     }                  
                try{
                    p2->use_p(n);
                    gameDisplay->notify(p2,2);                   
                }catch(NoAct i){
                  cout << "No Enough Act" << endl;
                }
                }
            }
        }
        else if(cmd_l == "hand"){
            if(turn == 1){
                p1->showhand();
                gameDisplay->handDisplay(p1->hand);
            }
            else{
                p2->showhand();
                gameDisplay->handDisplay(p2->hand);
            }
        }
        else if(cmd_l == "inspect"){
            s1 >> n;
            if(turn == 1){
                p1->showInspect(n);
                Card* my_c = (p1->board_M)[n - 1];
                gameDisplay->inspectDisplay(my_c);
            }
            else{
                Card* my_c = (p2->board_M)[n - 1];
                p2->showInspect(n);
                gameDisplay->inspectDisplay(my_c);
            }
        }
       else if(cmd_l == "board"){
         cout << *p1;
         cout << *p2;
       }
       else if(cmd_l == "discard"){
         if(test_mode == 1){
           s1 >> n;
           if(turn == 1){
             p1->discard(n - 1);
           }
           else{
            p2->discard(n - 1);
           }
         }
         else{
           cout << "Discard method is for testing mode only" << endl;
         }
       }
       else if(cmd_l == "draw"){
         if(test_mode == 1){
           if(turn == 1){
             if(p1->deck.size() >0){
               if(p1->hand.size() <5){
                 p1->hand.push_back(p1->deck[p1_deck_index + 1]);
                 p1_deck_index++;
                    }
                }
           }
           else{
             if(p2->deck.size() >0){
               if(p2->hand.size() <5){
                 p2->hand.push_back(p1->deck[p2_deck_index + 1]);
                 p2_deck_index++;
               }
                }
           }
         }
         else{
           cout << "Draw method is for testing mode only" << endl;
         }       
       }        
    }               
}


