// Jacob Knox CST211 Lab4 Due: 2/9/2023

// msvc memory leak detection removed for gcc
// #define _CRT_SECURE_NO_WARNINGS
// #define _CRTDBG_MAP_ALLOC

typedef bool (*FunctionPointer)(); // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// crt memory leak detection does not work with gcc. I'm using gcc's memory leak detection
// #include <crtdbg.h>
// #include <conio.h>
#include "Queue.h"

// Strings to test
const string NAMES[] = {"Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
						"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
						"Oliver", "Tobey"};

const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int REMOVE_SIZE = 5;

// Test function declaration
bool test_default_ctor();
bool test_param_ctor();
bool test_copy_ctor();
bool test_copy_wrap_around();
bool test_move_ctor();
bool test_move_wrap_around();
bool test_copy_op_eq();
bool test_copy_op_eq_wrap_around();
bool test_move_op_eq();
bool test_move_op_eq_wrap_around();
bool test_enqueue();
bool test_enqueue_limtis();
bool test_dequeue();
bool test_dequeue_limits();
bool test_peek();
bool test_peek_limits();
bool test_empty();
bool test_full();
bool test_size();

bool test_complex_enqueue();
bool test_complex_dequeue();

// Test functions for moves
Queue<int> ReturnIntQueue(size_t size, bool remove = false, bool refill = false);
Queue<string> ReturnStrQueue(bool remove = false);

// Array of test functions
FunctionPointer test_functions[] = {
	test_default_ctor, test_param_ctor, test_copy_ctor, test_copy_wrap_around, test_move_ctor, test_move_wrap_around,
	test_copy_op_eq, test_copy_op_eq_wrap_around, test_move_op_eq, test_move_op_eq_wrap_around, test_enqueue, test_enqueue_limtis, test_dequeue, test_dequeue_limits, test_peek,
	test_peek_limits, test_empty, test_full, test_size, test_complex_enqueue, test_complex_dequeue};

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int failed_tests = 0;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed" << endl;
		}
		else
		{
			failed_tests++;
			cout << "***** failed *****" << endl;
		}
	}

	cout << endl
		 << "Total tests: " << sizeof(test_functions) / sizeof(FunctionPointer) << endl;

	if (failed_tests > 0)
		cout << endl
			 << "You have " << failed_tests << " failed tests";
	else
		cout << endl
			 << "All tests passed! Good job!";

	cout << endl;
	system("pause");
	cout << "Exiting..." << endl;

	return 0;
}

// test default constructor sets the size to 0
bool test_default_ctor()
{
	bool pass = true;

	Queue<int> queue_test = Queue<int>();

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != 10)
	{
		pass = false;
	}

	cout << "Default ctor test ";

	return pass;
}

// test parameter constructor sets the size to the parameter
bool test_param_ctor()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Param ctor test ";

	return pass;
}

// test copy constructor
bool test_copy_ctor()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// dequeue some items to make sure the copy constructor moves start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	Queue<int> queue_test2(queue_test);

	// test that the copy constructor made a deep copy
	if (queue_test2.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test2.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test2.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	// test that the original queue is unchanged
	if (queue_test.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_copy_wrap_around()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// dequeue some items to make sure the copy constructor moves start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// cause a wrap around
	for (int i = NUM_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	Queue<int> queue_test2(queue_test);

	// test that the copy constructor made a deep copy
	if (queue_test2.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test2.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test2.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	// test that the original queue is unchanged
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Copy ctor wrap test ";

	return pass;
}

// test move constructor
bool test_move_ctor()
{
	bool pass = true;

	Queue<int> queue_test(ReturnIntQueue(NUM_SIZE, true));

	// test that the move constructor has moved the data
	if (queue_test.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Move ctor test ";

	return pass;
}

bool test_move_wrap_around()
{
	bool pass = true;

	Queue<int> queue_test(ReturnIntQueue(NUM_SIZE, true, true));

	// test that the move constructor made a deep move
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Move ctor wrap test ";

	return pass;
}

// test copy assignment operator
bool test_copy_op_eq()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// dequeue some items to make sure the copy op moves start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	Queue<int> queue_test2 = queue_test; // copy op =

	// test that the copy assignment operator made a deep copy
	if (queue_test2.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test2.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test2.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	// check that the original queue is still intact
	if (queue_test.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Copy op= test ";

	return pass;
}

// make sure the copy assignment operator works with wrap around
bool test_copy_op_eq_wrap_around()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// dequeue some items to make sure the copy constructor moves start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// cause a wrap around
	for (int i = NUM_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	Queue<int> queue_test2 = queue_test;

	// test that the copy constructor made a deep copy
	if (queue_test2.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test2.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test2.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	// test that the original queue is unchanged
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Copy ctor wrap test ";

	return pass;
}

// test move assignment operator
bool test_move_op_eq()
{
	bool pass = true;

	Queue<int> queue_test = ReturnIntQueue(NUM_SIZE, true); // move op =

	// test that the move assignment operator has moved the data
	if (queue_test.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Move op= test ";

	return pass;
}

// make sure the move assignment operator works with wrap around
bool test_move_op_eq_wrap_around()
{
	bool pass = true;

	Queue<int> queue_test = ReturnIntQueue(NUM_SIZE, true, true);

	// test that the move constructor made a deep move
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Move ctor wrap test ";

	return pass;
}

// test Enqueue
bool test_enqueue()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
		// make sure the Queue has the correct number of elements
		if (queue_test.getSize() != i + 1)
		{
			pass = false;
		}
	}

	// make sure the Queue is full
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	// dequeue some items to make sure the Enqueue moves the start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// make sure queue is not full and wrap around has occurred
	for (int i = NUM_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(i);
		// make sure the Queue has the correct number of elements
		if (queue_test.getSize() != i - REMOVE_SIZE + 1)
		{
			pass = false;
		}
	}

	// check that the Queue is full
	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	cout << "Enqueue test ";

	return pass;
}

// test Enqueue limits
bool test_enqueue_limtis()
{
	bool pass = false;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	try
	{
		// try to enqueue to a full queue
		queue_test.Enqueue(0);
	}
	catch (Exception &e)
	{
		pass = true;
	}

	// check the data is still correct
	for (int i = 0; i < NUM_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Enqueue limits test ";

	return pass;
}

// test Dequeue
bool test_dequeue()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// dequeue some items to make sure the Dequeue moves the start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// check that the Queue has the correct number of elements
	if (queue_test.getSize() != NUM_SIZE - REMOVE_SIZE)
	{
		pass = false;
	}

	// enqueue some items to make sure we can still enqueue after dequeue
	for (int i = NUM_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// make sure Dequeue removes the correct data
	for (int i = NUM_SIZE - REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != i)
		{
			pass = false;
			break;
		}
		// check that the Queue has the correct number of elements
		if (queue_test.getSize() != NUM_SIZE + REMOVE_SIZE - i - 1)
		{
			pass = false;
		}
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Dequeue test ";

	return pass;
}

// test Dequeue limits
bool test_dequeue_limits()
{
	bool pass = false;

	Queue<int> queue_test(NUM_SIZE);

	try
	{
		// try to Dequeue from empty Queue
		queue_test.Dequeue();
	}
	catch (Exception &e)
	{
		pass = true;
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Dequeue limits test ";

	return pass;
}

// test peek
bool test_peek()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		// make sure peek returns the correct data
		if (queue_test.Peek() != i)
		{
			pass = false;
			break;
		}
		queue_test.Dequeue();
	}

	// make sure wrap around works
	for (int i = NUM_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	for (int i = REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		// make sure peek returns the correct data
		if (queue_test.Peek() != i)
		{
			pass = false;
			break;
		}
		queue_test.Dequeue();
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Peek test ";

	return pass;
}

// test peek limits
bool test_peek_limits()
{
	bool pass = false;

	Queue<int> queue_test(NUM_SIZE);

	try
	{
		// try to peek from empty Queue
		queue_test.Peek();
	}
	catch (Exception &e)
	{
		pass = true;
	}

	// check list is still empty
	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Peek limits test ";

	return pass;
}

bool test_empty()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	// list should start empty
	if (!queue_test.isEmpty())
	{
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
		// list should not be empty at each Enqueue
		if (queue_test.isEmpty())
		{
			pass = false;
		}
	}

	cout << "isEmpty test ";

	return pass;
}

bool test_full()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	if (queue_test.isFull())
	{
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++)
	{
		// Queue should not be full until the last Enqueue
		if (queue_test.isFull())
		{
			pass = false;
		}
		queue_test.Enqueue(i);
	}

	if (!queue_test.isFull())
	{
		pass = false;
	}

	cout << "isFull test ";

	return pass;
}

bool test_size()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++)
	{
		// Queue should be the correct size after each Enqueue
		if (queue_test.getSize() != i)
		{
			pass = false;
		}
		queue_test.Enqueue(i);
	}

	if (queue_test.getSize() != NUM_SIZE)
	{
		pass = false;
	}

	cout << "getSize test ";

	return pass;
}

bool test_max_size()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	if (queue_test.getMaxSize() != NUM_SIZE)
	{
		pass = false;
	}

	cout << "getMaxSize test ";

	return pass;
}

bool test_complex_enqueue()
{
	bool pass = true;

	Queue<string> queue_test(NUM_NAMES);

	for (int i = 0; i < NUM_NAMES; i++)
	{
		queue_test.Enqueue(NAMES[i]);
		// make sure the Queue has the correct number of elements
		if (queue_test.getSize() != i + 1)
		{
			pass = false;
		}
	}

	// make sure the Queue is full
	if (queue_test.getSize() != NUM_NAMES)
	{
		pass = false;
	}

	// dequeue some items to make sure the Enqueue moves the start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// make sure queue is not full and wrap around has occurred
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(NAMES[i]);
		// make sure the Queue has the correct number of elements
		if (queue_test.getSize() != NUM_NAMES - REMOVE_SIZE + i + 1)
		{
			pass = false;
		}
	}

	// check that the Queue is full
	if (queue_test.getSize() != NUM_NAMES)
	{
		pass = false;
	}

	// make sure the Queue has the correct data
	for (int i = REMOVE_SIZE; i < NUM_SIZE + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != NAMES[i % NUM_NAMES])
		{
			pass = false;
			break;
		}
	}

	cout << "Enqueue test ";

	return pass;
}

bool test_complex_dequeue()
{
	bool pass = true;

	Queue<string> queue_test(NUM_NAMES);

	for (int i = 0; i < NUM_NAMES; i++)
	{
		queue_test.Enqueue(NAMES[i]);
	}

	// dequeue some items to make sure the Dequeue moves the start index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// check that the Queue has the correct number of elements
	if (queue_test.getSize() != NUM_NAMES - REMOVE_SIZE)
	{
		pass = false;
	}

	// enqueue some items to make sure we can still enqueue after dequeue
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Enqueue(NAMES[i]);
	}

	// make sure Dequeue removes the correct data
	for (int i = REMOVE_SIZE; i < NUM_NAMES + REMOVE_SIZE; i++)
	{
		if (queue_test.Dequeue() != NAMES[i % NUM_NAMES])
		{
			pass = false;
			break;
		}
		// check that the Queue has the correct number of elements
		if (queue_test.getSize() != NUM_NAMES - i + REMOVE_SIZE - 1)
		{
			pass = false;
			break;
		}
	}

	if (queue_test.getSize() != 0)
	{
		pass = false;
	}

	cout << "Dequeue test ";

	return pass;
}

// return a Queue of ints from 0 to size-1
Queue<int> ReturnIntQueue(size_t size, bool remove, bool refill)
{
	Queue<int> Queue(size);

	for (int i = 0; i < size; i++)
	{
		Queue.Enqueue(i);
	}

	if (remove)
	{
		for (int i = 0; i < REMOVE_SIZE; i++)
		{
			Queue.Dequeue();
		}
	}

	if (refill)
	{
		for (int i = size; i < size + REMOVE_SIZE; i++)
		{
			Queue.Enqueue(i);
		}
	}

	return Queue;
}

// return a Queue of strings from NAMES
Queue<string> ReturnStrQueue(bool remove)
{
	Queue<string> Queue(NUM_NAMES);

	for (string name : NAMES)
	{
		Queue.Enqueue(name);
	}

	if (remove)
	{
		for (int i = 0; i < REMOVE_SIZE; i++)
		{
			Queue.Dequeue();
		}
	}

	return Queue;
}