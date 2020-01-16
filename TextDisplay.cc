//
// Created by michael on 19/07/19.
//

#include "TextDisplay.h"

using namespace std;

string TextDisplay::drawBoard(const vector<Player*> player, 
					const vector<vector<Minion *>> minions, 
					const vector<vector<Ritual*>> r, 
					const vector<vector<Minion*>> graveyard){
	card_template_t player1;
	card_template_t player2;
	vector<card_template_t> minion1;
	vector<card_template_t> minion2;
	card_template_t ritual1 = CARD_TEMPLATE_BORDER;
	card_template_t ritual2 = CARD_TEMPLATE_BORDER;
	card_template_t graveyard1 = CARD_TEMPLATE_BORDER;
	card_template_t graveyard2 = CARD_TEMPLATE_BORDER;

	Player * p1 = player[0];
	Player * p2 = player[1];
	player1 = display_player_card(0,p1->getName(),p1->getHp(), p1->getMagic());
	player2 = display_player_card(1,p2->getName(), p2->getHp(), p2->getMagic());

	
	for (int i = 0 ; i < minions[0].size();i++){
		Minion* m = minions[0][i];

		if (m->getActiveSkill()){

			minion1.push_back(display_minion_activated_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef(),m->getActCost(),m->getDescription()));
		}else if (m->getEffect()){
			minion1.push_back(display_minion_triggered_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef(),m->getDescription()));
		}else{
			minion1.push_back(display_minion_no_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef()));
		}
		
	}
	for (int i = 0 ; i < minions[1].size();i++){
		Minion* m = minions[1][i];

		if (m->getActiveSkill()){
			minion2.push_back(display_minion_activated_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef(),m->getActCost(),m->getDescription()));
		}else if (m->getEffect()){
			minion2.push_back(display_minion_triggered_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef(),m->getDescription()));
		}else{
			minion2.push_back(display_minion_no_ability(m->getName(),m->getCost(),m->getAtk(),m->getDef()));
		}
		
	}

	if (r[0].size() > 0){
		Ritual* r1 = r[0][0];
		if (r1)
			ritual1 = r1->drawThis();
	}
	if (r[1].size() > 0){
		Ritual* r2 = r[1][0];
		if (r2)
			ritual2 = r2->drawThis();
	}

	if (graveyard[0].size() > 0){
		Minion* g1 = graveyard[0][graveyard[0].size()-1];
		if (g1->getActiveSkill()){
			graveyard1 = display_minion_activated_ability(g1->getName(),g1->getCost(),g1->getAtk(),g1->getDef(),g1->getActCost(),g1->getDescription());
		}else if (g1->getEffect()){
			graveyard1 = display_minion_triggered_ability(g1->getName(),g1->getCost(),g1->getAtk(),g1->getDef(),g1->getDescription());
		}else{
			graveyard1 = display_minion_no_ability(g1->getName(),g1->getCost(),g1->getAtk(),g1->getDef());
		}
	}else{
		graveyard1 = CARD_TEMPLATE_BORDER;
	}
	
	if (graveyard[1].size() > 0){
		Minion* g2 = graveyard[1][graveyard[1].size()-1];
		if (g2->getActiveSkill()){
			graveyard2 = display_minion_activated_ability(g2->getName(),g2->getCost(),g2->getAtk(),g2->getDef(),g2->getActCost(),g2->getDescription());
		}else if (g2->getEffect()){
			graveyard2 = display_minion_triggered_ability(g2->getName(),g2->getCost(),g2->getAtk(),g2->getDef(),g2->getDescription());
		}else{
			graveyard2 = display_minion_no_ability(g2->getName(),g2->getCost(),g2->getAtk(),g2->getDef());
		} 
	}else{
		graveyard2 = CARD_TEMPLATE_BORDER;
	}


	string s = "";

	// Draw the top line
	s += EXTERNAL_BORDER_CHAR_TOP_LEFT;
	for (int i = 0; i < 33*5; i++){
		s += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	s += EXTERNAL_BORDER_CHAR_TOP_RIGHT+"\n";

	
	// Draw the first row, including rituals, player, and graveyard.

	for (int i = 0 ; i < 11; i++){
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += ritual2[i];
		s += CARD_TEMPLATE_EMPTY[i];
		s += player2[i];
		s += CARD_TEMPLATE_EMPTY[i];
		s += graveyard2[i];
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += "\n";
	}


	for (int i = 0; i < 11; i++){
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		for (int j = 0; j < 5; j++){
			s += (minion2.size()>j ? minion2[j][i] : CARD_TEMPLATE_BORDER[i]);
		}
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += "\n";
	}
	
	for (int i = 0 ; i < 10; ++i){
		s += CENTRE_GRAPHIC[i];
		s += "\n";
	}
	for (int i = 0; i < 11; i++){
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		for (int j = 0; j < 5; j++){
			s += (minion1.size()>j ? minion1[j][i] : CARD_TEMPLATE_BORDER[i]);
		}
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += "\n";
	}
	for (int i = 0 ; i < 11; i++){
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += ritual1[i];
		s += CARD_TEMPLATE_EMPTY[i];
		s += player1[i];
		s += CARD_TEMPLATE_EMPTY[i];
		s += graveyard1[i];
		s += EXTERNAL_BORDER_CHAR_UP_DOWN;
		s += "\n";
	}

	s += EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
	for (int i = 0; i < 33*5; i++){
		s += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	s += EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT+"\n";	
	return s;
}

string TextDisplay::drawHand(std::vector<Card*> h){
	vector<card_template_t> hand;
	string s1;

	for (int i = 0 ; i < h.size();i++){
		Card* c = h[i];

		if (c->getType() == "Minion"){
			hand.push_back(c->drawThis());
		}else if (c ->getType() == "Spell" ){
			const Spell* s = dynamic_cast<Spell*>(c);
			hand.push_back(display_spell(s->getName(),s->getCost(), s->getDescription()));
		}else if (c->getType() == "Enchantment"){
			const Enchantment* e = dynamic_cast<Enchantment*>(c);
			if (e->getEffect()->atk == 0 && e->getEffect()->defence == 0){
				hand.push_back(display_enchantment(e->getName(),e->getCost(),e->getDescription()));
			}
			else if (e->getMultiplier()){
				hand.push_back(display_enchantment_attack_defence(e->getName(), 
								e->getCost(), e->getDescription(), "*" + to_string(e->getEffect()->atk),"*"+ to_string(e->getEffect()->defence)));
			}else{
				hand.push_back(display_enchantment_attack_defence(e->getName(), 
								e->getCost(), e->getDescription(), "+" + to_string(e->getEffect()->atk),"+"+ to_string(e->getEffect()->defence)));
			}
			
		}else if (c->getType() == "Ritual"){
			hand.push_back(c->drawThis());
		}
		
	}
	
	
	for (int i = 0; i < 11; i++){
		for (int j = 0; j < hand.size(); j++){
			s1 += hand[j][i];
		}
		s1 += "\n";
	}
	
	return s1;

}


string TextDisplay::inspectMinion(Minion* m){

	string s;
	card_template_t targetMinion = m->drawThis();
	vector<card_template_t> ench;

	for (int i = 0 ; i < m->getEnchantments().size(); i++){
		const Enchantment* e = m->getEnchantments()[i];
		if (e->getEffect()->atk == 0 && e->getEffect()->defence == 0){
			ench.push_back(display_enchantment(e->getName(),e->getCost(),e->getDescription()));
		}
		else if (e->getMultiplier()){
			ench.push_back(display_enchantment_attack_defence(e->getName(), 
							e->getCost(), e->getDescription(), "*" + to_string(e->getEffect()->atk),"*"+ to_string(e->getEffect()->defence)));
		}else{
			ench.push_back(display_enchantment_attack_defence(e->getName(), 
							e->getCost(), e->getDescription(), "+" + to_string(e->getEffect()->atk),"+"+ to_string(e->getEffect()->defence)));
		}	
	}

	
	for (int i = 0 ; i < 11; i++){
		s += targetMinion[i];
		s += "\n";
	}

	
	if (ench.size() > 0){
		while(ench.size() > 5){
			for (int i = 0 ; i < 11; i++){
				for (int j = 0 ; j < 5; j++){
					s += ench[j][i];
				}
				s += "\n";
			}
			for (int i = 0 ; i < 5; i++){
				ench.erase(ench.begin());
			}
		}

		for (int j = 0 ; j < 11; j++){
			for (int i = 0 ; i < ench.size(); i++){
				s += ench[i][j];
			}
			s += "\n";
		}
	}
	return s;
}
