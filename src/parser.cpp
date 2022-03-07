#include "parser.h"

TopDownParser::TopDownParser(const std::string raw_rules, const std::string input):input_word(input){
    read_rules(raw_rules);

}

TopDownParser::~TopDownParser(){
    for (auto x : list_of_states){
        delete x;
    }
}


TopDownParser::ParsingState::ParsingState(){
    i=0;
    level=0;
    symbol_alternative=0;
}


TopDownParser::ParsingState::ParsingState(const ParsingState* ps){
    state=ps->state;
    i=ps->i;
    alpha=ps->alpha;
    beta=ps->beta;
    level=ps->level;
    symbol_alternative=ps->symbol_alternative;

}

TopDownParser::ParsingState* TopDownParser::ParsingState::new_parsing_state(){
    TopDownParser::ParsingState* ps_ptr=new TopDownParser::ParsingState();
    return ps_ptr;
}

TopDownParser::ParsingState* TopDownParser::ParsingState::copy(const ParsingState* ps){
    TopDownParser::ParsingState* copy_ptr=new TopDownParser::ParsingState(ps);
    return copy_ptr;
}

void TopDownParser::print_rules_content() {
    std::cout<<"Rules:"<<std::endl;
    for (const auto x : extract_rule_symbols()){
        std::cout<<x<<" -> ";
        for (const auto y : rules[x]){
            std::cout<<y<<", ";
        }
        std::cout<<std::endl;
    }
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
            rules[curr_symbol].push_back(curr_rule);
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
                }
                else {
                    std::cerr<<"Cannot give more than 1 symbols in one rule (S>adeSxa is valid, Sk>fnmekSlsS or SL>kjdfSlsK is not)"<<std::endl;
                    exit(-1);
                }
            }
            else {
                std::cerr<<"Symbol cannot be a terminal (lower case character): "<<raw_rules[i]<<std::endl;
                exit(-1);
            }

        }
    }

    if (curr_rule!="" && curr_symbol!=""){
        rules[curr_symbol].push_back(curr_rule);
        curr_rule=curr_symbol="";
        after_arrow=false;
    }

    std::vector<std::string> symbols=extract_rule_symbols();
    if(std::find(symbols.begin(), symbols.end(),"S")==symbols.end()){
        std::cerr<<"Starting symbol is required! (S)"<<std::endl;
        exit(-1);
    }
}

void TopDownParser::start_parsing(){
    TopDownParser::ParsingState* new_state=TopDownParser::ParsingState::new_parsing_state();
    // init the starting state of the parser
    new_state->state=TopDownParser::StateofAnalysis::Q;
    new_state->i=0;
    new_state->level=0;
    new_state->symbol_alternative=0;
    new_state->beta="S";

    list_of_states.push_back(new_state);
    
    std::cerr<<"Parsing has started..."<<std::endl;
    extend("S", 0);
}

void TopDownParser::extend(std::string non_terminal, unsigned int num_of_alternative){
    if (num_of_alternative>=rules[non_terminal].size()){
        if (non_terminal=="S"){
            std::cerr<<"The input word is not an element of the given language"<<std::endl;
            std::cerr<<"Program exits..."<<std::endl;
            exit(-1);
        }
        backtrack_in_extension();
    }

    TopDownParser::ParsingState* new_state=TopDownParser::ParsingState::copy(list_of_states[list_of_states.size()-1]);
    new_state->alpha.push(non_terminal + std::to_string(num_of_alternative));
    new_state->beta.erase(0,1);
    new_state->beta=rules[non_terminal][num_of_alternative] + new_state->beta;
    new_state->level+=1;
    new_state->symbol_alternative=0;

    list_of_states.push_back(new_state);
    std::cerr<<non_terminal<<" was extended to the "<<num_of_alternative<<" alternative"<<std::endl;
    match_input();

}


void TopDownParser::match_input(){
    if (list_of_states[list_of_states.size()-1]->beta[0]==std::toupper(list_of_states[list_of_states.size()-1]->beta[0])){
        std::cerr<<"While matching input the first char of beta was non-terminal >> extending further..."<<std::endl;
        extend(std::string(1,list_of_states[list_of_states.size()-1]->beta[0]),0);
    }

    if (list_of_states[list_of_states.size()-1]->beta.length()>input_word.length()){
        std::cerr<<"While matching the input the length of beta was bigger than the input word's length >> backtrack in the input..."<<std::endl;
        backtrack_in_input();
    }

    if (list_of_states[list_of_states.size()-1]->beta[0]==input_word[list_of_states[list_of_states.size()-1]->i]){
        successful_matching();

    } else {
        unsuccessful_matching();
    }

    
}


std::vector<std::string> TopDownParser::extract_rule_symbols() const {
    std::vector<std::string> keys;

    for (auto const& element: rules){
        keys.push_back(element.first);
    }

    return keys;
}


