#ifndef CS246A5_RITUAL_H
#define CS246A5_RITUAL_H

#include "Card.h"
#include "Spell.h"
#include <iostream>
//#include "Observer.h"

class Ritual :public Card{

private:
    // The number of times it can be charged
    int charges;
    int ab_cost;
    Trigger t;
	void apply(const Spell* const spell); 
	   
public:

    Ritual(const Player* sec, const std::string &name, const Effect * eff,
            const std::string &description, int cost, int charge, int ab_cost, Trigger t);
    const Effect * const getEffect() const;
	const int getCharges() const;
    const Trigger& getTrig() const;
    const int getAbCost() const;
    Ritual* notify(const Trigger tr);
    void apply(const Card* c);

    card_template_t drawThis() override;
};


#endif //CS246A5_RITUAL_H
