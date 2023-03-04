#ifndef SORTS_H
#define SORTS_H

#include <vector>

#include "Array.h"

// bubble sort
void bubble_sort_array(Array<int>& array);
void bubble_sort_c_array(int* array, int length);
void bubble_sort_vector(std::vector<int>& vector);

void bubble_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length - 1; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void bubble_sort_c_array(int* array, int length) {
  int temp;
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length - 1; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void bubble_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length - 1; j++) {
      if (vector[j] > vector[j + 1]) {
        temp = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = temp;
      }
    }
  }
}

#endif  // SORTS_H
