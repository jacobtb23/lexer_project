#ifndef MAIN_UNTERMINATEDBLOCKCOMMENTAUTOMATON_H
#define MAIN_UNTERMINATEDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class UnterminatedBlockCommentAutomaton : public Automaton
{
public:
    UnterminatedBlockCommentAutomaton() : Automaton(TokenType::UNDEFINED) {}

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
        if(input[index] == '|') {
            inputRead++;
            index++;
            S2(input);
        }
        else {
            Serr();
        }
    }

    void S2(const std::string& input) {
        if(index == (int)input.size()) {
            //We found an unterminated block comment
        }

        else {
            if (input[index] == '\n') {
                newLines++;
            }

            inputRead++;
            index++;

            if (input[index - 1] != '|') {
                S2(input);
            }
            else {
                S3(input);
            }
        }
    }

    void S3(const std::string input) {
        if(input[index] == '#') {
            Serr();
        }
        else {
            S2(input);
        }
    }
};

#endif //MAIN_UNTERMINATEDBLOCKCOMMENTAUTOMATON_H
