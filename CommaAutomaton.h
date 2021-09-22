#ifndef CS236_PROJECT1_COMMAAUTOMATON_H
#define CS236_PROJECT1_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}

    void S0(const std::string& input) {
        if (input[index] == ',') {
            inputRead = 1;
        }

        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_COMMAAUTOMATON_H
