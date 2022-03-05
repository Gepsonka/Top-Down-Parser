#include "parser.h"

TopDownParser::TopDownParser(const std::string& raw_rules){
    read_rules(raw_rules);
}



void TopDownParser::read_rules(const std::string &raw_rules){
    std::string curr_symbol;
    std::string curr_rule;
    bool after_arrow=false; // check if we are after the '>' in the rule declaration

    for (int i=0;i<raw_rules.length();++i){
        if (raw_rules[i]=='>'){
            after_arrow=true;
        } 
        else if (raw_rules[i]==' '){
            rules[curr_symbol]->push_back(curr_rule);
            curr_rule=curr_symbol="";
            after_arrow=false;
        }

        else if (after_arrow){
            if (std::toupper(raw_rules[i])==raw_rules[i]){
                if (raw_rules.find(raw_rules[i]+">")==std::string::npos){
                    std::cerr<<"Error: Nothing comes from "<<raw_rules[i]<<std::endl;
                    exit(-1);
                }
                else {
                    curr_rule+=raw_rules[i];
                }
            }
            else {
                curr_rule+=raw_rules[i];
            }
        } 
        else {
            if (toupper(raw_rules[i])==raw_rules[i]){
                if (curr_symbol==""){
                    curr_symbol=raw_rules[i];

                    std::vector<std::string> keys=extract_rule_symbols();
                    if (std::find(keys.begin(), keys.end(), curr_symbol)!=keys.end()){
                        rules[curr_symbol]=std::make_unique<std::vector<std::string>>();
                    }
                }
                else {
                    std::cerr<<"Cannot give more than 1 symbols (S>adeSxa is valid, Sk>fnmekSlsS or SL>kjdfSlsK is not)"<<std::endl;
                    exit(-1);
                }
            }
            else {
                std::cerr<<"Symbol cannot be terminal (lower case character): "<<raw_rules[i]<<std::endl;
                exit(-1);
            }

        }
    }
}


std::vector<std::string> TopDownParser::extract_rule_symbols() const {
    std::vector<std::string> keys;

    for (auto const& element: rules){
        keys.push_back(element.first);
    }

    return keys;
}