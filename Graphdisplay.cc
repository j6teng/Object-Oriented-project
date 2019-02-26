#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "Graphdisplay.h"
#include "window.h"

using namespace std;

GraphDisplay::GraphDisplay(bool graphic):graphic{graphic} {
    if (graphic) {
        cout << "graphic Mode Active " << endl;
        w = new Xwindow(930, 660);
    }
    else {
        cout << "graphic Mode Deactive" << endl;
        w = nullptr;
    }
    h = nullptr;
    insp = nullptr;
}


void GraphDisplay::setPlayer(Player* p, int player){
    if (player == 1) {
        p1 = p;
    }
    else if (player == 2) {
        p2 = p;
    }
}

void GraphDisplay::setRitual(Card* c, int player) {
    if (player == 1) {
        r_p1 = c;
    }
    else if (player == 2) {
        r_p2 = c;
    }
}

void GraphDisplay::setGraveyard(vector<Card*> c, int player) {
    if (player == 1) {
        graveyard_p1 = c;
    }
    else if (player == 2) {
        graveyard_p2 = c;
    }
}
void GraphDisplay::setMinion(vector<Card*> c, int player) {
    if (player == 1) {
        board_M_p1 = c;
    }
    else if (player == 2) {
        board_M_p2 = c;
    }
}

void GraphDisplay::notify(Player* p,int i){
  setMinion(p->board_M,i);
  setGraveyard(p->graveyard,i);
  setRitual(p->ritual,i);
  board_graph();
}

void GraphDisplay::boardDisplay() {
    if (graphic == 1){
       board_graph();
    }
}

void GraphDisplay::handDisplay(vector<Card*> hand) {
    if (graphic == 1){
       hand_graph(hand);
    }
}



void GraphDisplay::board_graph() {
    drawSkele();
    drawPlayer();
    drawBoard();  
}

void GraphDisplay::hand_graph(std::vector<Card*> hand) {
    if (h == nullptr) {
        h = new Xwindow(960, 140);
    }
    drawHand(hand);
}


void GraphDisplay::inspectDisplay(Card* m) {
    if (insp == nullptr) {
        insp = new Xwindow(930, 660);
    }
    drawMinion(insp,0,0,m);
    vector<Card*> my_Ench = m->getEnch();
    int m_size = my_Ench.size();
    while (m_size > 0) {
      int line = 1;
      int count = 0;
        if (m_size >= 5) {
          for (int i = 0; i < 5; i++) {
            insp->fillRectangle((i + 1) * 5 + (i * 180), line * 120 + 10, 180, 120, Xwindow::White);
            insp->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 12, 173, 116, Xwindow::Black);
            if ((my_Ench[count]->getName() != "Giant Strength") && (my_Ench[count]->getName() != "Enrage")) {
                int cC = my_Ench[count]->getCost();
                drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30 + line * 120, to_string(cC));
                insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, line * 120 + 30,my_Ench[count]->getName(), Xwindow::White);
                insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176),line * 120 + 10, my_Ench[count]->getDes());
            }
            else {
                if(my_Ench[count]->getName() == "Giant Strength"){
                  int cC = 1;
                  drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20,line * 120 + 30, to_string(cC));
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, my_Ench[count]->getName(), Xwindow::White);
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                  drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 10, my_Ench[count]->getDes());
                  int a = 2;
                  string add = "+" + to_string(a);
                  drawAttack(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 175, line * 120 + 116 - 5, add);
                  drawLife(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 20, line * 120 + 116 - 5, add);
                }
               else{
                  int cC =  2;
                  drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, line * 120 + 30, to_string(cC));
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5,line * 120 + 30, m->getName(), Xwindow::White);
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                  drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 10, my_Ench[count]->getDes());
                  int a = 2;
                  string muti = "*" + to_string(a);
                  drawAttack(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 156, line * 120 + 116 + 5, muti);
                  drawLife(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 5, line * 120 + 116 + 5, muti);                             
                 }
          }
          count++;
        }
        line++;
      }
      else {
          for (int i = 0; i < m_size; i++) {
            insp->fillRectangle((i + 1) * 5 + (i * 180), line * 120 + 10, 180, 120, Xwindow::White);
            insp->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 12, 173, 116, Xwindow::Black);
            if ((my_Ench[count]->getName() != "Giant Strength") && (my_Ench[i]->getName() != "Enrage")) {
                int cC = my_Ench[i]->getCost();
                drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30 + line * 120, to_string(cC));
                insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, line * 120 + 30, my_Ench[count]->getName(), Xwindow::White);
                insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176),line * 120 + 10, my_Ench[i]->getDes());
            }
            else {
                if(my_Ench[count]->getName() == "Giant Strength"){
                  int cC =  1; 
                  drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, line * 120 + 30, to_string(cC));
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5,line * 120 + 30, my_Ench[count]->getName(), Xwindow::White);
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                  drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 10, my_Ench[count]->getDes());
                  int a = 2;
                  string add = "+" + to_string(a);
                  drawAttack(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 156, line * 120 + 116 + 5, add);
                  drawLife(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 5, line * 120 + 116 + 5, add);    
                }
               else{
                  int cC =  2;
                  drawMagic(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, line * 120 + 30, to_string(cC));
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5,line * 120 + 30, my_Ench[count]->getName(), Xwindow::White);
                  insp->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, line * 120 + 50, "Enchantment", Xwindow::White);
                  drawDes(insp,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), line * 120 + 10, my_Ench[count]->getDes());
                  int a = 2;
                  string muti = "*" + to_string(a);
                  drawAttack(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 156, line * 120 + 116 + 5, muti);
                  drawLife(insp, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 5, line * 120 + 116 + 5, muti);                             
                 }
          }
          count++;
        }
    }
    m_size = m_size - 5;
  }
}


void GraphDisplay::drawSkele() {
    w->fillRectangle(0, 0, 930, 660, Xwindow::Black);
    w->fillRectangle(0, 280, 930, 80, Xwindow::White);
    w->drawBigString(320, 335, "Sorcery", Xwindow::Black);
}

void GraphDisplay::drawLife(Xwindow* w, int x, int y, string life) {
    w->drawString(x,y,life, Xwindow::White);
}

void GraphDisplay::drawMagic(Xwindow* w, int x, int y, string magic) {
    w->drawString(x,y,magic, Xwindow::White);
}

void GraphDisplay::drawAttack(Xwindow* w, int x, int y, string attack) {
    w->drawString(x,y,attack, Xwindow::White);
}

void GraphDisplay::drawCost(Xwindow* w, int x, int y, string abilityCost) {
    w->drawString(x,y,abilityCost, Xwindow::White);
}

void GraphDisplay::drawDes(Xwindow* w, int x, int y, string desc) {
    int col = 0;
    int row = 0;
    string s;
    while(desc.length() - col > 20) {
        s = desc.substr(col,20);
        w->drawString(x + 10 - row, y + row * 10 + 60, s, Xwindow::White);
        row++;
        col += 20;
    }
    s = desc.substr(col, desc.length() - col);
    w->drawString(x + 10 - row, y + row * 15 + 55, s, Xwindow::White);
}

void GraphDisplay::drawMinion(Xwindow* w, int x, int y, Card* m) {
    w->fillRectangle(x, y, 176, 116, Xwindow::Black);
    string name = m->getName();
    w->drawString(x + 5, y + 15, name, Xwindow::White);
    int c = m->getCost();
    drawMagic(w, x + 176 - 15, y + 15, to_string(c));
    w->drawString(x + 176 - 50, y + 40, m->getType(), Xwindow::White);
    int a = m->getAttack();
    int d = m->getDefence();
    drawAttack(w, x + 5, y + 116 - 5, to_string(a));
    drawLife(w, x + 176 - 10, y + 116 - 5, to_string(d));
    int aD = m->getAbility_cost();
    int aE = m->getAbility();
    if(aE == 1) {
      if(aD != 0) {
        string s = m->getDes();
        drawCost(w, x + 5, y + 45, to_string(aD));
        drawDes(w, x + 10, y + 5, s);
      } 
      else {
        string s = m->getDes();
        drawDes(w, x, y + 5, s);
      }
    }
}

void GraphDisplay::drawPlayer() {
    w->fillRectangle(375, 10, 180, 120, Xwindow::White);
    w->fillRectangle(377, 12, 176, 116, Xwindow::Black);
    w->fillRectangle(375, 530, 180, 120, Xwindow::White);
    w->fillRectangle(377, 532, 176, 116, Xwindow::Black);
    w->drawString(400, 80, p1->name, Xwindow::White);
    w->drawString(400, 582, p2->name, Xwindow::White);
    w->fillRectangle(375, 110, 20, 20, Xwindow::White);
    w->fillRectangle(375, 630, 20, 20, Xwindow::White);
    w->fillRectangle(376, 111, 18, 18, Xwindow::Black);
    w->fillRectangle(376, 631, 18, 18, Xwindow::Black);
    int p1_life = p1->life;
    drawLife(w, 380, 125, to_string(p1_life));
    int p2_life = p2->life;
    drawLife(w, 380, 645, to_string(p2_life));
    w->fillRectangle(535, 110, 20, 20, Xwindow::White);
    w->fillRectangle(535, 630, 20, 20, Xwindow::White);
    w->fillRectangle(536, 111, 18, 18, Xwindow::Black);
    w->fillRectangle(536, 631, 18, 18, Xwindow::Black);
    int p1_magic = p1->magic;
    drawMagic(w, 538, 125, to_string(p1_magic));
    int p2_magic = p1->magic;
    drawMagic(w, 538, 645, to_string(p1_magic)); 
}

void GraphDisplay::drawBoard() {
    w->fillRectangle(10, 10, 180, 120, Xwindow::White);
    w->fillRectangle(10, 530, 180, 120, Xwindow::White);
    w->fillRectangle(12, 12, 176, 116, Xwindow::Black);
    w->fillRectangle(12, 532, 176, 116, Xwindow::Black);
    w->drawString(40, 40, "Ritual", Xwindow::White);
    w->drawString(40, 548, "Ritual", Xwindow::White);
    w->fillRectangle(735, 10, 180, 120, Xwindow::White);
    w->fillRectangle(735, 530, 180, 120, Xwindow::White);
    w->fillRectangle(737, 12, 176, 116, Xwindow::Black);
    w->fillRectangle(737, 532, 176, 116, Xwindow::Black);
    w->drawString(760, 40, "GraveYard", Xwindow::White);
    w->drawString(760, 548, "Graveyard", Xwindow::White);
    for (int i = 0; i < 5; ++i) {
        w->fillRectangle((i + 1) * 5 + (i * 180), 140, 180, 120, Xwindow::White);
        w->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 142, 173, 116, Xwindow::Black);
        w->drawString(68 + (i * 180), 180, "Minion", Xwindow::White);
    }
    for (int i = 0; i < 5; ++i) {
        w->fillRectangle((i + 1) * 5 + (i * 180), 400, 180, 120, Xwindow::White);
        w->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 402, 173, 116, Xwindow::Black);
        w->drawString(68 + (i * 180), 440, "Minion", Xwindow::White);
    }
    if(p1->h_ritual == 1){
    if (r_p1->getType() == "Ritual") {
        w->fillRectangle(12, 12, 176, 116, Xwindow::Brown);
        int rC = r_p1->getCost();
        drawMagic(w, 172, 25, to_string(rC));
        w->drawString(20, 25, r_p1->getName(), Xwindow::White);
        w->drawString(140, 45, "Ritual", Xwindow::White);
        int rCh = r_p1->getCharges();
        drawCost(w, 172, 118, to_string(rCh));
        drawDes(w, 20, 1, r_p1->getDes());
        int C = r_p1->getAbility_cost();
        w->drawString(20, 45, to_string(C), Xwindow::White);
    }
    }
    if(p2->h_ritual == 1){
    if (r_p2->getType() == "Ritual") {
        w->fillRectangle(12, 532, 176, 116, Xwindow::Brown);
        int rC = r_p2->getCost();
        drawMagic(w, 172, 550, to_string(rC));
        w->drawString(20, 550, r_p2->getName(), Xwindow::White);
        w->drawString(140, 570, "Ritual", Xwindow::Black);
        int rCh = r_p2->getCharges();
        drawCost(w, 172, 643, to_string(rCh));
        drawDes(w, 20, 540, r_p2->getDes());
        int C = r_p2->getAbility_cost();
        w->drawString(20, 570, to_string(C), Xwindow::White);
    }
    }
    if(p1->graveyard.size() > 0){
    for(int i = 0;i<p1->graveyard.size();i++){
      if (p1->graveyard[i]->getType() == "Minion") {
        drawMinion(w, 737, 12, p1->graveyard[i]);
       }
    }
    }
    if(p2->graveyard.size() > 0){
        for(int i = 0;i<p2->graveyard.size();i++){
          if (p2->graveyard[i]->getType() == "Minion") {
            drawMinion(w, 737, 532, p2->graveyard[i]);
        }
      }
    }
    for (int i = 0; i < p1->board_M.size(); ++i) {
        drawMinion(w, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) - 1, 142, p1->board_M[i]);
    }
    for (int i = 0; i < p2->board_M.size(); ++i) {
        drawMinion(w, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) - 1, 402, p2->board_M[i]);
    }
}

void GraphDisplay::drawHand(vector<Card*> hand) {
    h->fillRectangle(0, 0, 960, 140, Xwindow::Black);
    for (int i = 0; i < hand.size(); ++i) {
        if (hand[i]->getType() == "Ritual") {
            h->fillRectangle((i + 1) * 5 + (i * 180), 10, 180, 120, Xwindow::White);
            h->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 12, 173, 116, Xwindow::Black);
            int cC =  hand[i]->getCost();
            drawMagic(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30, to_string(cC));
            h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, hand[i]->getName(), Xwindow::White);
            h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 30, 50, "Ritual", Xwindow::White);
            int aC = hand[i]->getAbility_cost();
            drawCost(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 175, 50, to_string(cC));
            drawDes(h,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 10, hand[i]->getDes());
        }
        else if (hand[i]->getType() == "Enchantment") {
            h->fillRectangle((i + 1) * 5 + (i * 180), 10, 180, 120, Xwindow::White);
            h->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 12, 173, 116, Xwindow::Black);
            if ((hand[i]->getName() != "Giant Strength") && (hand[i]->getName() != "Enrage")) {
                int cC =  hand[i]->getCost();
                drawMagic(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30, to_string(cC));
                h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, hand[i]->getName(), Xwindow::White);
                h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, 50, "Enchantment", Xwindow::White);
                drawDes(h,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 10, hand[i]->getDes());
            }
            else {
                if(hand[i]->getName() == "Giant Strength"){
                  int cC =  hand[i]->getCost();
                  drawMagic(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30, to_string(cC));
                  h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, hand[i]->getName(), Xwindow::White);
                  h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, 50, "Enchantment", Xwindow::White);
                  drawDes(h,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 10, hand[i]->getDes());
                  int a = 2;
                  string add = "+" + to_string(a);
                  drawAttack(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 152, 116 + 8, add);
                  drawLife(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 1, 116 + 8, add);
                }
               else{
                  int cC =  hand[i]->getCost();
                  drawMagic(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30, to_string(cC));
                  h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, hand[i]->getName(), Xwindow::White);
                  h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 60, 50, "Enchantment", Xwindow::White);
                  drawDes(h,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 10, hand[i]->getDes());
                  int a = 2;
                  string muti = "*" + to_string(a);
                  drawAttack(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 152, 116 + 8, muti);
                  drawLife(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 1, 116 + 8, muti);                             
                 }
          }
        }
        else if (hand[i]->getType() == "Spell") {
            h->fillRectangle((i + 1) * 5 + (i * 180), 10, 180, 120, Xwindow::White);
            h->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 12, 173, 116, Xwindow::Black);
            int cC =  hand[i]->getCost();
            h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5, 30, hand[i]->getName(), Xwindow::White);
            drawMagic(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20, 30, to_string(cC));
            h->drawString((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) + 5 + 173 - 20 - 30, 50, "Spell", Xwindow::White);
            drawDes(h,(i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 15, hand[i]->getDes());
        }        
        else {
            h->fillRectangle((i + 1) * 5 + (i * 180), 10, 180, 120, Xwindow::White);
            h->fillRectangle((i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176), 12, 173, 116, Xwindow::Black);
            drawMinion(h, (i + 1) * 5 + (i+ 1) * 2 * 2 + (i * 176) - 2, 12, hand[i]);
        }
    }
}


