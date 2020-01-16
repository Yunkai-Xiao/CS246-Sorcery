//
// Created by michael on 19/07/19.
//

#include "Enchantment.h"

Enchantment::Enchantment(const Player *sec, const std::string &name, Effect *eff,
                         const std::string &description, int cost, bool silence,
                         bool multiplier)
        :Card{sec,name,eff,description,cost,"Enchantment"},
        multiplier{multiplier} ,silence{silence}{
}


bool Enchantment::getAddEnchantment() const{
    return addEnchantment;
}

const Effect * const Enchantment::getEffect() const{
    return eff;
}

bool Enchantment::getSilence() const{
    return silence;
}

bool Enchantment::getMultiplier() const {
    return multiplier;
}

int Enchantment::getAddAct() const {
    return eff->act;
}
