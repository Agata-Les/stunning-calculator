#include "parser.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(ParseTest, parses_single_numbers_negative) {
	std::string str {"-28"};
	std::vector<std::string> vec {"-28"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_simple_plus_operations_one_digit_numbers_rpn_output) {
	std::string str {"3+7"};
	std::vector<std::string> vec {"3","7","+"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_simple_minus_operations_one_digit_numbers_rpn_output) {
	std::string str {"3-7"};
	std::vector<std::string> vec {"3","7","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_longer_plus_minus_operations_one_digit_numbers_rpn_output) {
	std::string str {"3-7-2+8"};
	std::vector<std::string> vec {"3","7","-","2","-","8","+"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_simple_plus_minus_operations_more_digit_numbers_rpn_output) {
	std::string str {"93+712"};
	std::vector<std::string> vec {"93","712","+"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_longer_plus_minus_operations_more_digit_numbers_rpn_output) {
	std::string str {"13-789-2+48"};
	std::vector<std::string> vec {"13","789","-","2","-","48","+"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_longer_operations_more_digit_numbers_rpn_output) {
	std::string str {"45/15*2+405-12"};
	std::vector<std::string> vec {"45","15","/","2","*","405","+","12","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_longer_operations_more_digit_numbers_with_parenthesis_rpn_output) {
	std::string str {"45/15*(2+405)-12"};
	std::vector<std::string> vec {"45","15","/","2","405","+","*","12","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_with_unary_operations_produces_rpn_output) {
	std::string str {"45+-15++13--7"};
	std::vector<std::string> vec {"45","-15","+","13","+","-7","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_with_unary_operations_and_parenthesis_produces_rpn_output) {
	std::string str {"45*-15+((+13--7)*+8/-2)--15"};
	std::vector<std::string> vec {"45","-15","*","13","-7","-","8", "*","-2","/","+","-15","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, givenINFIX_produces_rpn_output_multiple_minuses) {
	std::string str {"2-3*5-8"};
	std::vector<std::string> vec {"2","3","5","*","-","8","-"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, parses_simple_abs) {
	std::string str {"|-28|"};
	std::vector<std::string> vec {"-28","|"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, parses_expression_inside_abs) {
	std::string str {"|28-128|"};
	std::vector<std::string> vec {"28","128","-","|"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, parses_abs_with_parenthesis) {
	std::string str {"|-4|+(12*|28-128|)"};
	std::vector<std::string> vec {"-4","|","12","28","128","-","|","*","+"};
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, many_absolute_values_inside_expression) {
	std::string str {"16*(12-|1-(2-24)|/(15-+2)-|-4|)+144"};
	std::vector<std::string> vec { "16", "12", "1", "2", "24", "-", "-", "|", "15", "2", "-", "/", "-", "-4", "|", "-", "*", "144", "+" };
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, minus_before_abs) {
	std::string str {"-|-2-3|"};
	std::vector<std::string> vec { "-2","3","-","|","-" };
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, minus_before_parenthesis) {
	std::string str {"-(-2-3)"};
	std::vector<std::string> vec { "-2","3","-","-" };
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, vertical_bars_next_to_each_other) {
	std::string str {"|-2+|-1+4||"};
	std::vector<std::string> vec { "-2","-1","4","+","|","+","|" };
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}

TEST(ParseTest, multiple_abs_nestings) {
	std::string str {"||-2||"};
	std::vector<std::string> vec { "-2","|","|" };
	EXPECT_EQ(parser::parseInfixIntoRPN(str), vec);
}
