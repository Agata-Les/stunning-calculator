#include "calculator.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(CalculateTest, givenRPN_calculates_simple_plus_operation_one_digit_numbers) {
	std::vector<std::string> vec {"3", "7", "+"};
    EXPECT_EQ(calculator::calculate(vec), 10);
}

TEST(CalculateTest, givenRPN_calculates_simple_plus_operation_more_digit_numbers) { 
	std::vector<std::string> vec {"13", "278", "+"};
    EXPECT_EQ(calculator::calculate(vec), 291);
}

TEST(CalculateTest, givenRPN_calculates_simple_plus_operation_negative_numbers) { 
	std::vector<std::string> vec {"-13", "278", "+"};
    EXPECT_EQ(calculator::calculate(vec), 265);
}

TEST(CalculateTest, givenRPN_calculates_simple_plus_operation_negative_numbers2) { 
	std::vector<std::string> vec {"13", "-278", "+"};
    EXPECT_EQ(calculator::calculate(vec), -265);
}

TEST(CalculateTest, givenRPN_calculates_longer_plus_operation_more_digit_numbers_neg_and_pos) { 
	std::vector<std::string> vec {"3", "7", "-5", "-12", "-", "+", "+"};
    EXPECT_EQ(calculator::calculate(vec), 17);
}

TEST(CalculateTest, givenRPN_calculates_longer_operations_more_digit_numbers_neg_and_pos) { 
	std::vector<std::string> vec {"10", "2", "6", "*", "3", "/", "-13", "9", "-", "+", "+"};
    EXPECT_EQ(calculator::calculate(vec), -8);
}

TEST(CalculateTest, calculate_simple_abs) {
	std::vector<std::string> vec {"-28","|"};
	EXPECT_EQ(calculator::calculate(vec), 28);
}

TEST(CalculateTest, calculate_expression_inside_abs) {
	std::vector<std::string> vec {"28","128","-","|"};
	EXPECT_EQ(calculator::calculate(vec), 100);
}

TEST(CalculateTest, calculate_abs_with_parenthesis) {
	std::vector<std::string> vec {"-4","|","12","28","128","-","|","*","+"};
	EXPECT_EQ(calculator::calculate(vec), 1204);
}

TEST(CalculateTest, many_absolute_values_inside_expression) {
	std::vector<std::string> vec { "16", "12", "1", "2", "24", "-", "-", "|", "15", "2", "-", "/", "-", "-4", "|", "-", "*", "144", "+" };
	EXPECT_EQ(calculator::calculate(vec), 256);
}

TEST(CalculateTest, minus_before_abs) {
	std::vector<std::string> vec { "-2","3","-","|","-" };
	EXPECT_EQ(calculator::calculate(vec), -5);
}

TEST(CalculateTest, minus_before_parenthesis) {
	std::vector<std::string> vec { "-2","3","-","-" };
	EXPECT_EQ(calculator::calculate(vec), 5);
}

TEST(CalculateTest, execute_test) {
	std::string str { "2+2" };
	EXPECT_EQ(calculator::execute(str), 4);
}

TEST(CalculateTest, execute_test_) {
	std::string str { "16*(12-|1-(2-24)|/(15-+2)-|-4|)+144" };
	EXPECT_EQ(calculator::execute(str), 256);
}

TEST(CalculateTest, execute_test__) {
	std::string str { "||-7||" };
	EXPECT_EQ(calculator::execute(str), 7);
}

TEST(CalculateTest, execute_test_2_) {
	std::string str { "((2+7)/3+(14-3)*4)/2" };
	EXPECT_EQ(calculator::execute(str), 23);
}

TEST(CalculateTest, execute_test_3_) {
	std::string str { "-(+(2+(-3)*(-2+3)))" };
	EXPECT_EQ(calculator::execute(str), 1);
}

TEST(CalculateTest, execute_test_4_) {
	std::string str { "-|2-7|+12+|3-4|" };
	EXPECT_EQ(calculator::execute(str), 8);
}

TEST(CalculateTest, execute_test_5_) {
	std::string str { "-(|2-7|+12+|3-4|)" };
	EXPECT_EQ(calculator::execute(str), -18);
}

TEST(CalculateTest, execute_test_6_) {
	std::string str { "|(2+|4-8|*|1-3|)+5|" };
	EXPECT_EQ(calculator::execute(str), 15);
}
