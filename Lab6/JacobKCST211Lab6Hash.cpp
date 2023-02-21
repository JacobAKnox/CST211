// Jacob Knox CST211 Lab6 Due: 3/2/2023

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
#include "Hash.h"

// Strings to test
const string NAMES[] = {"Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
                        "Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
                        "Oliver", "Tobey"};

// Test function declaration
bool test_default_ctor();

bool test_copy_ctor();

bool test_move_ctor();

bool test_op_equal();

bool test_move_op_equal();

// // Test functions for moves
HashTable<string, int> ReturnIntBST();
HashTable<string, string> ReturnStrBST();

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

  cout << "Default ctor test ";

  return pass;
}

bool test_copy_ctor() {
  bool pass = true;

  cout << "Copy ctor test ";

  return pass;
}

bool test_move_ctor() {
  bool pass = true;

  cout << "Move ctor test ";

  return pass;
}

bool test_op_equal() {
  bool pass = true;

  cout << "Copy op equals test ";

  return pass;
}

bool test_move_op_equal() {
  bool pass = true;

  cout << "Move op equals test ";

  return pass;
}

HashTable<string, int> ReturnIntHash() {
  HashTable<string, int> hash{};
  return hash;
}

HashTable<string, string> ReturnStrHash() {
  HashTable<string, string> hash{};
  return hash;
}
