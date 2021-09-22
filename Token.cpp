#include "Token.h"
#include <iostream>

using namespace std;

Token::Token(TokenType type, string description, int tokenStartLine) {
    this->type = type;
    this->description = description;
    this->tokenStartLine = tokenStartLine;
}

int Token::isComment() {
    if (type == TokenType::COMMENT) {
        return 1;
    }
    else {
        return 0;
    }
}

TokenType Token::ReturnTokenType() {
    return this->type;
}

string Token::ReturnTokenDescription() {
    return this->description;
}

void Token::toString() { //(COLON_DASH,":-",6)... example format.

    cout << ("(");
    //IF-IF ELSE TREE for token type.
    if(type == TokenType::COLON) {
        cout << "COLON,";
    }
    else if(type == TokenType::COLON_DASH) {
        cout << "COLON_DASH,";
    }
    else if(type == TokenType::COMMA) {
        cout << "COMMA,";
    }
    else if(type == TokenType::Q_MARK) {
        cout << "Q_MARK,";
    }
    else if(type == TokenType::LEFT_PAREN) {
        cout << "LEFT_PAREN,";
    }
    else if(type == TokenType::RIGHT_PAREN) {
        cout << "RIGHT_PAREN,";
    }
    else if(type == TokenType::MULTIPLY) {
        cout << "MULTIPLY,";
    }
    else if(type == TokenType::COMMENT) {
        cout << "COMMENT,";
    }
    else if(type == TokenType::ID) {
        cout << "ID,";
    }
    else if(type == TokenType::QUERIES) {
        cout << "QUERIES,";
    }
    else if(type == TokenType::PERIOD){
        cout << "PERIOD,";
    }
    else if(type == TokenType::FACTS) {
        cout << "FACTS,";
    }
    else if(type == TokenType::ADD) {
        cout << "ADD,";
    }
    else if(type == TokenType::UNDEFINED) {
        cout << "UNDEFINED,";
    }
    else if(type == TokenType::LEFT_PAREN) {
        cout << "LEFT_PAREN,";
    }
    else if(type == TokenType::SCHEMES) {
        cout << "SCHEMES,";
    }
    else if(type == TokenType::STRING) {
        cout << "STRING,";
    }
    else if(type == TokenType::EOF_TOKEN) {
        cout << "EOF,";
    }
    else if(type == TokenType::RULES) {
        cout << "RULES,";
    }
    cout << "\"" << description << "\"" << "," << tokenStartLine << ")" << endl;
}