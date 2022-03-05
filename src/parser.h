#ifndef TOP_DOWN_PARSER
#define TOP_DOWN_PARSER

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <cctype>
#include <memory>
#include <utility>
#include <algorithm>

class TopDownParser{
    enum StateofAnalysis{
        Q, // normal
        T, // acceptable
        B  // backtrack
    };

    struct ParsingState{
        StateofAnalysis state;
        std::string i; // pointer in the input word
        std::stack<std::string> alpha;
        std::stack<std::string> beta;

    };

    std::map<std::string,std::unique_ptr<std::vector<std::string>>> rules;

    void read_rules(const std::string &raw_rules);
    std::vector<std::string> extract_rule_symbols() const; // extract the key element from the rules


    std::vector<ParsingState> list_of_states; // for backtrack purposes
    
    bool match_input();
    bool backtrack_in_extension();
    bool backtrack_in_input();
    void successful_matching();
    void unsuccessful_matching();


    std::string input_word;

public:

    TopDownParser(const std::string& raw_rules);




};

#endif