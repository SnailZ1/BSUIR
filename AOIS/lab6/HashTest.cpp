#include "pch.h"
#include "CppUnitTest.h"
#include "../lab6/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTest
{
	TEST_CLASS(HashTest)
	{
	public:
		
		TEST_METHOD(testHash)
		{
			HashTable hashTable(3);
			string key;
			string value;
			hashTable.insert(key = "2", value = "dsfsf");
			hashTable.insert(key = "31", value = "dsfsf");
			hashTable.insert(key = "40", value = "dsfsf");
			hashTable.insert(key = "68", value = "dsfsf");
			hashTable.insert(key = "68", value = "sfsf");
			Assert::AreEqual<bool>(true, hashTable.get(key = "2", value));
			Assert::AreEqual<bool>(true, hashTable.get(key = "68", value));
			hashTable.print();
			Assert::AreEqual<bool>(true, hashTable.remove(key = "2"));
			Assert::AreEqual<bool>(true, hashTable.remove(key = "68"));
			Assert::AreEqual<bool>(false, hashTable.get(key = "68", value));
			Assert::AreEqual<bool>(false, hashTable.remove(key = "68"));
		}
	};
}
