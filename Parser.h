#ifndef MAIN_PARSER_H
#define MAIN_PARSER_H
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <set>

using namespace std;

class tokenException : public std::exception {
public:
    explicit tokenException(Token* badTokenIn) { badToken = badTokenIn;}
    Token* what() {return badToken;}
private:
    Token* badToken;
};

class Parser
{
private:
    unsigned int index;
    vector<Predicate*> schemeVector;
    vector<Predicate*> factsVector; //when adding to the fact also add to the set
    set<string> domainSet;
    vector<Predicate*> queriesVector;
    vector<Rule*> rulesVector;
public:

    Parser(); //create datalog object here?
    ~Parser();

    void ParseSyntax(vector<Token*> tokens); //Once you have implemented this, start checking for matches on the "Success" and "Failure"

    //Make functions for each production in the grammar given to you! This is just going to check syntax, that is why it is void.
    void DatalogProgram(vector<Token*> tokens);
    void SchemeList(vector<Token*> tokens);
    void FactList(vector<Token*> tokens);
    void RuleList(vector<Token*> tokens);
    void QueryList(vector<Token*> tokens);

    void Scheme(vector<Token*> tokens);
    void Fact(vector<Token*> tokens);
    void RuleFunction(vector<Token*> tokens);
    void Query(vector<Token*> tokens);

    void HeadPredicate(string &firstId, vector<Token*> tokens, vector<Parameter*> &parameterVector);
    void PredicateFunction(string &firstId, vector<Token*> tokens, vector<Parameter*> &parameterVector);

    void PredicateList(vector<Token*> tokens, vector<Parameter*> &parameterVector);
    void ParameterList(vector<Token*> tokens,vector<Parameter*> &parameterVector);
    void StringList(vector<Token*> tokens, vector<Parameter*> &parameterVector);
    void IdList(vector<Token*> tokens, vector<Parameter*> &parameterVector);
    void ParameterFunction(vector<Token*> tokens, vector<Parameter*> &parameterVector);
    //function that returns datalog program?



    //Datalog ParseDatalog();
    //Make functions for each production in the grammar given to you! These will actually create facts, schemes, rules, and domains

};
#endif //MAIN_PARSER_H
