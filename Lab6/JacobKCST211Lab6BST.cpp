// Jacob Knox CST211 Lab6 Due: 2/16/2023

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

typedef bool (*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// crt memory leak detection does not work with gcc. I'm using gcc's memory leak detection
// #include <crtdbg.h>
// #include <conio.h>
#include "BST.h"

// Strings to test
const string NAMES[] = {"Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
                        "Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
                        "Oliver", "Tobey"};

const int NUM_NAMES = 15;

// random sequence of numbers to test
const int NUMS[] = {63, 45, 15, 79, 64, 30, 19, 89, 3, 71};
const int NUM_SIZE = 10;

const int INORDER[] = {3, 15, 19, 30, 45, 63, 64, 71, 79, 89};

// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_move_ctor();
// bool test_op_equal();
// bool test_move_op_equal();
// bool test_is_empty();
// bool test_first_with_value();
// bool test_first_empty_list();
// bool test_last_with_value();
// bool test_last_empty_list();
// bool test_prepend();
// bool test_append();
// bool test_purge();
// bool test_extract_empty();
// bool test_extract_match();
// bool test_extract_no_match();
// bool test_inserta_empty();
// bool test_inserta_match();
// bool test_inserta_no_match();
// bool test_insertb_empty();
// bool test_insertb_match();
// bool test_insertb_no_match();

// // Test functions for moves
BST<int> ReturnIntBST();
// List<string> ReturnStrList();

int call_counter(bool reset = false);
void in_order_checker(int value);

// Array of test functions
FunctionPointer test_functions[] = {
    test_default_ctor,
    test_copy_ctor, test_move_ctor /*, test_op_equal, test_move_op_equal, test_is_empty,
     test_first_with_value, test_first_empty_list, test_last_with_value, test_last_empty_list,
     test_prepend, test_append, test_purge, test_extract_empty, test_extract_match,
     test_extract_no_match, test_inserta_empty, test_inserta_match, test_inserta_no_match,
     test_insertb_empty, test_insertb_match, test_insertb_no_match*/
};

int main() {
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  int failed_tests = 0;

  // Run the test functions
  for (FunctionPointer func : test_functions) {
    if (func()) {
      cout << "passed" << endl;
    } else {
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

bool test_default_ctor() {
  bool pass = true;

  BST<int> tree_test{};

  // make sure there are no nodes in the tree
  if (tree_test.GetRoot() != nullptr)
    pass = false;

  // make sure the height is 0
  if (tree_test.Height() != 0)
    pass = false;

  cout << "Default ctor test ";

  return pass;
}

bool test_copy_ctor() {
  bool pass = true;

  BST<int> tree_test{};
  for (int i = 0; i < NUM_SIZE; ++i)
    tree_test.Insert(NUMS[i]);

  BST<int> tree_test2{tree_test};  // Copy ctor

  // check height
  if (tree_test.Height() != tree_test2.Height())
    pass = false;

  // modify the original tree
  tree_test.Insert(1);

  // Check data integrity
  try {
    call_counter(true);
    tree_test2.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  // remove the added node
  tree_test.Delete(1);
  // modify the copy
  tree_test2.Insert(2);

  // make sure the original tree is not modified
  try {
    call_counter(true);
    tree_test.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Copy ctor test ";

  return pass;
}

bool test_move_ctor() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()}; // Move ctor

  //check height
  if (tree_test.Height() != 4)
    pass = false;

  // Check data integrity
  try {
    call_counter(true);
    tree_test.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Move ctor test ";

  return pass;
}

// bool test_op_equal()
// {
// 	bool pass = true;

// 	List<int> test_list;
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 		test_list.Append(i);

// 	List<int> list_test;
// 	list_test = test_list; //Op =

// 	// Check data integrity
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 	{
// 		if (list_test.First() != test_list.First())
// 			pass = false;
// 		list_test.Extract(i); //Remove first value
// 		test_list.Extract(i);
// 	}

// 	cout << "Op equals test ";

// 	return pass;
// }

// bool test_move_op_equal()
// {
// 	bool pass = true;

// 	List<int> test_list;
// 	test_list = ReturnIntList(); //Op =

// 	// Check data integrity
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 	{
// 		if (i != test_list.First())
// 			pass = false;
// 		test_list.Extract(i); //Remove first value
// 	}

// 	cout << "Move op equals test ";

// 	return pass;
// }

// bool test_is_empty()
// {
// 	bool pass = true;

// 	List<int> full_list;
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 		full_list.Append(i);

// 	List<int> empty_list;

// 	if (full_list.isEmpty())
// 		pass = false;

// 	if (!empty_list.isEmpty())
// 		pass = false;

// 	cout << "isEmpty test ";

// 	return pass;
// }

// bool test_first_with_value()
// {
// 	bool pass = true;

// 	List<int> full_list;
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 		full_list.Append(i);

// 	if (full_list.First() != 0)
// 		pass = false;

// 	cout << "First with value test ";

// 	return pass;
// }

// bool test_first_empty_list()
// {
// 	bool pass = false;

// 	List<int> empty_list;

// 	try
// 	{
// 		empty_list.First();
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "First with empty list test ";

// 	return pass;
// }

// bool test_last_with_value()
// {
// 	bool pass = false;

// 	List<int> full_list;
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 		full_list.Append(i);

// 	if (full_list.Last() == NUM_SIZE - 1)
// 		pass = true;

// 	cout << "Last with value test ";

// 	return pass;
// }

// bool test_last_empty_list()
// {
// 	bool pass = false;

// 	List<int> empty_list;

// 	try
// 	{
// 		empty_list.Last();
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Last with empty list test ";

// 	return pass;
// }

// bool test_prepend()
// {
// 	bool pass = true;
// 	int init_value = 5;
// 	int next_value = 3;

// 	List<int> test_list;

// 	// Prepend empty list
// 	test_list.Prepend(init_value);
// 	if (test_list.First() != init_value || test_list.Last() != init_value)
// 		pass = false;

// 	// Prepend list with existing values
// 	test_list.Prepend(next_value);
// 	if (test_list.First() != next_value || test_list.Last() != init_value)
// 		pass = false;

// 	cout << "Prepend test ";

// 	return pass;
// }

// bool test_append()
// {
// 	bool pass = true;
// 	int init_value = 5;
// 	int next_value = 3;

// 	List<int> test_list;

// 	// Append empty list
// 	test_list.Append(init_value);
// 	if (test_list.First() != init_value || test_list.Last() != init_value)
// 		pass = false;

// 	// Append list with existing values
// 	test_list.Append(next_value);
// 	if (test_list.First() != init_value || test_list.Last() != next_value)
// 		pass = false;

// 	cout << "Append test ";

// 	return pass;
// }

// bool test_purge()
// {
// 	bool pass = true;

// 	List<int> full_list;
// 	for (int i = 0; i < NUM_SIZE; ++i)
// 		full_list.Append(i);

// 	full_list.Purge();
// 	if (full_list.getHead() || full_list.getTail())
// 		pass = false;

// 	cout << "Purge test ";

// 	return pass;
// }

// bool test_extract_empty()
// {
// 	bool pass = false;
// 	int test_value = 5;

// 	List<int> empty_list;

// 	try
// 	{
// 		empty_list.Extract(test_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Extract empty list test ";

// 	return pass;
// }

// bool test_extract_match()
// {
// 	bool pass = true;

// 	List<int> test_list;
// 	for (int i = 1; i <= NUM_EXTRACT; ++i)
// 		test_list.Append(i);

// 	// List should have 1 2 3 4
// 	test_list.Extract(3); // Test extract from middle
// 	if (test_list.First() != 1 || test_list.Last() != 4)
// 		pass = false;

// 	// List should have 1 2 4
// 	test_list.Extract(1); // Test extract from front of list
// 	if (test_list.First() != 2 || test_list.Last() != 4)
// 		pass = false;

// 	// List should have 2 4
// 	test_list.Extract(4); // Test extract from back of list
// 	if (test_list.First() != 2 || test_list.Last() != 2)
// 		pass = false;

// 	// List should have 2
// 	test_list.Extract(2); // Test extract from list with 1 node
// 	if (test_list.getHead() || test_list.getTail())
// 		pass = false;

// 	cout << "Extract match test ";

// 	return pass;
// }

// bool test_extract_no_match()
// {
// 	bool pass = false;
// 	int test_value = 5;
// 	int fake_value = 3;

// 	List<int> empty_list;
// 	empty_list.Append(test_value);

// 	try
// 	{
// 		empty_list.Extract(fake_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Extract no match test ";

// 	return pass;
// }

// bool test_inserta_empty()
// {
// 	bool pass = false;
// 	int test_value = 5;
// 	int search_value = 7;

// 	List<int> empty_list;

// 	try
// 	{
// 		empty_list.InsertAfter(test_value, search_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Insert after empty list test ";

// 	return pass;
// }

// bool test_inserta_match()
// {
// 	bool pass = true;
// 	int init_value = 5;
// 	int first_new_value = 7;
// 	int second_new_value = 6;

// 	List<int> test_list;
// 	test_list.Append(init_value);

// 	// Test insert to end of list
// 	test_list.InsertAfter(first_new_value, init_value);

// 	// Test insert to middle of list
// 	test_list.InsertAfter(second_new_value, init_value);

// 	// List should contain 5 6 7
// 	if (test_list.Last() != first_new_value)
// 		pass = false;

// 	test_list.Extract(first_new_value);
// 	// List should contain 5 6
// 	if (test_list.Last() != second_new_value)
// 		pass = false;

// 	cout << "Insert after match test ";

// 	return pass;
// }

// bool test_inserta_no_match()
// {
// 	bool pass = false;
// 	int test_value = 5;
// 	int fake_value = 7;

// 	List<int> empty_list;
// 	empty_list.Append(test_value);

// 	try
// 	{
// 		empty_list.InsertAfter(test_value, fake_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Insert after no match test ";

// 	return pass;
// }

// bool test_insertb_empty()
// {
// 	bool pass = false;
// 	int test_value = 5;
// 	int search_value = 7;

// 	List<int> empty_list;

// 	try
// 	{
// 		empty_list.InsertBefore(test_value, search_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Insert before empty list test ";

// 	return pass;
// }

// bool test_insertb_match()
// {
// 	bool pass = true;
// 	int init_value = 7;
// 	int first_new_value = 5;
// 	int second_new_value = 6;

// 	List<int> test_list;
// 	test_list.Prepend(init_value);

// 	// Test insert to start of list
// 	test_list.InsertBefore(first_new_value, init_value);

// 	// Test insert to middle of list
// 	test_list.InsertBefore(second_new_value, init_value);

// 	// List should contain 5 6 7
// 	if (test_list.First() != first_new_value)
// 		pass = false;

// 	test_list.Extract(first_new_value);
// 	// List should contain 6 7
// 	if (test_list.First() != second_new_value)
// 		pass = false;

// 	cout << "Insert before match test ";

// 	return pass;
// }

// bool test_insertb_no_match()
// {
// 	bool pass = false;
// 	int test_value = 5;
// 	int fake_value = 7;

// 	List<int> empty_list;
// 	empty_list.Append(test_value);

// 	try
// 	{
// 		empty_list.InsertBefore(test_value, fake_value);
// 	}
// 	catch (Exception& exception)
// 	{
// 		exception.getMessage();
// 		pass = true;
// 	}

// 	cout << "Insert before no match test ";

// 	return pass;
// }

// keep track of how many times this function is called
// if reset is true, reset the counter to 0 for the next call i.e. return -1 when reset is true
int call_counter(bool reset) {
  static int counter = -1;

  if (reset)
    counter = -2;

  counter++;
  return counter;
}

// check the order of the nodes in the tree
void in_order_checker(int num) {
  if (num != INORDER[call_counter()])
    throw Exception("InOrderCheker failed");
}

BST<int> ReturnIntBST() {
  BST<int> tree;
  for (int num : NUMS) {
    tree.Insert(num);
  }
  return tree;
}
