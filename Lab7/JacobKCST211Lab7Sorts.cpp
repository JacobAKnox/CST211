// #define _CRTDBG_MAP_ALLOC

// CST 211 Lab7
// By Jacob Knox
// due 1/19/2023

typedef void (*FunctionPointer)();  // Define a funtion pointer type

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

// memory lead detection disabled becasue my compiler dosn't support this version
// i used a compiler flag in gcc
//  this can be uncommented if you are using visual studio
//  #include <crtdbg.h>
//  #include <conio.h>
#include "Array.h"
#include "Exception.h"

// Test function declaration

// Array of test functions
FunctionPointer test_functions[] = {};

int main(int argc, char *argv[]) {
  // memory leak checking disabled becasue gcc dosen't support these flags
  // i used a compiler flag in gcc
  // this can be uncommented if you are using visual studio
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  int failed_tests = 0;

  // Run the test functions
  for (FunctionPointer func : test_functions) {
  }

  return 0;
}
