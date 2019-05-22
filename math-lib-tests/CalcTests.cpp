#include "pch.h"
#include "../math-lib/InfixCalc.hpp"


TEST(OrderOfOperations, PlusMultiply) {
	InfixCalc calc;
	calc.ParseEquation("4+2*5");
	EXPECT_DOUBLE_EQ(14, calc.Compute());
}

TEST(OrderOfOperations, PlusMultiplyDivision) {
	InfixCalc calc;
	calc.ParseEquation("4+2*5/6");
	EXPECT_DOUBLE_EQ(5.6666666666666666, calc.Compute());
}

TEST(OrderOfOperations, PlusMultiplyFunc) {
	InfixCalc calc;
	calc.ParseEquation("4+log(20)*2*5");
	EXPECT_DOUBLE_EQ(17.010299956639813, calc.Compute());
}

TEST(OrderOfOperations, MinusMultiplyFunc) {
	InfixCalc calc;
	calc.ParseEquation("-4+log(20)*2*5");
	EXPECT_DOUBLE_EQ(9.010299956639813, calc.Compute());
}

TEST(OrderOfOperations, MinusPlusMultiplyFunc) {
	InfixCalc calc;
	calc.ParseEquation("4-log(20)*2*5");
	EXPECT_DOUBLE_EQ(-9.010299956639813, calc.Compute());
}

TEST(OrderOfOperations, MinusPlusMultiplyFunc2) {
	InfixCalc calc;
	calc.ParseEquation("4+log(20)*-2*5");
	EXPECT_DOUBLE_EQ(-9.010299956639813, calc.Compute());
}

TEST(Parsing, SpacesEquation) {
	InfixCalc calc;
	calc.ParseEquation("4 + log(20) *- 2 * 5");
	EXPECT_DOUBLE_EQ(-9.010299956639813, calc.Compute());
}

TEST(Parsing, SpacesVariable) {
	InfixCalc calc;
	calc.ParseEquation("4 *x");
	calc.SetVariable("x ", 5);
	EXPECT_DOUBLE_EQ(20, calc.Compute());
}

TEST(OrderOfOperations, Float) {
	InfixCalc calc;
	calc.ParseEquation("4.5+log(20)*-2*5");
	EXPECT_DOUBLE_EQ(-8.510299956639813, calc.Compute());
}