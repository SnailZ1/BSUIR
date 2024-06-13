#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NumbersTest
{
	TEST_CLASS(NumbersTest)
	{
	public:
		TEST_METHOD(CheckPrint)
		{
			IntNum a(5);
			a.printValue();
			FloatingData b(-2.543);
			b.displayValue();
			IntNum c(11);
			FixedPoint d = a / c;
			d.print();
		}

		TEST_METHOD(CheckIntSum)
		{
			IntNum a(6);
			IntNum b(-4);
			IntNum c(0);
			IntNum d = a + b;
			d = c + c;
			d = c + a;
			d = b + c;
		}

		TEST_METHOD(CheckMulti)
		{
			IntNum a(3);
			IntNum b(-5);
			IntNum c(0);
			IntNum d = a * b;
			d = c * c;
			d = c * a;
			d = b * c;
		}

		TEST_METHOD(CheckDiv)
		{
			IntNum a(1);
			IntNum d(0);
			IntNum b(-2);
			IntNum k(7);
			IntNum n(9);
			FixedPoint c = a / b;
			FixedPoint t;
			c = b / a;
			c = b / b;
			c = d / a;
			c.print();
			t = n / k;
		}

		TEST_METHOD(CheckIntBitsCount)
		{
			IntNum a(1);
			a.setBitsCount(8);
			Assert::AreEqual(8, a.getBitsCount());
		}

		TEST_METHOD(CheckFloatingSum)
		{
			FloatingData a(0);
			FloatingData b(-3);
			FloatingData c(-0.076);
			FloatingData d(0.007876);
			FloatingData e(67.07876);
			FloatingData f(-67.07876);
			FloatingData g(76425);
			a + a;
			f + e;
			c + a;
			c + b;
			d + g;
			e + f;
			g + c;
			b + c;
			g + d;
			FloatingData h(5);
			FloatingData i(3.01);
			FloatingData j(3.03);
			h + i;
			i + j;
			j + i;
			FloatingData k(0.0000000000000000000000000001);
		}

		TEST_METHOD(CheckDivisionByZero)
		{
			IntNum a(1);
			IntNum d(0);
			Assert::ExpectException<std::exception>([&]() {
				FixedPoint c = a / d;
			});
		}

		TEST_METHOD(CheckSumBitsError)
		{
			IntNum a(1);
			a.setBitsCount(16);
			IntNum d(3);
			d.setBitsCount(64);
			Assert::ExpectException<std::exception>([&]() {
				a + d;
			});
		}

		TEST_METHOD(CheckMultiBitsError)
		{
			IntNum a(1);
			a.setBitsCount(16);
			IntNum d(3);
			d.setBitsCount(64);
			Assert::ExpectException<std::exception>([&]() {
				a * d;
			});
		}

		TEST_METHOD(CheckDivBitsError)
		{
			IntNum a(1);
			a.setBitsCount(16);
			IntNum d(3);
			d.setBitsCount(64);
			Assert::ExpectException<std::exception>([&]() {
				a / d;
			});
		}

		TEST_METHOD(CheckEqualBitsError)
		{
			IntNum a(1);
			a.setBitsCount(16);
			IntNum d(3);
			d.setBitsCount(64);
			Assert::ExpectException<std::exception>([&]() {
				a = d;
			});
		}
	};
}