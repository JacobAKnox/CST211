#ifndef SORTS_H
#define SORTS_H

#include <vector>

#include "Array.h"

// bubble sort
void bubble_sort_array(Array<int>& array);
void bubble_sort_c_array(int* array, int length);
void bubble_sort_vector(std::vector<int>& vector);

// flagged bubble sort
void flagged_bubble_sort_array(Array<int>& array);
void flagged_bubble_sort_c_array(int* array, int length);
void flagged_bubble_sort_vector(std::vector<int>& vector);

// selection sort
void selection_sort_array(Array<int>& array);
void selection_sort_c_array(int* array, int length);
void selection_sort_vector(std::vector<int>& vector);

// insertion sort
void insertion_sort_array(Array<int>& array);
void insertion_sort_c_array(int* array, int length);
void insertion_sort_vector(std::vector<int>& vector);

// bubble sorts
void bubble_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  // loop through the array
  for (int i = 0; i < length; i++) {
    // check if each pair of elements is in order
    for (int j = 0; j < length - 1; j++) {
      if (array[j] > array[j + 1]) {
        // swap the elements
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

// flagged bubble sorts
void flagged_bubble_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  bool swapped = true;
  // keep looping until no swaps are made
  while (swapped) {
    swapped = false;
    // check if each pair of elements is in order
    for (int i = 0; i < length - 1; i++) {
      if (array[i] > array[i + 1]) {
        // swap the elements
        temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        // we swapped, so we need to loop again
        swapped = true;
      }
    }
  }
}

void flagged_bubble_sort_c_array(int* array, int length) {
  int temp;
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (int i = 0; i < length - 1; i++) {
      if (array[i] > array[i + 1]) {
        temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        swapped = true;
      }
    }
  }
}

void flagged_bubble_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (int i = 0; i < length - 1; i++) {
      if (vector[i] > vector[i + 1]) {
        temp = vector[i];
        vector[i] = vector[i + 1];
        vector[i + 1] = temp;
        swapped = true;
      }
    }
  }
}

// selection sorts
void selection_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  // loop through the array
  for (int i = 0; i < length; i++) {
    // find the smallest element in the unsorted part of the array
    int smallest = i;
    for (int j = i + 1; j < length; j++) {
      if (array[j] < array[smallest]) {
        smallest = j;
      }
    }
    // swap the smallest element with the first element in the unsorted part
    temp = array[i];
    array[i] = array[smallest];
    array[smallest] = temp;
  }
}

void selection_sort_c_array(int* array, int length) {
  int temp;
  for (int i = 0; i < length; i++) {
    int smallest = i;
    for (int j = i + 1; j < length; j++) {
      if (array[j] < array[smallest]) {
        smallest = j;
      }
    }
    temp = array[i];
    array[i] = array[smallest];
    array[smallest] = temp;
  }
}

void selection_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  for (int i = 0; i < length; i++) {
    int smallest = i;
    for (int j = i + 1; j < length; j++) {
      if (vector[j] < vector[smallest]) {
        smallest = j;
      }
    }
    temp = vector[i];
    vector[i] = vector[smallest];
    vector[smallest] = temp;
  }
}

// insertion sorts
void insertion_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  // loop through the array
  for (int i = 1; i < length; i++) {
    // insert the element at index i into the sorted part of the array
    for (int j = i; j > 0; j--) {
      if (array[j] < array[j - 1]) {
        temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
      } else {
        break;
      }
    }
  }
}

void insertion_sort_c_array(int* array, int length) {
  int temp;
  for (int i = 1; i < length; i++) {
    for (int j = i; j > 0; j--) {
      if (array[j] < array[j - 1]) {
        temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
      } else {
        break;
      }
    }
  }
}

void insertion_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  for (int i = 1; i < length; i++) {
    for (int j = i; j > 0; j--) {
      if (vector[j] < vector[j - 1]) {
        temp = vector[j];
        vector[j] = vector[j - 1];
        vector[j - 1] = temp;
      } else {
        break;
      }
    }
  }
}

#endif  // SORTS_H
