#include "Lexer.h"
#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string fileName = argv[1];
    ifstream input;
    input.open(fileName);

    //Check if file is opened...
    if(!input.is_open()) {
        cout << fileName << "cannot be found/opened." << endl;
        return 1;
    }

        //Read in file.
        string entireFile;
        entireFile = "";
        ostringstream os;

        os << input.rdbuf();
        entireFile = os.str();

        //Instantiate Lexer and pass file to lexer run() method...
        Lexer *lexerObj = new Lexer();
        lexerObj->Run(entireFile);

        Parser *parserObj = new Parser();
        parserObj->ParseSyntax(lexerObj->ReturnTokens());


        delete lexerObj;
        delete parserObj;


    return 0;
}