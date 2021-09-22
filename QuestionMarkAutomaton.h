#ifndef CS236_PROJECT1_QUESTIONMARKAUTOMATON_H
#define CS236_PROJECT1_QUESTIONMARKAUTOMATON_H

#include "Automaton.h"

class QuestionMarkAutomaton : public Automaton
{
public:
    QuestionMarkAutomaton() : Automaton(TokenType::Q_MARK) {}

    void S0(const std::string& input) {
        if (input[index] == '?') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //CS236_PROJECT1_QUESTIONMARKAUTOMATON_H
