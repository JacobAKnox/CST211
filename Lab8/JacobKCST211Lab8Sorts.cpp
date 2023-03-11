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
#include "Hash.h"
#include "List.h"
#include "LNode.h"
#include "Queue.h"

#include "Exception.h"

// i picked a semi random word to search for from the file
const string TEST_WORD = "WARRANTIES";

// wrap sdt::hash in a function so it can be used as a template parameter
size_t hash_func(const string &s) {
  static std::hash<string> func{};  // use std::hash to hash the string
  return func(s);
}

typedef void (*testing_func)(const vector<string> &);

void test_array(const vector<string> &data);
void test_list(const vector<string> &data);
void test_bst(const vector<string> &data);
void test_hash(const vector<string> &data);
void test_queue(const vector<string> &data);

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

void test_array(const vector<string> &data) {
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

void test_list(const vector<string> &data) {
  // create a list
  List<string> list;

  cout << "Testing List" << endl;
  // start the timer
  auto start = std::chrono::high_resolution_clock::now();
  // add the data to the list
  for (int i = 0; i < data.size(); i++) {
    list.Append(data[i]);
  }
  // stop the timer
  auto end = std::chrono::high_resolution_clock::now();
  // calculate the time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "List add time: " << duration.count() << " microseconds" << endl;

  // start the timer
  start = std::chrono::high_resolution_clock::now();
  // search for the test word
  LNode<string> *node = list.getHead();
  while (node != nullptr) {
    if (node->Value() == TEST_WORD) {
      break;
    }
    node = node->Next();
  }
  // stop the timer
  end = std::chrono::high_resolution_clock::now();

  // calculate the time
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "List search time: " << duration.count() << " microseconds" << endl << endl;
}

void test_bst(const vector<string> &data) {
  // create a bst
  BST<string> bst;

  cout << "Testing BST" << endl;
  // start the timer
  auto start = std::chrono::high_resolution_clock::now();
  // add the data to the bst
  for (int i = 0; i < data.size(); i++) {
    try {
      bst.Insert(data[i]);
    } catch (Exception &e) {
      // ignore duplicate words
    }
  }
  // stop the timer
  auto end = std::chrono::high_resolution_clock::now();
  // calculate the time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "BST add time: " << duration.count() << " microseconds" << endl;

  // start the timer
  start = std::chrono::high_resolution_clock::now();
  // search for the test word
  bst.Contains(TEST_WORD);
  // stop the timer
  end = std::chrono::high_resolution_clock::now();

  // calculate the time
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "BST search time: " << duration.count() << " microseconds" << endl << endl;
}

void test_hash(const vector<string> &data) {
  // create a hash table
  HashTable<string, int> hash{hash_func};

  cout << "Testing Hash" << endl;
  // start the timer
  auto start = std::chrono::high_resolution_clock::now();
  // add the data to the hash table
  for (int i = 0; i < data.size(); i++) {
    if (hash.contains(data[i])) {
      hash[data[i]]++;
      continue;
    }
    hash.Add(data[i], 1);
  }
  // stop the timer
  auto end = std::chrono::high_resolution_clock::now();
  // calculate the time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Hash add time: " << duration.count() << " microseconds" << endl;

  // start the timer
  start = std::chrono::high_resolution_clock::now();
  // search for the test word
  int count = hash[TEST_WORD];
  // stop the timer
  end = std::chrono::high_resolution_clock::now();

  // calculate the time
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Hash search time: " << duration.count() << " microseconds" << endl << endl;
}

void test_queue(const vector<string> &data) {
  // create a queue
  Queue<string> queue{(int) data.size()};

  cout << "Testing Queue" << endl;
  // start the timer
  auto start = std::chrono::high_resolution_clock::now();
  // add the data to the queue
  for (int i = 0; i < data.size(); i++) {
    queue.Enqueue(data[i]);
  }
  // stop the timer
  auto end = std::chrono::high_resolution_clock::now();
  // calculate the time
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Queue add time: " << duration.count() << " microseconds" << endl;

  // start the timer
  start = std::chrono::high_resolution_clock::now();
  // search for the test word
  while (!queue.isEmpty()) {
    if (queue.Dequeue() == TEST_WORD) {
      break;
    }
  }
  // stop the timer
  end = std::chrono::high_resolution_clock::now();

  // calculate the time
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Queue search time: " << duration.count() << " microseconds" << endl << endl;
}
