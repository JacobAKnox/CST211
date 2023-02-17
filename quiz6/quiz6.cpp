#include <array>
#include <list>
#include <iostream>

using std::array;
using std::list;
using std::cout;
using std::endl;

int main() {
    list<array<int, 2>> lofv{};

    for (int i = 0; i < 5; ++i) {
        array<int, 2> s{};
        for (int j = 0; j < 2; ++j) {
            s[j] = i + j;
        }
        lofv.push_back(s);
    }
    
    cout << "List:" << endl;
    for (auto &v : lofv) {
        cout << "Array: ";
        for (auto &i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
}
