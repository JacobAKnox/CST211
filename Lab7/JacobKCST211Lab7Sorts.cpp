// #define _CRTDBG_MAP_ALLOC

// CST 211 Lab7
// By Jacob Knox
// due 1/19/2023

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <vector>
using std::vector;

#include <chrono>
#include <random>

#include <string>
using std::to_string;

// memory lead detection disabled becasue my compiler dosn't support this version
// i used a compiler flag in gcc
//  this can be uncommented if you are using visual studio
//  #include <crtdbg.h>
//  #include <conio.h>
#include "Array.h"
#include "Exception.h"
#include "Sorts.h"

const int PRINT_PERCENT = 10;  // how often to print the current time

typedef void (*c_array_sort)(int*, int);    // Define a funtion pointer t sort a c-array
typedef void (*array_sort)(Array<int>&);    // Define a funtion pointer to sort an Array
typedef void (*vector_sort)(vector<int>&);  // Define a funtion pointer to sort a vector

typedef void (*test_func)(vector<int>&);  // Define a funtion pointer to a test function

// functions to setup the different data structures
Array<int> setup_array(vector<int> random_data);
int* setup_c_array(vector<int> random_data);
vector<int> setup_vector(vector<int> random_data);

// functions to test the different sorting algorithms
void time_c_array_sort(c_array_sort sort, int* array, int length);
void time_array_sort(array_sort sort, Array<int>& array);
void time_vector_sort(vector_sort sort, vector<int>& vector);

void generic_tester(vector<int> random_data, c_array_sort c_array_sort, array_sort array_sort, vector_sort vector_sort);

// testing functions
void test_bubble_sort(vector<int>& random_data);
void test_flagged_bubble_sort(vector<int>& random_data);
void test_selection_sort(vector<int>& random_data);
void test_insertion_sort(vector<int>& random_data);
void test_shell_sort(vector<int>& random_data);
void test_iterative_heap_sort(vector<int>& random_data);
void test_merge_sort(vector<int>& random_data);
void test_quick_sort(vector<int>& random_data);

ofstream file;  // file to write to

template <class... T>
void print(T... args) {
	// print to the console and to the file
	for (auto arg : {args...}) {
		cout << arg;
		file << arg;
	}
}

test_func test_functions[] = {test_bubble_sort, test_flagged_bubble_sort, test_selection_sort, test_insertion_sort,
                              test_shell_sort, test_iterative_heap_sort, test_merge_sort, test_quick_sort};

int main(int argc, char* argv[]) {
  // memory leak checking disabled becasue gcc dosen't support these flags
  // i used a compiler flag in gcc
  // this can be uncommented if you are using visual studio
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  // extract the length of the array from the command line
  int length = 0;
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <length>" << endl;
    return 1;
  }

  // convert the length to an integer
  try {
    length = std::stoi(argv[1]);
  } catch (std::invalid_argument) {
    // if the length is not a valid integer
    cout << "Invalid argument: " << argv[1] << endl;
    return 1;
  } catch (std::out_of_range) {
    // if the length is out of range
    cout << "Out of range: " << argv[1] << endl;
    return 1;
  }

  // Create a random number generator
  std::mt19937 gen(1);                                      // use a fixed seed for repeatability
                                                            // use a rang 10x bigger than the length of the array to avoid too many duplicates
  std::uniform_int_distribution<> distrib(1, length * 10);  // define the range

  // Create a vector for the random data
  vector<int> random_data;

  // Fill the vector with random data
  for (int i = 0; i < length; i++)
    random_data.push_back(distrib(gen));

  file.open("output.txt");

  // show random data at 10% intervals
  print("Random data: ");
  for (int i = 0; i < random_data.size(); i += random_data.size() / PRINT_PERCENT) {
    print(random_data[i]);
		print(" ");
  }
	print("\n", "\n");

  // run the tests
  for (test_func test : test_functions) {
    test(random_data);
  }

  file.close();

  return 0;
}

void generic_tester(vector<int> random_data, c_array_sort c_array_sort, array_sort array_sort, vector_sort vector_sort) {
  // Create a copy of the random data
  vector<int> data{random_data};

  // Setup the c-array
  int* c_array = setup_c_array(data);

  // Setup the Array
  Array<int> array = setup_array(data);

  // Setup the vector
  vector<int> vector = setup_vector(data);

  // Sort the c-array
  print("Sorting c-array", "\n");
  time_c_array_sort(bubble_sort_c_array, c_array, data.size());

  // Sort the Array
  print("Sorting Array", "\n");
  time_array_sort(bubble_sort_array, array);

  // Sort the vector
	print("Sorting vector", "\n");
  time_vector_sort(bubble_sort_vector, vector);

  // Free the c-array
  delete[] c_array;
  cout << endl;
}

void test_bubble_sort(vector<int>& random_data) {
  print("Testing bubble sort", "\n");
  generic_tester(random_data, bubble_sort_c_array, bubble_sort_array, bubble_sort_vector);
}

void test_flagged_bubble_sort(vector<int>& random_data) {
  print("Testing flagged bubble sort", "\n");
  generic_tester(random_data, flagged_bubble_sort_c_array, flagged_bubble_sort_array, flagged_bubble_sort_vector);
}

void test_selection_sort(vector<int>& random_data) {
  print("Testing selection sort", "\n");
  generic_tester(random_data, selection_sort_c_array, selection_sort_array, selection_sort_vector);
}

void test_insertion_sort(vector<int>& random_data) {
  print("Testing insertion sort", "\n");
  generic_tester(random_data, insertion_sort_c_array, insertion_sort_array, insertion_sort_vector);
}

void test_shell_sort(vector<int>& random_data) {
  print("Testing shell sort", "\n");
  generic_tester(random_data, shell_sort_c_array, shell_sort_array, shell_sort_vector);
}

void test_iterative_heap_sort(vector<int>& random_data) {
  print("Testing iterative heap sort", "\n");
  generic_tester(random_data, iterative_heap_sort_c_array, iterative_heap_sort_array, iterative_heap_sort_vector);
}

void test_merge_sort(vector<int>& random_data) {
  print("Testing merge sort", "\n");
  generic_tester(random_data, merge_sort_c_array, merge_sort_array, merge_sort_vector);
}

void test_quick_sort(vector<int>& random_data) {
  print("Testing quick sort", "\n");
  generic_tester(random_data, quick_sort_c_array, bubble_sort_array, bubble_sort_vector);
}

Array<int> setup_array(vector<int> random_data) {
  // Create an array of the correct size
  Array<int> array(random_data.size());

  // Copy the data into the array
  for (int i = 0; i < random_data.size(); i++) {
    array[i] = random_data[i];
  }

  return array;
}

int* setup_c_array(vector<int> random_data) {
  // Create an array of the correct size
  int* array = new int[random_data.size()];

  // Copy the data into the array
  for (int i = 0; i < random_data.size(); i++) {
    array[i] = random_data[i];
  }

  return array;
}

vector<int> setup_vector(vector<int> random_data) {
  // copy the data into a new vector
  vector<int> array{random_data};
  return array;
}

void time_c_array_sort(c_array_sort sort, int* array, int length) {
  // Create a timer
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

  // Sort the array
  sort(array, length);

  // Stop the timer
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

  // Calculate the elapsed time
  std::chrono::duration<double> elapsed = end - start;

  // Print the elapsed time
	print("Elapsed time: ");
	print(elapsed.count());
	print(" seconds\n");

  // Print elements at 10% intervals
	print("Elements at 10% intervals: ", "\n");
  int last = 0;
  for (int i = 0; i < length; i += length / PRINT_PERCENT) {
		print(to_string(array[i]));
		print(" ");
    // check if the array is sorted
    if (array[i] < last) {
			print("ERROR: array not sorted", "\n");
      // throw an exception to stop the program
      throw Exception("Array not sorted");
    }
    last = array[i];
  }
  print("\n");
}

void time_array_sort(array_sort sort, Array<int>& array) {
  // Create a timer
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

  // Sort the array
  sort(array);

  // Stop the timer
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

  // Calculate the elapsed time
  std::chrono::duration<double> elapsed = end - start;

  // Print the elapsed time
  print("Elapsed time: ");
  print(elapsed.count());
  print(" seconds\n");

  // Print elements at 10% intervals
	print("Elements at 10% intervals: ", "\n");
  int last = 0;
  for (int i = 0; i < array.getLength(); i += array.getLength() / PRINT_PERCENT) {
		print(to_string(array[i]));
		print(" ");
    // check if the array is sorted
    if (array[i] < last) {
			print("ERROR: array not sorted", "\n");
      // throw an exception to stop the program
      throw Exception("Array not sorted");
    }
    last = array[i];
  }
  print("\n");
}

void time_vector_sort(vector_sort sort, vector<int>& vector) {
  // Create a timer
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

  // Sort the array
  sort(vector);

  // Stop the timer
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

  // Calculate the elapsed time
  std::chrono::duration<double> elapsed = end - start;

  // Print the elapsed time
  print("Elapsed time: ");
  print(elapsed.count());
  print(" seconds\n");

  // print elements at 10% intervals
	print("Elements at 10% intervals: ", "\n");
  int last = 0;
  for (int i = 0; i < vector.size(); i += vector.size() / PRINT_PERCENT) {
		print(to_string(vector[i]));
		print(" ");
    // check if the array is sorted
    if (vector[i] < last) {
			print("ERROR: array not sorted", "\n");
      // throw an exception to stop the program
      throw Exception("Array not sorted");
    }
    last = vector[i];
  }
	print("\n");
}
