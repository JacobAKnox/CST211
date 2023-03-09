// CST211 Final Challenge
// Jacob Knox
// due 3/15/2023

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

void sort(vector<int>& v);
void print(vector<int>& v, int percent);

const int LENGTH = 10000;

int main() {
  // seed the random number generator
  std::random_device rd;
  // using a constant seed for repeatability
  std::mt19937 gen(1);
  std::uniform_int_distribution<> small_dis(1, LENGTH / 10);
  std::uniform_int_distribution<> large_dis(1, LENGTH * 10);

  // create a vector of 10000 random numbers
  vector<int> small_range;
  vector<int> large_range;
  for (int i = 0; i < LENGTH; i++) {
    small_range.push_back(small_dis(gen));
    large_range.push_back(large_dis(gen));
  }

  // print the small range
  cout << "Every 1000th element in small range:" << endl;
  print(small_range, 10);

  // time the small range sort
  auto start = std::chrono::high_resolution_clock::now();
  sort(small_range);
  auto end = std::chrono::high_resolution_clock::now();

  // print the time it took to sort the small range
  std::chrono::duration<double> elapsed_seconds = end - start;
  cout << "Small range sort took " << elapsed_seconds.count() << " seconds" << endl;

  // print every 1000th number in the small range
  cout << "Every 1000th number:" << endl;
  print(small_range, 10);

  cout << endl;

  // print the large range
  cout << "Every 1000th element in large range:" << endl;
  print(large_range, 10);

  // time the large range sort
  start = std::chrono::high_resolution_clock::now();
  sort(large_range);
  end = std::chrono::high_resolution_clock::now();

  // print the time it took to sort the large range
  elapsed_seconds = end - start;
  cout << "Large range sort took " << elapsed_seconds.count() << " seconds" << endl;

  // print every 1000th number in the large range
  cout << "Every 1000th number:" << endl;
  print(large_range, 10);

  return 0;
}

void sort(vector<int>& v) {
  // find the min and max values in the vector
  int min = v[0];
  int max = v[0];
  for (int i = 1; i < v.size(); i++) {
    if (v[i] < min) {
      min = v[i];
    } else if (v[i] > max) {
      max = v[i];
    }
  }

  // create a vector of counters
  vector<int> counters(max - min + 1);

  // count the number of times each value appears
  for (int i = 0; i < v.size(); i++) {
    counters[v[i] - min]++;
  }

  // add elements to the vector in sorted order
  int index = 0;
  // loop over each counter index
  for (int i = 0; i < counters.size(); i++) {
    // add an element for the value of the counter index
    for (int j = 0; j < counters[i]; j++) {
      v[index++] = i + min;
    }
  }
}

void print(vector<int>& v, int percent) {
  // print every percentth number in the vector
  int jump = v.size() / percent;

  for (int i = 0; i < v.size(); i += jump) {
    cout << v[i] << " ";
  }
  cout << endl;
}
