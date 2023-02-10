#include <iostream>

using std::cin;
using std::cout;
using std::endl;

float displayNum(int n1, float n2) {
  cout << "The int number is " << n1 << endl;
  cout << "The double number is " << n2 << endl;

  return n1 + n2;
}

int main() {
  int num1 = 5;
  float num3, num2 = 5.5;

  float (*func)(int, float);
  func = displayNum;

  // calling the function
  num3 = func(num1, num2);
  cout << "The sum is " << num3 << endl;
  return 0;
}
