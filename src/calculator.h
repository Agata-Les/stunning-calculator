#pragma once

#include <string>
#include <vector>

namespace calculator {
	int calculate(std::vector<std::string> const & RPN_expr);
	int execute(std::string & input);
	/** 
	* @param token must not be empty
	*/
	bool isNumber(std::string const & token);
}
