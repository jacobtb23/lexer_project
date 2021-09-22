#ifndef COLONAUTOMATON_H
#define COLONAUTOMATON_H

#include "Automaton.h"

class ColonAutomaton : public Automaton
{
public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}

    void S0(const std::string& input){    if (input[index] == ':') {
        if(input[index] == ':')
        inputRead = 1;
        }

        else {
            Serr();
        }
    }
};

#endif //COLONAUTOMATON_H

