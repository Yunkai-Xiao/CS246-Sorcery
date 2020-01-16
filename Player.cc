#include "Player.h"
#include <cstdlib>

using namespace std;

void alter_str(string &str){
	for(char &e: str){
		if(e == ' '){
			e = '_';
		}
	}
}

// =========================== Kind of Like Getters ============================

string Player::getName() const{
	return name;
}
bool Player::isDead() const {
		return hp <= 0;
}

vector<Card*> Player::getHand(){
		return hand;
}

int Player::getMagic() const {
		return magic;
}

int Player::getHp() const{
	return hp;
}
// ====================== End of Kind of Like Getters ==========================

// ================================ Functions ==================================
void Player::collision(const Minion* const minion){
	hp -= minion->getAtk();
	return;
}
void Player::changeMagic(int amount){
		magic += amount;
}

Card* Player::getCard(int idx, int testing) const{
		if(idx < hand.size() && ( hand[idx]->getCost() <= magic || testing )){
				Card * card = hand[idx]; 
				return card;
		}
		return nullptr;
}

void Player::unsummon(Card *card) {
		if (hand.size() >= 5)
			throw "Invalid Move"; 
		hand.emplace_back(card);
}

void Player::summon(int idx){
		magic -= hand[idx]->getCost();
		magic = max(0, magic);
		hand.erase(hand.begin() + idx);
}

void Player::discard(int idx) {
		if(idx >= 0 && idx < hand.size()){
			delete hand[idx];	
			hand.erase(hand.begin() + idx);
		}
}

void Player::apply(const Card* const c){
	if (c->getType() == "Ritual"){
		magic += c->getEffect()->playermagic;
	}
}

void Player::draw() {
		if(deck.empty()){
				return;
		}
		if(hand.size() < 5){
			int drawidx = rand() % deck.size();
				hand.emplace_back(deck[drawidx]);
				deck.erase(deck.begin() + drawidx);
		} 
}

// This is miraculously true xD
void Player::shuffle() {
		std::random_shuffle(deck.begin(), deck.end());
}

Card* Player::notify(const Trigger trig){
		if(trig == Trigger::Start){
				magic += 1;
		}
		return nullptr;
}

// ============================= End of Functions ==============================


using namespace std;
void Player::loadDeck(string filename){

    for (int i = 0;i < deck.size(); i++){
        delete deck[i];
    }

	ifstream file{filename};

	string cardName;

	while(getline(file, cardName)){
			alter_str(cardName);
			ifstream card{cardName + ".txt"};

			// First line is the type of the card such that it can all different
			// constructors
			string name;
			getline(card, name);

			string type;
			getline(card, type);

			// Cost
			int cost;
			card >> cost;
			card.ignore();

			if(type == "Minion"){

					int atk, def;
					card >> atk >> def;
					card.ignore();
					
					string triggertype;
					getline(card,triggertype);
					if (triggertype == "Null"){
							Minion* m = new Minion(this, name,"",cost,def,atk,Trigger::NoTrigger);
							deck.push_back(m);
							continue;
					}else if(triggertype == "Trig"){
							string desc;
							getline(card,desc);
							int trigtime;
							card >> trigtime;
							card.ignore();
							Trigger triggertime;
							triggertime = (Trigger)trigtime;

							bool summon;
							card >> summon;

							int atk_c, def_c, act_c, ab_cost,charge, playermagic;
							bool kill, resurrect, player, single,unsummon;
							string zone;
							card >> atk_c >> def_c >> act_c >> ab_cost >> kill >> unsummon >> resurrect >> player >> playermagic >> single >> zone >> charge ;
							card.ignore();
							Effect* eff = new Effect{atk_c,def_c,act_c,ab_cost,kill,unsummon,resurrect,player,playermagic, single,zone,charge};
							
							if (summon){
									string summonname;
									getline(card,summonname);

									int def_s, atk_s, act, ab_cost, amount;
									Effect* e = nullptr; // Expand if necessary

									card >> def_s >> atk_s >> act >> ab_cost >> amount;

									Info * i = new Info{summonname,def_s, atk_s, act, ab_cost, amount, e};
									Minion* m = new Minion(this, name, desc, cost, def, atk, triggertime, eff,nullptr, 0,i);
									deck.push_back(m);

									continue;
							}
							Minion* m = new Minion(this, name, desc, cost, def, atk, triggertime, eff);
							deck.push_back(m);
							continue;
					}else if(triggertype == "Acti"){
							string desc;
							getline(card,desc);

							int ability_cost;
							card >> ability_cost;

							bool summon;
							card >> summon;

							int atk_c, def_c, act_c, ab_cost,charge, playermagic;
							bool kill, resurrect, player,unsummon, single;
							string zone;

							card >> atk_c >> def_c >> act_c >> ab_cost >> kill >> unsummon >> resurrect >> player >> playermagic >> single >> zone >> charge;

							Effect* eff = new Effect{atk_c,def_c,act_c,ab_cost,kill,unsummon,resurrect,player,playermagic,single,zone,charge};

							if (summon){

									string summonname;
									getline(card,summonname);
									getline(card,summonname);
									int def_s, atk_s, act, ab_cost, amount;
									Effect* e = nullptr; // Expand if necessary

									card >> def_s >> atk_s >> act >> ab_cost >> amount;
									Info * i = new Info{summonname ,def_s, atk_s, act, ab_cost, amount, e};
									Minion* m = new Minion(this, name, desc, cost, def, atk, (Trigger)0, nullptr,eff, ability_cost,i);
									deck.push_back(m);
									continue;
							}

							Minion* m = new Minion(this, name, desc, cost, def, atk, (Trigger)0, nullptr, eff,ability_cost);
							deck.push_back(m);
							continue;
					}

			}else  if (type == "Ritual"){
					string desc;
					getline(card, desc);
					int ability_cost;
					card >> ability_cost;

					int charge;
					card >> charge;

					int atk_c, def_c, act, ab_cost,charge_change, playermagic;
					bool kill, summon, resurrect, player, single;
					string zone;

					card >> atk_c >> def_c >> act >> ab_cost >> kill >> summon >> resurrect >> player >> playermagic >> single >> zone >> charge_change;
					Effect* eff = new Effect{atk_c,def_c,act,ab_cost,kill,summon,resurrect,player,playermagic,single,zone,charge_change};
					card.ignore();
					Trigger t;
					int tr;
					card >> tr;
					t = (Trigger)tr;

					Ritual* r = new Ritual(this,name,eff,desc,cost,charge,ability_cost,t);
					deck.push_back(r);
					continue;
			}else if(type == "Enchantment"){


					string desc;
					getline(card,desc);
					if (desc == "Null"){
							desc = "";
					}

					bool multi;
					card >> multi;

					int atk_c, def_c, act, ab_cost,charge, playermagic;
					bool kill, summon, resurrect, player, single;
					string zone;

					card >> atk_c >> def_c >> act >> ab_cost >> kill >> resurrect >> player >> playermagic >> single >> zone >> charge;
					Effect* eff = new Effect{atk_c,def_c,act,ab_cost,kill,summon,resurrect,player,playermagic,single,zone,charge};

					int ac_round;
					card >> ac_round;

					bool silence;
					card >> silence;

					Enchantment* e = new Enchantment(this,name,eff,desc,cost,silence, multi);
					deck.push_back(e);
					continue;
			}else if(type == "Spell"){
					string desc;
					getline(card,desc);

					int atk_c, def_c, act, ab_cost,charge, playermagic;
					bool kill, unsummon, resurrect, player, single;
					string zone;

					card >> atk_c >> def_c >> act >> ab_cost >> kill >> unsummon >>resurrect >> player >> playermagic >> single >> zone >> charge;
					Effect* eff = new Effect{atk_c,def_c,act,ab_cost,kill,unsummon,resurrect,player,playermagic,single,zone,charge};
					
					int undo;
					card >> undo;
					Spell* s = new Spell(this,name,eff,desc,cost,undo);
					deck.emplace_back(s);
					
					continue;
			}
	}
}

// ====================== Constructors and Destructors =========================

Player::Player(const string &name, std::string deck):name{name} {
	loadDeck(deck);
}

Player::~Player(){
	for (int i = 0 ; i < hand.size();i++){
		delete hand[i];
	}

	for (int i = 0; i < deck.size();i++){
		delete deck[i];
	}
}

// ================= End of Constructors and Destructors =======================
