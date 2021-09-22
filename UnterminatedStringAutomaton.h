#ifndef CS236_PROJECT1_UNTERMINATEDSTRINGAUTOMATON_H
#define CS236_PROJECT1_UNTERMINATEDSTRINGAUTOMATON_H

#include "Automaton.h"

class UnterminatedStringAutomaton : public Automaton
{
public:
    UnterminatedStringAutomaton() : Automaton(TokenType::UNDEFINED) {}

    void S0(const std::string& input) {
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }

    void S1(const std::string& input) {

        //Check for EOF ...Does this work?
        if (index == (int)input.size()) {
            //Unterminated string...
        }

        else {
            if (input[index] == '\n') {
                newLines++;
            }

            inputRead++;
            index++;

            if (input[index - 1] != '\'') {
                S1(input);
            } else {
                S2(input);
            }
        }
    }

    void S2(const std::string& input) {
        if (input[index] == '\'') { //SEGFAULT ON DOUBLE QUOTES
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_UNTERMINATEDSTRINGAUTOMATON_H
