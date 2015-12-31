// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection
//

#pragma once
#include "error.h"
#include <ostream>
#include <sstream>
#include "leaker.h"

template <typename T>
struct Node
{
	// Data in this node
	T mData;
	// Link to previous node
	Node* mPrev;
	// Link to next node
	Node* mNext;
};

template <typename T>
class ITPDoubleList
{
public:
	// Function: Default Constructor
	// Purpose: Initializes size to 0 and head/tail to null
	// Input: None
	// Returns: Nothing
	ITPDoubleList()
	{
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
		mCurr = nullptr;
	}

	// Function: Destructor
	// Purpose: Calls the clear function to delete the list
	// Input: None
	// Returns: Nothing
	~ITPDoubleList()
	{
		clear();
	}

	// Function: Copy Constructor
	// Purpose: Initializes this list as a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: Nothing
	ITPDoubleList(const ITPDoubleList& other)
	{
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;

		Node<T>* temp = other.mHead;
		while (temp != nullptr)
		{
			insert_back(temp->mData);
			temp = temp->mNext;
		}
	}

	// Assignment Operator
	// Function: Assignment Operator
	// Purpose: Clear this list, and then make a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: *this
	ITPDoubleList& operator=(const ITPDoubleList& other)
	{
		clear();
		Node<T>* temp = other.mHead;
		while (temp != nullptr)
		{
			insert_back(temp->mData);
			temp = temp->mNext;
		}

		return *this;
	}

	// Function: clear
	// Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
	// Input: None
	// Returns: Nothing
	void clear()
	{
		while (mSize > 0)
		{
			remove_front();
		}
	}

	// Function: size
	// Purpose: Gets the current size of the linked list
	// Input: None
	// Returns: size of the list
	unsigned size() const
	{
		return mSize;
	}

	// Function: insert_front
	// Purpose: Inserts a node to the front of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void insert_front(const T& value)
	{
		Node<T>* temp = new Node<T>;

		temp->mData = value;
		temp->mPrev = nullptr;
		temp->mNext = mHead;

		if (mSize == 0)
		{
			mTail = temp;
			mHead = temp;
		}
		else
		{
			mHead->mPrev = temp;
			mHead = temp;
		}
		mSize++;
	}

	// Function: get_front
	// Purpose: Gets the value of the node at the front of the list
	// Input: None
	// Returns: Value of the node at the front of the list
	T& get_front()
	{
		return mHead->mData;
	}

	// Function: remove_front
	// Purpose: Removes the node at the front of the list
	// Input: None
	// Returns: None
	void remove_front()
	{
		//if size == 0, no dice
		if (mSize == 0)
		{
			return;
		}
		//if size == 1, empty list, set all to null
		else if (mSize == 1)
		{
			delete mHead;
			mHead = nullptr;
			mTail = nullptr;
			mCurr = nullptr;
		}
		//else:
		else
		{
			//set head to current head.next
			mHead = mHead->mNext;

			//set new head.previous to null
			delete mHead->mPrev;
			mHead->mPrev = nullptr;
			reset();
		}
		//reduce size
		mSize--;
	}

	// Function: insert_back
	// Purpose: Inserts a node to the back of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void insert_back(const T& value)
	{
		Node<T>* temp = new Node <T> ;
		temp->mData = value;
		temp->mPrev = mTail;
		temp->mNext = nullptr;

		if (mSize == 0)
		{
			mTail = temp;
			mHead = temp;
		}
		else
		{
			mTail->mNext = temp;
			mTail = temp;
		}

		mSize++;
	}

	// Function: get_back
	// Purpose: Gets the value of the node at the back of the list
	// Input: None
	// Returns: Value of the node at the back of the list
	T& get_back()
	{
		return mTail->mData;
	}

	// Function: remove_back
	// Purpose: Removes the node at the back of the list
	// Input: None
	// Returns: Nothing
	void remove_back()
	{
		//if size == 0, no dice
		if (mSize == 0)
		{
			return;
		}
		//if size == 1, empty list, set all to null
		else if (mSize == 1)
		{
			delete mHead;
			mHead = nullptr;
			mTail = nullptr;
			mCurr = nullptr;
		}
		//else:
		else
		{
			//set tail to current tail.previous
			mTail = mTail->mPrev;

			//set new tail.next to null
			delete mTail->mNext;
			mTail->mNext = nullptr;
			reset();
		}
		//reduce size
		mSize--;
	}

	// Function: reset
	// Purpose: Moves the current "read" pointer to the beginning of the list
	// Input: None
	// Returns: Nothing
	void reset()
	{
		mCurr = mHead;
	}

	// Function: has_next
	// Purpose: Checks to see if there is another node after the currently read node
	// Input: None
	// Returns: True to indicate there is another valid node to read
	bool has_next()
	{
		if (mCurr->mNext == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
    }

	// Function: has_prev
	// Purpose: Checks to see if there is another node after the currently read node
	// Input: None
	// Returns: True to indicate there is another valid node to read
	bool has_prev()
	{
		if (mCurr->mPrev == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// Function: move_next
	// Purpose: Moves the reading pointer to the next node
	// Input: None
	// Returns: Nothing
	void move_next()
	{
		if (has_next())
		{
			mCurr = mCurr->mNext;
		}
	}

	// Function: movePrev
	// Purpose: Moves the reading pointer to the previous node
	// Input: None
	// Returns: Nothing
	void move_prev()
	{
		if (has_prev())
		{
			mCurr = mCurr->mPrev;
		}
		else
		{
			error("Reached beginning of vector");
		}
	}

	// Function: get_at_curr
	// Purpose: Gets the value of the node at the current reader pointer
	// Input: None
	// Returns: Value of the node at the reader pointer
	T& get_at_curr()
	{
		return mCurr->mData;
	}

	// Function: add_at_curr
	// Purpose: Inserts a node at the current reader location in the list
	// Input: Value to store in the new node
	// Returns: Nothing
	void add_at_curr(const T& value)
	{
		if (mCurr == mHead)
		{
			insert_front(value);
		}
		else
		{
			Node<T>* temp = new Node<T>;
			temp->mData = value;
			temp->mPrev = mCurr->mPrev;
			temp->mNext = mCurr;

			if (mSize == 0)
			{
				mTail = temp;
				mHead = temp;
			}
			else
			{
				mCurr->mPrev = temp;
				mCurr->mPrev->mPrev->mNext = temp;
			}
			mSize++;
		}
	}
	
	// Function: remove_at_curr
	// Purpose: Removes the node pointed to by the current read pointer
	// Input: None
	// Returns: Nothing
	void remove_at_curr()
	{
		if (mCurr == mHead)
		{
			remove_front();
		}
		else if (mCurr == mTail->mPrev)
		{
			remove_back();
		}
		else
		{
			mCurr->mPrev->mNext = mCurr->mNext;
			mCurr->mNext->mPrev = mCurr->mPrev;
			delete mCurr;
			mSize--;
			reset();
		}
	}

private:
	// Pointer to the head node
	Node<T>* mHead;
	// Pointer to the tail node
	Node<T>* mTail;
	// Pointer to current node
	Node<T>* mCurr;
	// Number of nodes currently in the list
	unsigned mSize;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!! DO NOT EDIT BELOW THIS LINE !!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
	// Function: Output Stream Operator
	// Purpose: Prints the contents of the list to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, list to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
	{
		os << "{";
		
		Node<T>* temp = list.mHead;
		while (temp != nullptr)
		{
			os << temp->mData;
			if (temp != list.mTail)
			{
				os << ",";
			}

			temp = temp->mNext;
		}

		os << "}";
		return os;
	}

	// Function: toString
	// Purpose: Converts list to a string
	// Input: None
	// Output: String (in the format as the ostream)
	std::string toString() const
	{
		std::stringstream str;
		str << *this;
		return str.str();
	}

	// Function: toReverseString
	// Purpose: Outputs the list in reverse
	// Input: None
	// Output: String in reverse
	std::string toReverseString() const
	{
		std::stringstream str;
		
		str << "{";

		Node<T>* temp = mTail;
		while (temp != nullptr)
		{
			str << temp->mData;
			if (temp != mHead)
			{
				str << ",";
			}

			temp = temp->mPrev;
		}

		str << "}";
		
		return str.str();
	}
};
