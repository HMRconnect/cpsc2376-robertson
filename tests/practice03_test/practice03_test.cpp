#include "pch.h"
#include "CppUnitTest.h"
#include "../../practice/Practice03/practice03.cpp"
#include <stdexcept>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
	TEST_CLASS(practice03test)
	{
	public:
		//sumRange
		TEST_METHOD(TestSumRange1)
		{
			Assert::AreEqual(MathUtils::sumRange(1, 5),15);
		}
		TEST_METHOD(TestSumRange2)
		{
			Assert::AreEqual(MathUtils::sumRange(1, -1),0);
		}
		TEST_METHOD(TestSumRange3)
		{
			Assert::AreEqual(MathUtils::sumRange(0, 0), 0);
		}

		//containsNegative
		TEST_METHOD(TestContainsNegative1)
		{
			std::vector<int> v{0,0,0,0};
			Assert::IsFalse(MathUtils::containsNegative(v));
		}
		TEST_METHOD(TestContainsNegative2)
		{
			std::vector<int> v{1,1,1};
			Assert::IsFalse(MathUtils::containsNegative(v));
		}
		TEST_METHOD(TestContainsNegative3)
		{
			std::vector<int> v{-1,-1,-1};
			Assert::IsTrue(MathUtils::containsNegative(v));
		}

		//findMax
		TEST_METHOD(TestFindMax1)
		{
			std::vector<int> v;
			Assert::ExpectException<std::invalid_argument>([&]() 
			{
				MathUtils::findMax(v);
			});
			
		}
		TEST_METHOD(TestFindMax2)
		{
			std::vector<int> v{1,2,3};
			Assert::AreEqual(MathUtils::findMax(v), 3);
		}
		TEST_METHOD(TestFindMax3)
		{
			std::vector<int> v{ 3,3,1 };
			Assert::AreEqual(MathUtils::findMax(v), 3);
		}
		TEST_METHOD(TestFindMax4)
		{
			std::vector<int> v{ -1,-1,0 };
			Assert::AreEqual(MathUtils::findMax(v), 0);
		}
	};
}
