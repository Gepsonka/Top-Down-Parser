#include <iostream>
#include <string>
#include "parser.h"



int main(){
    std::string input;

    getline(std::cin,input);

    TopDownParser TDP(input);

    //std::cout<<input;

    return 0;
}





