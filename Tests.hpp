// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!! DO NOT EDIT THIS FILE !!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma once
#include "MiniCppUnit.hpp"
#include <sstream>
#include "ITPDoubleList.hpp"

class ListTest : public TestFixture<ListTest>
{
public:
	TEST_FIXTURE_DESCRIBE(ListTest, "Testing ITPDoubleList...")
	{
		TEST_CASE_DESCRIBE(testDefaultConstructor, "Testing default constructor and size");
		TEST_CASE_DESCRIBE(testInsertFront, "Testing insert_front");
		TEST_CASE_DESCRIBE(testGetFront, "Testing get_front (and insert_front)");
		TEST_CASE_DESCRIBE(testRemoveFront, "Testing remove_front (and insert_front)");
		TEST_CASE_DESCRIBE(testInsertBack, "Testing insert_back");
		TEST_CASE_DESCRIBE(testGetBack, "Testing get_back (and insert_back)");
		TEST_CASE_DESCRIBE(testRemoveBack, "Testing remove_back (and insert_back)");
		TEST_CASE_DESCRIBE(testClear, "Tests the clear function (and insert_front)");
		TEST_CASE_DESCRIBE(testCopyConstructor, "Test the copy constructor (and insert_back)");
		TEST_CASE_DESCRIBE(testAssignment, "Test the assignment operator (and insert_back)");
		TEST_CASE_DESCRIBE(testReadAtCurr, "Tests the read at current pointer (and iterate through list)");
		TEST_CASE_DESCRIBE(testInsertAtCurr, "Tests insertion at current position (begin, middle, end)");
		TEST_CASE_DESCRIBE(testRemoveAtCurr, "Tests delete at current position (begin, middle, end)");
	}
	
	void testDefaultConstructor()
	{
		ITPDoubleList<int> test;
		
		// Make sure the list is constructed with a size of 0
		ASSERT_EQUALS(0U, test.size());

		// This verifies that the head is null
		ASSERT_EQUALS("{}", test.toString());

		// This verifies that the tail is null
		ASSERT_EQUALS("{}", test.toReverseString());
	}

	void testInsertFront()
	{
		ITPDoubleList<int> test;

		for (int i = 0; i < 5; i++)
		{
			test.insert_front(i * 5);
		}

		// List should now have a size of 5
		ASSERT_EQUALS(5U, test.size());

		// This verifies the numbers are correct, as well as head of the list
		// and the next pointer of each node
		ASSERT_EQUALS("{20,15,10,5,0}", test.toString());

		// This verifies the tail of the list as well as the prev pointers of each node
		ASSERT_EQUALS("{0,5,10,15,20}", test.toReverseString());
	}

	void testGetFront()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_front(i * 3);
			// This is just checking that whatever value we just added to the front
			// is the same value that we get with get_front!
			ASSERT_EQUALS(i * 3, test.get_front());
			
			// List should now have a size of i + 1
			ASSERT_EQUALS(unsigned(i + 1), test.size());
		}
	}

	void testRemoveFront()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 3; i++)
		{
			test.insert_front(i * 7);
		}

		// List should now have a size of 3
		ASSERT_EQUALS(3U, test.size());

		// These should be correct if the inserts worked
		ASSERT_EQUALS("{14,7,0}", test.toString());
		ASSERT_EQUALS("{0,7,14}", test.toReverseString());

		// Try one remove
		test.remove_front();
		// List should now have a size of 2
		ASSERT_EQUALS(2U, test.size());
		// List should now have these values
		ASSERT_EQUALS("{7,0}", test.toString());
		ASSERT_EQUALS("{0,7}", test.toReverseString());

		// Try another remove
		test.remove_front();
		// List should now have a size of 1
		ASSERT_EQUALS(1U, test.size());
		// List should now have these values
		ASSERT_EQUALS("{0}", test.toString());
		ASSERT_EQUALS("{0}", test.toReverseString());

		// Try last remove (both head and tail should be null)
		test.remove_front();
		// List should now have a size of 0
		ASSERT_EQUALS(0U, test.size());
		// List should now be empty
		ASSERT_EQUALS("{}", test.toString());
		ASSERT_EQUALS("{}", test.toReverseString());
	}

	void testInsertBack()
	{
		ITPDoubleList<int> test;

		for (int i = 0; i < 5; i++)
		{
			test.insert_back(i * 5);
		}

		// List should now have a size of 5
		ASSERT_EQUALS(5U, test.size());

		// This verifies the numbers are correct, as well as head of the list
		// and the next pointer of each node
		ASSERT_EQUALS("{0,5,10,15,20}", test.toString());

		// This verifies the tail of the list as well as the prev pointers of each node
		ASSERT_EQUALS("{20,15,10,5,0}", test.toReverseString());
	}

	void testGetBack()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_back(i * 3);
			// This is just checking that whatever value we just added to the front
			// is the same value that we get with get_back!
			ASSERT_EQUALS(i * 3, test.get_back());

			// List should now have a size of i + 1
			ASSERT_EQUALS(unsigned(i + 1), test.size());
		}
	}

	void testRemoveBack()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 3; i++)
		{
			test.insert_back(i * 7);
		}

		// List should now have a size of 3
		ASSERT_EQUALS(3U, test.size());

		// These should be correct if the inserts worked
		ASSERT_EQUALS("{0,7,14}", test.toString());
		ASSERT_EQUALS("{14,7,0}", test.toReverseString());

		// Try one remove
		test.remove_back();
		// List should now have a size of 2
		ASSERT_EQUALS(2U, test.size());
		// List should now have these values
		ASSERT_EQUALS("{0,7}", test.toString());
		ASSERT_EQUALS("{7,0}", test.toReverseString());

		// Try another remove
		test.remove_back();
		// List should now have a size of 1
		ASSERT_EQUALS(1U, test.size());
		// List should now have these values
		ASSERT_EQUALS("{0}", test.toString());
		ASSERT_EQUALS("{0}", test.toReverseString());

		// Try last remove (both head and tail should be null)
		test.remove_back();
		// List should now have a size of 0
		ASSERT_EQUALS(0U, test.size());
		// List should now be empty
		ASSERT_EQUALS("{}", test.toString());
		ASSERT_EQUALS("{}", test.toReverseString());
	}

	void testClear()
	{
		ITPDoubleList<int> test;

		for (int i = 0; i < 20; i++)
		{
			test.insert_front(i * 5);
		}

		// List should now have a size of 20
		ASSERT_EQUALS(20U, test.size());

		test.clear();

		// List should now have a size of 0
		ASSERT_EQUALS(0U, test.size());
		// List should now be empty (this tests that head/tail are now null)
		ASSERT_EQUALS("{}", test.toString());
		ASSERT_EQUALS("{}", test.toReverseString());
	}

	void testCopyConstructor()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_back(i * 2);
		}

		ITPDoubleList<int> copy(test);

		// Size of copy should be 10
		ASSERT_EQUALS(10U, copy.size());

		// Copy should contain these values
		ASSERT_EQUALS("{0,2,4,6,8,10,12,14,16,18}", copy.toString());
		ASSERT_EQUALS("{18,16,14,12,10,8,6,4,2,0}", copy.toReverseString());
	}

	void testAssignment()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_back(i * 2);
		}

		ITPDoubleList<int> copy;

		// Let's add stuff to copy first
		for (int i = 0; i < 5; i++)
		{
			copy.insert_back(i * 7);
		}

		copy = test;

		// Size of copy should be 10
		ASSERT_EQUALS(10U, copy.size());

		// Copy should contain these values
		ASSERT_EQUALS("{0,2,4,6,8,10,12,14,16,18}", copy.toString());
		ASSERT_EQUALS("{18,16,14,12,10,8,6,4,2,0}", copy.toReverseString());
	}

	void testReadAtCurr()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_back(i * 2);
		}

		test.reset();
		int i = 0;
		while (test.has_next())
		{
			ASSERT_EQUALS(i, test.get_at_curr());
			test.move_next();
			i+=2;
		}

		while (test.has_prev())
		{
			ASSERT_EQUALS(i, test.get_at_curr());
			test.move_prev();
			i -= 2;
		}
	}

	void testInsertAtCurr()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 5; i++)
		{
			test.insert_back(i * 2);
		}

		test.reset();
		
		int num = 42;
		test.add_at_curr(num);
		// Size of copy should be 6
		ASSERT_EQUALS(6U, test.size());
		ASSERT_EQUALS("{42,0,2,4,6,8}", test.toString());


		test.move_next();
		test.move_next();
		test.move_next();
		test.add_at_curr(++num);
		ASSERT_EQUALS(7U, test.size());
		ASSERT_EQUALS("{42,0,2,4,43,6,8}", test.toString());

		test.move_next();
		test.move_next();
		test.move_next();
		test.move_next();
		test.add_at_curr(++num);
		ASSERT_EQUALS(8U, test.size());
		ASSERT_EQUALS("{42,0,2,4,43,6,44,8}", test.toString());
	}


	void testRemoveAtCurr()
	{
		ITPDoubleList<int> test;
		for (int i = 0; i < 10; i++)
		{
			test.insert_back(i * 2);
		}

		test.reset();
		ASSERT_EQUALS(10U, test.size());
		ASSERT_EQUALS("{0,2,4,6,8,10,12,14,16,18}", test.toString());
		ASSERT_EQUALS(0, test.get_at_curr());
		test.remove_at_curr();
		ASSERT_EQUALS(9U, test.size());
		ASSERT_EQUALS("{2,4,6,8,10,12,14,16,18}", test.toString());
		test.move_next();
		test.move_next();
		test.move_next();
		test.move_next();
		test.remove_at_curr();
		ASSERT_EQUALS(8U, test.size());
		ASSERT_EQUALS("{2,4,6,8,12,14,16,18}", test.toString());
		test.move_next();
		test.move_next();
		test.move_next();
		test.move_next();
		test.move_next();
		test.move_next();
		test.remove_at_curr();
		ASSERT_EQUALS(7U, test.size());
		ASSERT_EQUALS("{2,4,6,8,12,14,16}", test.toString());
	}
};

REGISTER_FIXTURE(ListTest);
