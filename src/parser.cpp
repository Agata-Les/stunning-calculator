#include "parser.h"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <numeric>

std::vector<std::string>parser::parseInfixIntoRPN(std::string & input){
	std::vector<std::string> result_RPN;
	std::stack<char> operators;
	std::string token;
	/** 
	* @param absFlags takes 
	  1 -> left vertical bar
	  -1 -> right vertical bar
	*/
	std::vector<int> absFlags;
	bool unaryOperatorFlag {true};
	int absFlagsCounter {0};

	loadLeftRightVerticalBars(absFlags, input);
	validateInput(input, absFlags);

	for(auto it_str_input = input.begin(); it_str_input != input.end(); ++it_str_input){
	//Parsing digits
		if(std::isdigit(*it_str_input)){	
			token.push_back(*it_str_input);
			unaryOperatorFlag = false;
		}
	//Parsing parenthesis
		else if(*it_str_input == '(') operators.push('(');
		else if(*it_str_input == ')') {
			if(!token.empty()) result_RPN.push_back(token);
			while ((!operators.empty()) && (operators.top() != '(')){
				loadOperatorToResultAndPop(operators, result_RPN);
			}		
			if(!operators.empty()) operators.pop();
			token.clear();
		}
	//Parsing abs expressions
		else if(*it_str_input == '|' && absFlags.at(absFlagsCounter) == 1){
			operators.push('|');
			++absFlagsCounter;
		}
		else if(*it_str_input == '|' && absFlags.at(absFlagsCounter) == (-1)){
			if(!token.empty()) result_RPN.push_back(token);
			while ((!operators.empty()) && (operators.top() != '|')){
				loadOperatorToResultAndPop(operators, result_RPN);
			}		
			if(!operators.empty()) operators.pop();
			result_RPN.push_back("|");
			token.clear();
			++absFlagsCounter;
		}
	//Parsing operators 
		else {
			if(!token.empty()) result_RPN.push_back(token);
			if(unaryOperatorFlag == true && (*it_str_input == '-')){
				if(std::isdigit(*(it_str_input+1))) token.push_back(*it_str_input);
				else operators.push(*it_str_input);
			}
			if(unaryOperatorFlag == false){
				while(!operators.empty() && (operators.top() != '(' && operators.top() != '|') 
								&& isOperatorGreaterThanOrEqual(*it_str_input, operators.top())){
					loadOperatorToResultAndPop(operators, result_RPN);
				}		
				operators.push(*it_str_input);
				token.clear();
				unaryOperatorFlag = true;
			}
		}
	}
	if(!token.empty()) result_RPN.push_back(token);
	while(!operators.empty()){
		loadOperatorToResultAndPop(operators, result_RPN);
	}
	return result_RPN;
}

void parser::loadLeftRightVerticalBars(std::vector<int> & absFlags, const std::string & input){
	if(*input.begin() == '|') absFlags.push_back(1);
	if(input.size() > 1){
		for(auto it = input.begin()+1; it != input.end(); ++it){
			if(*it == '|' && !isdigit(*(it-1)) && *(it-1) != ')' && ! (*(it-1) == '|' && absFlags.back() == (-1))){
				absFlags.push_back(1);
			}
			else if(*it == '|' && (isdigit(*(it-1)) || *(it-1) == ')' || (*(it-1) == '|' && absFlags.back() == (-1)))){
				absFlags.push_back(-1);
			}
		}
	}
}

void parser::validateInput(std::string & input, const std::vector<int> absFlags){
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char x){return std::isspace(x);}), input.end());
	if(input.empty()) throw "Empty string";
	if(!isNumberInInput(input)) throw "No number in input";
	if(!areBracketsAndVerticalBarsCorrect(absFlags, input)) throw "Operators unmatched";
	if(!areOperatorsInValidOrder(absFlags, input)) throw "Operators invalid";
	if(arePlusMinusOperatorsTooMany(input)) throw "Syntax error";
}

bool parser::isNumberInInput(const std::string & input){
	for(auto it = input.begin(); it != input.end(); ++it){
		if(std::isdigit(*it)) return true;
	}
	return false;
}

bool parser::areBracketsAndVerticalBarsCorrect(std::vector<int> const & absFlags, std::string const & input){
	std::string::size_type bracketCounter {1};
	std::string::size_type verticalBarsCounter {0};

	if(std::accumulate(absFlags.begin(), absFlags.end(), 0) != 0) return false;
	for(auto it = input.begin(); it != input.end(); ++it){
		if(*it == '|') ++verticalBarsCounter;
		if(*it == '(') ++bracketCounter;
		if(*it == ')') --bracketCounter;
		if(bracketCounter == 0) return false;
	}
	return (bracketCounter == 1 && verticalBarsCounter%2==0);
}

bool parser::areOperatorsInValidOrder(const std::vector<int> absFlags, const std::string & input){
	int absFlagsCounter {0};

//--Check if first element is valid
	if(input.front() != '+' && input.front() != '-' && !std::isdigit(input.front()) && input.front() != '(' && !(input.front() == '|' 
		&& absFlags.at(absFlagsCounter) == 1)) return false;
	else if(input.front() == '|') ++absFlagsCounter;
//--Check if operators are used correctly
	for(auto it = input.begin()+1; it != input.end(); ++it){
		if(*it == '*' || *it == '/' || *it == ')'){
			if(*(it-1) != ')' && !std::isdigit(*(it-1)) && !(*(it-1) == '|' && absFlags.at(absFlagsCounter-1) == (-1))) return false;
		}
		else if(*it == '('){
			if( *(it-1) == ')' || std::isdigit(*(it-1)) || (*(it-1) == '|' && absFlags.at(absFlagsCounter-1) == (-1))) return false;
		}	
		else if(std::isdigit(*it)){
			if( *(it-1) == ')' || (*(it-1) == '|' && absFlags.at(absFlagsCounter-1) == -1)) return false;
		}
		else if(*it == '|' && absFlags.at(absFlagsCounter) == 1){
			if(*(it-1) == ')' || std::isdigit(*(it-1)) || (*(it-1) == '|' && absFlags.at(absFlagsCounter-1) == (-1)) ) return false;
			++absFlagsCounter;
		}
		else if(*it == '|' && absFlags.at(absFlagsCounter) == (-1)){
			if(*(it-1) != ')' && !std::isdigit(*(it-1)) && !(absFlags.at(absFlagsCounter-1) == (-1))) return false;
			++absFlagsCounter;
		}
		else if(*it != '+' && *it != '-') return false;
	}
//--Check if last element is valid
	if(input.back() != ')' && !std::isdigit(input.back()) && input.back() != '|') return false; 
	return true;
}

bool parser::arePlusMinusOperatorsTooMany(const std::string & input){
	unsigned int plusMinusCounter {0};
	
	for(auto it = input.begin(); it != input.end(); ++it){
		if(*it == '+' || *it == '-'){
			if(++plusMinusCounter > 2) return true;
		}
		else plusMinusCounter = 0;
	}
	return false;
}

void parser::loadOperatorToResultAndPop(std::stack<char> & operators, std::vector<std::string> & result){
	std::string token4operators;
	token4operators.push_back(operators.top());
	result.push_back(token4operators);
	operators.pop();
}

bool parser::isOperatorGreaterThanOrEqual(const char & token, const char stackTop){
	if(token == '-' || token == '+') return true;
	if((token == '*' || token == '/') && (stackTop == '*' || stackTop == '/')) return true;
	return false;
}
