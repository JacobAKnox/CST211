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
#include "Exception.h"

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

bool test_bracket_op();

bool test_add();

bool test_remove();
bool test_remove_exception();

// Test functions for moves
HashTable<int, int> ReturnIntHash();
HashTable<string, string> ReturnStrHash();

// hash from int to int
size_t intHash(const int& key);

// Array of test functions
FunctionPointer test_functions[] = {test_default_ctor, test_copy_ctor, test_move_ctor, test_op_equal,
                                    test_move_op_equal, test_bracket_op, test_add, test_remove, test_remove_exception};

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

bool test_bracket_op() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  for (int i = 0; i < 7; i++) {
    // test adding a value
    hashTable[i] = i;
    // test getting a value
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
    if (hashTable.size() != i + 1) {
      cout << "Size is not " << i + 1 << endl;
      pass = false;
    }
  }

  if (hashTable.size() != 7) {
    cout << "Size is not 7" << endl;
    pass = false;
  }

  // max size being default indicates that the table has not been resized
  if (hashTable.max_size() != 10) {
    cout << "Max size is not 10" << endl;
    pass = false;
  }

  // resize the table above 75% full
  hashTable[8] = 8;
  if (hashTable.size() != 8) {
    cout << "Size is not 8" << endl;
    pass = false;
  }
  // double size indicates that the table has been resized and rehashed
  if (hashTable.max_size() != 20) {
    cout << "Max size is not 20" << endl;
    pass = false;
  }
  if (hashTable[8] != 8) {
    cout << "Value is not 8" << endl;
    pass = false;
  }

  cout << "Bracket op test ";

  return pass;
}

bool test_add() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  for (int i = 0; i < 7; i++) {
    // test adding a value
    hashTable.Add(i, i);
    // make sure the value is there
    if (hashTable[i] != i) {
      cout << "Value is not " << i << endl;
      pass = false;
    }
    // make sure the size is correct
    if (hashTable.size() != i + 1) {
      cout << "Size is not " << i + 1 << endl;
      pass = false;
    }
  }

  if (hashTable.size() != 7) {
    cout << "Size is not 7" << endl;
    pass = false;
  }
  // max size being default indicates that the table has not been resized
  if (hashTable.max_size() != 10) {
    cout << "Max size is not 10" << endl;
    pass = false;
  }

  // resize the table above 75% full
  hashTable.Add(8, 8);
  if (hashTable.size() != 8) {
    cout << "Size is not 8" << endl;
    pass = false;
  }
  // double size indicates that the table has been resized and rehashed
  if (hashTable.max_size() != 20) {
    cout << "Max size is not 20" << endl;
    pass = false;
  }
  if (hashTable[8] != 8) {
    cout << "Value is not 8" << endl;
    pass = false;
  }

  cout << "Add test ";

  return pass;
}

bool test_remove() {
  bool pass = true;

  HashTable<int, int> hashTable{ReturnIntHash()};

  // test removing a value that does not exist
  try {
    hashTable.Remove(11);
    cout << "Remove did not throw an exception" << endl;
    pass = false;
  } catch (const Exception& e) {
    // do nothing
  }

  for (int i = 0; i < 10; i++) {
    // test removing a value
    hashTable.Remove(i);
    // make sure the value is gone
    if (hashTable.contains(i)) {
      cout << "Value is still there" << endl;
      pass = false;
    }
    // make sure the size is correct
    if (hashTable.size() != 9 - i) {
      cout << "Size is not " << 9 - i << endl;
      pass = false;
    }
  }

  if (hashTable.size() != 0) {
    cout << "Size is not 0" << endl;
    pass = false;
  }

  cout << "Remove test ";

  return pass;
}

bool test_remove_exception() {
  bool pass = true;

  HashTable<int, int> hashTable{intHash};

  try {
    // test removing a value that does not exist
    hashTable.Remove(0);
    cout << "Remove exception test ";
    pass = false;
  } catch (const Exception& e) {
    // test that the correct exception is thrown
    cout << "Remove exception test ";
  }

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
