#include "Parser.h"
#include "Parameter.h"
#include "Predicate.h"
#include <iostream>
using namespace std;

Parser::Parser() {}

Parser::~Parser() {
    for (Predicate *deletePointer : schemeVector) {
        delete deletePointer;
    }
    schemeVector.clear();

    for (Predicate *deletePointer : factsVector) {
        delete deletePointer;
    }
    factsVector.clear();

    for (Predicate *deletePointer : queriesVector) {
        delete deletePointer;
    }
    queriesVector.clear();

    for (Rule *deletePointer : rulesVector) { //class?
        delete deletePointer;
    }
    rulesVector.clear();

    domainSet.clear();

}

void Parser::ParseSyntax(vector<Token*> tokens) {

    index = 0;
    try {
        DatalogProgram(tokens);
    }
    catch (tokenException &error) {
        cout << "Failure!" << endl;
        cout << "  ";
        error.what()->toString();
    }
}

void Parser::DatalogProgram(vector<Token*> tokens) {
    //check for schemes keyword
    if(tokens.at(index)->ReturnTokenType() == TokenType::SCHEMES) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //now we are looking for a scheme... At least one scheme is required.
    Scheme(tokens);
    SchemeList(tokens);

    if(tokens.at(index)->ReturnTokenType() == TokenType::FACTS) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Looking for a fact. Although, they are not required.
    FactList(tokens);

    //Checking for rules keyword
    if(tokens.at(index)->ReturnTokenType() == TokenType::RULES) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //checking for a rule. Although, they are not required.
    RuleList(tokens);

    //Check for the keyword Queries...
    if(tokens.at(index)->ReturnTokenType() == TokenType::QUERIES) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for a colon
    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
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
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //->toString() is called here?
    cout << "Schemes(" << schemeVector.size() << "):";
    for (unsigned int i = 0; i < schemeVector.size(); i++){
        cout << endl;
        cout << "  ";
        schemeVector.at(i)->PredicateToString();

    }

    cout << endl << "Facts(" << factsVector.size() << "):";
    for (unsigned int i = 0; i < factsVector.size(); i++){
        cout << endl;
        cout << "  ";
        factsVector.at(i)->PredicateToString();
        cout << ".";
    }

    cout << endl << "Rules(" << rulesVector.size() << "):";
    for (unsigned int i = 0; i < rulesVector.size(); i++){
        cout << endl;
        cout << "  ";
        rulesVector.at(i)->RulesToString();
        cout << ".";
    }

    cout << endl <<  "Queries(" << queriesVector.size() << "):";
    for (unsigned int i = 0; i < queriesVector.size(); i++){
        cout << endl;
        cout << "  ";
        queriesVector.at(i)->PredicateToString();
        cout << "?";
    }
    cout << endl << "Domain(" << domainSet.size() << "):";
    set<string>::iterator domainIterator = domainSet.begin();
    for (unsigned int i = 0; i < domainSet.size(); i++) {
        cout << endl;
        cout << "  ";
        string setItem = domainIterator->substr(0, domainIterator->size());
        cout << setItem;
        domainIterator++;
    }
    cout << endl;
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
        throw tokenException(tokens.at(index));
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
        throw tokenException(tokens.at(index));
    }
}

void Parser::RuleList(vector<Token*> tokens) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::QUERIES) { //If next token is in the follow set, then we want to stop...
        //What happens here for Lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::ID) { //If in first set keep going!
        RuleFunction(tokens);
        RuleList(tokens);
    }
    else {
        throw tokenException(tokens.at(index));
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
        throw tokenException(tokens.at(index));
    }
}

void Parser::Scheme(vector<Token*> tokens) {

    string firstID = "";
    vector<Parameter*> parameterVector;

    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        firstID = tokens.at(index)->ReturnTokenDescription();
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for ID again.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {

        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        index++;
    }
    else {
        throw tokenException(tokens.at(index));
    }

    IdList(tokens, parameterVector); //pass reference to vector of parameters.

    //Look for final right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    Predicate* newPredicate = new Predicate(firstID,parameterVector);
    schemeVector.push_back(newPredicate);
}

void Parser::Fact(vector<Token*> tokens) {

    string firstID = "";
    vector<Parameter*> parameterVector;

    //Check for ID.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        firstID = tokens.at(index)->ReturnTokenDescription();
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    if(tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        domainSet.insert(tokens.at(index)->ReturnTokenDescription());
        index++;
    }
    else {
        throw tokenException(tokens.at(index));
    }

    StringList(tokens, parameterVector); //How do we get this to stop?

    //Look for final right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for period
    if(tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    Predicate* newPredicate = new Predicate(firstID,parameterVector);
    factsVector.push_back(newPredicate);

}

void Parser::RuleFunction(vector<Token*> tokens) {
    string firstID = "";
    vector<Parameter*> parameterVector;

    HeadPredicate(firstID, tokens, parameterVector); //Rules start with head predicates

    if(tokens.at(index)->ReturnTokenType() == TokenType::COLON_DASH) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    PredicateFunction(firstID,tokens, parameterVector);
    PredicateList(tokens, parameterVector);

    //check for colon...
    if(tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    Rule* newRule = new Rule(headPredicate,rulePredicates);
    rulesVector.push_back(newRule);
    rulePredicates.clear();

}

void Parser::Query(vector<Token*> tokens) {
    string firstID = "";
    vector<Parameter*> parameterVector;

    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        firstID = tokens.at(index)->ReturnTokenDescription();
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for ID again.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID || tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        index++;
    }
    else {
        throw tokenException(tokens.at(index));
    }

    StringOrIdList(tokens, parameterVector);

    //Look for final right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    if(tokens.at(index)->ReturnTokenType() == TokenType::Q_MARK) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    Predicate* newPredicate = new Predicate(firstID,parameterVector);
    queriesVector.push_back(newPredicate);
}

void Parser::HeadPredicate(string &firstId, vector<Token*> tokens, vector<Parameter*> &parameterVector) {

    //Check for ID
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        firstId = tokens.at(index)->ReturnTokenDescription();
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for another ID.
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Get ID's
    IdList(tokens,parameterVector);

    //Then check for the last Right Parenthesis.
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    headPredicate = new Predicate(firstId, parameterVector);
    parameterVector.clear();
}

void Parser::PredicateFunction(string &firstId, vector<Token *> tokens, vector<Parameter*> &parameterVector) {

    //Check for ID
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        firstId = tokens.at(index)->ReturnTokenDescription();
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    //Check for Left Parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::LEFT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

   //check for a parameter and then parameter list
    ParameterFunction(tokens, parameterVector);
    ParameterList(tokens, parameterVector);

    //Look for right parenthesis
    if(tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) {
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }

    Predicate* newPredicate = new Predicate(firstId,parameterVector);
    rulePredicates.push_back(newPredicate);
    parameterVector.clear();
}

void Parser::PredicateList(vector<Token*> tokens, vector<Parameter*> &parameterVector) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::PERIOD) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        //Call predicate and predicate list.
        string firstId;
        PredicateFunction(firstId,tokens,parameterVector);
        PredicateList(tokens, parameterVector);
    }
    else {
        throw tokenException(tokens.at(index));
    }
}

void Parser::ParameterList(vector<Token*> tokens, vector<Parameter*> &parameterVector) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        //Call predicate and predicate list.
        ParameterFunction(tokens,parameterVector );
        ParameterList(tokens, parameterVector);
    }
    else {
        throw tokenException(tokens.at(index));
    }
}

void Parser::StringList(vector<Token*> tokens, vector<Parameter*> &parameterVector) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        if(tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
            Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
            parameterVector.push_back(newParameter);
            domainSet.insert(tokens.at(index)->ReturnTokenDescription());
            index++;
            StringList(tokens, parameterVector);
        }
        else {
            throw tokenException(tokens.at(index));
        }
    }
    else {
        throw tokenException(tokens.at(index));
    }
}

void Parser::IdList(vector<Token*> tokens, vector<Parameter*> &parameterVector) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
            Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
            parameterVector.push_back(newParameter);
            index++;
            IdList(tokens, parameterVector);
        }
        else {
            throw tokenException(tokens.at(index));
        }
    }
    else {
        throw tokenException(tokens.at(index));
    }
}

void Parser::StringOrIdList(vector<Token *> tokens, vector<Parameter *> &parameterVector) {
    if (tokens.at(index)->ReturnTokenType() == TokenType::RIGHT_PAREN) { //If next token is in the follow set, then we want to stop...
        //lambda
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::COMMA) { //Next character is in the first set, keep looking...
        index++;

        if(tokens.at(index)->ReturnTokenType() == TokenType::ID || tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
            Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
            parameterVector.push_back(newParameter);
            index++;
            StringOrIdList(tokens, parameterVector);
        }
        else {
            throw tokenException(tokens.at(index));
        }
    }
    else {
        throw tokenException(tokens.at(index));
    }
}

void Parser::ParameterFunction(vector<Token *> tokens, vector<Parameter *> &parameterVector) {
    if(tokens.at(index)->ReturnTokenType() == TokenType::ID) {
        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        index++;
    }
    else if (tokens.at(index)->ReturnTokenType() == TokenType::STRING) {
        Parameter* newParameter = new Parameter(tokens.at(index)->ReturnTokenDescription());
        parameterVector.push_back(newParameter);
        index++;
    }
    else {
        throw tokenException(tokens.at(index)); // Output troublesome token.
    }
}

