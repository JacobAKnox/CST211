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

// shell sort
void shell_sort_array(Array<int>& array);
void shell_sort_c_array(int* array, int length);
void shell_sort_vector(std::vector<int>& vector);

// iterative heap sort
void iterative_heap_sort_array(Array<int>& array);
void iterative_heap_sort_c_array(int* array, int length);
void iterative_heap_sort_vector(std::vector<int>& vector);

// heap helper functions
void heapify_array(Array<int>& array, int length, int i);
void heapify_c_array(int* array, int length, int i);
void heapify_vector(std::vector<int>& vector, int length, int i);


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

// shell sorts
void shell_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  // loop through the array with a gap of 2^k - 1
  for (int gap = 1; gap < length; gap = 3 * gap + 1) {
    // loop through the array with the current gap
    for (int i = gap; i < length; i++) {
      // insert the element at index i into the sorted part of the array
      for (int j = i; j >= gap; j -= gap) {
        if (array[j] < array[j - gap]) {
          temp = array[j];
          array[j] = array[j - gap];
          array[j - gap] = temp;
        }
      }
    }
  }
}

void shell_sort_c_array(int* array, int length) {
  int temp;
  for (int gap = 1; gap < length; gap = 3 * gap + 1) {
    for (int i = gap; i < length; i++) {
      for (int j = i; j >= gap; j -= gap) {
        if (array[j] < array[j - gap]) {
          temp = array[j];
          array[j] = array[j - gap];
          array[j - gap] = temp;
        }
      }
    }
  }
}

void shell_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  for (int gap = 1; gap < length; gap = 3 * gap + 1) {
    for (int i = gap; i < length; i++) {
      for (int j = i; j >= gap; j -= gap) {
        if (vector[j] < vector[j - gap]) {
          temp = vector[j];
          vector[j] = vector[j - gap];
          vector[j - gap] = temp;
        }
      }
    }
  }
}

// iterative heap sorts
void iterative_heap_sort_array(Array<int>& array) {
  int temp;
  int length = array.getLength();
  // sort the array
  for (int i = length - 1; i >= 0; i--) {
    // make the array have the max heap property
    heapify_array(array, length, i);
    // swap the root with the last element
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
  }
}

void iterative_heap_sort_c_array(int* array, int length) {
  int temp;
  // sort the array
  for (int i = length - 1; i >= 0; i--) {
    // make the array have the max heap property
    heapify_c_array(array, length, i);
    // swap the root with the last element
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
  }
}

void iterative_heap_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  // sort the array
  for (int i = length - 1; i >= 0; i--) {
    // make the array have the max heap property
    heapify_vector(vector, length, i);
    // swap the root with the last element
    temp = vector[0];
    vector[0] = vector[i];
    vector[i] = temp;
  }
}

// heap helper functions
void heapify_array(Array<int>& array, int length, int i) {
  int temp;
  int largest = i;
  int left = 2 * i + 1; // left child
  int right = 2 * i + 2; // right child
  // if the left child is larger than the root
  if (left < length && array[left] > array[largest]) {
    // the left child is the largest
    largest = left;
  }
  // if the right child is larger than the root
  if (right < length && array[right] > array[largest]) {
    // the right child is the largest
    largest = right;
  }
  // swap the largest element with the root
  if (largest != i) {
    temp = array[i];
    array[i] = array[largest];
    array[largest] = temp;
    // heapify the sub-tree
    heapify_array(array, length, largest);
  }
}

void heapify_c_array(int* array, int length, int i) {
  int temp;
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2; 
  if (left < length && array[left] > array[largest]) {
    largest = left;
  }
  if (right < length && array[right] > array[largest]) {
    largest = right;
  }
  if (largest != i) {
    temp = array[i];
    array[i] = array[largest];
    array[largest] = temp;
    heapify_c_array(array, length, largest);
  }
}

void heapify_vector(std::vector<int>& vector, int length, int i) {
  int temp;
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < length && vector[left] > vector[largest]) {
    largest = left;
  }
  if (right < length && vector[right] > vector[largest]) {
    largest = right;
  }
  if (largest != i) {
    temp = vector[i];
    vector[i] = vector[largest];
    vector[largest] = temp;
    heapify_vector(vector, length, largest);
  }
}

#endif  // SORTS_H
