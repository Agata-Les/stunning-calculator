#include <iostream>
#include <string>
#include "calculator.h"

int main(){
	std::string equation;

	while (std::cin.good()){
		std::getline(std::cin, equation);
		std::cout<<calculator::execute(equation)<<std::endl;
	}
	return 0;
}
