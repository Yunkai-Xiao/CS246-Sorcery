
#ifndef CS246A5_TEXTDISPLAY_H
#define CS246A5_TEXTDISPLAY_H


#include "Ritual.h"
#include "Minion.h"
#include "Player.h"
#include <string>
#include <vector>
#include "ascii_graphics.h"
#include <iostream>


class TextDisplay{
    std::string s;
    public:

    std::string drawBoard(const std::vector<Player*> player, 
                    const std::vector<std::vector<Minion *>> minions, 
                    const std::vector<std::vector<Ritual*>> r, 
                    const std::vector<std::vector<Minion*>> graveyard );
    std::string drawHand(std::vector<Card*> h);
    std::string inspectMinion(Minion* m);
};


#endif //CS246A5_TEXTDISPLAY_H
