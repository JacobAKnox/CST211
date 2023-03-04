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

// merge sort base calls
void merge_sort_array(Array<int>& array);
void merge_sort_c_array(int* array, int length);
void merge_sort_vector(std::vector<int>& vector);

// merge sort recursive calls
void merge_sort_array(Array<int>& array, int left, int right);
void merge_sort_c_array(int* array, int left, int right);
void merge_sort_vector(std::vector<int>& vector, int left, int right);

// merge helper functions
void merge_array(Array<int>& array, int left, int middle, int right);
void merge_c_array(int* array, int left, int middle, int right);
void merge_vector(std::vector<int>& vector, int left, int middle, int right);

// quick sort base calls
void quick_sort_array(Array<int>& array);
void quick_sort_c_array(int* array, int length);
void quick_sort_vector(std::vector<int>& vector);

// quick sort recursive calls
void quick_sort_array(Array<int>& array, int left, int right);
void quick_sort_c_array(int* array, int left, int right);
void quick_sort_vector(std::vector<int>& vector, int left, int right);

// quick sort partition helper function
int partition_array(Array<int>& array, int left, int right);
int partition_c_array(int* array, int left, int right);
int partition_vector(std::vector<int>& vector, int left, int right);

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
  // heapify the array
  for (int i = length / 2 - 1; i >= 0; i--) {
    heapify_array(array, length, i);
  }
  // sort the array
  for (int i = length - 1; i >= 0; i--) {
    // swap the root with the last element
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    // make the array have the max heap property
    heapify_array(array, i, 0);
  }
}

void iterative_heap_sort_c_array(int* array, int length) {
  int temp;
  for (int i = length / 2 - 1; i >= 0; i--) {
    heapify_c_array(array, length, i);
  }
  for (int i = length - 1; i >= 0; i--) {
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    heapify_c_array(array, i, 0);
  }
}

void iterative_heap_sort_vector(std::vector<int>& vector) {
  int temp;
  int length = vector.size();
  for (int i = length / 2 - 1; i >= 0; i--) {
    heapify_vector(vector, length, i);
  }
  for (int i = length - 1; i >= 0; i--) {
    temp = vector[0];
    vector[0] = vector[i];
    vector[i] = temp;
    heapify_vector(vector, i, 0);
  }
}

// heap helper functions
void heapify_array(Array<int>& array, int length, int i) {
  int top = array[i];
  int larger = i;
  while (i < length / 2) {  // swap each element with its larger child
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // find the larger child
    if (right < length && array[right] > array[left]) {
      larger = right;
    } else {
      larger = left;
    }
    // swap the element with its larger child
    if (top >= array[i])
      break;
    array[i] = array[larger];
    i = larger;
  }
  // place the element in the correct position
  array[i] = top;
}

void heapify_c_array(int* array, int length, int i) {
  int top = array[i];
  int larger = i;
  while (i < length / 2) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (right < length && array[right] > array[left]) {
      larger = right;
    } else {
      larger = left;
    }
    if (top >= array[i])
      break;
    array[i] = array[larger];
    i = larger;
  }
  array[i] = top;
}

void heapify_vector(std::vector<int>& vector, int length, int i) {
  int top = vector[i];
  int larger = i;
  while (i < length / 2) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (right < length && vector[right] > vector[left]) {
      larger = right;
    } else {
      larger = left;
    }
    if (top >= vector[i])
      break;
    vector[i] = vector[larger];
    i = larger;
  }
  vector[i] = top;
}

// merge sorts
void merge_sort_array(Array<int>& array) {
  // call the recursive function on the entire array
  merge_sort_array(array, 0, array.getLength() - 1);
}

void merge_sort_c_array(int* array, int length) {
  merge_sort_c_array(array, 0, length - 1);
}

void merge_sort_vector(std::vector<int>& vector) {
  merge_sort_vector(vector, 0, vector.size() - 1);
}

// merge recursive calls
void merge_sort_array(Array<int>& array, int left, int right) {
  // if there are less than two elements, the array is sorted
  if (left < right) {
    // find the middle of the array
    int middle = (left + right) / 2;
    // sort the left and right halves of the array
    merge_sort_array(array, left, middle);
    merge_sort_array(array, middle + 1, right);
    // merge the two halves
    merge_array(array, left, middle, right);
  }
}

void merge_sort_c_array(int* array, int left, int right) {
  if (left < right) {
    int middle = (left + right) / 2;
    merge_sort_c_array(array, left, middle);
    merge_sort_c_array(array, middle + 1, right);
    merge_c_array(array, left, middle, right);
  }
}

void merge_sort_vector(std::vector<int>& vector, int left, int right) {
  if (left < right) {
    int middle = (left + right) / 2;
    merge_sort_vector(vector, left, middle);
    merge_sort_vector(vector, middle + 1, right);
    merge_vector(vector, left, middle, right);
  }
}

// merge helper functions
void merge_array(Array<int>& array, int left, int middle, int right) {
  // create a temporary array to hold the sorted elements
  Array<int> temp(right - left + 1);
  // set the indices for the left and right halves
  int left_index = left;
  int right_index = middle + 1;
  // set the index for the temporary array
  int temp_index = 0;
  // merge the two halves
  while (left_index <= middle && right_index <= right) {
    // copy the smaller element to the temporary array
    if (array[left_index] < array[right_index]) {
      temp[temp_index] = array[left_index];
      // increment the index of the left half
      left_index++;
    } else {
      temp[temp_index] = array[right_index];
      // increment the index of the right half
      right_index++;
    }
    // increment the index of the temporary array
    temp_index++;
  }
  // copy the remaining elements from the left half
  while (left_index <= middle) {
    temp[temp_index] = array[left_index];
    left_index++;
    temp_index++;
  }
  // copy the remaining elements from the right half
  while (right_index <= right) {
    temp[temp_index] = array[right_index];
    right_index++;
    temp_index++;
  }
  // copy the sorted elements from the temporary array to the original array
  for (int i = left; i <= right; i++) {
    array[i] = temp[i - left];
  }
}

void merge_c_array(int* array, int left, int middle, int right) {
  int* temp = new int[right - left + 1];
  int left_index = left;
  int right_index = middle + 1;
  int temp_index = 0;
  while (left_index <= middle && right_index <= right) {
    if (array[left_index] < array[right_index]) {
      temp[temp_index] = array[left_index];
      left_index++;
    } else {
      temp[temp_index] = array[right_index];
      right_index++;
    }
    temp_index++;
  }
  while (left_index <= middle) {
    temp[temp_index] = array[left_index];
    left_index++;
    temp_index++;
  }
  while (right_index <= right) {
    temp[temp_index] = array[right_index];
    right_index++;
    temp_index++;
  }
  for (int i = left; i <= right; i++) {
    array[i] = temp[i - left];
  }
  delete[] temp;
}

void merge_vector(std::vector<int>& vector, int left, int middle, int right) {
  std::vector<int> temp(right - left + 1);
  int left_index = left;
  int right_index = middle + 1;
  int temp_index = 0;
  while (left_index <= middle && right_index <= right) {
    if (vector[left_index] < vector[right_index]) {
      temp[temp_index] = vector[left_index];
      left_index++;
    } else {
      temp[temp_index] = vector[right_index];
      right_index++;
    }
    temp_index++;
  }
  while (left_index <= middle) {
    temp[temp_index] = vector[left_index];
    left_index++;
    temp_index++;
  }
  while (right_index <= right) {
    temp[temp_index] = vector[right_index];
    right_index++;
    temp_index++;
  }
  for (int i = left; i <= right; i++) {
    vector[i] = temp[i - left];
  }
}

// quick sort base calls
void quick_sort_array(Array<int>& array) {
  // call the recursive quick sort function
  quick_sort_array(array, 0, array.getLength() - 1);
}

void quick_sort_c_array(int* array, int length) {
  quick_sort_c_array(array, 0, length - 1);
}
void quick_sort_vector(std::vector<int>& vector) {
  quick_sort_vector(vector, 0, vector.size() - 1);
}

// quick sort recursive calls
void quick_sort_array(Array<int>& array, int left, int right) {
  // if there are less than two elements, the array is sorted
  if (left < right) {
    // partition the array
    int pivot = partition_array(array, left, right);
    // sort the left and right halves of the array
    quick_sort_array(array, left, pivot);
    quick_sort_array(array, pivot + 1, right);
  }
}

void quick_sort_c_array(int* array, int left, int right) {
  if (left < right) {
    int pivot = partition_c_array(array, left, right);
    quick_sort_c_array(array, left, pivot);
    quick_sort_c_array(array, pivot + 1, right);
  }
}

void quick_sort_vector(std::vector<int>& vector, int left, int right) {
  if (left < right) {
    int pivot = partition_vector(vector, left, right);
    quick_sort_vector(vector, left, pivot);
    quick_sort_vector(vector, pivot + 1, right);
  }
}

// quick sort partition helper function
int partition_array(Array<int>& array, int left, int right) {
  // set the pivot to the middle element
  int pivot = array[(left + right) / 2];

  // left and right indices
  int left_index = left - 1;
  int right_index = right + 1;

  // partition the array
  while (true)
  {
    do {
      // increment the left index until an element greater than the pivot is
      // found
      left_index++;
    } while (array[left_index] < pivot);

    do {
      // decrement the right index until an element less than the pivot is
      // found
      right_index--;
    } while (array[right_index] > pivot);

    // if the left index is greater than or equal to the right index, the
    // partition is complete return the right index
    if (left_index >= right_index) {
      return right_index;
    }

    // swap the elements at the left and right indices
    int temp = array[left_index];
    array[left_index] = array[right_index];
    array[right_index] = temp;
  }
}

int partition_c_array(int* array, int left, int right) {
  int pivot = array[(left + right) / 2];
  int left_index = left - 1;
  int right_index = right + 1;
  while (true)
  {
    do {
      left_index++;
    } while (array[left_index] < pivot);
    do {
      right_index--;
    } while (array[right_index] > pivot);
    if (left_index >= right_index) {
      return right_index;
    }
    int temp = array[left_index];
    array[left_index] = array[right_index];
    array[right_index] = temp;
  }
}

int partition_vector(std::vector<int>& vector, int left, int right) {
  int pivot = vector[(left + right) / 2];
  int left_index = left - 1;
  int right_index = right + 1;
  while (true)
  {
    do {
      left_index++;
    } while (vector[left_index] < pivot);
    do {
      right_index--;
    } while (vector[right_index] > pivot);
    if (left_index >= right_index) {
      return right_index;
    }
    int temp = vector[left_index];
    vector[left_index] = vector[right_index];
    vector[right_index] = temp;
  }
}

#endif  // SORTS_H
