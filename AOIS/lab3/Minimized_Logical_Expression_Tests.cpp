#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/LogicalExpression.h"
#include "../lab3/OptimizedLogicalExpr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinimizedLogicalExpressionTests
{
	TEST_CLASS(MinimizedLogicalExpressionTests)
	{
	public:

		TEST_METHOD(TestExp1)
		{
			LogicalExpr exp("!a|b|c");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp2)
		{
			LogicalExpr exp("a|!b&!b&a");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp3)
		{
			LogicalExpr exp("((a|b)&c)>(d~e)");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp4)
		{
			LogicalExpr exp("((a|b)&c)>(d~c)&!a|c&a~!b>a");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp5)
		{
			LogicalExpr exp("!((((p&r)|(q~s))|((!p)>s))|(p|(!q)))");
			exp.displayInfo();
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp6)
		{
			LogicalExpr exp("((((p&r)|(q~s))|((!p)>s))|(p|(!q)))");
			exp.displayInfo();
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp7)
		{
			LogicalExpr exp("(!a&!b&c)|(!a&b&!c)|(!a&b&c)|(a&b&!c)");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp8)
		{
			LogicalExpr exp("(a|b)~(c&c)");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp9)
		{
			LogicalExpr exp("(a>!b)~(b>!c)|a&b");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp10)
		{
			LogicalExpr exp("!a>b>a");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp11)
		{
			LogicalExpr exp("!a>b>b");
			OptimizedLogicalExpr min_exp(exp);
			exp.displayInfo();
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp12)
		{
			LogicalExpr exp("!((a&!a)&(b&!b))");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp13)
		{
			LogicalExpr exp("(a&!a)&(b&!b)");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp14)
		{
			LogicalExpr exp("!((a&!a)&(b&!b)&(c&!c))");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}

		TEST_METHOD(TestExp15)
		{
			LogicalExpr exp("(a&!a)&(b&!b)&(c&!c)");
			OptimizedLogicalExpr min_exp(exp);
			min_exp.displayInfo();
		}
	};
}