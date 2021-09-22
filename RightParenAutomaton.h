#ifndef CS236_PROJECT1_RIGHTPARENAUTOMATON_H
#define CS236_PROJECT1_RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}

    void S0(const std::string& input) {
        if (input[index] == ')') {
            inputRead = 1;
        }

        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_RIGHTPARENAUTOMATON_H
