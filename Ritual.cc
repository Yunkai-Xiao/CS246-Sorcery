//
// Created by michael on 19/07/19.
//

#include "Ritual.h"
Ritual::Ritual(const Player* sec, const std::string &name, const Effect * eff,
            const std::string &description, int cost, int charge, int ab_cost,Trigger tr)
            :Card{sec,name,eff,description,cost,"Ritual"},charges{charge},ab_cost{ab_cost},t{tr}{

}

void Ritual::apply(const Spell* const spell){
	if(spell == nullptr){
		return;
	}
	const Effect* const e = spell->getEffect();	
	charges += e->charge;
}

const int Ritual::getAbCost() const{
	return ab_cost;
}
const int Ritual::getCharges() const{
	return charges;
}
const Trigger& Ritual::getTrig() const{
	return t;
}

const Effect * const Ritual::getEffect() const{
	return eff;
}

void Ritual::apply(const Card *card) {
    if (card->getType() == "Spell"){
        apply((Spell*)card);
    }
}

Ritual* Ritual::notify(const Trigger tr){
	if(this->t == tr && charges >= ab_cost){
		std::cerr << name << " is triggered";
		charges -= ab_cost;
		return this;
	} else {
		return nullptr;
	}
}

card_template_t Ritual::drawThis(){
	
	return display_ritual(name,cost,ab_cost,description,charges);
}

