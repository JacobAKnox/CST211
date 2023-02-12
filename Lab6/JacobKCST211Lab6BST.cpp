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
bool test_op_equal();
bool test_move_op_equal();

// // Test functions for moves
BST<int> ReturnIntBST();
// List<string> ReturnStrList();

int call_counter(bool reset = false);
void in_order_checker(int value);

// Array of test functions
FunctionPointer test_functions[] = {test_default_ctor, test_copy_ctor,
 test_move_ctor, test_op_equal, test_move_op_equal};

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

  BST<int> tree_test{ReturnIntBST()};  // Move ctor

  // check height
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

bool test_op_equal() {
  bool pass = true;

  BST<int> tree_test{};
  for (int i = 0; i < NUM_SIZE; ++i)
    tree_test.Insert(NUMS[i]);

  BST<int> tree_test2 = tree_test;  // Copy op

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

  cout << "Copy op equals test ";

  return pass;
}

bool test_move_op_equal() {
  bool pass = true;

  BST<int> tree_test = ReturnIntBST();  // Move op

  // check height
  if (tree_test.Height() != 4)
    pass = false;

  // Check data integrity
  try {
    call_counter(true);
    tree_test.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Move op equals test ";

  return pass;
}

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
