cmake_minimum_required(VERSION 3.16)
project(CS236project_again)

set(CMAKE_CXX_STANDARD 14)

add_executable(CS236project_again main.cpp AddAutomaton.h Automaton.h ColonDashAutomaton.h ColonDashAutomaton.cpp CommaAutomaton.h FactsAutomaton.h IdAutomaton.h LeftParenAutomaton.h Lexer.h Lexer.cpp MultiplyAutomaton.h PeriodAutomaton.h QueriesAutomaton.h QuestionMarkAutomaton.h RightParenAutomaton.h RulesAutomaton.h SchemesAutomaton.h StringsAutomata.h Token.h Token.cpp UnterminatedStringAutomaton.h LineCommentAutomaton.h BlockCommentAutomaton.h UnterminatedBlockCommentAutomaton.h Parser.h Parser.cpp Parameter.h Predicate.h Rule.h DataLog.h)
