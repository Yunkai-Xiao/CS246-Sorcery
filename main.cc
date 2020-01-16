#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "Board.h"

using namespace std;
int main(int argc, char** argv) {
    int testing = 0;
    string deck1 = "default.deck";
    string deck2 = "default.deck";
    string infile = "";
    int init = 0;
    ifstream initfile;
    for (int i = 1; i < argc; i++){
        string arguments = argv[i];
        if (arguments == "-testing"){
            testing = 1;        
        }else if (arguments == "-deck1"){
            deck1 = argv[i+1]; 
            i++;
        }else if(arguments == "-deck2"){
            deck2 = argv[i+1];
            i++;
        }else if(arguments == "-init"){
            init = 1;
            try{
                initfile.open(argv[i+1]);
            }catch(...){
                std::cerr << "error: cannot find the file" << endl;
            }
            i ++;
        }
    }


    string p1name, p2name;
    std::cout << "Enter Player1's name:" << endl;
    if (!(getline(initfile,p1name))){
        getline(cin,p1name);
    }
    
    std::cout << "Enter Player2's name:" << endl;
    if (!(getline(initfile,p2name))){
        getline(cin,p2name);
    }
    Board * b = new Board(p1name,p2name,deck1,deck2);
    b->shuffle(testing);
    while (b->getWinner() == -1){
        std::cout << "Enter Command:" << endl;
        string commandline;
        if (!(getline(initfile,commandline))){
            getline(cin, commandline);
        }
       

        stringstream s{commandline};
        
        string command;
        s >> command;

        if (command == "help"){
            b->help();
        }else if (command == "end"){

            b->endTurn();

            b->startTurn();
        }else if (command == "quit"){
            delete b;
            return 0;
        }else if (command == "draw"){
            if (testing){
                b->drawCard();
            }
        }else if (command == "discard"){
            int idx = 0;
            s >> idx;
            if (testing){
                b->discardCard(idx-1);
            }
        }else if (command == "attack"){
            int currentidx,targetidx;
            s >> currentidx;
            if (!(s>>targetidx)){
                b->attack(currentidx-1);
            }else{
                b->attack(currentidx-1,targetidx-1);
            }
        }else if (command == "play"){
            int currentidx, playeridx;
            char targetidx;
            
            s >> currentidx;
            if (!(s >> playeridx)){
                b->play(currentidx-1, testing);
            }else{
                s >> targetidx;
                if (targetidx == 'r'){
                    b->play(currentidx-1,playeridx-1, 5, testing);
                }else{
                    b->play(currentidx-1,playeridx-1,(targetidx- '1'), testing);
                }
            }
        }else if (command == "use"){
            int currentidx, playeridx;
            char targetidx;
            
            s >> currentidx;
            if (!(s >> playeridx)){
                b->use(currentidx-1, testing);
            }else{
                s >> targetidx;
                if (targetidx == 'r'){
                    b->use(currentidx-1,playeridx-1, 5, testing);
                }else{
                    b->use(currentidx-1,playeridx-1,(targetidx- '1'), testing);
                }
            }
        }else if (command == "inspect"){
            int idx;
            s >> idx;

            b->drawMinion(idx-1);
        }else if (command == "hand"){
            b->drawHand();
        }else if (command == "board"){
            b->drawBoard();
        }
    } 
    std::cout << b->getPlayerName(b->getWinner()^1) << " Wins!" << endl;

    delete b; 
}
