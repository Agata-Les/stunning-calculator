#pragma once

#include <string>
#include <vector>
#include <stack>

namespace parser{
	std::vector<std::string> parseInfixIntoRPN (std::string & input);
	void validateInput(std::string & input, const std::vector<int> absFlags);
	/** 
	* @param operators must not be empty
	*/
	void loadOperatorToResultAndPop(std::stack<char> & operators, std::vector<std::string> & result);
	void loadLeftRightVerticalBars(std::vector<int> & absFlags, const std::string & input);
	bool isOperatorGreaterThanOrEqual(const char & token, const char stackTop);
	bool areBracketsAndVerticalBarsCorrect(const std::vector<int> & absFlags, const std::string & input);
	bool areOperatorsInValidOrder(const std::vector<int> absFlags, const std::string & input);
	bool arePlusMinusOperatorsTooMany(const std::string & input);
	bool isNumberInInput(const std::string & input);
}
