#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/Polynomial.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::wstring ToString(const Polynom& polynom) {
	std::wstringstream _s;
	for (int i = 0; i < polynom.getDegree(); i++) {
		_s << polynom[i];
	}
	return _s.str();
}

namespace PolynomialTest
{
	TEST_CLASS(PolynomialTest)
	{
	public:

		TEST_METHOD(TestFunc)
		{
			Polynom p1(3, { 1,3,3 });
			Assert::AreEqual<double>(3, p1.getDegree());
		}
		TEST_METHOD(TestOperatora1)
		{
			Polynom p1(3, { 1,5,3 });
			Assert::AreEqual<double>(5, p1[2]);
		}
		TEST_METHOD(TestOperatora2)
		{
			Polynom p1(3, { 1,3,3 });
			Assert::AreEqual<double>(13, p1(2));
		}
		TEST_METHOD(TestOperatora3)
		{
			Polynom p1(3, { 1,3,3 });
			Polynom p2(2, { 1,2 });
			Polynom res = p1 + p2;
			Polynom expected(3, { 2,5,3 });
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(TestOperatora4)
		{
			Polynom p1(3, { 1,3,3 });
			Polynom p2(2, { 1,2 });
			p1 += p2;
			Polynom res(3, { 2,5,3 });
			Assert::AreEqual(res, p1);
		}
		TEST_METHOD(TestOperatora5)
		{
			Polynom p1(3, { 1,3,3 });
			Polynom p2(2, { 1,2 });
			Polynom res = p1 - p2;
			Polynom expected(3, { 0,1,3 });
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(TestOperatora6)
		{
			Polynom p1(3, { 1,3,3 });
			Polynom p2(2, { 1,2 });
			p1 -= p2;
			Polynom res(3, { 0,1,3 });
			Assert::AreEqual(res, p1);
		}
		TEST_METHOD(TestOperatora7)
		{
			Polynom p1(2, { 1,1 });
			Polynom p2(2, { 1,1 });
			Polynom res = p1 * p2;
			Polynom expected(3, { 1,2,1 });
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(TestOperatora8)
		{
			Polynom p1(2, { 1,1 });
			Polynom p2(2, { 1,1 });
			p1 *= p2;
			Polynom res(3, { 1,2,1 });
			Assert::AreEqual(res, p1);
		}
		TEST_METHOD(TestOperatora9)
		{
			Polynom p1(3, { 1,2,1 });
			Polynom p2(2, { 1,1 });
			Polynom res = p1 / p2;
			Polynom expected(2, { 1,1 });
			Assert::AreEqual(expected, res);
		}
		TEST_METHOD(TestOperatora10)
		{
			Polynom p1(3, { 1,2,1 });
			Polynom p2(2, { 1,1 });
			p1 /= p2;
			Polynom res(2, { 1,1 });
			Assert::AreEqual(res, p1);
		}
	};
}
