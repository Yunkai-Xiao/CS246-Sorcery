
#include "Board.h"
#include "Tool.h"
using namespace std;


Board::Board(string p1name, string p2name,string deck1,string deck2){
    Player* p1 = new Player(p1name,deck1);
    Player* p2 = new Player(p2name,deck2);
    
    players.push_back(p1);
    players.push_back(p2);

    vector<Minion*> g1,g2,m1,m2;
    vector<Ritual*> r1,r2;
    r1.push_back(nullptr);
    r2.push_back(nullptr);


    graveyard.push_back(g1);
    graveyard.push_back(g2);
    minions.emplace_back(m1);
    minions.emplace_back(m2);
    rituals.push_back(r1);
    rituals.push_back(r2);

    td = new TextDisplay();

}

Board::~Board(){
    delete td;

    for (int i = 0 ; i < players.size();i++){
        delete players[i];
    }

    for (int i = 0 ; i < graveyard.size();i++){
        for (int j = 0 ; j < graveyard[i].size(); j++){
            delete graveyard[i][j];
        }
    }

    for (int i = 0 ; i < minions.size();i++){
        for (int j = 0 ; j < minions[i].size();j++){
            delete minions[i][j];
        }
    }

    for (int i = 0 ; i < rituals.size();i++){
        for (int j = 0 ; j < rituals[i].size();j++){
            delete rituals[i][j];
        }
    }
}

void Board::shuffle(int testing){
    if(testing){
        players[player_idx]->shuffle();
        players[player_idx^1]->shuffle();
    }
    for(int i =0; i < 5; ++i){
        players[player_idx]->draw();
        players[player_idx^1]->draw();
    }
}

void Board::drawCard(){
    players[player_idx]->draw();
}

void Board::drawMinion(int idx){
    cout << (td->inspectMinion(minions[player_idx][idx])) << endl;
}
void Board::discardCard(int idx){
    players[player_idx]->discard(idx);
}
void Board::drawBoard(){
    cout << (td->drawBoard(players,minions,rituals,graveyard)) << endl;
}

void Board::drawHand(){
    cout << (td->drawHand(players[player_idx]->getHand()));
}
string Board::getPlayerName(int idx){
    return players[idx]->getName();
}
int Board::getWinner() const{
    return winner;
}
void Board::help() {
    cout<<"Commands: help -- Display this message.\n"
        "          end  -- End the current player's turn.\n"
        "          quit -- End the game.\n"
        "          attack minion other-minion -- Orders minion to attack other-minion.\n"
        "          attack minion -- Orders minion to attack the opponent.\n"
        "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
        "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\n"
        "          inspect minion -- View a minion's card and all enchantments on that minion.\n"
        "          hand -- Describe all cards in your hand.\n"
        "          board -- Describe all cards on the board.\n";
}



void Board::applyAll(Card* c){
    const Effect * const e = c->getEffect();
    const Player* const p = c->getPlayer();
    string zone = e->zone;

    if ((zone == "Allied" || zone == "All") && (p == players[player_idx])){
        players[player_idx]->apply(c); // Change the player.apply(c)
        for(int i = 0; i < minions[player_idx].size(); ++i){
            minions[player_idx][i]->apply(c);
            die(minions[player_idx][i]);
        }

        if (rituals[player_idx][0]){
            rituals[player_idx][0]->apply(c);
        }
    }
    if ((zone == "Opponent" || zone == "All") && (p == players[player_idx^1])){
        players[player_idx^1]->apply(c); // Change the player.apply(c)
        for(int i = 0; i < minions[player_idx^1].size(); ++i){
            minions[player_idx^1][i]->apply(c);
            die(minions[player_idx^1][i]);
        }

        if (rituals[player_idx^1][0]){
            rituals[player_idx^1][0]->apply(c);
        }    
    }
    return;
}

void Board::applySingle(Card* c){
    const Effect* const e = c->getEffect();
    const Player* const p = c->getPlayer();
    if (minions[player_idx].empty()){
			return;
	}
	if( (e->player == true) && (e->zone == "Allied") && (p == players[player_idx])){        
        players[player_idx]->changeMagic(1);       
        return;
    }else if(e->self){
        c->apply(c);
        die(dynamic_cast<Minion*>(c));
        return;
    }else if(((e->zone == "Allied") || (e->zone == "All")) && (p == players[player_idx])){
		
        minions[player_idx].back()->apply(c);

        die(minions[player_idx].back());

        return;
    }else if((e->zone == "Opponent" || e->zone == "All") && p != players[player_idx]){
		if (minions[player_idx].empty()){return;}
        minions[player_idx].back()->apply(c);

        die(minions[player_idx].back());
        return;
    }

}

void Board::die(const Minion* const c){
    if (c == nullptr) return;
	if(c->isDead()){
        for(int i = 0; i < minions[player_idx].size(); ++i){
            if(minions[player_idx][i] == c){
                graveyard[player_idx].emplace_back(minions[player_idx][i]);

                minions[player_idx].erase(minions[player_idx].begin() + i);
                notifyAll(Trigger::MLeave);

                return;
            }
        }

        for(int i = 0; i < minions[player_idx^1].size(); ++i){
            if(minions[player_idx^1][i] == c){
                graveyard[player_idx^1].emplace_back(minions[player_idx^1][i]);
                minions[player_idx^1].erase(minions[player_idx^1].begin() + i);
				notifyAll(Trigger::MLeave);
                return;
            }
        }
		
    }
    return ;

}

void Board::notifyAll(Trigger t){
    using namespace std;

    players[player_idx]->notify(t);

    for(int i = 0; i < minions[player_idx].size(); ++i){

        Minion* c = minions[player_idx][i]->notify(t);

        if(c){
            if(c->getEffect()->single){
                applySingle(c);
            }else{
                applyAll(c);
            }
        }

    }

    if(rituals[player_idx][0]){
        Ritual *c = rituals[player_idx][0]-> notify(t);

        if(c){
            if(c->getEffect()->single){
                applySingle(c);
            }else{
                applyAll(c);
            }
        }
    }



    if(t != Trigger::Start && t!= Trigger::End){

        for(int i = 0; i < minions[player_idx^1].size(); ++i){
            Card *c = minions[player_idx^1][i]->notify(t);
            if(c){
                if(c->getEffect()->single){
                    applySingle(c);
                }else{
                    applyAll(c);
                }
            }
        }


        if(rituals[player_idx^1][0]){
            Card *c = rituals[player_idx^1][0] -> notify(t);
            if(c){
                if(c->getEffect()->single){

                    applySingle(c);
                }else{
                    applyAll(c);
                }
            }

        }
    }

}

void Board::startTurn(){
    notifyAll(Trigger::Start);
    players[player_idx]->draw();
}

void Board::endTurn(){
    notifyAll(Trigger::End);
    notifyAll(Trigger::End);
    player_idx^=1;
}

void Board::attack(int i, int j){


    if(minions[player_idx][0]->getAct()){
        int atk1 = minions[player_idx^1][j]->getAtk();

        minions[player_idx^1][j]->collision(minions[player_idx][i]);
        minions[player_idx][0]->action();


        minions[player_idx][i]->collision(minions[player_idx^1][j]);
        die(minions[player_idx][i]);
        die(minions[player_idx^1][j]);

    }


}

void Board::attack(int i){
    if(minions[player_idx][0]->getAct()){
        players[player_idx^1]->collision(minions[player_idx][i]);
        minions[player_idx][0]->action();
    }
    if(players[player_idx^1]->isDead()){
        winner = player_idx^1;
    }
}

void Board::play(int idx, int testing){
    Card *c = players[player_idx]->getCard(idx, testing);
    if(c == nullptr) {

        return;
    }
    const string ty = c->getType(); 
    if(ty == "Enchantment"){

        return;
    }
    if(ty == "Minion"){
        if(minions[player_idx].size() < 5){

            minions[player_idx].emplace_back(dynamic_cast<Minion*>(c));
            players[player_idx]->summon(idx);

            notifyAll(Trigger::MEntry);

            return;
        }

        return;
    }
    if(ty == "Spell"){
        if(c->getEffect()->single){

            return;
        } else if(c->getEffect()->resurrect){
            if (!graveyard[player_idx].empty() && minions[player_idx].size() < 5){\
                graveyard[player_idx].back()->resurrect();
                minions[player_idx].push_back(graveyard[player_idx].back());
                graveyard[player_idx].pop_back();
            	players[player_idx]->summon(idx);
			}

        }else {
            players[player_idx]->summon(idx);
            applyAll(c);
            return;
        }
    }
    if(ty == "Ritual"){
        players[player_idx]->summon(idx);
        delete rituals[player_idx][0];
        rituals[player_idx].clear();
        rituals[player_idx].emplace_back(dynamic_cast<Ritual*>(c));
        return;
    }
}


void Board::play(int idx, int j, int a_idx, int testing){
    Card *c = (Card*)players[player_idx]->getCard(idx, testing);
    if(c == nullptr) {

        return;
    }
    const string ty = c->getType(); 
    if(ty == "Enchantment"){
        if(a_idx == 5){

            return;
        } else {
            minions[j][a_idx]->apply(c);
            players[player_idx]->summon(idx);
            return;
        }}
    if(ty == "Minion"){

        return;
    }
    if(ty == "Spell"){
        if( c->getEffect()->single == 0){

            return;
        } else if (c->getEffect()->unsummon){
            try{
                players[j]->unsummon(minions[j][a_idx]);
                minions[j].erase(minions[j].begin()+a_idx);
                players[player_idx]->summon(idx);
            }catch(string e){

            }
        }else{
            if(a_idx == 5){
                if(rituals[j][0]){
                    if(c->getEffect()->kill){
                        delete rituals[player_idx][0];
                        rituals[player_idx].clear();
                        players[player_idx]->summon(idx);
                        return;
                    }
                    rituals[j][0]->apply(c);
                    players[player_idx]->summon(idx);
                    return;
                } else {

                    return;
                } 
            }else {
                minions[j][a_idx]->apply(c);
                die(minions[j][a_idx]);
            	players[player_idx]->summon(idx);
			}
            return;
        }
    }
    if(ty == "Ritual"){
        return;
    }
}


void Board::use(int idx, int testing){
    Minion *m = minions[player_idx][idx];
    if(m->getAct()){
        if( (m->getActCost() <= players[player_idx]->getMagic() || testing ) && m->getActCost() != -1){
            const Effect * const ef = m->getActiveSkill(); 
            if(ef && !(ef->single)) {
                int n = m->getInfo()->amount;
                for(int i = 0; i < n; ++i){

                    if(minions[player_idx].size() < 5){
                        Minion *m1 = new Minion(players[player_idx], "Air Elemental", "", 0, 1,1, Trigger::NoTrigger);
                        minions[player_idx].emplace_back(m1);
                        notifyAll(Trigger::MEntry);
                    }
                }
                m->action();
                if(!testing){
                    players[player_idx]->changeMagic(-1 * (m->getActCost()));
                }
                return;
            }
        }
    }
}


void Board::use(int idx, int j, int a_idx, int testing){
    Minion *m = minions[player_idx][idx];
    if(m->getAct()){
        if( (m->getActCost() <= players[player_idx]->getMagic() || testing )&& m->getActCost() != -1){
            if(m->getActiveSkill()->single)
            {
                minions[j][a_idx]->apply(dynamic_cast<Card*>(m));
                die(minions[j][a_idx]);
                m->action();
                if(!testing){
                    players[player_idx]->changeMagic(-1 * (m->getActCost()));
                }
                return;
            }
        }
    }
}

