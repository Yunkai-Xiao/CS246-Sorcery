//
// Created by michael on 19/07/19.
//

#ifndef CS246A5_MINION_H
#define CS246A5_MINION_H

#include "Card.h"
#include "Enchantment.h"
#include "Spell.h"
#include "Ritual.h"

struct Info{
    // Card Name
    std::string name;

    // Combat strength
    int def = 0, atk = 0;

    // Number of actions it is allowed
    int act = 0;
    int ab_cost = 0;
    int amount;
    // Active skill
    Effect* activeSkill;
};

/*
 * Max of 5 are allowed to be played, if 5 are already played,
 * no more minion should be played.
 *
 * When a new minion is placed on the board, it will occupy the
 * currently left-most position in the board.
 *       #### Notice that the board is DIFFERENT from Grid.
 *
 * -> To attack the opposing player. The opposing player loses
 *    life equal to the attack value of the minion.
 * -> To attack an opposing minion. Both minion damage one another:
 *    minion A reduces minion B's defence by A's attack and vise versa
 * -> To use an activated ability
 *
 * ===================================================================
 *
 * -> Activated abilities cost magic and an action point to use, and
 *    work similar to playing a spell card
 * -> Triggered abilities are activated for free whenever a certain
 *    condition is met.
 *
 * ===================================================================
 * -> A minion can only have one ability of each type.
 */

class Minion : public Card{
private:
    // Combat strength
    int def = 0, atk = 0;

    // Action every round
    int act_round = 0;

    // Number of actions it is allowed
    int act = -1;
    int ab_cost = -1;

    // Enchantments that might be removed, stats
    int last_added = 0;
    std::vector<Enchantment*> enchantments;

    // If silent
    bool silent;

    // Trigger
    Trigger trigger;

    // Active skill
    const Effect* activeSkill;

    // If it can summon
    Info * summon_info = nullptr;
    bool summon;


    // Functions
    void apply(const Minion * const min);
    void apply(const Ritual * const ritual);
    void apply(const Spell * const spell);
    void apply(Enchantment * enchantment);
    bool getSilence() const;
public:
 
    // Constructor
    Minion(const Player* sec, const std::string &name, const std::string &description,
            int cost, int def, int atk, Trigger tr, const Effect *trigger = nullptr,
            const Effect *actEff = nullptr, int ab_cost = 0, Info* summon_info = nullptr);

    // We note that the enchantments are stored only in here,
    // and is unique to each particular minion, that is, an enchantment
    // can only be applied to a specific minion. When the minion is dead,
    // the minion should take care of the cards
    ~Minion();


    // Getters and determining functions
    void resurrect();

    void restoreAct();

	bool isDead() const ;

    bool getAct();

    int getActCost() const ;
    
    int getAtk() const ;

    int getDef() const;

    const Effect * const getActiveSkill() const ;

    std::vector<Enchantment*> getEnchantments();

    bool canSummon() const;
    Info * getInfo() const;

    void apply(Card * card);

    void action();
    
    void collision( const Minion * const from);

    Minion* notify(const Trigger trig);

    card_template_t drawThis();
};


#endif //CS246A5_MINION_H
