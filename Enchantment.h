//
// Created by michael on 19/07/19.
//

#ifndef CS246A5_ENCHANTMENT_H
#define CS246A5_ENCHANTMENT_H

#include "Card.h"

/*
 * Modifications that can be played onn minions
 */

class Enchantment : public Card{
private:

    bool addEnchantment;
	bool silence;
	bool multiplier;

public:
    Enchantment(const Player *sec, const std::string &name,  Effect *eff,
            const std::string &description, int cost, bool silence, bool multiplier = false);

	const Effect * const getEffect() const;

	bool getAddEnchantment() const;

	bool getSilence() const;

	bool getMultiplier() const;

	int getAddAct() const;
};

#endif //CS246A5_ENCHANTMENT_H
