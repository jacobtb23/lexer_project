#include "Parser.h"
#include "Predicate.h"
#include <iostream>

using namespace std;

Parser::Parser() {}

Parser::~Parser() {}

void Parser::ParseSyntax(vector<Token*> tokens) {
    cout << endl << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Testing for the parser:" << endl << endl;

    index = 0;
    try {
        DatalogProgram(tokens);
    }
    catch (Token* error) {
        cout << "Failure!" << endl;
        cout << "  ";
        error->toString();
    }
}

void Parser::DatalogProgram(vector<Token*> tokens) {
    //check for schemes keyword
    if(tokens.at(index)->ReturnTokenType() == TokenType::SCHEMES) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //now we are looking for a scheme... At least one scheme is required.
    Scheme(tokens);
    SchemeList(tokens);

    if(tokens.at(index)->ReturnTokenType() == TokenType::FACTS) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Looking for a fact. Although, they are not required.
    FactList(tokens);

    //Checking for rules keyword
    if(tokens.at(index)->ReturnTokenType() == TokenType::RULES) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //checking for a rule. Although, they are not required.
    RuleList(tokens);

    //Check for the keyword Queries...
    if(tokens.at(index)->ReturnTokenType() == TokenType::QUERIES) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for a colon
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Call query. At least one is required.
    Query(tokens);
    QueryList(tokens);

    //We made it!
    if(tokens.at(index)->ReturnTokenType() == TokenType::EOF_TOKEN) {
        index++;
        cout << "Success!" << endl;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }
}

void Parser::SchemeList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::FACTS) { //If next token is in the follow set, then we want to stop...
        //What happens here for Lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        Scheme(tokens);
        SchemeList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::FactList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RULES) { //If next token is in the follow set, then we want to stop...
        //What happens here for Lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::ID) { //If in first set keep going!
        Fact(tokens);
        FactList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::RuleList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::QUERIES) { //If next token is in the follow set, then we want to stop...
        //What happens here for Lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::ID) { //If in first set keep going!
        Rule(tokens);
        RuleList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::QueryList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::EOF_TOKEN) { //If next token is in the follow set, then we want to stop...
        //What happens here for Lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::ID) { //First set of predicate is ID.
        Query(tokens);
        QueryList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::Scheme(vector<Token*> tokens) {
    //string firstID = "";
    //vector<Parameter*> parameters;
    //vector of parameters -> &passbyreference to idlist

    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        //TODO return the current ID and set to predicate id?
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for ID again.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        //TODO push back first element onto vector of parameters in predicate object
        index++;
    }
    else {
        throw (tokens.at(index));
    }

    IdList(tokens); //pass reference to vector of parameters.

    //Look for final right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //TODO make predicate object?
}

void Parser::Fact(vector<Token*> tokens) {
    //Check for ID.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for ID again.
    if(tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
        index++;
    }
    else {
        throw (tokens.at(index));
    }

    //Lok for ID's...
    StringList(tokens); //How do we get this to stop?

    //Look for final right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for period
    if(tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }
}

void Parser::Rule(vector<Token*> tokens) {

    HeadPredicate(tokens); //Rules start with head predicates

    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON_DASH) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    Predicate(tokens);
    PredicateList(tokens);

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

}

void Parser::Query(vector<Token*> tokens) {
    //Starts with a predicate.
    Predicate(tokens);

    //Look for a Question Mark.
    if (tokens.at(index)->ReturnTokenType() == TokenType::Q_MARK) { //If next token is in the follow set, then we want to stop...
        index++;
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::HeadPredicate(vector<Token*> tokens) {
    //Check for ID
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for another ID.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Get ID's
    IdList(tokens);

    //Then check for the last Right Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }
}

void Parser::Predicate(vector<Token*> tokens) {
    //Check for ID
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }

   //check for a parameter and then parameter list
    Parameter(tokens);
    ParameterList(tokens);

    //Look for right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }
}

void Parser::PredicateList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        //Call predicate and predicate list.
        Predicate(tokens);
        PredicateList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::ParameterList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        //Call predicate and predicate list.
        Parameter(tokens);
        ParameterList(tokens);
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::StringList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        if(tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
            index++;
            StringList(tokens);
        }
        else {
            throw (tokens.at(index));
        }
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::IdList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
            index++;
            IdList(tokens);
        }
        else {
            throw (tokens.at(index));
        }
    }
    else {
        throw (tokens.at(index));
    }
}

void Parser::Parameter(vector<Token*> tokens) {
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        index++;
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
        index++;
    }
    else {
        throw (tokens.at(index)); // Output troublesome token.
    }
}

