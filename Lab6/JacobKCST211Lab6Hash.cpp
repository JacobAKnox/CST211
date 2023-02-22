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

using std::hash;

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

bool test_param_ctor();

bool test_copy_ctor();

bool test_move_ctor();

bool test_op_equal();

bool test_move_op_equal();

// Test functions for moves
HashTable<int, int> ReturnIntHash();
HashTable<string, string> ReturnStrHash();

// hash from int to int
size_t intHash(const int& key);

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

  HashTable<string, int> hashTable{};
  
  if (hashTable.size() != 0) {
    cout << "Size is not 0" << endl;
    pass = false;
  }

  if (hashTable.max_size() != 10) {
    cout << "Max size is not 10" << endl;
    pass = false;
  }
  
  if (hashTable.hash_key("test") != hash<string>{}("test")) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Default ctor test ";

  return pass;
}

bool test_param_ctor() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  if (hashTable.size() != 0) {
    cout << "Size is not 0" << endl;
    pass = false;
  }

  if (hashTable.max_size() != 10) {
    cout << "Max size is not 10" << endl;
    pass = false;
  }

  if (hashTable.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Param ctor test ";

  return pass;
}

bool test_copy_ctor() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  for (int i = 0; i < 10; i++) {
    hashTable.Add(i, i);
  }
             
  HashTable<int, int> hashTable2{hashTable};

  if (hashTable2.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable2[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable2.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  // verify that the copy is independent of the original
  hashTable2.Add(10, 10);
  if (hashTable.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Copy ctor test ";

  return pass;
}

bool test_move_ctor() {
  bool pass = true;

  HashTable<int, int> hashTable{ReturnIntHash()};

  if (hashTable.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Move ctor test ";

  return pass;
}

bool test_op_equal() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  for (int i = 0; i < 10; i++) {
    hashTable.Add(i, i);
  }

  HashTable<int, int> hashTable2 = hashTable;

  if (hashTable2.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable2[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable2.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  // verify that the copy is independent of the original
  hashTable2.Add(10, 10);
  if (hashTable.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Copy op equals test ";

  return pass;
}

bool test_move_op_equal() {
  bool pass = true;

  HashTable<int, int> hashTable = ReturnIntHash();

  if (hashTable.size() != 10) {
    cout << "Size is not 10" << endl;
    pass = false;
  }

  for (int i = 0; i < 10; i++) {
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
  }

  if (hashTable.hash_key(1) != intHash(1)) {
    cout << "Hash function is not set" << endl;
    pass = false;
  }

  cout << "Move op equals test ";

  return pass;
}

size_t intHash(const int& key) {
  return key;
}

HashTable<int, int> ReturnIntHash() {
  HashTable<int, int> hash{intHash};

  for (int i = 0; i < 10; i++)
    hash.Add(i, i);

  return hash;
}

HashTable<string, string> ReturnStrHash() {
  HashTable<string, string> hash{};
  return hash;
}
