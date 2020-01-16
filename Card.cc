#include "Card.h"
#include "Enchantment.h"

using namespace std;

// ======================= Constructors and Destructors =======================
Card::Card(const Player* sec, const std::string &name, const Effect * eff,
            const std::string &description, int cost, const string type)
            :owner{sec}, name{name}, description{description}, cost{cost},eff{eff}, type{type}{
}

Card::~Card() {
    delete eff;
    //delete owner;
}

// ================== End of Constructors and Destructors ======================

// ============================ Getters ========================================
const string Card::getType() const{
    return type;
}
string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

string Card::getDescription() const {
    return description;
}

const Effect * const  Card::getEffect() const {
    return eff;
}

const Player* Card::getPlayer() const {
	return owner;
}

// ======================== End of Getters =====================================

void Card::apply(Card* c){}

Card* Card::notify(const Trigger t){}

card_template_t Card::drawThis(){}

