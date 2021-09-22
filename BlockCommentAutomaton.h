#ifndef MAIN_BLOCKCOMMENTAUTOMATON_H
#define MAIN_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}

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
            Serr();
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
            inputRead++;
            index++;
            //do nothing. we've closed the block comment.
        }
        else {
            S2(input);
        }
    }
};

#endif //MAIN_BLOCKCOMMENTAUTOMATON_H
