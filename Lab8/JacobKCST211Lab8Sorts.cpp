// #define _CRTDBG_MAP_ALLOC

// CST 211 Lab8
// By Jacob Knox
// due 3/15/2023

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include <chrono>
#include <string>
using std::to_string;

#include <functional>

// memory lead detection disabled becasue my compiler dosn't support this version
// i used a compiler flag in gcc
//  this can be uncommented if you are using visual studio
//  #include <crtdbg.h>
//  #include <conio.h>
#include "Array.h"
#include "BST.h"
#include "Exception.h"
#include "Hash.h"
#include "List.h"
#include "Queue.h"

// i picked a semi random word to search for from the file
const string TEST_WORD = "sheets";

// wrap sdt::hash in a function so it can be used as a template parameter
size_t hash_func(const string &s) {
  static std::hash<string> func{};  // use std::hash to hash the string
  return func(s);
}

typedef void (*testing_func)(vector<string> &);

void test_array(vector<string> &data);
void test_list(vector<string> &data);
void test_bst(vector<string> &data);
void test_hash(vector<string> &data);
void test_queue(vector<string> &data);

testing_func funcs[] = {test_array, test_list, test_bst, test_hash, test_queue};

int main(int argc, char *argv[]) {
  // memory leak checking disabled becasue gcc dosen't support these flags
  // i used a compiler flag in gcc
  // this can be uncommented if you are using visual studio
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  // extract the length of the array from the command line
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string filename = argv[1];

  // open file
  ifstream file;
  file.open(filename);
  // file is automatically closed when it goes out of scope
  if (!file.is_open()) {
    cout << "Error opening file: " << filename << endl;
    return 1;
  }

  // populate the vector with the data from the file
  vector<string> data;
  string word;
  while (file >> word) {
    data.push_back(word);
  }

  cout << "Testing with " << data.size() << " words" << endl << endl;

  // run each test
  for (int i = 0; i < 5; i++) {
    funcs[i](data);
  }

  return 0;
}

void test_array(vector<string> &data) {
  // create an array of the same size as the vector
  Array<string> array(data.size());

  cout << "Testing Array" << endl;
  // start the timer
  auto start = std::chrono::high_resolution_clock::now();
  // add the data to the array
  for (int i = 0; i < data.size(); i++) {
    array[i] = data[i];
  }
  // stop the timer
  auto end = std::chrono::high_resolution_clock::now();
  // calculate the time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Array add time: " << duration.count() << " microseconds" << endl;

  // start the timer
  start = std::chrono::high_resolution_clock::now();
  // search for the test word
  for (int i = 0; i < array.getLength(); i++) {
    if (array[i] == TEST_WORD) {
      break;
    }
  }
  // stop the timer
  end = std::chrono::high_resolution_clock::now();

  // calculate the time
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Array search time: " << duration.count() << " microseconds" << endl << endl;
}

void test_list(vector<string> &data) {}
void test_bst(vector<string> &data) {}
void test_hash(vector<string> &data) {}
void test_queue(vector<string> &data) {}
