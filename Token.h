#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    UNDEFINED,
    ID,
    STRING,
    EOF_TOKEN,
    COMMENT
};

class Token
{
private:
    // add member variables for information needed by Token
    string description;
    int tokenStartLine;
    TokenType type;

public:
    Token(TokenType type, string description, int line);
    void toString(); //(COLON_DASH,":-",6)... example format.
    int isComment();
    TokenType ReturnTokenType();
    string ReturnTokenDescription();

};

#endif // TOKEN_H
