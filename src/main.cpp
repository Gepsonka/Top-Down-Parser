#include <iostream>
#include <string>
#include "parser.h"



int main(){
    std::string rules, input;

    std::cout<<"Enter the rules:"<<std::endl;
    getline(std::cin,rules);

    std::cout<<"Enter the input word"<<std::endl;
    getline(std::cin,input);

    TopDownParser TDP(rules,input);

    TDP.print_rules_content();
    //std::cout<<input;

    return 0;
}





