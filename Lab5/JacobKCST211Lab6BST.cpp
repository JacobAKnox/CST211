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

const string DELETE_NAMES[] = {"Kate", "Tobey", "Ann", "Elaine", "Kian", "Oliver", "Stephanie",
                               "Wanda", "Alex", "Josh", "Oscar", "Terry", "Brit", "Seth", "Kyle"};

const string INORDER_NAMES[] = {"Alex", "Ann", "Brit", "Elaine", "Josh", "Kate", "Kian",
                                "Kyle", "Oliver", "Oscar", "Seth", "Stephanie", "Terry",
                                "Tobey", "Wanda"};

const int NAME_HEIGHTS[] = {1, 2, 2, 3, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5};
const int DELETE_NAME_HEIGHTS[] = {5, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 1, 0};
const int NAME_MAX_HEIGHT = 5;
const int NUM_NAMES = 15;

// random sequence of numbers to test
const int NUMS[] = {63, 45, 15, 79, 64, 30, 19, 89, 3, 71};
const int DELETE_ORDER[] = {19, 3, 30, 15, 45, 71, 64, 89, 79, 63};
const int HEIGHTS[] = {1, 2, 3, 3, 3, 4, 5, 5, 5, 5};
const int DELETE_HEIGHTS[] = {4, 4, 4, 4, 4, 3, 3, 2, 1, 0};
const int MAX_HEIGHT = 5;
const int NUM_SIZE = 10;

const int INORDER[] = {3, 15, 19, 30, 45, 63, 64, 71, 79, 89};
const int PREORDER[] = {63, 45, 15, 3, 30, 19, 79, 64, 71, 89};
const int POSTORDER[] = {3, 19, 30, 15, 45, 71, 64, 89, 79, 63};
const int BREADTH[] = {63, 45, 79, 15, 64, 89, 3, 30, 71, 19};

// Test function declaration
bool test_default_ctor();

bool test_copy_ctor();
bool test_complex_copy_ctor();

bool test_move_ctor();
bool test_complex_move_ctor();

bool test_op_equal();
bool test_complex_op_equal();

bool test_move_op_equal();
bool test_complex_move_op_equal();

bool test_insert();
bool test_insert_duplicate();
bool test_insert_complex();
bool test_insert_complex_duplicate();

bool test_delete();
bool test_delete_not_found();
bool test_delete_root();

bool test_purge();
bool test_empty_purge();

bool test_height();
bool test_empty_height();

bool test_in_order();
bool test_pre_order();
bool test_post_order();
bool test_breadth();

bool test_contains();

// // Test functions for moves
BST<int> ReturnIntBST();
BST<string> ReturnStrBST();

int call_counter(bool reset = false);
void in_order_checker(int value);
void pre_order_checker(int value);
void post_order_checker(int value);
void breadth_order_checker(int value);

void name_in_order_checker(string value);

// Array of test functions
FunctionPointer test_functions[] = {test_default_ctor, test_copy_ctor,
  test_move_ctor, test_op_equal, test_move_op_equal, test_insert,
  test_insert_duplicate, test_delete, test_delete_not_found,
  test_delete_root, test_purge, test_empty_purge, test_height, test_empty_height,
  test_in_order, test_pre_order, test_post_order, test_breadth, test_contains, 
  test_complex_copy_ctor, test_complex_move_ctor, test_complex_op_equal, 
  test_complex_move_op_equal, test_insert_complex, test_insert_complex_duplicate};

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
  for (int num : NUMS)
    tree_test.Insert(num);

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

bool test_complex_copy_ctor() {
  bool pass = true;

  BST<string> tree_test{}; 
  for (string name: NAMES)
    tree_test.Insert(name);

  BST<string> tree_test2{tree_test};  // Copy ctor

  // check height
  if (tree_test.Height() != tree_test2.Height())
    pass = false;
  
  // modify the original tree
  tree_test.Insert("A");

  // Check data integrity
  try {
    call_counter(true);
    tree_test2.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  // remove the added node
  tree_test.Delete("A");
  // modify the copy
  tree_test2.Insert("B");

  // make sure the original tree is not modified
  try {
    call_counter(true);
    tree_test.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Complex copy ctor test ";

  return pass;
}

bool test_move_ctor() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};  // Move ctor

  // check height
  if (tree_test.Height() != MAX_HEIGHT)
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

bool test_complex_move_ctor() {
  bool pass = true;

  BST<string> tree_test{ReturnStrBST()};  // Move ctor

  // check height
  if (tree_test.Height() != MAX_HEIGHT)
    pass = false;

  // Check data integrity
  try {
    call_counter(true);
    tree_test.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Complex move ctor test ";

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

bool test_complex_op_equal() {
  bool pass = true;

  BST<string> tree_test{};
  for (string name : NAMES)
    tree_test.Insert(name);

  BST<string> tree_test2 = tree_test;  // Copy op

  // check height
  if (tree_test.Height() != tree_test2.Height())
    pass = false;

  // modify the original tree
  tree_test.Insert("A");

  // Check data integrity
  try {
    call_counter(true);
    tree_test2.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  // remove the added node
  tree_test.Delete("A");
  // modify the copy
  tree_test2.Insert("B");

  // make sure the original tree is not modified
  try {
    call_counter(true);
    tree_test.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Complex copy op equals test ";

  return pass;
}

bool test_move_op_equal() {
  bool pass = true;

  BST<int> tree_test = ReturnIntBST();  // Move op

  // check height
  if (tree_test.Height() != MAX_HEIGHT)
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

bool test_complex_move_op_equal() {
  bool pass = true;

  BST<string> tree_test = ReturnStrBST();  // Move op

  // check height
  if (tree_test.Height() != MAX_HEIGHT)
    pass = false;

  // Check data integrity
  try {
    call_counter(true);
    tree_test.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Complex move op equals test ";

  return pass;
}

bool test_insert() {
  bool pass = true;

  BST<int> tree_test{};

  // insert the numbers in the array
  for (int i = 0; i < NUM_SIZE; ++i) {
    tree_test.Insert(NUMS[i]);
    if (tree_test.Height() != HEIGHTS[i]) {
      // make sure the height is correct for each insertion
      pass = false;
      break;
    }
  }

  // check data order
  try {
    call_counter(true);
    tree_test.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Insert test ";

  return pass;
}

bool test_insert_duplicate() {
  bool pass = true;

  BST<int> tree_test{};

  tree_test.Insert(1);

  // insert 1 again
  try {
    tree_test.Insert(1);
    pass = false;
  } catch (Exception &e) {
    // make sure an exception is thrown
  }

  cout << "Insert duplicate test ";

  return pass;
}

bool test_insert_complex() {
  bool pass = true;

  BST<string> tree_test{};

  // insert the names in the array
  for (int i = 0; i < NUM_NAMES; ++i) {
    tree_test.Insert(NAMES[i]);
    if (tree_test.Height() != NAME_HEIGHTS[i]) {
      // make sure the height is correct for each insertion
      pass = false;
      break;
    }
  }
  
  // check data order
  try {
    call_counter(true);
    tree_test.InOrder(name_in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Complex insert test ";

  return pass;
}

bool test_insert_complex_duplicate() {
  bool pass = true;

  BST<string> tree_test{};

  tree_test.Insert("A");

  // insert "A" again
  try {
    tree_test.Insert("A");
    pass = false;
  } catch (Exception &e) {
    // make sure an exception is thrown
  }

  cout << "Complex insert duplicate test ";

  return pass;
}

bool test_delete() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // delete the numbers in the array
  for (int i = 0; i < NUM_SIZE; ++i) {
    tree_test.Delete(DELETE_ORDER[i]);
    if (tree_test.Height() != DELETE_HEIGHTS[i]) {
      // make sure the height is correct for each deletion
      pass = false;
      break;
    }
    if (tree_test.Contains(DELETE_ORDER[i])) {
      // make sure the node is deleted
      pass = false;
      break;
    }
  }

  cout << "Delete test ";

  return pass;
}

bool test_delete_not_found() {
  bool pass = true;

  BST<int> tree_test{};

  // delete a non-existent node
  try {
    tree_test.Delete(1);
    pass = false;
  } catch (Exception &e) {
    // make sure an exception is thrown
  }

  cout << "Delete non-existent test ";

  return pass;  //
}

bool test_delete_root() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // delete the root
  // with the current insert order the root is always the first element inserted
  // the tree should be empty after this and no memory leaks
  tree_test.Delete(NUMS[0]);

  // make sure the root is deleted
  if (tree_test.Contains(NUMS[0]))
    pass = false;

  // make sure the height is correct
  if (tree_test.Height() != 0)
    pass = false;

  cout << "Delete root test ";

  return pass;
}

bool test_purge() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // purge the tree
  tree_test.Purge();

  // make sure the tree is empty
  for (int num : NUMS) {
    if (tree_test.Contains(num)) {
      pass = false;
      break;
    }
  }

  // make sure the height is correct
  if (tree_test.Height() != 0)
    pass = false;

  cout << "Purge test ";

  return pass;
}

bool test_empty_purge() {
  bool pass = true;

  BST<int> tree_test{};

  // purge the empty tree
  tree_test.Purge();

  // make sure the tree is empty
  for (int num : NUMS) {
    if (tree_test.Contains(num)) {
      pass = false;
      break;
    }
  }

  // make sure the height is correct
  if (tree_test.Height() != 0)
    pass = false;

  cout << "Empty purge test ";

  return pass;
}

bool test_height() {
  bool pass = true;

  BST<int> tree_test{};

  if (tree_test.Height() != 0)
    pass = false;

  try {
    // insert the numbers in the array
    for (int i = 0; i < NUM_SIZE; ++i) {
      tree_test.Insert(NUMS[i]);
      if (tree_test.Height() != HEIGHTS[i]) {
        // make sure the height is correct for each insertion
        pass = false;
        break;
      }
    }
  } catch (Exception &e) {
    pass = false;
  }

  // make sure the height is correct
  if (tree_test.Height() != MAX_HEIGHT)
    pass = false;

  for (int i = 0; i < NUM_SIZE; ++i) {
    tree_test.Delete(DELETE_ORDER[i]);
    if (tree_test.Height() != DELETE_HEIGHTS[i]) {
      // make sure the height is correct for each deletion
      pass = false;
      break;
    }
  }

  cout << "Height test ";

  return pass;
}

bool test_empty_height() {
  bool pass = true;

  BST<int> tree_test{};

  // make sure the height is correct
  if (tree_test.Height() != 0)
    pass = false;

  cout << "Empty height test ";

  return pass;
}

bool test_in_order() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // check data order
  try {
    call_counter(true);
    tree_test.InOrder(in_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "InOrder test ";

  return pass;
}

bool test_pre_order() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // check data order
  try {
    call_counter(true);
    tree_test.PreOrder(pre_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "PreOrder test ";

  return pass;
}

bool test_post_order() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // check data order
  try {
    call_counter(true);
    tree_test.PostOrder(post_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "PostOrder test ";

  return pass;
}

bool test_breadth() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // check data order
  try {
    call_counter(true);
    tree_test.BreadthFirst(breadth_order_checker);
  } catch (Exception &e) {
    pass = false;
  }

  cout << "Breadth test ";

  return pass;
}

bool test_contains() {
  bool pass = true;

  BST<int> tree_test{ReturnIntBST()};

  // check if the tree contains the numbers
  for (int num : NUMS) {
    if (!tree_test.Contains(num)) {
      pass = false;
      break;
    }
  }

  cout << "Contains test ";

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

void pre_order_checker(int num) {
  if (num != PREORDER[call_counter()])
    throw Exception("PreOrderCheker failed");
}

void post_order_checker(int num) {
  if (num != POSTORDER[call_counter()])
    throw Exception("PostOrderCheker failed");
}

void breadth_order_checker(int num) {
  if (num != BREADTH[call_counter()])
    throw Exception("LevelOrderCheker failed");
}

void name_in_order_checker(string name) {
  if (name != INORDER_NAMES[call_counter()])
    throw Exception("NameInOrderCheker failed");
}

// return a BST with the numbers in NUMS
BST<int> ReturnIntBST() {
  BST<int> tree{};
  for (int num : NUMS) {
    tree.Insert(num);
  }
  return tree;
}

BST<string> ReturnStrBST() {
  BST<string> tree{};
  for (string str : NAMES) {
    tree.Insert(str);
  }
  return tree;
}
