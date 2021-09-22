#include "Lexer.h"
#include "Token.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringsAutomata.h"
#include "UnterminatedStringAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "UnterminatedBlockCommentAutomaton.h"
#include "IdAutomaton.h"
#include "Automaton.h"
#include <iostream>
#include <cctype>

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
    //Create individual automata that identify failed strings and filed block comments
}

Lexer::~Lexer() {
    //Or do I need to loop through and delete? Ask about this...
    for (Automaton *deletePointer : automata) {
        delete deletePointer;
    }
    automata.clear();

    for (Token *deleteToken : tokens) {
        delete deleteToken;
    }
    tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringsAutomaton());
    automata.push_back(new UnterminatedStringAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new UnterminatedBlockCommentAutomaton());
    automata.push_back(new IdAutomaton());
    //Keywords before ID's...
}

vector<Token*> Lexer::ReturnTokens() {
    return tokens;
}

void Lexer::Run(string& input) {
    //Parallel and Max Algorithm
    int lineNumber = 1;
    while(input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);

        if (input.at(0) == '\n') {
            lineNumber++;
            input.erase(0,1);
            continue;
        }
        else if(isspace(input.at(0)) || input.at(0) == '\r') {
            input.erase(0,1);
            continue;
        }

        // Parallel...
        for (Automaton* currentAutomaton : automata) {
          int inputRead = currentAutomaton->Start((const string)input);
          if(inputRead > maxRead) {
              maxRead = inputRead;
              maxAutomaton = currentAutomaton;
          }
        }

        //And Max...
        Token *newToken;
        if(maxRead > 0) {
            // get rid of comments for lab 2;
           newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
           lineNumber = lineNumber + maxAutomaton->NewLinesRead();

           //lab 2 requires that no comment tokens are created.
           if(newToken->isComment() == 1) {
               //do nothing...
           }
           else {
               tokens.push_back(newToken);
           }
        }

        else{
            maxRead = 1;
            newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
            tokens.push_back(newToken);
        }

        try {
           input = input.erase(0, maxRead);
        } catch (out_of_range&) {
            cout << endl << "Oops, string is too short!" << endl;
        }
    }

    // Append EOF token.
    Token *eof;
    eof = new Token(TokenType::EOF_TOKEN,"",lineNumber);
    tokens.push_back(eof);

    // Output all tokens...
    for(int i=0; i<(int)tokens.size(); i++) {
        Token printToken = *tokens.at(i);
        printToken.toString();
    }

    // Output total number of tokens
    cout << "Total Tokens = " << tokens.size();
}
