
#ifndef CS246A5_SPELL_H
#define CS246A5_SPELL_H

#include "Card.h"

/*
 * Spells are the simplest type of card. A spell simply
 * changes the game in some way (such as by increasing its
 * caster's life by 5 or killing a chosen minion) and is then
 * removed from the game.
 */

class Spell : public Card{

bool undo;
public:
    Spell(const Player *sec, const std::string &name, Effect *eff,
        const std::string &description, int cost, bool undo );

    bool getUndo() const;
};

#endif //CS246A5_SPELL_H
