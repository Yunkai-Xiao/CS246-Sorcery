#ifndef _CS246A5_EFFECT_H
#define _CS246A5_EFFECT_H

#include <string>

// Created for the use of the applyEffect
// The information that needed to change the stats of Card
struct Effect{
    // change of Attack
    int attack_change;
    
    // change of defence
    int defence_change;

    // die or not
    bool die;

    // change of ability
    bool given;
    bool taken;
    Effect* ability;

    // Zone that will be affected
    // "Opponent", "Allied", "All"
    std::string zone;

    // target
    bool single;
    bool self;
};
#endif
