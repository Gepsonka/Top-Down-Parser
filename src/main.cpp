#include <iostream>
#include <string>
#include "parser.h"



int main(){
    std::string input;

    std::cout<<"Enter the rules:"<<std::endl;
    getline(std::cin,input);

    TopDownParser TDP(input);

    TDP.print_rules_content();
    //std::cout<<input;

    return 0;
}





