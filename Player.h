//
// Created by michael on 19/07/19.
//

#ifndef CS246A5_PLAYER_H
#define CS246A5_PLAYER_H

#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Observer.h"
#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Tool.h"

class Player : public Observer{
private:
    // Basic stat"
    int hp = 20;
    int magic = 3;
    std::string name;

    std::vector<Card*> hand;

    std::vector<Card*> deck;


public:

    void shuffle();

    int getHp() const;
    // Getters
    bool isDead() const;

    std::vector<Card*> getHand();

    std::string getName() const;

    int getMagic() const;
// Functions Card* summon(int idx);
	
    void loadDeck(std::string filename);

	void changeMagic(int amount);

    void unsummon(Card * card);

    void summon(int idx);

	Card* getCard(int idx, int testing) const;
	 
    void discard(int idx);

    void collision(const Minion* const minion);
    
    void apply(const Card* const card);


    void draw();

    Card* notify(const Trigger t);

    // Constructors and Destructors
    Player(const std::string& name,std::string deck);
    ~Player();
};


#endif //CS246A5_PLAYER_H
