#ifndef CS236_PROJECT1_LEFTPARENAUTOMATON_H
#define CS236_PROJECT1_LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}

    void S0(const std::string& input) {
        if (input[index] == '(') {
            inputRead = 1;
        }

        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_LEFTPARENAUTOMATON_H
