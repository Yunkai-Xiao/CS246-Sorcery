#ifndef TOOL_H
#define TOOL_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map> 
// ============================= Triggers ===========================

enum Trigger{
	NoTrigger,Start,MEntry,MLeave,End,
};


// ============================= End of Triggers ====================

// ============================= Effects ============================

struct Effect {
    // stats
    int atk, defence;
    int act;
    int ab_cost;

    // Special Effects
    bool kill;
    bool unsummon;
    bool resurrect;

    // Types of Effects
    const bool player;
    int playermagic;
    
    // The Effect needs to have a target or not
    bool single;

    // The area that the Effect can work on
    // "Opponent", "Allied", and "All"
    std::string zone;
    // Change for ritual
    int charge;

    // Target index of the other player's minions
    // Note this can be applied on my own minions
    int target;

    bool self;

};

// ====================== End of Effects ============================

#endif
