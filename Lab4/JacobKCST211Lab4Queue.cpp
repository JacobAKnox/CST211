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

const string REVERSE_NAMES[] = {"Tobey", "Oliver", "Oscar", "Wanda",
								"Stephanie", "Elaine", "Ann", "Terry", "Kate", "Kian", "Josh", "Alex",
								"Seth", "Brit", "Kyle"};

const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int REMOVE_SIZE = 5;

// Test function declaration
bool test_default_ctor();
bool test_param_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_copy_op_eq();
bool test_move_op_eq();
bool test_enqueue();
bool test_enqueue_limtis();
bool test_dequeue();
bool test_dequeue_limits();
bool test_peek();
bool test_peek_limits();
bool test_empty();
bool test_full();
bool test_size();
bool test_print();

bool test_complex_default_ctor();
bool test_complex_param_ctor();
bool test_complex_copy_ctor();
bool test_complex_move_ctor();
bool test_complex_copy_op_eq();
bool test_complex_move_op_eq();
bool test_complex_enqueue();
bool test_complex_enqueue_limtis();
bool test_complex_dequeue();
bool test_complex_dequeue_limits();
bool test_complex_peek();
bool test_complex_peek_limits();
bool test_complex_empty();
bool test_complex_full();
bool test_complex_size();

// Test functions for moves
Queue<int> ReturnIntQueue(size_t size, bool remove = false);
Queue<string> ReturnStrQueue(bool remove = false);

// Array of test functions
FunctionPointer test_functions[] = {test_default_ctor, test_param_ctor, test_copy_ctor, test_move_ctor,
									test_copy_op_eq, test_move_op_eq, test_enqueue, test_enqueue_limtis, test_dequeue, test_dequeue_limits, test_peek,
									test_peek_limits, test_empty, test_full, test_size, test_print /*, test_complex_default_ctor, test_complex_param_ctor, test_complex_copy_ctor,
									 test_complex_move_ctor, test_complex_copy_op_eq, test_complex_move_op_eq, test_complex_enqueue, test_complex_enqueue_limtis,
									 test_complex_dequeue, test_complex_dequeue_limits, test_complex_peek, test_complex_peek_limits, test_complex_empty,
									 test_complex_full, test_complex_size */
};

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

	// dequeue some items to make sure the Enqueue moves the end index
	for (int i = 0; i < REMOVE_SIZE; i++)
	{
		queue_test.Dequeue();
	}

	// make sure queue is not full
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

bool test_print()
{
	bool pass = true;

	Queue<int> queue_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++)
	{
		queue_test.Enqueue(i);
	}

	// it is hard to test print
	// we can check that it does not crash
	// and manually check it looks correct
	queue_test.Print();

	cout << "Print test ";

	return pass;
}

// bool test_complex_default_ctor()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>();

// 	// make sure defaults get set and Queue is empty
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	if (queue_test.getMaxSize() != -1) {
// 		pass = false;
// 	}

// 	cout << "Complex Default constructor test ";

// 	return pass;
// }

// bool test_complex_param_ctor()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// make sure size is set and Queue is empty
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	if (queue_test.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	cout << "Complex Parameterized constructor test ";

// 	return pass;
// }

// bool test_complex_copy_ctor()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	Queue<string> stack_test2 = Queue<string>(queue_test);

// 	// check metadata
// 	if (stack_test2.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	if (stack_test2.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	//check that the data is the same
// 	for (string name : REVERSE_NAMES) {
// 		if (stack_test2.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Copy constructor test ";

// 	return pass;
// }

// bool test_complex_move_ctor()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	Queue<string> stack_test2 = ReturnStrStack();

// 	// check metadata
// 	if (stack_test2.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	if (stack_test2.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	//check that the data is the same
// 	for (string name : REVERSE_NAMES) {
// 		if (stack_test2.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Move constructor test ";

// 	return pass;
// }

// bool test_complex_copy_op_eq()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	Queue<string> stack_test2;

// 	stack_test2 = queue_test;

// 	//check meta data
// 	if (stack_test2.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	if (stack_test2.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	//check that the data is the same
// 	for (string name : REVERSE_NAMES) {
// 		if (stack_test2.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Copy operator= test ";

// 	return pass;
// }

// bool test_complex_move_op_eq()
// {
// 	bool pass = true;

// 	Queue<string> stack_test2;

// 	stack_test2 = ReturnStrStack();

// 	//check meta data
// 	if (stack_test2.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	if (stack_test2.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	//check that the data is the same
// 	for (string name : REVERSE_NAMES) {
// 		if (stack_test2.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Move operator= test ";

// 	return pass;
// }

// bool test_complex_enqueue()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	int i = 0;
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 		i++;
// 		// make sure the Queue has the correct size
// 		if (queue_test.getSize() != i) {
// 			pass = false;
// 		}
// 	}

// 	//check that the data is correct
// 	for (string name : REVERSE_NAMES) {
// 		if (queue_test.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Enqueue test ";

// 	return pass;
// }

// bool test_complex_enqueue_limtis()
// {
// 	bool pass = false;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	//casue an overflow
// 	try {
// 		queue_test.Enqueue("overflow");
// 	}
// 	catch (exception e) {
// 		pass = true;
// 	}

// 	//check meta data
// 	if (queue_test.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	if (queue_test.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	//check that the data is correct
// 	for (string name : REVERSE_NAMES) {
// 		if (queue_test.Dequeue() != name) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Enqueue limits test ";

// 	return pass;
// }
// bool test_complex_dequeue()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	//check that the data is correct
// 	int i = NUM_NAMES;
// 	for (string name : REVERSE_NAMES) {
// 		if (queue_test.Dequeue() != name) {
// 			pass = false;
// 		}
// 		i--;
// 		// make sure the Queue has the correct size
// 		if (queue_test.getSize() != i) {
// 			pass = false;
// 		}
// 	}

// 	//check meta data
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	cout << "Complex Dequeue test ";

// 	return pass;
// }

// bool test_complex_dequeue_limits()
// {
// 	bool pass = false;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	//cause an underflow
// 	try {
// 		queue_test.Dequeue();
// 	}
// 	catch (exception e) {
// 		pass = true;
// 	}

// 	//check meta data
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	if (queue_test.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	cout << "Complex Dequeue limits test ";

// 	return pass;
// }

// bool test_complex_peek()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 	}

// 	//check that the data is correct
// 	for (string name : REVERSE_NAMES) {
// 		if (queue_test.Peek() != name) {
// 			pass = false;
// 		}
// 		queue_test.Dequeue();
// 	}

// 	cout << "Complex Peek test ";

// 	return pass;
// }

// bool test_complex_peek_limits()
// {
// 	bool pass = false;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	//cause an underflow
// 	try {
// 		queue_test.Peek();
// 	}
// 	catch (exception e) {
// 		pass = true;
// 	}

// 	//check meta data
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	if (queue_test.getMaxSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	cout << "Complex Peek limits test ";

// 	return pass;
// }

// bool test_complex_empty()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	//check that the Queue starts empty
// 	if (!queue_test.IsEmpty()) {
// 		pass = false;
// 	}

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 		//check that the Queue is not empty
// 		if (queue_test.IsEmpty()) {
// 			pass = false;
// 		}
// 	}

// 	//check that the data is correct
// 	for (string name : REVERSE_NAMES) {
// 		// Queue should not be empty
// 		if (queue_test.IsEmpty()) {
// 			pass = false;
// 		}
// 		queue_test.Dequeue();
// 	}

// 	//check that the Queue is empty
// 	if (!queue_test.IsEmpty()) {
// 		pass = false;
// 	}

// 	cout << "Complex Empty test ";

// 	return pass;
// }

// bool test_complex_full()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	//check that the Queue does not start full
// 	if (queue_test.IsFull()) {
// 		pass = false;
// 	}

// 	// fill the Queue
// 	for (string name : NAMES) {
// 		//Queue should not fill up
// 		if (queue_test.IsFull()) {
// 			pass = false;
// 		}
// 		queue_test.Enqueue(name);
// 	}

// 	// Queue should be full here
// 	if (!queue_test.IsFull()) {
// 		pass = false;
// 	}

// 	//check that the data is correct
// 	for (string name : REVERSE_NAMES) {
// 		queue_test.Dequeue();
// 		// Queue should not be full
// 		if (queue_test.IsFull()) {
// 			pass = false;
// 		}
// 	}

// 	cout << "Complex Full test ";

// 	return pass;
// }

// bool test_complex_size()
// {
// 	bool pass = true;

// 	Queue<string> queue_test = Queue<string>(NUM_NAMES);

// 	//check that the Queue starts empty
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	// fill the Queue
// 	int i = 0;
// 	for (string name : NAMES) {
// 		queue_test.Enqueue(name);
// 		i++;
// 		//check that the Queue has the correct size
// 		if (queue_test.getSize() != i) {
// 			pass = false;
// 		}
// 	}

// 	//check the full size of the Queue
// 	if (queue_test.getSize() != NUM_NAMES) {
// 		pass = false;
// 	}

// 	i = NUM_NAMES;
// 	for (string name : REVERSE_NAMES) {
// 		// Queue should not be empty
// 		queue_test.Dequeue();
// 		i--;
// 		//check that the Queue has the correct size
// 		if (queue_test.getSize() != i) {
// 			pass = false;
// 		}
// 	}

// 	//check that the Queue is empty
// 	if (queue_test.getSize() != 0) {
// 		pass = false;
// 	}

// 	cout << "Complex Size test ";

// 	return pass;
// }

// return a Queue of ints from 0 to size-1
Queue<int> ReturnIntQueue(size_t size, bool remove)
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