#include "pch.h"
#include "../math-lib/VariableSet.hpp"

TEST(VariableSet, IsVariable_True) 
{
	VariableSet<std::string, double> varSet;
	varSet.SetVariable("x", 5);
	
	EXPECT_EQ(true, varSet.IsVariable("x"));
}

TEST(VariableSet, IsVariable_False) 
{
	VariableSet<std::string, double> varSet;
	varSet.SetVariable("y", 5);

	EXPECT_EQ(false, varSet.IsVariable("x"));
}

TEST(VariableSet, RemoveVariable_Removed)
{
	VariableSet<std::string, double> varSet;
	varSet.SetVariable("x", 5);
	varSet.RemoveVariable("x");

	EXPECT_EQ(false, varSet.IsVariable("x"));

	bool isException = false;
	try
	{
		varSet.GetVariableValue("x");
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);
}

TEST(VariableSet, RemoveVariable_NotRemoved)
{
	VariableSet<std::string, double> varSet;
	varSet.SetVariable("x", 5);
	varSet.RemoveVariable("y");

	ASSERT_EQ(true, varSet.IsVariable("x"));
	ASSERT_EQ(5, varSet.GetVariableValue("x"));
}

TEST(VariableSet, RemoveVariable)
{
	VariableSet<std::string, double> varSet;

	varSet.SetVariable("x", 5);
	varSet.SetVariable("y", 10);
	ASSERT_EQ(5, varSet.GetVariableValue("x"));
	ASSERT_EQ(10, varSet.GetVariableValue("y"));
}

TEST(VariableSet, NamesCase)
{
	VariableSet<std::string, double> varSet;

	varSet.SetVariable("x", 5);
	varSet.SetVariable("X", 10);

	ASSERT_EQ(5, varSet.GetVariableValue("x"));
	ASSERT_EQ(10, varSet.GetVariableValue("X"));
}

TEST(VariableSet, NamesSpace)
{
	VariableSet<std::string, double> varSet;

	varSet.SetVariable("x ", 5);

	ASSERT_EQ(5, varSet.GetVariableValue(" x"));
}

TEST(VariableSet, NamesSpecial)
{
	VariableSet<std::string, double> varSet;

	bool isException = false;

	isException = false;
	try
	{
		varSet.SetVariable("x$", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x y", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x+", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x-", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x*", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x/", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x\\", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x[", 5);
	}
	catch (std::exception & e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x]", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x(", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x)", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x|", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x%", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x^", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x&", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x#", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x@", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x!", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x~", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x;", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x,", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x.", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x?", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x<", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x>", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);

	isException = false;
	try
	{
		varSet.SetVariable("x'", 5);
	}
	catch (std::exception& e)
	{
		isException = true;
	}
	ASSERT_TRUE(isException);
}
