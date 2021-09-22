#ifndef CS236_PROJECT1_IDAUTOMATON_H
#define CS236_PROJECT1_IDAUTOMATON_H

#include "Automaton.h"
#include <cctype>

class IdAutomaton : public Automaton
{
public:
    IdAutomaton() : Automaton(TokenType::ID) {}

    void S0(const std::string& input) {
        if (isalpha(input[index]) != 0) {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }

    void S1(const std::string& input) {
        while(isalpha(input[index]) || isdigit(input[index])) {
            inputRead++;
            index++;
        }
    }
};
#endif //CS236_PROJECT1_IDAUTOMATON_H
