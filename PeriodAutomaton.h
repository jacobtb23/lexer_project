#ifndef CS236_PROJECT1_PERIODAUTOMATON_H
#define CS236_PROJECT1_PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}

    void S0(const std::string& input) {
        if (input[index] == '.') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_PERIODAUTOMATON_H
