//
// Created by michael on 19/07/19.
//

#include "Minion.h"

using namespace std;

// ======================= Constructors and Destructors =======================

Minion::Minion(const Player *sec, const std::string &name,
        const std::string &description, int cost, int def, int atk, Trigger tr,
           const Effect *trigger, const Effect *actEff, int ab_cost, Info * summon_info):
           // MIL for construction
           Card{sec,name, trigger, description, cost,"Minion"},
           activeSkill{actEff}, ab_cost{ab_cost},summon_info{summon_info},
           def{def},atk{atk},trigger{tr}{
     // Initializing the two vectors for abilities and stats
}

Minion::~Minion() {

    for(auto &e: enchantments){
        delete e;
        e = nullptr;
    }

    delete activeSkill;
    delete summon_info;
}

// ================== End of Constructors and Destructors ======================

// ====================== Practically are Getters ==============================
void Minion::resurrect(){
	def = 1;
}
void Minion::restoreAct(){
    int max = 1;
    for (int i = 0 ; i < enchantments.size(); i++){
        max += enchantments[i]->getEffect()->act;
    }
    act = max;
}
bool Minion::isDead() const {
    return def <= 0;
}

int Minion::getActCost() const {
    return silent ? -1 : ab_cost;
}

bool Minion::getAct(){
    int max = act;
    for (int i = 0 ; i < enchantments.size(); i++){
        max += enchantments[i]->getEffect()->act;
    }
    if (max < act){
        act = max;
    }
    return act > 0;
}
std::vector<Enchantment*> Minion::getEnchantments(){
    return enchantments;
}
int Minion::getAtk() const {
    int ans = atk;
    for (int i = 0; i < enchantments.size(); i++){
        Enchantment* e = enchantments[i];
        if (e->getMultiplier()){
            int atkmul = e->getEffect()->atk;
            ans *= atkmul; 
        }
        else{
            int atkchange = e->getEffect()->atk;
            ans += atkchange;
        }
    }
    return ans;
}

int Minion::getDef() const{
    int ans = def;
    for (int i = 0; i < enchantments.size(); i++){
        Enchantment* e = enchantments[i];
        if (e->getMultiplier()){
            int defmul = e->getEffect()->defence;
            ans *= defmul; 
        }
        else{
            int defchange = e->getEffect()->defence;
            ans += defchange;
        }
    }
    return ans;
}

bool Minion::getSilence() const{
    int ans = def;
    for (int i = 0; i < enchantments.size(); i++){
        Enchantment* e = enchantments[i];
        if (e->getSilence()){
            return true;
        }
    }
    return false;
}

const Effect* const Minion::getActiveSkill() const {

    if(getSilence()){
        return nullptr;
    }
    return activeSkill;
}

bool Minion::canSummon() const {
    return summon;
}

Info* Minion::getInfo() const {
    return summon_info;
}

// =============== End of Practically are Getters ==============================

// ============================ METHODS ========================================

void Minion::action(){
    act --;
}
// We note at this point, by program invariance, this is strictly
// happening for the collision

void Minion::collision(const Minion *const from) {
    def = max(0, def - from->getAtk());
}

// We note that this is applying the effects onto myself, the determination
// of target population is determined in the board, at this point, I should
// modify my data accordingly

void Minion::apply(const Spell *const spell) {
    if(spell == nullptr){
        return;
    }

    if(spell->getUndo()){
        delete enchantments.back();
        enchantments.pop_back();
    }

    // We note that spells can only have a single effect, which should be
    // applied instantly without delay, then, modification of data should
    // be made instantly. Also, since this is spell, the damage or
    // healing cannot be reversed.

    const Effect * const effect = spell->getEffect();

    if(effect->kill){
        def = 0;
        return;
    }

 
    def = max(0, def + effect->defence);
    atk = max(0, atk + effect->atk);

    act += effect->act;
}

// Apply the Enchantment to the minion
void Minion::apply(Enchantment * enchantment) {
    if(enchantment == nullptr){
        return;
    }

    enchantments.emplace_back(enchantment);
    act += enchantment->getEffect()->act;
}

// Apply the effect in the Ritual
void Minion::apply(const Ritual *const ritual) {

    if(ritual == nullptr){
        return;
    }
    const Effect * effect = ritual->getEffect();
    
    if (effect->kill){
        def = 0;
        return;
    }

    def = max(0, def + effect->defence);
    atk = max(0, atk + effect->atk);

    act = max(0, act + effect->act); 

}

void Minion::apply(const Minion * const min) {
    if(min == nullptr){
        return;
    }

    const Effect * effect = min->getActiveSkill() ? min->getActiveSkill() :
                                                    min->getEffect();

    def = max(0, def + effect->defence);
    atk = max(0, atk + effect->atk);

    act = max(0, act + effect->act);
}

void Minion::apply(Card *card) {

    if (card->getType() == "Minion"){
        apply(dynamic_cast<Minion*>(card));
    }else if (card->getType() == "Ritual"){
        apply(dynamic_cast<Ritual*>(card));
    }else if (card->getType() == "Spell"){
        apply(dynamic_cast<Spell*>(card));
    }else if (card->getType() == "Enchantment"){
        apply(dynamic_cast<Enchantment*>(card));
    }
}

Minion * Minion::notify(const Trigger trig) {
    if(trig == Trigger::Start){
        restoreAct();
    }

    if(trig == Trigger::End){
        act = 0;
    }

    if(trigger == trig && act != -1){

        return this;
    }

    return nullptr;
}

card_template_t Minion::drawThis(){

    if (getActiveSkill()){
        return display_minion_activated_ability(this->getName(),this->getCost(),this->getAtk(),this->getDef(),this->getActCost(),this->getDescription());
    }else if (getEffect()){
        return display_minion_triggered_ability(this->getName(),this->getCost(),this->getAtk(),this->getDef(),this->getDescription());
    }else{
        return display_minion_no_ability(this->getName(),this->getCost(),this->getAtk(),this->getDef());
    }
}

// ============================ End of METHODS =================================
