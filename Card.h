//
// Created by michael on 19/07/19.
//

#ifndef CS246A5_CARD_H
#define CS246A5_CARD_H
#include "ascii_graphics.h"
#include "Observer.h"
#include "Tool.h"
#include <string>
#include <algorithm>
#include <vector>


class Player;
class Board;

class Card: public Observer{
protected:
    const std::string name;
    const std::string description;
    const std::string type;

    const Player* owner;

    // Number of Magic that is needed to cast the card const int cost; Effect *eff = nullptr;
    int cost;

    const Effect *eff; 

public:

    // ========================= Getters ==================================
    std::string getName() const;
    std::string getDescription() const;
    int getCost() const;
    const std::string getType() const;
    
    const Player* getPlayer() const;

    virtual void apply(Card *c);

    // ========================= Functions ================================
    virtual const Effect * const getEffect() const;

    // ========================= Functions ================================
    virtual Card* notify(const Trigger trig);
    
    virtual card_template_t drawThis();

    // =================== Constructors and Destructors ===================
    Card(const Player* sec, const std::string &name, const Effect * eff,
            const std::string &description, int cost, const std::string type);

    virtual ~Card();
};


#endif //CS246A5_CARD_H
