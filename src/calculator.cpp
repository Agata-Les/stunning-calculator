#include "calculator.h"
#include "parser.h"
#include <stack>
#include <cstdlib>
#include <cctype>
#include <iostream>

int calculator::execute(std::string & input){
	try{
		return calculate(parser::parseInfixIntoRPN(input));
	}
	catch(const char * errorMsg){
		std::cerr<<errorMsg<<std::endl;
	}
	return -1;
}

int calculator::calculate(std::vector<std::string> const & RPNexpr){
	std::stack<int> stack;
	int result, leftNumber, rightNumber;

	for(auto itRPNexpr = RPNexpr.begin(); itRPNexpr != RPNexpr.end(); ++itRPNexpr){
		if(isNumber(*itRPNexpr)){
			stack.push(std::stoi(*itRPNexpr));
		}
		else if(*itRPNexpr == "|"){
			leftNumber = stack.top();
			stack.pop();
			if(leftNumber < 0) leftNumber *= (-1);
			stack.push(leftNumber);
		}
		else if(stack.size() == 1 && (*itRPNexpr == "-" || *itRPNexpr == "+")){
			leftNumber = stack.top();
			stack.pop();
			if(*itRPNexpr == "-") leftNumber *= (-1);
			stack.push(leftNumber);
		}
		else{
			rightNumber = stack.top();
			stack.pop();
			leftNumber = stack.top();
			stack.pop();
				if(*itRPNexpr == "+") result = leftNumber + rightNumber;
				if(*itRPNexpr == "-") result = leftNumber - rightNumber;
				if(*itRPNexpr == "*") result = leftNumber * rightNumber;
				if(*itRPNexpr == "/"){
					if(rightNumber == 0) throw "Division by zero";
					else result = leftNumber / rightNumber;
				}					
			stack.push(result);
		}
	}
	return stack.top();
}

bool calculator::isNumber(std::string const & token){
	if(!std::isdigit(*token.begin()) && !(*token.begin() == '-' && token.size() > 1)) return false;
	else if(token.size() > 1){
		for(auto it = token.begin()+1; it != token.end(); ++it){
			if(!std::isdigit(*it)) return false;
		}
	}
	return true;
}
