#ifndef _BOARD_H_
#define _BOARD_H_

#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include "TextDisplay.h"
//#include "GraphicDisplay.h"
#include "Tool.h"

class Board {
private:
    TextDisplay* td = nullptr;
    //GraphicDisplay *gd = nullptr;

    int player_idx = 0;
    int winner = -1;
    std::vector<Player*> players;

    std::vector<std::vector<Minion*>> graveyard;

    std::vector<std::vector<Minion*>> minions;

    std::vector<std::vector<Ritual*>> rituals;
    

    // ============================ Functions ==================================
public:

    Board(std::string p1name, std::string p2name, std::string deck1, std::string deck2);

    ~Board();

    void drawCard();
    void discardCard(int idx);
    void drawHand();
    void drawBoard();
    void drawMinion(int idx);
    int getWinner() const;
    void shuffle(int testing);
    std::string getPlayerName(int idx);
    
    void attack(int i, int j);
    
    void attack(int idx);
    
    void die( const Minion* const c);
    
    void use(int idx, int j, int a_idx, int testing);

    void use(int idx, int testing);

    void play(int idx, int j, int a_idx, int testing);

    void play(int idx, int testing);

    void applyAll(Card* c);

    void applySingle(Card* c);

    void notifyAll(Trigger t);

    void startTurn();

    void endTurn();

    void init();

    void help();

};


#endif 
