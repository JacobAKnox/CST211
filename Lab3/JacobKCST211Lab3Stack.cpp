//Jacob Knox CST211 Lab3 Due: 2/2/2023

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// crt memory leak detection does not work with gcc. I'm using gcc's memory leak detection
// #include <crtdbg.h>
// #include <conio.h>
#include "Stack.h"

// Strings to test
const string NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const string REVERSE_NAMES[] = { "Tobey", "Oliver", "Oscar", "Wanda", 
"Stephanie", "Elaine", "Ann", "Terry", "Kate", "Kian", "Josh", "Alex",
"Seth", "Brit", "Kyle" };

const int NUM_NAMES = 15;
const int NUM_SIZE = 10;

// Test function declaration
bool test_default_ctor();
bool test_param_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_copy_op_eq();
bool test_move_op_eq();
bool test_push();
bool test_push_limtis();
bool test_pop();
bool test_pop_limits();
bool test_peek();
bool test_peek_limits();
bool test_empty();
bool test_full();
bool test_size();

bool test_complex_default_ctor();
bool test_complex_param_ctor();
bool test_complex_copy_ctor();
bool test_complex_move_ctor();
bool test_complex_copy_op_eq();
bool test_complex_move_op_eq();
bool test_complex_push();
bool test_complex_push_limtis();
bool test_complex_pop();
bool test_complex_pop_limits();
bool test_complex_peek();
bool test_complex_peek_limits();
bool test_complex_empty();
bool test_complex_full();
bool test_complex_size();

// Test functions for moves
Stack<int> ReturnIntStack(size_t size);
Stack<string> ReturnStrStack();

// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor, test_param_ctor, test_copy_ctor, test_move_ctor,
test_copy_op_eq, test_move_op_eq, test_push, test_push_limtis, test_pop, test_pop_limits, test_peek, 
test_peek_limits, test_empty, test_full, test_size, test_complex_default_ctor, test_complex_param_ctor, test_complex_copy_ctor,
test_complex_move_ctor, test_complex_copy_op_eq, test_complex_move_op_eq, test_complex_push, test_complex_push_limtis,
test_complex_pop, test_complex_pop_limits, test_complex_peek, test_complex_peek_limits, test_complex_empty,
test_complex_full, test_complex_size };

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

	cout << endl << "Total tests: " << sizeof(test_functions) / sizeof(FunctionPointer) << endl;

	if (failed_tests > 0)
		cout << endl << "You have " << failed_tests << " failed tests";
	else
		cout << endl << "All tests passed! Good job!";

	cout << endl;
	system("pause");
	cout << "Exiting..." << endl;

	return 0;
}

// test default constructor sets the size to 0
bool test_default_ctor()
{
	bool pass = true;

	Stack<int> stack_test = Stack<int>();

	if (stack_test.getMaxSize() != -1) {
		pass = false;
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Default ctor test ";

	return pass;
}

// test parameter constructor sets the size to the parameter
bool test_param_ctor()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	if (stack_test.getMaxSize() != NUM_SIZE) {
		pass = false;
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Param ctor test ";

	return pass;
}

// test copy constructor
bool test_copy_ctor()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
	}

	Stack<int> stack_test2(stack_test);

	// test that the copy constructor made a deep copy
	if (stack_test2.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_SIZE) {
		pass = false;
	}

	for (int i = NUM_SIZE-1; i > 0; i--) {
		if (stack_test2.Pop() != i) {
			pass = false;
		}
	}

	cout << "Copy ctor test ";

	return pass;
}

// test move constructor
bool test_move_ctor()
{
	bool pass = true;

	Stack<int> stack_test(ReturnIntStack(NUM_SIZE));

	// test that the move constructor has moved the data
	if (stack_test.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_SIZE) {
		pass = false;
	}

	for (int i = NUM_SIZE-1; i > 0; i--) {
		if (stack_test.Pop() != i) {
			pass = false;
		}
	}

	cout << "Move ctor test ";

	return pass;
}

// test copy assignment operator
bool test_copy_op_eq()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
	}

	Stack<int> stack_test2;
	stack_test2 = stack_test; // copy op =

	// test that the copy assignment operator made a deep copy
	if (stack_test2.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_SIZE) {
		pass = false;
	}

	for (int i = NUM_SIZE-1; i > 0; i--) {
		if (stack_test2.Pop() != i) {
			pass = false;
		}
	}

	cout << "Copy op= test ";

	return pass;
}

// test move assignment operator
bool test_move_op_eq()
{
	bool pass = true;

	Stack<int> stack_test = ReturnIntStack(NUM_SIZE); // move op =

	// test that the move assignment operator has moved the data
	if (stack_test.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_SIZE) {
		pass = false;
	}

	for (int i = NUM_SIZE-1; i > 0; i--) {
		if (stack_test.Pop() != i) {
			pass = false;
		}
	}

	cout << "Move op= test ";

	return pass;
}

// test push
bool test_push()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
		// make sure the stack has the correct number of elements
		if (stack_test.getNumElements() != i+1) {
			pass = false;
		}
	}

	// make sure the stack is full
	if (stack_test.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	// make sure the stack has the correct data
	for (int i = NUM_SIZE-1; i > 0; i--) {
		if (stack_test.Pop() != i) {
			pass = false;
		}
	}

	cout << "Push test ";

	return pass;
}

// test push limits
bool test_push_limtis()
{
	bool pass = false;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
	}

	try {
		stack_test.Push(0);
	}
	catch (Exception &e) {
		pass = true;
	}

	// check the data is still correct
	for (int i = NUM_SIZE-1; i >= 0; i--) {
		if (stack_test.Pop() != i) {
			pass = false;
		}
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Push limits test ";

	return pass;
}

// test pop
bool test_pop()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
	}

	// make sure pop removes the correct data
	for (int i = NUM_SIZE-1; i >= 0; i--) {
		if (stack_test.Pop() != i) {
			pass = false;
			break;
		}
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Pop test ";

	return pass;
}

// test pop limits
bool test_pop_limits()
{
	bool pass = false;

	Stack<int> stack_test(NUM_SIZE);

	try {
		// try to pop from empty stack
		stack_test.Pop();
	}
	catch (Exception &e) {
		pass = true;
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Pop limits test ";

	return pass;
}

// test peek
bool test_peek()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
	}

	// make sure peek returns the correct data
	for (int i = NUM_SIZE-1; i >= 0; i--) {
		if (stack_test.Peek() != i) {
			pass = false;
			break;
		}
		stack_test.Pop();
	}

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Peek test ";

	return pass;
}

// test peek limits
bool test_peek_limits()
{
	bool pass = false;

	Stack<int> stack_test(NUM_SIZE);

	try {
		stack_test.Peek();
	}
	catch (Exception &e) {
		pass = true;
	}

	// check list is still empty
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Peek limits test ";

	return pass;
}

bool test_empty()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	//list should start empty
	if (!stack_test.IsEmpty()) {
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++) {
		stack_test.Push(i);
		//list should not be empty at each push
		if (stack_test.IsEmpty()) {
			pass = false;
		}
	}

	cout << "isEmpty test ";

	return pass;
}

bool test_full()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	if (stack_test.IsFull()) {
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++) {
		// stack should not be full until the last push
		if (stack_test.IsFull()) {
			pass = false;
		}
		stack_test.Push(i);
	}

	if (!stack_test.IsFull()) {
		pass = false;
	}

	cout << "isFull test ";

	return pass;
}

bool test_size()
{
	bool pass = true;

	Stack<int> stack_test(NUM_SIZE);

	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	for (int i = 0; i < NUM_SIZE; i++) {
		//stack should be the correct size after each push
		if (stack_test.getNumElements() != i) {
			pass = false;
		}
		stack_test.Push(i);
	}

	if (stack_test.getNumElements() != NUM_SIZE) {
		pass = false;
	}

	cout << "getNumElements test ";

	return pass;
}

bool test_complex_default_ctor() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>();

	// make sure defaults get set and stack is empty
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	if (stack_test.getMaxSize() != -1) {
		pass = false;
	}

	cout << "Complex Default constructor test ";

	return pass;
}

bool test_complex_param_ctor() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// make sure size is set and stack is empty
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	cout << "Complex Parameterized constructor test ";

	return pass;
}

bool test_complex_copy_ctor() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	Stack<string> stack_test2 = Stack<string>(stack_test);

	// check metadata
	if (stack_test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	//check that the data is the same
	for (string name : REVERSE_NAMES) {
		if (stack_test2.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Copy constructor test ";

	return pass;	
}

bool test_complex_move_ctor() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	Stack<string> stack_test2 = ReturnStrStack();

	// check metadata
	if (stack_test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	//check that the data is the same
	for (string name : REVERSE_NAMES) {
		if (stack_test2.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Move constructor test ";

	return pass;	
}

bool test_complex_copy_op_eq()
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	Stack<string> stack_test2;

	stack_test2 = stack_test;

	//check meta data
	if (stack_test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	//check that the data is the same
	for (string name : REVERSE_NAMES) {
		if (stack_test2.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Copy operator= test ";

	return pass;	
}

bool test_complex_move_op_eq() 
{ 
	bool pass = true;

	Stack<string> stack_test2;

	stack_test2 = ReturnStrStack();

	//check meta data
	if (stack_test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	if (stack_test2.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	//check that the data is the same
	for (string name : REVERSE_NAMES) {
		if (stack_test2.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Move operator= test ";

	return pass;	
}

bool test_complex_push() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	int i = 0;
	for (string name : NAMES) {
		stack_test.Push(name);
		i++;
		// make sure the stack has the correct size
		if (stack_test.getNumElements() != i) {
			pass = false;
		}
	}

	//check that the data is correct
	for (string name : REVERSE_NAMES) {
		if (stack_test.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Push test ";

	return pass;
}

bool test_complex_push_limtis() 
{ 
	bool pass = false;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	//casue an overflow
	try {
		stack_test.Push("overflow");
	}
	catch (exception e) {
		pass = true;
	}

	//check meta data
	if (stack_test.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	//check that the data is correct
	for (string name : REVERSE_NAMES) {
		if (stack_test.Pop() != name) {
			pass = false;
		}
	}

	cout << "Complex Push limits test ";

	return pass;
}
bool test_complex_pop() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	//check that the data is correct
	int i = NUM_NAMES;
	for (string name : REVERSE_NAMES) {
		if (stack_test.Pop() != name) {
			pass = false;
		}
		i--;
		// make sure the stack has the correct size
		if (stack_test.getNumElements() != i) {
			pass = false;
		}
	}

	//check meta data
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Complex Pop test ";

	return pass;
}

bool test_complex_pop_limits() 
{ 
	bool pass = false;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	//cause an underflow
	try {
		stack_test.Pop();
	}
	catch (exception e) {
		pass = true;
	}

	//check meta data
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	cout << "Complex Pop limits test ";

	return pass;
}

bool test_complex_peek() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
	}

	//check that the data is correct
	for (string name : REVERSE_NAMES) {
		if (stack_test.Peek() != name) {
			pass = false;
		}
		stack_test.Pop();
	}

	cout << "Complex Peek test ";

	return pass;
}

bool test_complex_peek_limits() 
{ 
	bool pass = false;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	//cause an underflow
	try {
		stack_test.Peek();
	}
	catch (exception e) {
		pass = true;
	}

	//check meta data
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	if (stack_test.getMaxSize() != NUM_NAMES) {
		pass = false;
	}

	cout << "Complex Peek limits test ";

	return pass;
}

bool test_complex_empty() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	//check that the stack starts empty
	if (!stack_test.IsEmpty()) {
		pass = false;
	}

	// fill the stack
	for (string name : NAMES) {
		stack_test.Push(name);
		//check that the stack is not empty
		if (stack_test.IsEmpty()) {
			pass = false;
		}
	}

	//check that the data is correct
	for (string name : REVERSE_NAMES) {
		// stack should not be empty
		if (stack_test.IsEmpty()) {
			pass = false;
		}
		stack_test.Pop();
	}

	//check that the stack is empty
	if (!stack_test.IsEmpty()) {
		pass = false;
	}

	cout << "Complex Empty test ";

	return pass;
}

bool test_complex_full() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	//check that the stack does not start full
	if (stack_test.IsFull()) {
		pass = false;
	}

	// fill the stack
	for (string name : NAMES) {
		//stack should not fill up
		if (stack_test.IsFull()) {
			pass = false;
		}
		stack_test.Push(name);
	}

	// stack should be full here
	if (!stack_test.IsFull()) {
		pass = false;
	}

	//check that the data is correct
	for (string name : REVERSE_NAMES) {
		stack_test.Pop();
		// stack should not be full
		if (stack_test.IsFull()) {
			pass = false;
		}
	}

	cout << "Complex Full test ";

	return pass;
}

bool test_complex_size() 
{ 
	bool pass = true;

	Stack<string> stack_test = Stack<string>(NUM_NAMES);

	//check that the stack starts empty
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	// fill the stack
	int i = 0;
	for (string name : NAMES) {
		stack_test.Push(name);
		i++;
		//check that the stack has the correct size
		if (stack_test.getNumElements() != i) {
			pass = false;
		}
	}

	//check the full size of the stack
	if (stack_test.getNumElements() != NUM_NAMES) {
		pass = false;
	}

	i = NUM_NAMES;
	for (string name : REVERSE_NAMES) {
		// stack should not be empty
		stack_test.Pop();
		i--;
		//check that the stack has the correct size
		if (stack_test.getNumElements() != i) {
			pass = false;
		}
	}

	//check that the stack is empty
	if (stack_test.getNumElements() != 0) {
		pass = false;
	}

	cout << "Complex Size test ";

	return pass;
}

//return a stack of ints from 0 to size-1
Stack<int> ReturnIntStack(size_t size)
{
	Stack<int> stack(size);

	for (int i = 0; i < size; i++) {
		stack.Push(i);
	}

	return stack;
}

// return a stack of strings from NAMES
Stack<string> ReturnStrStack()
{
	Stack<string> stack(NUM_NAMES);

	for (string name : NAMES) {
		stack.Push(name);
	}

	return stack;
}