#ifndef MAIN_LINECOMMENTAUTOMATON_H
#define MAIN_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input) {
        if (input[index] == '#') {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }

    void S1(const std::string& input) {
        if (input[index] == '|') {
            Serr();
        }
        else {
            S2(input);
        }
    }
    void S2(const std::string& input) {

        if (input[index] == '\n') {
            //End comment
        }
        else if (index == (int)input.size()) {
            //End comment
        }

        else {
            inputRead++;
            index++;
            S2(input);
        }
    }
};

#endif //MAIN_LINECOMMENTAUTOMATON_H
