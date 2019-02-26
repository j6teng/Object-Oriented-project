#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "player.h"
#include <memory>
#include <vector>



class Xwindow;

class GraphDisplay {
    int graphic;
    Xwindow* w;
    Xwindow* h;
    Xwindow* insp;
    Player* p1;
    Player* p2;
    Card* r_p1;
    Card* r_p2;
    std::vector<Card*> graveyard_p1;
    std::vector<Card*> graveyard_p2; 
    std::vector<Card*> board_M_p1;
    std::vector<Card*> board_M_p2;
    void board_graph();
    void hand_graph(std::vector<Card*> hand);
    void drawSkele();
    void drawPlayer();
    void drawBoard();
    void drawHand(std::vector<Card*> hand);
    void drawLife(Xwindow* w, int x, int y, std::string hp);
    void drawMagic(Xwindow* w, int x, int y, std::string mp);
    void drawAttack(Xwindow* w, int x, int y, std::string atk);
    void drawCost(Xwindow* w, int x, int y, std::string abilityCost);
    void drawMinion(Xwindow* w, int x, int y, Card* m);
    void drawDes(Xwindow* w, int x, int y, std::string desc);
    void setRitual(Card* c, int player);
    void setGraveyard(std::vector<Card*> c, int player);
    void setMinion(std::vector<Card*> c, int player);
public:
    GraphDisplay(bool graphic);
    void setPlayer(Player* p, int player);
    void boardDisplay();
    void handDisplay(std::vector<Card*> hand);
    void inspectDisplay(Card* m);
    void notify(Player* p,int i);
};



#endif
