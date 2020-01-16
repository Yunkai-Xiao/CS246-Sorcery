//
// Created by michael on 19/07/19.
//

#include "Spell.h"
#include "Tool.h"

Spell::Spell(const Player *sec, const std::string &name,  Effect *eff,
        const std::string &description, int cost, bool undo):Card{sec,name,eff,description,cost,"Spell"},undo{undo}{}

bool Spell::getUndo() const{ 
        return undo;
}




