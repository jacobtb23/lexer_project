#ifndef MAIN_PARSER_H
#define MAIN_PARSER_H
#include "Token.h"
#include "Predicate.h"
using namespace std;

class Parser //Holds all the functions for the parsing process and has access to the tokens created by the lexer
{
private:
    unsigned int index;
    //vector<Predicate*> schemeVector;
    //vector<Predicate*> factsVector;
    //vector<Predicate*> queriesVector;

public:

    Parser();
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
    void Rule(vector<Token*> tokens);
    void Query(vector<Token*> tokens);

    void HeadPredicate(vector<Token*> tokens);
    void Predicate(vector<Token*> tokens);

    void PredicateList(vector<Token*> tokens);
    void ParameterList(vector<Token*> tokens);
    void StringList(vector<Token*> tokens);
    void IdList(vector<Token*> tokens);
    void Parameter(vector<Token*> tokens);



    //Datalog ParseDatalog();
    //Make functions for each production in the grammar given to you! These will actually create facts, schemes, rules, and domains

};
#endif //MAIN_PARSER_H
