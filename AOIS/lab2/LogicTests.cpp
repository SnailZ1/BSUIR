#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2/LogicalExpression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTests
{
	TEST_CLASS(LogExprTests)
	{
	public:
		TEST_METHOD(CheckExpression)
		{
			LogExpr exp("a|b&c~!a>h");
			exp.infoPrint();
		}
	};
}